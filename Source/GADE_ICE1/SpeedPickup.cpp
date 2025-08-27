#include "SpeedPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

ASpeedPickup::ASpeedPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create sphere collider
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->InitSphereRadius(100.f);
    CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
    RootComponent = CollisionComp;

    // Bind overlap event
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASpeedPickup::OnOverlapBegin);

    // Create mesh (for visuals)
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
}

void ASpeedPickup::BeginPlay()
{
    Super::BeginPlay();
}

void ASpeedPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if we touched a character
    if (ACharacter* Player = Cast<ACharacter>(OtherActor))
    {
        if (UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement())
        {
            // Apply boost
            MoveComp->MaxWalkSpeed += BoostAmount;

            // Setup timer to remove boost after duration
            FTimerHandle TimerHandle;
            GetWorldTimerManager().SetTimer(TimerHandle, [MoveComp, this]()
                {
                    MoveComp->MaxWalkSpeed -= BoostAmount;
                    Destroy(); // remove the pickup from the world
                }, BoostDuration, false);
        }
    }
}