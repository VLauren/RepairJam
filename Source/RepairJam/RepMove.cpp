
#include "RepMove.h"
#include "RepPawn.h"

void URepMove::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Movimiento Horizontal

	float speed = ((ARepPawn*)GetOwner())->MovementSpeed;
	float rotSpeed = ((ARepPawn*)GetOwner())->RotationSpeed;
	FVector InputVector = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (InputVector.X != 0.0f || InputVector.Y != 0)
		moving = true;
	else
		moving = false;

	// ====================

	// direccion calculada relativo a camara

	if (Camera != nullptr)
	{
		FVector camFwd = Camera->GetActorForwardVector();
		camFwd.Z = 0;
		FVector move = camFwd.Rotation().RotateVector(InputVector);

		FHitResult Hit;
		TickMove = FMath::Lerp(TickMove,  move * speed * DeltaTime, 0.2f);
		SafeMoveUpdatedComponent(TickMove, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Resbalar por la superficie
		if (Hit.IsValidBlockingHit())
			SlideAlongSurface(TickMove, 1.f - Hit.Time, Hit.Normal, Hit);

		// Orientacion del modelo
		if (!InputVector.IsNearlyZero())// && IsGrounded() && jumpFrames <= 0)
		{
			// Target rotation
			FRotator ctrlRot = move.Rotation();
			// float rotLerpSpeed = ((ACroshPawn*)GetOwner())->RotationLerpSpeed;
			float rotLerpSpeed = 0.1f;

			// Rotate character towards target rotation
			CurrentRotation = FMath::Lerp(CurrentRotation, ctrlRot, rotLerpSpeed);
			UpdatedComponent->GetOwner()->SetActorRotation(CurrentRotation);
		}
	}


	// ====================

	/*
	FVector forward = GetOwner()->GetActorForwardVector();

	if (InputVector.X > 0)
		TickMove = FMath::Lerp(TickMove, InputVector.X * forward * speed * DeltaTime, 0.2f);
	// else if(InputVector.Y != 0 && InputVector.X <= 0)
		// TickMove = FMath::Lerp(TickMove, forward * speed * DeltaTime, 0.2f);
	// else
		// TickMove = FMath::Lerp(TickMove, FVector::ZeroVector, 0.2f);

	FHitResult Hit;
	SafeMoveUpdatedComponent(TickMove, UpdatedComponent->GetComponentRotation(), true, Hit);


	// Orientacion del modelo
	if (!InputVector.IsNearlyZero())// && IsGrounded() && jumpFrames <= 0)
	{
		float rotLerpSpeed = 0.01f;

		// Target rotation
		FRotator targetRot = CurrentRotation.Add(0, DeltaTime * rotSpeed * InputVector.Y, 0);
		if (InputVector.X < 0 && InputVector.Y == 0)
			targetRot = CurrentRotation.Add(0, DeltaTime * rotSpeed * 1, 0);

		// Rotate character towards target rotation
		CurrentRotation = FMath::Lerp(CurrentRotation, targetRot, rotLerpSpeed);
		UpdatedComponent->GetOwner()->SetActorRotation(CurrentRotation);
	}
	*/

	// ====================

	/*
	FHitResult Hit;
	TickMove = FMath::Lerp(TickMove, InputVector * speed * DeltaTime, 0.2f);
	SafeMoveUpdatedComponent(TickMove, UpdatedComponent->GetComponentRotation(), true, Hit);

	// Orientacion del modelo
	if (!InputVector.IsNearlyZero())// && IsGrounded() && jumpFrames <= 0)
	{
		// Target rotation
		FRotator ctrlRot = InputVector.Rotation();
		// float rotLerpSpeed = ((ACroshPawn*)GetOwner())->RotationLerpSpeed;
		float rotLerpSpeed = 0.1f;

		// Rotate character towards target rotation
		CurrentRotation = FMath::Lerp(CurrentRotation, ctrlRot, rotLerpSpeed);
		UpdatedComponent->GetOwner()->SetActorRotation(CurrentRotation);
	}
	*/
}

bool URepMove::IsMoving()
{
	return moving;
}
