// Fill out your copyright notice in the Description page of Project Settings.


#include "HideFunction.h"

// Sets default values for this component's properties
UHideFunction::UHideFunction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHideFunction::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialiseObject();
	
	
}


// Called every frame
void UHideFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHideFunction::InitialiseObject()
{
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InUse = false;

	GetOwner()->GetComponents(ListOfMeshes);
	GetOwner()->GetComponents(ListOfBoxes);

	if(MeshTarget)
	{
		FString name = MeshTarget->GetName();
	}

	for(int i = 0;i<ListOfMeshes.Num();i++)
	{
		FString MeshName = ListOfMeshes[i]->GetName();
	}

	for(int i = 0;i<ListOfBoxes.Num();i++)
	{
		FString SceneName = ListOfBoxes[i]->GetName();
		if(SceneName==FString("Box"))
		{
			CollisionBox=ListOfBoxes[i];
		}
	}
}

void UHideFunction::Open(float DeltaTime)
{
	if(MeshTarget&&ListOfMeshes[0])
	{
		FString name = MeshTarget->GetName();
		for(int i = 0;i<ListOfMeshes.Num();i++)
		{
			name = ListOfMeshes[i]->GetStaticMesh()->GetName();
			FString ComparisonName = MeshTarget->GetName();
			if(name==ComparisonName)
			{
				InitialLocation = ListOfMeshes[i]->GetRelativeLocation();
				if(InUse==false)
				{
					NewX = InitialLocation.X + TranslatorX;
					NewY = InitialLocation.Y + TranslatorY;
					NewZ = InitialLocation.Z + TranslatorZ;
					FVector TargetLocation(NewX, NewY, NewZ);;
					ListOfMeshes[i]->SetRelativeLocation(TargetLocation);
					InUse = true;
					if(CanHide)
					{
						Hide();
					}
					return;
				}
				else
				{
					NewX = InitialLocation.X - TranslatorX;
					NewY = InitialLocation.Y - TranslatorY;
					NewZ = InitialLocation.Z - TranslatorZ;
					FVector TargetLocation(NewX, NewY, NewZ);;
					ListOfMeshes[i]->SetRelativeLocation(TargetLocation);
					InUse = false;
					return;
				}
				
			}
		}
	} 
}

void UHideFunction::Hide()
{
	//Code for detaching and moving it to world location vector set individually in editor
}
