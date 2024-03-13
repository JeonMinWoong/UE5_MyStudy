// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType : uint8
{
	Student = 1 UMETA(DispayName = "For Student"),
	Teacher UMETA(DispayName = "For Teacher"),
	Staff UMETA(DispayName = "For Staff"),
	Invalid
};

/**
 * 
 */
UCLASS()
class UNREALCOMPOSITION_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();

	ECardType GetCardType() const { return CardType; }
	void SetCardType(ECardType InCardType) { CardType = InCardType; }
	
private:

	UPROPERTY()
	ECardType CardType;
	
	UPROPERTY()
	int32 Id;
};
