
#include "RepMove.h"
#include "RepPawn.h"

void URepMove::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Movimiento Horizontal

	float speed = ((ARepPawn*)GetOwner())->MovementSpeed;
	FVector InputVector = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (InputVector.Size() > 0.0f)
		moving = true;
	else
		moving = false;

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
}

bool URepMove::IsMoving()
{
	return moving;
}
