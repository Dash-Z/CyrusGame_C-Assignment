#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnedBox.generated.h"

UCLASS()
class CYRUSGAME_API ASpawnedBox : public AActor
{
    GENERATED_BODY()

public:
    ASpawnedBox();

    void InitializeBox(UStaticMesh* Mesh, UMaterialInterface* Material, int32 InitialHealth, FVector Scale);

protected:
    virtual void BeginPlay() override;

private:
    // ✅ Expose this so it is editable in the Blueprint
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization", meta = (AllowPrivateAccess = "true"))
    UStaticMesh* DefaultMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization", meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* DefaultMaterial;

    UPROPERTY()
    UMaterialInstanceDynamic* DynamicMaterial;

    int32 Health;

public:
    void TakeDamage();
};
