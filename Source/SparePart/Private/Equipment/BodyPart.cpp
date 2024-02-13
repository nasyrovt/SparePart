// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BodyPart.h"

#include "Kismet/GameplayStatics.h"

UBodyPart::UBodyPart()
{
	
}

void UBodyPart::ActionInputPressed()
{
	Execute_ActionInputPressedBP(this);
}

void UBodyPart::ActionInputReleased()
{
	Execute_ActionInputReleasedBP(this);
}

void UBodyPart::SetOwner(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}


