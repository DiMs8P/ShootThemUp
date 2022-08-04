// Shoot them up game, All rights received


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* Player)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Player);
    if (!HealthComponent)
        return false;
    return HealthComponent->TryToAddHealth(HealthValue);
}