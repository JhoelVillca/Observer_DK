// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Plataforma.h"
#include "ISuscriptor.h"
#include "ITransfromar.h"
#include "Enemigos.generated.h"

UCLASS()
class DONKEYKONG_USFX_API AEnemigos : public ACharacter, public IISuscriptor, public IITransfromar
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TMap<int, APlataforma*> Posicion;

	//para vigilar
	FVector PosicionInicial;
	FVector LimiteInicial;
	FVector LimiteFinal;
	FVector posicionActual;
	FRotator mirar;
	FTimerHandle Timer;
	bool moverse;
	float incremento;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Transformar() override {};
	void Actualizar() override {};
};
