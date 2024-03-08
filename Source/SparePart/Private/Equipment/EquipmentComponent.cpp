// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentComponent.h"

#include "Equipment/EquipmentActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ScaleOverride = FVector(1.f);
	SpawnOffset = FVector(50.f);
	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	for(TTuple<TEnumAsByte<EBodyPartType>, TSubclassOf<UBodyPart>> BodyPartKVP : BodyPartsClassMap)
	{
		if(BodyPartKVP.Value)
		{
			if(UBodyPart* BodyPartObj = NewObject<UBodyPart>(this, BodyPartKVP.Value))
			{
				if(ACharacter* Owner = Cast<ACharacter>(GetOwner()))
				{
					BodyPartObj->SetOwner(Owner);
					BodyPartsMap.Add(BodyPartKVP.Key, BodyPartObj);
				}
			}
		}
	}
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::DropBodyPartBySlot(EBodyPartType InBodyPart)
{
	if(const TSubclassOf<UBodyPart> BodyPart = BodyPartsClassMap[InBodyPart])
	{
		FTransform Transform = GetOwner()->GetTransform();
		FVector OffsetLocation = Transform.GetLocation() + SpawnOffset;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		
		FHitResult HitResult;
		TArray<AActor*> ActorsToIgnore;
		if(UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			OffsetLocation,
			OffsetLocation + 2000*FVector(0.f, 0.f,-1.f),
			ObjectTypes, false,
			ActorsToIgnore, EDrawDebugTrace::None,
			HitResult, true))
		{
			Transform.SetLocation(HitResult.Location);
		}
		Transform.SetRotation(Transform.GetRotation());
		Transform.SetScale3D(ScaleOverride);

		AEquipmentActor* ItemToDrop = Cast<AEquipmentActor>(GetWorld()->SpawnActor(EquipmentActorClassOverride, &Transform));
		ItemToDrop->SetBodyPartClass(BodyPart);
		ItemToDrop->SetBodyPart(BodyPartsMap[InBodyPart]);
		ItemToDrop->UpdateVisuals();
		BodyPartsMap[InBodyPart]->OnDropped();
		BodyPartsMap[InBodyPart]->DestroyComponent();
	}
}

void UEquipmentComponent::SetBodyPartBySlot(const EBodyPartType BodyPartType, const TSubclassOf<UBodyPart> BodyPartClass)
{
	if(BodyPartClass)
	{
		if(BodyPartsClassMap.Contains(BodyPartType))
		{
			DropBodyPartBySlot(BodyPartType);
		}
		BodyPartsClassMap.Add(BodyPartType, BodyPartClass);
		UBodyPart* NewBodyPart = NewObject<UBodyPart>(this, BodyPartClass);
		if(ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
		{
			NewBodyPart->SetOwner(OwnerCharacter);
		}
		
		BodyPartsMap.Add(BodyPartType, NewBodyPart);

		NewBodyPart->OnAddedToPlayer();
		
		if(OnNewPartAdded.IsBound())
		{
			OnNewPartAdded.Broadcast(NewBodyPart);
		}
	}
}

UBodyPart* UEquipmentComponent::GetBodyPartBySlot(const EBodyPartType BodyPartType, bool& bSuccess)
{
	if(BodyPartsMap.Contains(BodyPartType) && BodyPartsMap[BodyPartType])
	{
		bSuccess = true;
		return BodyPartsMap[BodyPartType];
	}
	bSuccess = false;
	return nullptr;
}

