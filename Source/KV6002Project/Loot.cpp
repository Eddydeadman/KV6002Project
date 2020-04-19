// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot.h"

// Sets default values for this component's properties
ULoot::ULoot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULoot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULoot::Loot()
{
	UE_LOG(LogTemp, Warning, TEXT("Loot has been called"));
	GetOwner()->Destroy();
}
