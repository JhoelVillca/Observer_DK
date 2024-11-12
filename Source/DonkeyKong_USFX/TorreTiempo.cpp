// Fill out your copyright notice in the Description page of Project Settings.


#include "TorreTiempo.h"

// Sets default values
ATorreTiempo::ATorreTiempo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATorreTiempo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorreTiempo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATorreTiempo::CambioDeLaHora()
{
	NotificarASuscriptores();
}

void ATorreTiempo::FijarLaHoraDelDia(FString _Tiempo)
{
	Tiempo = _Tiempo;
	CambioDeLaHora();
}

