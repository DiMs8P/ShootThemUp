// Shoot them up game, All rights received

#include "AI/Services/STUChangeWeaponService.h"
#include "AI/STUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
    {
        WeaponComponent->NextWeapon();
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
