// Shoot them up game, All rights received

#include "STUBasePlayerController.h"
#include "Components/STURespawnComponent.h"

ASTUBasePlayerController::ASTUBasePlayerController()
{
    STURespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void ASTUBasePlayerController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);

    GetOnNewPawnNotifier().Broadcast(InPawn);
}