// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoDragon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TorreTiempo.h"
#include "Publicador.h"

// Sets default values
AEnemigoDragon::AEnemigoDragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/FourEvilDragonsHP/Meshes/DragonTheUsurper/DragonTheUsurperSK.DragonTheUsurperSK'"));
    if (MeshAsset.Succeeded())
    {
        SkeletalMesh->SetSkeletalMesh(MeshAsset.Object);
    }
    SkeletalMesh->SetupAttachment(RootComponent);
    SkeletalMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
    SkeletalMesh->SetRelativeLocation(FVector(0.0f, 0.f, -400.0f));
    // Cargar la animaci�n
    static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationAsset(TEXT("AnimSequence'/Game/FourEvilDragonsHP/Animations/DragonTheUsurper/FlyForwardAnim.FlyForwardAnim'"));
    if (AnimationAsset.Succeeded())
    {
        MyAnimationAsset = AnimationAsset.Object;
    }
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;

    atacarAve = true;
    vigilarAve = true;
	incremento = 6.0f;
}

// Called when the game starts or when spawned
void AEnemigoDragon::BeginPlay()
{
	Super::BeginPlay();
    if (MyAnimationAsset && SkeletalMesh)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Animaci�n cargada"));
        SkeletalMesh->PlayAnimation(MyAnimationAsset, true); // false significa que no se repetir� en bucle
    }
}

// Called every frame
void AEnemigoDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemigoDragon::vigilar()
{
    posicionActual = GetActorLocation();
    mirar = GetActorRotation();
    if (moverse)
    {
        if (posicionActual.Y <= LimiteInicial.Y) {
            posicionActual.Y += incremento;
            mirar.Yaw = 0;
        }
        else moverse = false;
    }
    else
    {
        if (posicionActual.Y >= LimiteFinal.Y) {
            posicionActual.Y -= incremento;
            mirar.Yaw = 180;
        }
        else moverse = true;
    }
    SetActorLocation(posicionActual);
    SetActorRotation(mirar);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Vigilando"));
}

void AEnemigoDragon::atacar()
{
    APawn* Player1 = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player1) {
        FVector Direction = (Player1->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        // Mover directamente el actor
        FVector NewLocation = GetActorLocation() + (Direction * 10.0f);
        SetActorLocation(NewLocation);
        FRotator NewRotation = Direction.Rotation();
        NewRotation.Pitch = 0.0f;
        NewRotation.Roll = 0.0f;
        NewRotation.Yaw > 0 ? NewRotation.Yaw = 0 : NewRotation.Yaw = 180;
        SetActorRotation(NewRotation);
    }
}

void AEnemigoDragon::EstablecerTorreDelReloj(ATorreTiempo* _TorreDelReloj)
{
    TorreDelReloj = _TorreDelReloj;
    TorreDelReloj->Suscribirse(this);
}

void AEnemigoDragon::Actualizar()
{
	Transformar();
}

void AEnemigoDragon::Transformar()
{
    if (TorreDelReloj->ObtenerTiempo() == "Noche")
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Noche te atacannnnnn"));
        vigilarAve = true; atacarAve = false;
        PosicionInicial = GetActorLocation();
        LimiteInicial = PosicionInicial + FVector(0, 2000, 0);
        LimiteFinal = PosicionInicial + FVector(0, -2000, 0);
        GetWorld()->GetTimerManager().SetTimer(observar, this, &AEnemigoDragon::vigilar, 0.009f, vigilarAve);
    }
    else if (TorreDelReloj->ObtenerTiempo() == "Dia")
    {
        vigilarAve = false; atacarAve = true;
        GetWorld()->GetTimerManager().SetTimer(observar, this, &AEnemigoDragon::atacar, 0.009f, atacarAve);
    }
}

void AEnemigoDragon::cancelar()
{
    TorreDelReloj->CancelarSuscripcion(this);
}

