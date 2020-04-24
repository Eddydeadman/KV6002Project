// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"
#include "HiddenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KV6002PROJECT_API AHiddenPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
    AHiddenPlayerController (const FObjectInitializer& ObjectInitializer);
	void Escape(float Value);
    virtual void SetupInputComponent();
};
