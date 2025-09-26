#include "PlatformManager.h"
#include "RotatingPlatform.h"
#include "MovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

APlatformManager::APlatformManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void APlatformManager::BeginPlay()
{
    Super::BeginPlay();

    //���� �� ���� �� ����
    for (int32 i = 0; i < NumPlatformsToSpawn; i++)
    {
        SpawnRandomPlatform();
    }

    //���� ����: �ֱ������� �� �÷��� ����
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Spawn,
        this,
        &APlatformManager::SpawnRandomPlatform,
        10.0f, // 10�ʸ��� ����
        true
    );
}

void APlatformManager::SpawnRandomPlatform()
{
    if (!RotatingPlatformClass || !MovingPlatformClass) return;

    //���� ��ġ
    FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnAreaExtent);
    FRotator SpawnRot = FRotator::ZeroRotator;

    //�����ϰ� ȸ��/�̵� �÷��� ����
    bool bSpawnRotating = FMath::RandBool();
    if (bSpawnRotating)
    {
        ARotatingPlatform* RotPlatform = GetWorld()->SpawnActor<ARotatingPlatform>(RotatingPlatformClass, SpawnLoc, SpawnRot);
        if (RotPlatform)
        {
            RotPlatform->RotationSpeed = FMath::RandRange(50.f, 200.f);
        }
    }
    else
    {
        AMovingPlatform* MovPlatform = GetWorld()->SpawnActor<AMovingPlatform>(MovingPlatformClass, SpawnLoc, SpawnRot);
        if (MovPlatform)
        {
            MovPlatform->MoveSpeed = FMath::RandRange(100.f, 400.f);
            MovPlatform->MaxRange = FMath::RandRange(200.f, 800.f);
            MovPlatform->MoveDirection = FVector(FMath::FRandRange(-1.f, 1.f), FMath::FRandRange(-1.f, 1.f), 0).GetSafeNormal();
        }
    }
}

