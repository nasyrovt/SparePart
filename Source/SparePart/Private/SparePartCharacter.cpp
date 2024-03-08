// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparePart/Public/SparePartCharacter.h"

#include "KismetTraceUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Equipment/EquipmentComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

ASparePartCharacter::ASparePartCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComponent"));
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASparePartCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

AActor* ASparePartCharacter::GetAutoAimTarget(float range, float angle)
{
	AActor* result = nullptr;

	TArray<FOverlapResult> overlapResults = TArray<FOverlapResult>();
	// get box of the same length and width as cone, uses half-extent
	auto collisionShape = FCollisionShape().MakeBox(FVector(range / 2.0f,
															  ((1 / tan(90 - (angle / 2))) * range / 2.0f) / 2.0f,
															  100.f));
	auto collisionQueryParams = FCollisionQueryParams("autoAim", false, this);
	// Do box overlap
	GetWorld()->OverlapMultiByChannel(overlapResults, this->GetActorLocation(),
									  this->GetActorRotation().Quaternion(),
									  ECC_Pawn, collisionShape, collisionQueryParams);

	//debug function for drawing the box, note that it doesn't quite spawn in the right spot
	if(bDebugAutoAim)
	{
		DrawDebugBox(GetWorld(), (this->GetActorLocation() + this->GetActorForwardVector() * range / 2.0f), FVector(range / 2.0f,
																  ((1 / tan(90 - (angle / 2))) * range / 2.0f) / 2.0f,
																  100.f), FColor::Red, false, 2.0f);
	}
	if (!overlapResults.IsEmpty())
	{
		FVector forwardVector = this->GetActorForwardVector();
		FVector location = this->GetActorLocation();
		TArray<AActor*> actorsInCone = TArray<AActor*>();
		
		for (FOverlapResult overlap : overlapResults)
		{
			// Check if actor is in auto aim cone
			AActor* hitActor = overlap.GetActor();
			FVector HitVector = location - hitActor->GetActorLocation();
			float hitAngle = 1 / cos(forwardVector.Dot(HitVector) / (forwardVector.Length() * HitVector.Length()));
			
			if (hitAngle <= angle / 2.0f && hitActor->ActorHasTag("aimable"))
			{
				actorsInCone.Add(overlap.GetActor());
			}
		}

		for (auto actor : actorsInCone)
		{
			if (!result)
			{
				result = actor;
			}
			else if((location - actor->GetActorLocation()).Length() < (location - result->GetActorLocation()).Length())
			{
				result = actor;
			}
		}
	}
	return result;
}
