// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/DamageableComponent.h"

#include "Health/HealthBarWidget.h"


// Sets default values for this component's properties
UDamageableComponent::UDamageableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	maxHealth = 100;
	currentHealth = maxHealth;
	
	static ConstructorHelpers::FClassFinder<UHealthBarWidget> HealthBarWidgetClass(TEXT("/Game/SparePart/Public/Health/HealthBarWidget.h"));
	if(HealthBarWidgetClass.Succeeded())
	{
		Super::WidgetClass = HealthBarWidgetClass.Class;
	}
}


// Called when the game starts
void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageableComponent::PassHealthBarReference(UHealthBarWidget* HealthBarWidget)
{
	Super::SetWidget(HealthBarWidget);
	Super::SetHiddenInGame(true);
}
