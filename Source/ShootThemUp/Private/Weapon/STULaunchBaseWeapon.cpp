#include "Weapon/STULaunchBaseWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULaunchBaseWeapon::StartFire() {
    MakeShot();
}

void ASTULaunchBaseWeapon::MakeShot() {
    if (!GetWorld() || IsAmmoEmpty())
        return;

    FVector StartPosition;
    FVector EndPosition;

    if (!GetTraceData(StartPosition, EndPosition))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, StartPosition, EndPosition);

    const FVector StartPoint = GetMuzzleLocation();
    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : EndPosition;
    const FVector Direction = (EndPoint - StartPoint).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());

    ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        Projectile->SetShootDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
}