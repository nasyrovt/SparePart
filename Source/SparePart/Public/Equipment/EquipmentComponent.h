// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "UnknownBodyPartWidget.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPartAdded, UBodyPart*, AddedBodyPart);

UCLASS(Config=Game, defaultconfig)
class SPAREPART_API UEquipmentSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UEquipmentSettings();
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUnknownBodyPartWidget> UnknownWidgetClass;
};


class AEquipmentActor;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPAREPART_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UPROPERTY(BlueprintAssignable)
	FOnNewPartAdded OnNewPartAdded;

	UPROPERTY(Transient)
	UUnknownBodyPartWidget* NewPartWidget = nullptr;

	UPROPERTY(Transient)
	AEquipmentActor* RecentlyDroppedItem = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Equipment")
	TMap<TEnumAsByte<EBodyPartType>, UBodyPart*> BodyPartsMap;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TMap<TEnumAsByte<EBodyPartType>, TSubclassOf<UBodyPart>> BodyPartsClassMap;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TSet<TSubclassOf<UBodyPart>> KnownParts;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	FVector SpawnOffset;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	FVector ScaleOverride;

	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TSubclassOf<AEquipmentActor> EquipmentActorClassOverride;

	AEquipmentActor* DropBodyPartBySlot(EBodyPartType BodyPart);
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void SetBodyPartBySlot(FBodyPartInfo BodyPart, TSubclassOf<UBodyPart> BodyPartClass);

	UFUNCTION(BlueprintCallable, Category="Equipment")
	UBodyPart* GetBodyPartBySlot(EBodyPartType BodyPartType, bool &bSuccess);
};
