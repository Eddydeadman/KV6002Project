// Fill out your copyright notice in the Description page of Project Settings.


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

void UGrabber::Check()
{
	if(HitActor){
		Hider = HitActor->FindComponentByClass<UHideFunction>();
	}
	if(Hider)
	{
		Hider->Open(FrameTime);
	}
}

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


void UGrabber::SetupInputComponent()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		InputHandler->BindAction("Hide", IE_Pressed, this, &UGrabber::Check);
		InputHandler->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}
