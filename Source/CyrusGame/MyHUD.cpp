#include "MyHUD.h"
#include "PlayerHUDWidget.h"
#include "Blueprint/UserWidget.h"

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("HUD Widget Created and Added to Viewport!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to Create HUD Widget!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass is NULL! Assign the UI Widget in the HUD Blueprint."));
    }
}

void AMyHUD::UpdatePlayerScore(int32 Score)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateScore(Score);
    }
}
