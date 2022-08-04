// Shoot them up game, All rights received


#include "Pickups/STUAmmoPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePickupTo(APawn* Player) {
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Player);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Player);
    if (!WeaponComponent)
        return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}

