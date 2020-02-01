// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RepairJamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class REPAIRJAM_API ARepairJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure)
		FRotator SLerp(FRotator A, FRotator B, float alpha);
};
