// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedMesh.h"

// Sets default values
ASpawnedMesh::ASpawnedMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnedMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnedMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

