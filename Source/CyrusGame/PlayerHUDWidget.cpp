#include "PlayerHUDWidget.h"
#include "Components/TextBlock.h"

void UPlayerHUDWidget::UpdateScore(int32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::AsNumber(Score));
    }
}
