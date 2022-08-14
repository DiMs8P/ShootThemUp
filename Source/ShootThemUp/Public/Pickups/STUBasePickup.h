// Shoot them up game, All rights received

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASTUBasePickup();

protected:
    // Called when the game starts or when spawned

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float RespawnDelay = 5.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.0f;

    virtual bool GivePickupTo(APawn* Player);
    void Respawn();
    void PickupWasTaken();

    void GenerateRotationYaw();

    FTimerHandle RespawnTimerHandle;
};
