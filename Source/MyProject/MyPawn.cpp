// MyPawn.cpp
#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 1. �浹 ������Ʈ
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    RootComponent = CapsuleComp;
    CapsuleComp->SetSimulatePhysics(false);

    // 2. Skeletal Mesh
    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetSimulatePhysics(false);

    // 3. Spring Arm & Camera
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // 4. �̵� �ӵ�
    MoveSpeed = 600.f;
    TurnSpeed = 100.f;
}

void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input Setup
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            // ���⼭ Input Mapping Context�� �߰� (�����Ϳ��� ���� IMC ����)
            // Subsystem->AddMappingContext(MyIMC, 0);
        }
    }
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
        EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
    }
}

void AMyPawn::Move(const FInputActionValue& Value)
{
    MoveInput = Value.Get<FVector2D>();
}

void AMyPawn::Look(const FInputActionValue& Value)
{
    LookInput = Value.Get<FVector2D>();
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �̵�
    FVector Forward = GetActorForwardVector() * MoveInput.Y * MoveSpeed * DeltaTime;
    FVector Right = GetActorRightVector() * MoveInput.X * MoveSpeed * DeltaTime;
    AddActorLocalOffset(Forward + Right, true);

    // ȸ��
    FRotator NewRot = GetActorRotation();
    NewRot.Yaw += LookInput.X * TurnSpeed * DeltaTime;
    AddActorLocalRotation(FRotator(0.f, LookInput.X * TurnSpeed * DeltaTime, 0.f));
    FRotator CameraRot = SpringArm->GetComponentRotation();
    CameraRot.Pitch = FMath::Clamp(CameraRot.Pitch + LookInput.Y * TurnSpeed * DeltaTime, -80.f, 80.f);
    SpringArm->SetWorldRotation(CameraRot);
}
