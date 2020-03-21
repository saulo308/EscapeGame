// Malik Games proprety

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Line trace function to get the object when player press grab input
	UFUNCTION()
	FHitResult LineTraceObject() const;
	
	//Grab and release functions
	UFUNCTION()
	void Grab();

	UFUNCTION()
	void Release();

	UFUNCTION()
	FVector GetGrabEndPosition() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float GrabMaxDistance = 100.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	//Set physics and input handlers functions
	UFUNCTION()
	void FindPhysicsHandler();

	UFUNCTION()
	void FindInputHandler();
};
