// Author - Nathan Jackson Student Number:16012679


#include "HideFunction.h"

// Sets default values for this component's properties
UHideFunction::UHideFunction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHideFunction::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerControls = GetWorld()->GetFirstPlayerController();
	InitialiseObject();
	Camera = ActorThatOpens->FindComponentByClass<UCameraComponent>();
	
}


// Called every frame
void UHideFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Initalising the object involves setting the actor that opens as the player character to be used with the hide function
	// as well as collecting a list of attached components to the master object and adding them to the StaticMesh array
void UHideFunction::InitialiseObject()
{
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InUse = false;
	GetOwner()->GetComponents(ListOfMeshes);
}

// The open function checks to see if this object has the target mesh in the array and uses the
	// translator floats to set a new world location. Uses a bool to decide whether to open or close
void UHideFunction::Open()
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
						Hide(CameraLocation, CameraRotation);
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

	// The hide function is called at the end of the open function if the boolean "CanHide" is set to true
	// it detaches the camera from the player and moves it to the CameraLocation vector which is set for each 
	// instance to make it accurate as desired
void UHideFunction::Hide(FVector NewLocation, FRotator NewRotation)
{
	if(InUse == true)
	{
		StorePlayerLocation = Camera->GetComponentLocation();
		StorePlayerRotation = Camera->GetComponentRotation();
		Camera->SetWorldRotation(NewRotation, false, nullptr, ETeleportType::None);
		Camera->SetWorldLocation(NewLocation);
		ActorThatOpens->SetActorHiddenInGame(true);
		ActorThatOpens->DisableInput(PlayerControls);
		GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UHideFunction::Escape, 10.0f);
	}
}

	//The escape function used for exiting the location, sets camera transformations to where they were and enables 
	//controls again
void UHideFunction::Escape()
{
	Camera->SetWorldRotation(StorePlayerRotation, false, nullptr, ETeleportType::None);
	Camera->SetWorldLocation(StorePlayerLocation);
	ActorThatOpens->SetActorHiddenInGame(false);
	ActorThatOpens->EnableInput(PlayerControls);
	ActorThatOpens->ResetOwnedComponents();
}

	//Accessor for the InUse boolean
bool UHideFunction::GetInUse()
{
	return InUse;
}


