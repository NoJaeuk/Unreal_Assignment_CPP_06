#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    // 루트 컴포넌트 생성
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // 메쉬 생성 및 루트에 붙이기
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    // 충돌 세팅
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

    // Sweep=true로 이동 → 캐릭터 충돌 적용
    AddActorWorldOffset(Move, true);

    // 왕복 거리 체크
    float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
    if (DistanceMoved >= MaxRange)
    {
        bMovingForward = !bMovingForward;
        StartLocation = GetActorLocation();
    }
}
