#include "BoxActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ABoxActor::ABoxActor()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = MeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (BoxMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(BoxMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Content/Materials/BoxMaterialTest")); // Ensure you create this material
    if (MaterialAsset.Succeeded())
    {
        DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this);
        MeshComponent->SetMaterial(0, DynamicMaterial);
    }
}

void ABoxActor::BeginPlay()
{
    Super::BeginPlay();
}

void ABoxActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABoxActor::InitializeBox(int32 InHealth, int32 InScore, const FLinearColor& InColor)
{
    Health = InHealth;
    Score = InScore;

    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue("BaseColor", InColor);
    }
}
