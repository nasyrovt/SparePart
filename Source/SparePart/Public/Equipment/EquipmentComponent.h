// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


class AEquipmentActor;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPAREPART_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, Category="Equipment")
	TMap<TEnumAsByte<EBodyPartType>, UBodyPart*> BodyPartsMap;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TMap<TEnumAsByte<EBodyPartType>, TSubclassOf<UBodyPart>> BodyPartsClassMap;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	FVector SpawnOffset;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	FVector ScaleOverride;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TSubclassOf<AEquipmentActor> EquipmentActorClassOverride;

	void DropBodyPartBySlot(EBodyPartType BodyPart);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void SetBodyPartBySlot(EBodyPartType BodyPartType, TSubclassOf<UBodyPart> BodyPartClass);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	UBodyPart* GetBodyPartBySlot(EBodyPartType BodyPartType, bool &bSuccess);
};
