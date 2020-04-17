// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "HideFunction.generated.h"  
 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KV6002PROJECT_API UHideFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UHideFunction();
	TArray<UStaticMeshComponent*> ListOfMeshes;
	TArray<UBoxComponent*> ListOfBoxes;
	UPROPERTY(EditAnywhere)
	UStaticMesh* MeshTarget;
	void Open(float DeltaTime);
	void Hide();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void InitialiseObject();

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UBoxComponent* CollisionBox;


	FVector InitialLocation;

	float NewX;
	float NewY;
	float NewZ;
	float CloseSpeed = 2.0f;
	UPROPERTY(EditAnywhere)
	FString TypeOfObject;
	UPROPERTY(EDITANYWHERE)
	FVector CameraLocation;

	UPROPERTY(EditAnywhere)
	bool CanHide;

	UPROPERTY(EditAnywhere)
	float TranslatorX;
	UPROPERTY(EditAnywhere)
	float TranslatorY;
	UPROPERTY(EditAnywhere)
	float TranslatorZ;
	bool InUse;

		
};
