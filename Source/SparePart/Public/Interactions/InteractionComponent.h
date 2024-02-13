// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionExecuted);

UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class SPAREPART_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInteractionExecuted OnInteractionExecuted;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ResetUsability();

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInteractionIndicatorState(float GetDistanceToPlayer);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInteractionButtonVisibility(bool bCanBeExecuted);

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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	bool bIsReusable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(EditConditionHides=bIsReusable))
	float ReuseResetTime = 3.f;
	
	FTimerHandle ReuseTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float VisibilityDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float ExecutionDistance = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	bool bIsAvailable = true;
};
