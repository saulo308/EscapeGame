// Malik Games proprety

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Setting audio component
	SetUpAudioComponent();

	//Testing if OpenDoorTrigger is valid
	if(!OpenDoorTrigger)
		UE_LOG(LogTemp,Error,TEXT("The object %s has a TriggerComponent set to null"),*GetOwner()->GetName());

	//Setting Initial and current Z axis(Yaw) rotation of the door
	InitialDoorRotation = CurrentDoorRotation = GetOwner()->GetActorRotation();
	//Door Open angle is the initial yaw rotation + the informed angle on the editor(by default is 90º)
	DoorOpenAngle += InitialDoorRotation.Yaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Setting how long the game has been played
	float TimePlayed = GetWorld()->GetTimeSeconds();

	//Testing if player is colliding with trigger volume
	if(OpenDoorTrigger && GetTotalMassOnTrigger() >= MassToOpenDoor){
		OpenCloseDoor(DeltaTime,DoorOpenAngle,DoorOpenSpeed);
		TimeDoorLastOpened = TimePlayed;

		if(!bDoorIsOpen && OpenDoorAudioComponent)
			PlayDoorSound();
	}else if(OpenDoorTrigger && (TimePlayed - TimeDoorLastOpened >= DoorCloseDelay)){ //Calculating the time player has moved out from trigger
		OpenCloseDoor(DeltaTime,InitialDoorRotation.Yaw,DoorCloseSpeed);

		if(!bDoorIsClosed && OpenDoorAudioComponent)
			PlayDoorSound();
	}
}

void UOpenDoor::OpenCloseDoor(float DeltaTime, float TargetYaw, float Speed){
	//Changing z axis(Yaw) rotation of the door to be the value of the lerp and setting new rotation
	CurrentDoorRotation.Yaw = FMath::Lerp(CurrentDoorRotation.Yaw, TargetYaw, DeltaTime * Speed);
	GetOwner()->SetActorRotation(CurrentDoorRotation);
}

float UOpenDoor::GetTotalMassOnTrigger(){
	//Total mass local variable
	float TotalMass = 0.f;	

	//Checking if trigger is set
	if(!OpenDoorTrigger) return TotalMass;

	//TArray of actor inside the trigger volume
	TArray<AActor*> ActorsOnTrigger;

	//Getting Overlapping actors on trigger and sum mass up
	OpenDoorTrigger->GetOverlappingActors(ActorsOnTrigger);
	for(auto Actor : ActorsOnTrigger){
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::SetUpAudioComponent(){
	OpenDoorAudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!OpenDoorAudioComponent)
		UE_LOG(LogTemp,Error,TEXT("Could not find audio component on %s"), *GetOwner()->GetName());
}

void UOpenDoor::PlayDoorSound(){
	OpenDoorAudioComponent->Play();
	bDoorIsOpen = !bDoorIsOpen;
	bDoorIsClosed = !bDoorIsClosed;
}

