// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparePart/Public/SparePartCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
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
	
	AutoAimCollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	AutoAimCollisionMesh->SetupAttachment(GetRootComponent());
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASparePartCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

AActor* ASparePartCharacter::GetAutoAimTarget()
{
	AActor* result = nullptr;

	TArray<AActor*> overlappedActors;
	AutoAimCollisionMesh->GetOverlappingActors(overlappedActors);

	if(!overlappedActors.IsEmpty())
	{
		for(AActor* overlappedActor : overlappedActors)
		{
			if (!result && overlappedActor->ActorHasTag("aimable"))
			{
				result = overlappedActor;
			}
			// get closest actor
			else if(overlappedActor->ActorHasTag("aimable") && (GetActorLocation() - overlappedActor->GetActorLocation()).Length() < (GetActorLocation() - result->GetActorLocation()).Length())
			{
				result = overlappedActor;
			}
		}
	}
	return result;
}
