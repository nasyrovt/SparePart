// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPAREPART_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);
	virtual bool Initialize() override;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional), Category="Widget")
	UProgressBar* HealthBar;
};
