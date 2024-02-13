// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InteractionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SPAREPART_API UInteractionSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UInteractionSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual TStatId GetStatId() const override;
	void UpdateClosestToPlayerInteraction();

	virtual void Tick(float DeltaTime) override;
	
	void RegisterInteraction(class UInteractionComponent* Interaction);
	void UnregisterInteraction(class UInteractionComponent* Interaction);
	bool IsComponentClosestToPlayer(const UInteractionComponent* InteractionComponent) const;
	void HandleInteractionInputPressed();

private:
	UPROPERTY(Transient)
	TArray<UInteractionComponent*> InteractionsArray;
	
	UPROPERTY(Transient)
	UInteractionComponent* ClosestToPlayerInteraction = nullptr;
};
