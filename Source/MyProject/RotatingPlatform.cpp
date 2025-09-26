#include "RotatingPlatform.h"

ARotatingPlatform::ARotatingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void ARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator Rotation(0.f, RotationSpeed * DeltaTime, 0.f);
    AddActorLocalRotation(Rotation);
}

