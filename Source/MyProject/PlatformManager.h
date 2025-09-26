#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformManager.generated.h"

// 미리 선언
class ARotatingPlatform;
class AMovingPlatform;

UCLASS()
class MYPROJECT_API APlatformManager : public AActor
{
    GENERATED_BODY()

public:
    APlatformManager();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
    TSubclassOf<ARotatingPlatform> RotatingPlatformClass;

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
    TSubclassOf<AMovingPlatform> MovingPlatformClass;

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
    int32 NumPlatformsToSpawn = 5;

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
    FVector SpawnAreaExtent = FVector(2000, 2000, 500);

    FTimerHandle TimerHandle_Spawn;

    UFUNCTION()
    void SpawnRandomPlatform();
};
