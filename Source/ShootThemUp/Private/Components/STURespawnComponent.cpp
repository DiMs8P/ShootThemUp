// Shoot them up game, All rights received

#include "Components/STURespawnComponent.h"
#include "Player/STUGameModeBase.h"

USTURespawnComponent::USTURespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;

    RespawnCountDown = RespawnTime;

    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    UE_LOG(LogTemp, Display, TEXT("RespawnTimeRemaining: %i"), RespawnCountDown);
    if (--RespawnCountDown == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("RespawnTime"));
        if (GetWorld())
        {
            GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

            const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
            if (!GameMode)
                return;

            GameMode->RespawnRequest(Cast<AController>(GetOwner()));
        }
    }
}

bool USTURespawnComponent::IsRespawnInProgress() const {
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}