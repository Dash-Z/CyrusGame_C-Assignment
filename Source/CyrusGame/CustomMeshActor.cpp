#include "CustomMeshActor.h"
#include "Components/StaticMeshComponent.h"

ACustomMeshActor::ACustomMeshActor()
{
    //PrimaryActorTick.bCanEverTick = false;

    // ✅ Create a Scene Component as the Root (Prevents Root Component issues)
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // ✅ Create a Static Mesh Component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(Root);

    // ✅ Enable Physics & Collision
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
    MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

    // ✅ Default Health
    Health = 100;
    ScorePoints = 50;
}

void ACustomMeshActor::BeginPlay()
{
    Super::BeginPlay();

    // Apply initial Mesh and Material
    ApplyMeshAndMaterial();
}

void ACustomMeshActor::ApplyMeshAndMaterial()
{
    // ✅ Assign Mesh
    if (SelectedMesh)
    {
        MeshComponent->SetStaticMesh(SelectedMesh);
        UE_LOG(LogTemp, Warning, TEXT("Mesh Assigned Successfully!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SelectedMesh is NULL! Assign a mesh."));
    }

    // ✅ Assign Material
    if (SelectedMaterial)
    {
        MeshComponent->SetMaterial(0, SelectedMaterial);
        UE_LOG(LogTemp, Warning, TEXT("Material Assigned Successfully!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SelectedMaterial is NULL!"));
    }
}

void ACustomMeshActor::TakeDamage()
{
    Health--;
    UE_LOG(LogTemp, Warning, TEXT("Box Health Updated: %d"), Health);

    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Box Destroyed!"));
        Destroy();
    }
}
