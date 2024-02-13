// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "SparePartPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class SPAREPART_API ASparePartPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASparePartPlayerController();

protected:

	void HandleInteractionInput();
	
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();
};


