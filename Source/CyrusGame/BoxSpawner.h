#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "BoxSpawner.generated.h"

USTRUCT()
struct FBoxType
{
    GENERATED_BODY()

    FString Name;
    UStaticMesh* Mesh;
    UMaterialInterface* Material;
    int32 Health;
    FVector Scale;
};

UCLASS()
class CYRUSGAME_API ABoxSpawner : public AActor
{
    GENERATED_BODY()

public:
    ABoxSpawner();

protected:
    virtual void BeginPlay() override;

private:
    void FetchData();
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void SpawnBox(FVector Location, FRotator Rotation, const FBoxType& BoxType);

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class ASpawnedBox> BoxClass;

    FHttpModule* HttpModule;
    TMap<FString, FBoxType> BoxTypes;
};
