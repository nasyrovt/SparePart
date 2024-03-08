// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentActor.h"

#include "Equipment/EquipmentComponent.h"
#include "Interactions/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEquipmentActor::AEquipmentActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
}

void AEquipmentActor::HandleInteractionPressed()
{
	if(const ASparePartCharacter* PlayerCharacter = Cast<ASparePartCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if(UEquipmentComponent* EquipmentComponent = PlayerCharacter->GetEquipmentComponent())
		{
			if(BodyPart && BodyPartClass)
			{
				EquipmentComponent->SetBodyPartBySlot(BodyPart->PartInfo, BodyPartClass);
			}
		}
	}
	
	HandleInteractionPressedBP();
	Destroy();
}

// Called when the game starts or when spawned
void AEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
	InteractionComponent = Cast<UInteractionComponent>(GetComponentByClass(UInteractionComponent::StaticClass()));
	if(BodyPartClass)
	{
		BodyPart = Cast<UBodyPart>(NewObject<UBodyPart>(this, BodyPartClass));
		if(InteractionComponent)
		{
			InteractionComponent->InitWithPartInfo(BodyPart->PartInfo);
		}
		UpdateVisuals();
	}
	
	if(InteractionComponent)
	{
		InteractionComponent->OnInteractionExecuted.AddDynamic(this, &AEquipmentActor::HandleInteractionPressed);
	}
}

// Called every frame
void AEquipmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEquipmentActor::UpdateVisuals()
{
	if(BodyPart)
	{
		if(BodyPart->PartInfo.PartMesh)
		{
			MeshComponent->SetStaticMesh(BodyPart->PartInfo.PartMesh);
		}

		if(InteractionComponent)
		{
			InteractionComponent->InitWithPartInfo(BodyPart->PartInfo);
			InteractionComponent->RequestRedraw();
		}
	}

	
}

void AEquipmentActor::SetBodyPart(UBodyPart* InBodyPart)
{
	BodyPart = InBodyPart;
}

void AEquipmentActor::SetBodyPartClass(TSubclassOf<UBodyPart> InBodyPartClass)
{
	BodyPartClass = InBodyPartClass;
}


