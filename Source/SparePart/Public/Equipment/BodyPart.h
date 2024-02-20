// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPartActions.h"
#include "UObject/Object.h"
#include "BodyPart.generated.h"


UENUM()
enum EBodyPartType : uint8
{
	RightArm, LeftArm, Body, Head, Legs
};


USTRUCT(Blueprintable, BlueprintType)
struct FBodyPartInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EBodyPartType> PartType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText PartName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText PartDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText PartModificationText;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TSoftObjectPtr<Texture> PartImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* PartMesh;
};



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPAREPART_API UBodyPart : public UActorComponent, public IBodyPartActions
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadOnly, Transient, meta=(AllowPrivateAccess))
	ACharacter* OwnerCharacter;

public:
	UBodyPart();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Part Info")
	FBodyPartInfo PartInfo;

	UFUNCTION(BlueprintCallable)
	virtual void ActionInputPressed() override;

	UFUNCTION(BlueprintCallable)
	virtual void ActionInputReleased() override;

	void SetOwner(ACharacter* InOwner);
	
	void OnAddedToPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnAddedToPlayerBP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDroppedBP();

	void OnDropped();
};
