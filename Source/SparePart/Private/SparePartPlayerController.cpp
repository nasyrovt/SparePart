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

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASparePartPlayerController::ASparePartPlayerController()
{
	
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

	
	
}

