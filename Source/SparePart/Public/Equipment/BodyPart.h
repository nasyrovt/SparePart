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

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBodyPartType> PartType;
	
	UPROPERTY(EditAnywhere)
	FText PartName;

	UPROPERTY(EditAnywhere)
	FText PartDescription;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UMeshComponent> PartMesh;
};



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPAREPART_API UBodyPart : public UObject, public IBodyPartActions
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadOnly, Transient, meta=(AllowPrivateAccess))
	ACharacter* OwnerCharacter;

public:
	UBodyPart();

	UPROPERTY(EditAnywhere, Category="Part Info")
	FBodyPartInfo PartInfo;

	UFUNCTION(BlueprintCallable)
	virtual void FireAction() override;

	UFUNCTION()
	void SetOwner(ACharacter* InOwner);
};
