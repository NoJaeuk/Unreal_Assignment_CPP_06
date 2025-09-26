// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class MYPROJECT_API ARotatingPlatform : public AActor
{
    GENERATED_BODY()

public:
    ARotatingPlatform();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Settings")
    float RotationSpeed = 45.f; // 초당 회전 속도

};
