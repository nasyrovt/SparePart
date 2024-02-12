// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentComponent.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UEquipmentComponent::SetBodyPartBySlot(const EBodyPartType BodyPartType, const TSubclassOf<UBodyPart> BodyPartClass)
{
	if(BodyPartClass)
	{
		BodyPartsClassMap.Add(BodyPartType, BodyPartClass);
		UBodyPart* NewBodyPart = NewObject<UBodyPart>(this, BodyPartClass);
		if(ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
		{
			NewBodyPart->SetOwner(OwnerCharacter);
		}
		BodyPartsMap.Add(BodyPartType, NewBodyPart);
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

