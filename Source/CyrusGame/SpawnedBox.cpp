#include "SpawnedBox.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ASpawnedBox::ASpawnedBox()
{
    PrimaryActorTick.bCanEverTick = false;

    // ✅ Create a Static Mesh Component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // ✅ Allow mesh changes in the Blueprint
    MeshComponent->SetMobility(EComponentMobility::Movable);

    // ✅ Enable physics simulation
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
    MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

    // ✅ Assign a default cube mesh if no mesh is provided
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        DefaultMesh = CubeMesh.Object;
        MeshComponent->SetStaticMesh(DefaultMesh);
    }
}

void ASpawnedBox::BeginPlay()
{
    Super::BeginPlay();
}

void ASpawnedBox::InitializeBox(UStaticMesh* Mesh, UMaterialInterface* Material, int32 InitialHealth, FVector Scale)
{
    Health = InitialHealth;
    SetActorScale3D(Scale);

    // ✅ Assign Mesh (if provided)
    if (Mesh)
    {
        MeshComponent->SetStaticMesh(Mesh);
        UE_LOG(LogTemp, Warning, TEXT("Box Mesh Assigned Successfully!"));
    }
    else if (DefaultMesh)
    {
        MeshComponent->SetStaticMesh(DefaultMesh);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Mesh Assigned! Box may be invisible."));
    }

    // ✅ Assign Material (if provided)
    if (Material)
    {
        DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
        if (DynamicMaterial)
        {
            MeshComponent->SetMaterial(0, DynamicMaterial);
            UE_LOG(LogTemp, Warning, TEXT("Box Material Assigned Successfully!"));
        }
    }
    else if (DefaultMaterial)
    {
        MeshComponent->SetMaterial(0, DefaultMaterial);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Material is NULL!"));
    }
}
