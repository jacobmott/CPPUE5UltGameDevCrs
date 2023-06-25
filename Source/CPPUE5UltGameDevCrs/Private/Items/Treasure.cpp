// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "Interfaces/PickupInterface.h"
#include "Components/SphereComponent.h"


void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 100.f, 5.f, FColor::Blue, 5.f);
//
  //if (GEngine)
  //{
  //  GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString::Printf(TEXT("ATreasure::OnSphereOverlap Here1")), false);
  //}
//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 60.f, 5.f, FColor::Red, 5.f);
//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f, FColor::Green, 5.f);

  //if (alreadyPickedUp) return;
  //if (GEngine)
  //{
  //	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString::Printf(TEXT("ATreasure::OnSphereOverlap Here2")), false);
  //}

  IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
  if (PickupInterface)
	{
    PickupInterface->AddGold(this);
    SpawnPickupSound();
		//alreadyPickedUp = true;
		Destroy();
	}
}