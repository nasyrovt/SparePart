// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BodyPart.h"

#include "Kismet/GameplayStatics.h"

UBodyPart::UBodyPart()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBodyPart::ActionInputPressed()
{
	Execute_ActionInputPressedBP(this);
}

void UBodyPart::ActionInputReleased()
{
	Execute_ActionInputReleasedBP(this);
}

void UBodyPart::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBodyPart::SetOwner(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}

void UBodyPart::OnAddedToPlayer()
{
	OnAddedToPlayerBP();
}

void UBodyPart::OnDropped()
{
	OnDroppedBP();
}


