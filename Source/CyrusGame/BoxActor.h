#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"

UCLASS()
class CYRUSGAME_API ABoxActor : public AActor
{
    GENERATED_BODY()

public:
    ABoxActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void InitializeBox(int32 InHealth, int32 InScore, const FLinearColor& InColor);

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    UMaterialInstanceDynamic* DynamicMaterial;

    int32 Health;
    int32 Score;
};
