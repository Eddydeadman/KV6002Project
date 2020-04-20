// Author - Nathan Jackson Student Number:16012679

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "HideFunction.generated.h"  
 
/*
	The HideFunction component is used on different objects to classify what actions it 
	takes when the player interacts with it, will translate meshes to search through and 
	move the player camera if it is possible to hide inside
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KV6002PROJECT_API UHideFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Default Constructor, sets tick component to true
	UHideFunction();
	// An array to hold the list of static meshes that are attached to the object
	TArray<UStaticMeshComponent*> ListOfMeshes;
	// A static mesh variable that can be set anywhere in order to be useable for different 
	// objects, is used to determine what mesh is to be moved when opening or closing
	UPROPERTY(EditAnywhere)
	UStaticMesh* MeshTarget;

	// The open function checks to see if this object has the target mesh in the array and uses the
	// translator floats to set a new world location. Uses a bool to decide whether to open or close
	void Open(float DeltaTime);

	// The hide function is called at the end of the open function if the boolean "CanHide" is set to true
	// it detaches the camera from the player and moves it to the CameraLocation vector which is set for each 
	// instance to make it accurate as desired @param New location for the camera
	void Hide(FVector NewLocation);

	bool GetInUse();
	
	UPROPERTY(BlueprintReadOnly)
	bool InUse;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Initalising the object involves setting the actor that opens as the player character to be used with the hide function
	// as well as collecting a list of attached components to the master object and adding them to the StaticMesh array
	void InitialiseObject();

	// An actor pointer that is set as the player character upon initialisation
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	// The initial vector of the static mesh, used when translating
	FVector InitialLocation;

	// New X coordinate of the mesh, determined through initial location and the translator
	float NewX;
	// New Y coordinate of the mesh, determined through initial location and the translator
	float NewY;
	// New Z coordinate of the mesh, determined through initial location and the translator
	float NewZ;

	// A string variable that declares the category of object for the AI logic to use to determine it's actions
	UPROPERTY(EditAnywhere)
	FString TypeOfObject;

	// An instance editable variable that is set as the desired location to move the camera too
	UPROPERTY(EDITANYWHERE)
	FVector CameraLocation;

	// A boolean to set whether or not this object can be hidden inside or not
	UPROPERTY(EditAnywhere)
	bool CanHide;

	//	The customisable translator for the X-Coordinate of the static mesh to translate
	UPROPERTY(EditAnywhere)
	float TranslatorX;
	//	The customisable translator for the Y-Coordinate of the static mesh to translate
	UPROPERTY(EditAnywhere)
	float TranslatorY;
	//	The customisable translator for the Z-Coordinate of the static mesh to translate
	UPROPERTY(EditAnywhere)
	float TranslatorZ;

	// A boolean that is set when the object is currently open/hidden inside
	

	// Camera pointer to be assigned to the player camera on startup
	UCameraComponent* Camera;

	// Input component pointer to hold the default values of the player
	UInputComponent* PlayerControls = nullptr;

	// Input component to be altered when hiding
	UInputComponent* HiddenControls = nullptr;	
};
