// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "CPPUE5UltGameDevCrs/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/SlashCharacter.h"
#include "Interfaces/PickupInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
  ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  RootComponent = ItemMesh;

  Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
  Sphere->SetupAttachment(GetRootComponent());

  ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
  ItemEffect->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

  //UE_LOG(LogTemp, Warning, TEXT("Begin Play Called!"));
  //
  //
  //if (GEngine) {
  //	GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Cyan, FString("Item OnScreen Message"));
  //}

  //UWorld* World = GetWorld();
  //
  //SetActorLocation(FVector(0.f, 0.f, 100.f));
  //SetActorRotation(FRotator(0.f, 45.f, 0.f));
  //
  //FVector Location = GetActorLocation();
  //FVector Forward = GetActorForwardVector();
  //
  //DRAW_SPHERE(Location);
  ////DRAW_LINE(Location, Location + Forward * 100.f);
  //DRAW_VECTOR(Location, Location + Forward * 100.f);
  Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
  Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}


void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  //const FString OtherActorName = OtherActor->GetName();
  //if (GEngine)
  //{
  //  GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
  //}

  IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
  if (PickupInterface)
  {
    PickupInterface->SetOverlappingItem(this);
  }



}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  //const FString OtherActorName = FString("Ending Overlap with: ") + OtherActor->GetName();
  //if (GEngine)
  //{
  //  GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Blue, OtherActorName);
  //}

  IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
  if (PickupInterface)
  {
    PickupInterface->SetOverlappingItem(nullptr);
  }

}

void AItem::SpawnPickupSystem()
{
  if (PickupEffect)
  {
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
      this,
      PickupEffect,
      GetActorLocation()
    );
  }
}

void AItem::SpawnPickupSound()
{
  if (PickupSound)
  {
    UGameplayStatics::SpawnSoundAtLocation(
      this,
      PickupSound,
      GetActorLocation()
    );
  }
}




// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

  //UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
  //
  //if (GEngine) {
  //
  //	FString Name = GetName();
  //	FString Message = FString::Printf(TEXT("Item Name: %s"), *Name);
  //	//FString Message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);
  //	//GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Green, Message);
  //	GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Green, Message);
  //
  //
  //	UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *Name);
  //
  //}


  // Movement rate in units of cm/s
  //float MovementRate = 50.f;
  //float RotationRate = 45.f;

  // MovementRate * DeltaTime (cm/s) * (s/frame) = (cm/frame)

  //AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
  //AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));


  RunningTime += DeltaTime;

  //float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
  //
  //AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ)); 



  //DRAW_SPHERE_SingleFrame(GetActorLocation());
  //DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
  //
  //FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
  //DRAW_POINT_SingleFrame(AvgVector);

  if (ItemState == EItemState::EIS_Hovering)
  {
    AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
  }
}

float AItem::TransformedSin()
{
  return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
  return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}



