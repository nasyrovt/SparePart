// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SparePartCharacter.h"
#include "UObject/Interface.h"
#include "BodyPartActions.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBodyPartActions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPAREPART_API IBodyPartActions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void FireAction()
	{
		FireActionBP();
	}
	
	UFUNCTION(BlueprintImplementableEvent)
	void FireActionBP();
};
