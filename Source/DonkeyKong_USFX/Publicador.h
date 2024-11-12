// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISuscriptor.h"
#include "Publicador.generated.h"

UCLASS()
class DONKEYKONG_USFX_API APublicador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APublicador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AActor*>Suscriptores;
	IISuscriptor* Subs;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Suscribirse(AActor* _Suscriptor);

	//Eliminar de la lista el suscriptor pasado
	virtual void CancelarSuscripcion(AActor* _RemoverSuscriptor);

	//Notificar a todos los suscriptores que algo ha cambiado
	virtual void NotificarASuscriptores();

};
