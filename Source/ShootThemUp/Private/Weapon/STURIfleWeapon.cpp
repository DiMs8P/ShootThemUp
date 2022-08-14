// Shoot them up game, All rights received

#include "Weapon/STURIfleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTURIfleWeapon::ASTURIfleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURIfleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURIfleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURIfleWeapon::StartFire, TimeBetweenShots, true);
    MakeShot();
}

void ASTURIfleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(FireTimerHandle);
    SetMuzzleFXVisibility(false);
}

void ASTURIfleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) // IsAmmoEmpty()
    {
        return;
        StopFire();
    }

    FVector StartPosition;
    FVector EndPosition;

    if (!GetTraceData(StartPosition, EndPosition))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, StartPosition, EndPosition);

    FVector TraceFXEnd = EndPosition;

    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        // DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Blue, false, 3.0f, 0, 3.0f);
        // DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Black, false, 5.0f);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    //else
    //{
    //    // DrawDebugLine(GetWorld(), GetMuzzleLocation(), EndPosition, FColor::Blue, false, 3.0f, 0, 3.0f);
    //}
    SpawnTraceFX(GetMuzzleLocation(), TraceFXEnd);
    DecreaseAmmo();
}

bool ASTURIfleWeapon::GetTraceData(FVector& StartPosition, FVector& EndPosition) const
{
    FVector ViewLocation; // <------------ to 59 line
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    StartPosition = ViewLocation; // SocketTransform.GetLocation();
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector Direction = FMath::VRandCone(ViewRotation.Vector(), HalfRad); // SocketTransform.GetRotation().GetForwardVector();
    EndPosition = ViewLocation + Direction * TraceMaxDistance;
    return true;
}

void ASTURIfleWeapon::MakeDamage(const FHitResult HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ASTURIfleWeapon::InitMuzzleFX() {
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void ASTURIfleWeapon::SetMuzzleFXVisibility(bool Visible) {
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }

}

void ASTURIfleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) {
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    
    }

    }
