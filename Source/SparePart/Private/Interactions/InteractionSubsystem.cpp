// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Interactions\InteractionSubsystem.h"

#include "GameFramework/Character.h"
#include "Interactions/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"

UInteractionSubsystem::UInteractionSubsystem()
{
	
}

void UInteractionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UInteractionSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

TStatId UInteractionSubsystem::GetStatId() const
{
	return Super::GetStatID();
}

void UInteractionSubsystem::UpdateClosestToPlayerInteraction()
{
	if(const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float ClosestToPlayerDistance = FVector::Distance(PlayerLocation, InteractionsArray[0]->GetComponentLocation());
		for (UInteractionComponent* Interaction : InteractionsArray)
		{
			FVector CurrentComponentLocation = Interaction->GetComponentLocation();
			const float CurrentDistanceToPlayer = FVector::Distance(PlayerLocation, CurrentComponentLocation);
			if(ClosestToPlayerDistance >= CurrentDistanceToPlayer)
			{
				ClosestToPlayerDistance = CurrentDistanceToPlayer;
				ClosestToPlayerInteraction = Interaction;
			}
		}
	}
}

void UInteractionSubsystem::Tick(float DeltaTime)
{
	UpdateClosestToPlayerInteraction();
}

void UInteractionSubsystem::RegisterInteraction(UInteractionComponent* Interaction)
{
	InteractionsArray.Add(Interaction);
}

void UInteractionSubsystem::UnregisterInteraction(UInteractionComponent* Interaction)
{
	if(InteractionsArray.Contains(Interaction))
	{
		InteractionsArray.Remove(Interaction);
	}
}

bool UInteractionSubsystem::IsComponentClosestToPlayer(const UInteractionComponent* InteractionComponent) const
{
	return InteractionComponent == ClosestToPlayerInteraction;
}

void UInteractionSubsystem::HandleInteractionInputPressed()
{
	if(ClosestToPlayerInteraction)
	{
		ClosestToPlayerInteraction->Execute();
	}
}
