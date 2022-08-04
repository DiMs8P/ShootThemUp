// Shoot them up game, All rights received

#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::BeginPlay() {
    Super::BeginPlay();
    auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (PlayerHudWidget)
    {
        PlayerHudWidget->AddToViewport();
    }
}

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();

   // DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{

    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineLenght = 10.0f;
    const float LineThikness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineLenght, Center.Max, Center.Min + HalfLineLenght, Center.Max, LineColor, LineThikness);
    DrawLine(Center.Min, Center.Max - HalfLineLenght, Center.Min, Center.Max + HalfLineLenght, LineColor, LineThikness);
}
