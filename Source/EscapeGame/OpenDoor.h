// Malik Games proprety

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void OpenCloseDoor(float DeltaTime, float TargetYaw, float Speed);

	UFUNCTION()
	float GetTotalMassOnTrigger();

private:
	FRotator InitialDoorRotation,CurrentDoorRotation;

	//How much the door will open(in angles). By default, the door will open 90º degrees
	UPROPERTY(EditAnywhere)
	float DoorOpenAngle = 90.f;

	//Reference to the trigger that opens the door. This reference is set on editor
	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenDoorTrigger = nullptr;

	//The time the door was last opened and close delay
	float TimeDoorLastOpened = 0.f;

	//How long the door will remain open for
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.4f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 70.f;

	//Audio Component to open door
	UPROPERTY()
	UAudioComponent* OpenDoorAudioComponent = nullptr;
	UPROPERTY()
	bool bDoorIsOpen = false;
	UPROPERTY()
	bool bDoorIsClosed = true;

	UFUNCTION()
	void SetUpAudioComponent();
	UFUNCTION()
	void PlayDoorSound();
};
