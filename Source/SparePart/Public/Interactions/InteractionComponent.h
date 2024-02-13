﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionPopupComponent.h"
#include "Components/WidgetComponent.h"
#include "Equipment/BodyPart.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionExecuted);

UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class SPAREPART_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();
	void RegisterToSubsystem();

	UPROPERTY(BlueprintAssignable)
	FOnInteractionExecuted OnInteractionExecuted;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ResetUsability();

	UPROPERTY(Transient)
	UInteractionPopupComponent* PopupWC = nullptr;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInteractionIndicatorState(float GetDistanceToPlayer);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInteractionButtonVisibility(bool bCanBeExecuted);

	virtual void OnRegister() override;
	
	void ReInit();
	UFUNCTION(BlueprintImplementableEvent)
	void ReInitBP();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsClosestToPlayer();

	UFUNCTION(BlueprintCallable)
	float GetDistanceToPlayer();
	
	UFUNCTION(BlueprintPure)
	virtual bool CanBeExecuted();
	
	UFUNCTION(BlueprintPure)
	virtual bool CanBeVisible();

	virtual void Execute();

	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteBP();

	UFUNCTION(BlueprintCallable)
	void InitWithPartInfo(const FBodyPartInfo& PartInfo);

	UFUNCTION(BlueprintImplementableEvent)
	void InitWithPartInfoBP(const FBodyPartInfo& PartInfo);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction|Settings")
	bool bIsReusable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(EditCondition=bIsReusable))
	float ReuseResetTime = 3.f;
	
	FTimerHandle ReuseTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction|Widget")
	FText InteractionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction|Settings")
	float VisibilityDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction|Settings")
	float ExecutionDistance = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction|Debug")
	bool bIsAvailable = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction|Popup")
	bool bHasPopup;
};
