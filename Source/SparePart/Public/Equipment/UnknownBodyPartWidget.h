// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "EquipmentActor.h"
#include "Blueprint/UserWidget.h"
#include "Interactions/InteractionComponent.h"
#include "UnknownBodyPartWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPAREPART_API UUnknownBodyPartWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FOnInputAction OnInputActionCallback;

	UPROPERTY()
	UInteractionComponent* RelatedInteractionToActivate = nullptr;

	UUnknownBodyPartWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetDependentPopupComponent(UInteractionComponent* InteractionComponent);

	FBodyPartInfo BodyPartInfo;

	UFUNCTION(BlueprintCallable)
	void HandleContinueButton();
	
	virtual void InitializeInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void InitWithPartInfoBP(FBodyPartInfo InPartInfo);
};
