// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/DamageableComponent.h"

#include "PlayMontageCallbackProxy.h"
#include "GameFramework/Character.h"
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

void UDamageableComponent::Die(FName name)
{
	if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		Owner->SetActorTickEnabled(false);
	}
}


void UDamageableComponent::ShouldDie()
{
	if (currentHealth <= 0)
	{
		if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
		{
			USkeletalMeshComponent* Skeleton = Owner->GetMesh();

			static ConstructorHelpers::FObjectFinder<UAnimMontage> montageRef(TEXT("/Game/Content/TopDown/Enemy/GunAnims/Dying_Montage.Dying_Montage"));
			
			if (UAnimInstance* AnimInstance = Skeleton->GetAnimInstance())
			{
				UPlayMontageCallbackProxy* PlayMontageCallbackProxy =
					UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(Skeleton, montageRef.Object);

				PlayMontageCallbackProxy->OnCompleted.AddDynamic(this, &UDamageableComponent::Die);
			}
		}
	}
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

float UDamageableComponent::DealDamage(float damage)
{
	// Can be extended to calculate damage w/ more complexity
	currentHealth -= damage;
	ShouldDie();
	return damage;
}
