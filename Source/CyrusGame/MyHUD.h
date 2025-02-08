#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class CYRUSGAME_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    /** Updates the player's score on the UI */
    void UpdatePlayerScore(int32 Score);

protected:
    /** The Widget class for the HUD */
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UPlayerHUDWidget> HUDWidgetClass;

    /** Reference to the actual Widget */
    UPROPERTY()
    UPlayerHUDWidget* HUDWidget;
};
