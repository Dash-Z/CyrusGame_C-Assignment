#include "BoxSpawner.h"
#include "SpawnedBox.h"
#include "Engine/World.h"
#include "Materials/MaterialInterface.h"

ABoxSpawner::ABoxSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    HttpModule = &FHttpModule::Get();
}

void ABoxSpawner::BeginPlay()
{
    Super::BeginPlay();
    FetchData();
}

void ABoxSpawner::FetchData()
{
    FString Url = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &ABoxSpawner::OnResponseReceived);
    Request->SetURL(Url);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
}

void ABoxSpawner::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed!"));
        return;
    }

    FString ResponseString = Response->GetContentAsString();
    UE_LOG(LogTemp, Warning, TEXT("Received JSON: %s"), *ResponseString);

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON!"));
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* ObjectsArray;
    if (JsonObject->TryGetArrayField(TEXT("objects"), ObjectsArray))
    {
        for (const TSharedPtr<FJsonValue>& Entry : *ObjectsArray)
        {
            TSharedPtr<FJsonObject> ObjectData = Entry->AsObject();
            if (!ObjectData.IsValid()) continue;

            FString Type = ObjectData->GetStringField("type");
            if (!BoxTypes.Contains(Type)) continue;

            TSharedPtr<FJsonObject> Transform = ObjectData->GetObjectField("transform");
            if (!Transform.IsValid()) continue;

            FVector Location = FVector::ZeroVector;
            FVector Scale = FVector(1.0f);
            FRotator Rotation = FRotator::ZeroRotator;

            const TArray<TSharedPtr<FJsonValue>>* LocationArray;
            if (Transform->TryGetArrayField("location", LocationArray) && LocationArray->Num() == 3)
            {
                Location.X = (*LocationArray)[0]->AsNumber();
                Location.Y = (*LocationArray)[1]->AsNumber();
                Location.Z = (*LocationArray)[2]->AsNumber();
            }

            const TArray<TSharedPtr<FJsonValue>>* RotationArray;
            if (Transform->TryGetArrayField("rotation", RotationArray) && RotationArray->Num() == 3)
            {
                Rotation.Pitch = (*RotationArray)[0]->AsNumber();
                Rotation.Yaw = (*RotationArray)[1]->AsNumber();
                Rotation.Roll = (*RotationArray)[2]->AsNumber();
            }

            SpawnBox(Location, Rotation, BoxTypes[Type]);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find 'objects' in JSON!"));
    }
}

void ABoxSpawner::SpawnBox(FVector Location, FRotator Rotation, const FBoxType& BoxType)
{
    if (!BoxClass)
    {
        UE_LOG(LogTemp, Error, TEXT("BoxClass is NULL! Cannot spawn."));
        return;
    }

    FActorSpawnParameters SpawnParams;
    ASpawnedBox* SpawnedBox = GetWorld()->SpawnActor<ASpawnedBox>(BoxClass, Location, Rotation, SpawnParams);

    if (SpawnedBox)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawned box: %s at %s"), *BoxType.Name, *Location.ToString());
        SpawnedBox->InitializeBox(BoxType.Mesh, BoxType.Material, BoxType.Health, BoxType.Scale);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn box at location %s"), *Location.ToString());
    }
}
