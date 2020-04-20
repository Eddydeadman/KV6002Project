// Author - Nathan Jackson Student Number:16012679

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Loot.generated.h"

/*
	A simple component that is added to the loot objects and has one simple
	method to destroy the actor when it is grabbed
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KV6002PROJECT_API ULoot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULoot();

	// Destroys the object it is attached to
	int Loot();
	float Score = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	AActor* Player;

		
};
