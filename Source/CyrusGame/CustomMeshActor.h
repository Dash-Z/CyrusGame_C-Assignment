#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomMeshActor.generated.h"

UCLASS()
class CYRUSGAME_API ACustomMeshActor : public AActor
{
    GENERATED_BODY()

public:
    ACustomMeshActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    UStaticMesh* SelectedMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    UMaterialInterface* SelectedMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    int32 Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Mesh")
    int32 ScorePoints;

    UFUNCTION(BlueprintCallable, Category = "Custom Mesh")
    void ApplyMeshAndMaterial();

    void TakeDamage();
};
