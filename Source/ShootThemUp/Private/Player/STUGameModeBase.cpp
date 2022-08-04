// Shoot them up game, All rights received


#include "STUGameModeBase.h"
#include "STUBaseCharacter.h"
#include "STUBasePlayerController.h"
#include "UI/STUGameHUD.h"

ASTUGameModeBase::ASTUGameModeBase() {
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUBasePlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}
