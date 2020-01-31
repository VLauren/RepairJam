// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RepMove.generated.h"

/**
 * 
 */
UCLASS()
class REPAIRJAM_API URepMove : public UPawnMovementComponent
{
	GENERATED_BODY()

private:

	FRotator CurrentRotation;
	FVector TickMove;
	bool moving;

public:

	UFUNCTION(BlueprintPure)
		bool IsMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
