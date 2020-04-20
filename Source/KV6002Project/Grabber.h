// Author - Nathan Jackson Student Number:16012679

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "HideFunction.h"
#include "Loot.h"
#include "Grabber.generated.h"

/*
	The grabber component is attached to the player character and is used to find where 
	the player is looking and when buttons are pressed, checks if there is a hit object by 
	the line trace and if so calls a method accordingly
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KV6002PROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// When button assigned as "Check" is pressed, checks to see if the hit object has a 
	// hide function attached, and if so, calls the open function of that component
	void Check();

	// When the grab button is pressed, checks if the hit object has a loot component attached
	// and calls the loot function if it does
	void Grab();

	// Hide function pointer used  when identifying whether the targeted object has a hide function component and 
	// is a assigned as a pointer to that component
	UHideFunction* Hider;
	// Loot component pointer used  when identifying whether the targeted object has a loot component and 
	// is a assigned as a pointer to that component
	ULoot* Loot;
	// Score counter for the player
	UPROPERTY(BlueprintReadOnly)
	int Score;

	int GetScore();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// A float used as a distance with which the line trace is tracked
	float Reach = 120.f;

	// Frametime set every tick so can be used in multiple functions
	float FrameTime;

	// Gets the player view point location and rotation and uses the reach to get a start and end point
	// for the line trace and then, if the object hit is a physics actor, registers the hit target
	void TrackSight(float);

	// A pointer to an actor, used to register the line traces' hit result
	AActor* HitActor;

	// Input Component used to get the input from the player character
	UInputComponent* InputHandler = nullptr;

	// Gets the key binds from the project settings and assigns them to call methods when pressed
	void SetupInputComponent();
	
};
