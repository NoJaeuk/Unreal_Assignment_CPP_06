#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    // ��Ʈ ������Ʈ ����
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // �޽� ���� �� ��Ʈ�� ���̱�
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    // �浹 ����
    MeshComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    MeshComp->CanCharacterStepUpOn = ECB_Yes;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float MoveDelta = MoveSpeed * DeltaTime;
    FVector Direction = bMovingForward ? MoveDirection.GetSafeNormal() : -MoveDirection.GetSafeNormal();
    FVector Move = Direction * MoveDelta;

    // Sweep=true�� �̵� �� ĳ���� �浹 ����
    AddActorWorldOffset(Move, true);

    // �պ� �Ÿ� üũ
    float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
    if (DistanceMoved >= MaxRange)
    {
        bMovingForward = !bMovingForward;
        StartLocation = GetActorLocation();
    }
}
