// MyPawn.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
    GENERATED_BODY()

public:
    AMyPawn();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;

private:
    // Components
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    // Movement
    FVector2D MoveInput;
    FVector2D LookInput;
    float MoveSpeed;
    float TurnSpeed;

    // Functions
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
};
