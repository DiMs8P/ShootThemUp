// Shoot them up game, All rights received

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
//#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

USTUWeaponFXComponent::USTUWeaponFXComponent() {}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult HitResult)
{
    auto ImpactData = DefaultImpactData;

    if (HitResult.PhysMaterial.IsValid())
    {
        const auto PhysMat = HitResult.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }
    // niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        HitResult.ImpactPoint,                                 //
        HitResult.ImpactNormal.Rotation());

    // decale
    auto DecaleComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecaleData.Material,                //
        ImpactData.DecaleData.Size,                    //
        HitResult.ImpactPoint,                         //
        HitResult.ImpactNormal.Rotation());
    if (DecaleComponent)
    {
        DecaleComponent->SetFadeOut(ImpactData.DecaleData.LifeTime, ImpactData.DecaleData.FadeOutTime);
    }
}
