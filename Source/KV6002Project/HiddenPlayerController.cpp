// Fill out your copyright notice in the Description page of Project Settings.

#include "HiddenPlayerController.h"

AHiddenPlayerController::AHiddenPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

};


void AHiddenPlayerController::SetupInputComponent(){
	
	Super::SetupInputComponent();

	check(InputComponent);

	if (InputComponent != NULL)
	{
		InputComponent->BindAxis("Escape", this, &AHiddenPlayerController::Escape);
	}
}


void AHiddenPlayerController::Escape(float Value)
{
	class UGrabber* Grabber = GetOwner()->FindComponentByClass<UGrabber>();
    Grabber->Escape();
}