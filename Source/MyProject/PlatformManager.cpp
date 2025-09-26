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

    //시작 시 여러 개 스폰
    for (int32 i = 0; i < NumPlatformsToSpawn; i++)
    {
        SpawnRandomPlatform();
    }

    //도전 과제: 주기적으로 새 플랫폼 스폰
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Spawn,
        this,
        &APlatformManager::SpawnRandomPlatform,
        10.0f, // 10초마다 스폰
        true
    );
}

void APlatformManager::SpawnRandomPlatform()
{
    if (!RotatingPlatformClass || !MovingPlatformClass) return;

    //랜덤 위치
    FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnAreaExtent);
    FRotator SpawnRot = FRotator::ZeroRotator;

    //랜덤하게 회전/이동 플랫폼 선택
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

