// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BodyPart.h"

#include "Kismet/GameplayStatics.h"

UBodyPart::UBodyPart()
{
	World = GetWorld();
}

void UBodyPart::FireAction()
{
	Execute_FireActionBP(this);
}

void UBodyPart::SetOwner(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}


