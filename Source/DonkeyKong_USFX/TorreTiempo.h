// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Publicador.h"
#include "TorreTiempo.generated.h"

UCLASS()
class DONKEYKONG_USFX_API ATorreTiempo : public APublicador
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorreTiempo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FString Tiempo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CambioDeLaHora();

	//Ajuste la hora de esta TorredelReloj
	void FijarLaHoraDelDia(FString _Tiempo);

	//Devuelve el tiempo de la TorreDelReloj
	FORCEINLINE FString ObtenerTiempo() { return Tiempo; };
};
