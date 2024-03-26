// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/UnknownBodyPartWidget.h"

#include "Kismet/GameplayStatics.h"

UUnknownBodyPartWidget::UUnknownBodyPartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetInputActionBlocking(true);
}

void UUnknownBodyPartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnInputActionCallback.BindDynamic(this, &UUnknownBodyPartWidget::HandleContinueButton);
	
	ListenForInputAction(FName("Interaction"), IE_Pressed, true, OnInputActionCallback);
}

void UUnknownBodyPartWidget::SetDependentPopupComponent(UInteractionComponent* InteractionComponent)
{
	RelatedInteractionToActivate = InteractionComponent;
}

void UUnknownBodyPartWidget::HandleContinueButton()
{
	if(RelatedInteractionToActivate)
	{
		RelatedInteractionToActivate->SetVisibility(true);
	}
	RemoveFromParent();
}

void UUnknownBodyPartWidget::InitializeInputComponent()
{
	Super::InitializeInputComponent();
}
