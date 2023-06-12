// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"


class AItem;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;

UCLASS()
class CPPUE5ULTGAMEDEVCRS_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	void EKeyPressed();

	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* SlashContext;

	///** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MovementAction;

  ///** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction* LookAction;


	
  ///** EKey Pressed Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction* EKeyPressedAction;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	private:
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;

		UPROPERTY(VisibleAnywhere, Category = Hair)
	  UGroomComponent* Hair;

    UPROPERTY(VisibleAnywhere, Category = Hair)
    UGroomComponent* Eyebrows;

		ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

};
