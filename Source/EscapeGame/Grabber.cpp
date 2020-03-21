// Malik Games proprety

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUTPARAM

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Setting PhysicsHandler and InputHandler
	FindPhysicsHandler();
	FindInputHandler();	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If there's a grabbed object, update it's location to the grab position(End grab position)
	if(PhysicsHandle && PhysicsHandle->GrabbedComponent)
		PhysicsHandle->SetTargetLocation(GetGrabEndPosition());
}

//This function handles the player's object grab
void UGrabber::Grab()
{
	//Raycasting to see if an object we can grab is in front of player
	FHitResult ActorHit = LineTraceObject();

	//If the raycast succeed(Hit an object that we can grab)
	if(PhysicsHandle && ActorHit.GetActor()){

		//Setting component to grab
		UPrimitiveComponent* ObjectToGrab = ActorHit.GetComponent();

		//Getting Location to grab object
		FVector LocationToGrab = GetGrabEndPosition();

		//Grabbing
		PhysicsHandle->GrabComponentAtLocation(ObjectToGrab,NAME_None,LocationToGrab);
	}
}

//This function handles the player's object release
void UGrabber::Release()
{
	//If player pressed to release component and there's a component attached, release
	if(PhysicsHandle && PhysicsHandle->GrabbedComponent)
		PhysicsHandle->ReleaseComponent();
}

//Getting PhysicsHandler
void UGrabber::FindPhysicsHandler()
{
	//Getting PhysicsHandle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
		UE_LOG(LogTemp,Error,TEXT("No Physics Handle Component found on %s!"), *GetOwner()->GetName());
}

//Getting InputHandler and binding actions
void UGrabber::FindInputHandler()
{
	//Getting Input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(!InputComponent){
		UE_LOG(LogTemp,Error,TEXT("No Input Component found on %s!!"),*GetOwner()->GetName());
	}else{
		//Binding Grab event to action(Mouse rigth click)
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
	}
}

//This function raycast from player to objects on front of him and only succeds when object has type of PhysicsBody
FHitResult UGrabber::LineTraceObject() const
{
	//Setting end position of raycast
	FVector LineTraceEnd = GetGrabEndPosition();

	//Setting HitResult variable and Query Parameters
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
	
	//Making RayCast
	GetWorld()->LineTraceSingleByObjectType(
		OUTPARAM Hit,
		GetOwner()->GetActorLocation(),
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//If hit was success
	if(Hit.GetActor()){
		UE_LOG(LogTemp, Warning, TEXT("The object hit name is:%s"), *Hit.GetActor()->GetName());
	}

	return Hit;
}

FVector UGrabber::GetGrabEndPosition() const
{
	//Getting Player's viewpoint to use it to calculate raycast's end position vector
	FVector PlayerViewPointPosition;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPARAM PlayerViewPointPosition,
		OUTPARAM PlayerViewPointRotation
	);

	//Calculating where the ray will end and returning it
	return PlayerViewPointPosition + PlayerViewPointRotation.Vector() * GrabMaxDistance;
}

