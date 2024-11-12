// Fill out your copyright notice in the Description page of Project Settings.


#include "Publicador.h"

// Sets default values
APublicador::APublicador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APublicador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APublicador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APublicador::Suscribirse(AActor* _Suscriptor)
{
	Suscriptores.Add(_Suscriptor);
}

void APublicador::CancelarSuscripcion(AActor* _RemoverSuscriptor)
{
	Suscriptores.Remove(_RemoverSuscriptor);
}

void APublicador::NotificarASuscriptores()
{
	for (AActor* Suscriptor : Suscriptores) {
		Subs = Cast<IISuscriptor>(Suscriptor);
		if (Subs) {
			Subs->Actualizar();
		}
	}
}

