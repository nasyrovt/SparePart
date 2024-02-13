// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparePart/Public/SparePartPlayerController.h"

#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Interactions/InteractionSubsystem.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASparePartPlayerController::ASparePartPlayerController()
{
	
}

void ASparePartPlayerController::HandleInteractionInput()
{
	if(const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if(UInteractionSubsystem* InteractionSubsystem = GameInstance->GetSubsystem<UInteractionSubsystem>())
		{
			InteractionSubsystem->HandleInteractionInputPressed();
		}
	}
}

void ASparePartPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
}

void ASparePartPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Interaction", IE_Pressed, this, &ASparePartPlayerController::HandleInteractionInput);
	
}

