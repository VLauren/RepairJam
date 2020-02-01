#include "RepPawn.h"

ARepPawn::ARepPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Capsula del personaje (componente raiz)
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(34.0f, 65.0f);
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	CapsuleComponent->SetVisibility(true);

	// Malla del personaje
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (Mesh != nullptr)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CapsuleComponent);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	// Component de movimiento
	Movement = CreateDefaultSubobject<URepMove>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;

	// Valores por defecto
	MovementSpeed = 300.0f;
	RotationSpeed = 90.0f;
}

void ARepPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ARepPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARepPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input de movimiento
	PlayerInputComponent->BindAxis("MoveRight", this, &ARepPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARepPawn::MoveForward);
}

void ARepPawn::MoveForward(float AxisValue)
{
	Movement->AddInputVector(AxisValue * FVector::ForwardVector);
}

void ARepPawn::MoveRight(float AxisValue)
{
	Movement->AddInputVector(AxisValue * FVector::RightVector);
}

