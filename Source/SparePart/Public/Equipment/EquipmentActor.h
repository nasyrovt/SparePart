// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "GameFramework/Actor.h"
#include "EquipmentActor.generated.h"

UCLASS()
class SPAREPART_API AEquipmentActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquipmentActor();

protected:
	UFUNCTION()
	void HandleInteractionPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleInteractionPressedBP();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UInteractionComponent* InteractionComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PartInformation")
	TSubclassOf<UBodyPart> BodyPartClass;

	UPROPERTY(VisibleAnywhere)
	UBodyPart* BodyPart = nullptr;
	
};
