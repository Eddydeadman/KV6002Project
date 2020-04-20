// Author - Nathan Jackson Student Number:16012679


#include "Grabber.h"

#define OUT

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
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TrackSight(DeltaTime);
	Score = 0;
}

// Gets the player view point location and rotation and uses the reach to get a start and end point
// for the line trace and then, if the object hit is a physics actor, registers the hit target
void UGrabber::TrackSight(float DeltaTime)
{
	FrameTime = DeltaTime;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*2000.f;
	GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
	);
	HitActor = Hit.GetActor();
}

// When button assigned as "Check" is pressed, checks to see if the hit object has a 
// hide function attached, and if so, calls the open function of that component
void UGrabber::Check()
{
	if(HitActor){
		Hider = HitActor->FindComponentByClass<UHideFunction>();
		UE_LOG(LogTemp, Warning, TEXT("Actor has been hit"));
	}
	if(Hider)
	{
		Hider->Open(FrameTime);
		UE_LOG(LogTemp, Warning, TEXT("Hider component"));
	}
}


// When the grab button is pressed, checks if the hit object has a loot component attached
// and calls the loot function if it does
void UGrabber::Grab()
{
	if(HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor has been hit"));
		Loot = HitActor->FindComponentByClass<ULoot>();
	}
	if(Loot)
	{
		Loot->Loot();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Loot Component Found"));
	}
	
}

	// Gets the key binds from the project settings and assigns them to call methods when pressed
void UGrabber::SetupInputComponent()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber has detected the input component on %s"), *GetOwner()->GetName());
		InputHandler->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandler->BindAction("Check", IE_Pressed, this, &UGrabber::Check);
	}
}



