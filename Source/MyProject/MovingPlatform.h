// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MYPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
    AMovingPlatform();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root; 

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    FVector StartLocation;
    bool bMovingForward = true;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Settings")
    float MoveSpeed = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Settings")
    float MaxRange = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Settings")
    FVector MoveDirection = FVector(1, 0, 0); 
};
