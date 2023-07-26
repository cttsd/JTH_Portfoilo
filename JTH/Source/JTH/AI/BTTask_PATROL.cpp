// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_PATROL.h"

UBTTask_PATROL::UBTTask_PATROL()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}