// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageableComponent.generated.h"


class UHealthBarWidget;

UCLASS(ClassGroup=(Custom), Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class SPAREPART_API UDamageableComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void ShouldDie();
	UFUNCTION()
	void Die(FName name);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="Health")
	float maxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn), Category="Health")
	float currentHealth;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;
	UFUNCTION(BlueprintCallable)
	void PassHealthBarReference(UHealthBarWidget* HealthBarWidget);
	UFUNCTION(BlueprintCallable)
	float TakeDamage(float damage);
};
