// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasK_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"

UBTTasK_Shoot::UBTTasK_Shoot()
{
	NodeName = "Shoot";	
}

EBTNodeResult::Type UBTTasK_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();
	
	return EBTNodeResult::Succeeded; 
}
