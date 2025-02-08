// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYRUSGAME_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    /** Updates the score text in the UI */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateScore(int32 Score);

protected:
    /** Reference to the Score Text UI element */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;
};
