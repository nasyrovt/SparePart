// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/InteractionComponent.h"

#include "GameFramework/Character.h"
#include "Interactions/InteractionSubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Space = EWidgetSpace::Screen;
	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if(UInteractionSubsystem* InteractionSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<
		UInteractionSubsystem>())
	{
		InteractionSubsystem->RegisterInteraction(this);
	}
	
}

void UInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(UInteractionSubsystem* InteractionSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<
		UInteractionSubsystem>())
	{
		InteractionSubsystem->UnregisterInteraction(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

void UInteractionComponent::ResetUsability()
{
	
}


void UInteractionComponent::ReInit()
{
	ReuseTimer.Invalidate();
	ReInitBP();
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsClosestToPlayer())
	{
		if(CanBeVisible())
		{
			UpdateInteractionIndicatorState(GetDistanceToPlayer());
			UpdateInteractionButtonVisibility(CanBeExecuted());
		}
	}
	else
	{
		ReInit();
	}
}

bool UInteractionComponent::IsClosestToPlayer()
{
	if(const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if(const UInteractionSubsystem* InteractionSubsystem = GameInstance->GetSubsystem<UInteractionSubsystem>())
		{
			return InteractionSubsystem->IsComponentClosestToPlayer(this);
		}
	}
	return false;
}

float UInteractionComponent::GetDistanceToPlayer()
{
	if(const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		return FVector::Distance(PlayerLocation, GetComponentLocation());
	}
	return -1.f;
}

bool UInteractionComponent::CanBeExecuted()
{
	const float DistanceToPlayer = GetDistanceToPlayer();
	if(DistanceToPlayer == -1.f || DistanceToPlayer > AvailabilityDistance)
	{
		return false;
	}
	return true;
}

bool UInteractionComponent::CanBeVisible()
{
	const float DistanceToPlayer = GetDistanceToPlayer();
	if(DistanceToPlayer == -1.f || DistanceToPlayer > VisibilityDistance)
	{
		return false;
	}
	return true;
}

void UInteractionComponent::Execute()
{
	ExecuteBP();

	if(bIsReusable)
	{
		//FTimerManager::SetTimer(ReuseTimer, &UInteractionComponent::ResetUsability, ReuseResetTime, false);
	}

}

