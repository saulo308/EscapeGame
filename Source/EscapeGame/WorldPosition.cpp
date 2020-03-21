// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//Getting object name
	FString ObjectName;
	ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("This component is attached to: %s"), *ObjectName);

	//Getting world position(1)
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp,Warning,TEXT("The object position is: %s"), *ObjectPosition);
	FString ObjectPosition2 = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp,Warning,TEXT("The object transform location is:%s"), *ObjectPosition2);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

