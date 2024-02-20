// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthBarWidget.h"

#include "Blueprint/WidgetTree.h"

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UHealthBarWidget::Initialize()
{
	return Super::Initialize();
	// static ConstructorHelpers::FClassFinder<UHealthBarWidget> ProgressBarWidgetClass(TEXT("/Engine/Source/Runtime/UMG/Public/Components/ProgressBar.h"));
	// if(WidgetTree)
	// {
	// 	HealthBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass(), TEXT("HealthBar"));
	// 	WidgetTree->RootWidget = HealthBar;
	// } else succeeded = false;
	// return succeeded;
}
