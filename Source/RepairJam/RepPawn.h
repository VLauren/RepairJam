// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "RepMove.h"
#include "RepPawn.generated.h"

UCLASS()
class REPAIRJAM_API ARepPawn : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RotationSpeed;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URepMove* Movement;

public:	

	ARepPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

};
