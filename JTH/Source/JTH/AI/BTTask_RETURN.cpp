// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RETURN.h"

UBTTask_RETURN::UBTTask_RETURN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}