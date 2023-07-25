// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_IDLE.h"
#include <Global/GlobalCharacter.h>
#include <AI/AICon.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "Kismet/GameplayStatics.h"
#include "Math/NumericLimits.h"

EBTNodeResult::Type UBTTask_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::IDLE);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	if (5.0f <= GetStateTime(OwnerComp))
	{
		// 그럼 순찰할까?
		// 그냥 5초간 다시 대기하자.
		// SetStateChange(OwnerComp, AIState::MOVE);
		// return;
	}

	FString TargetTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));


	if (0 != TargetActors.Num())
	{
		AActor* ResultActor = nullptr;
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Dis = (Pawn->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRange <= Dis)
			{
				continue;
			}

			if (Range > Dis)
			{
				Range = Dis;
				ResultActor = TargetActors[i];
			}
		}

		if (nullptr != ResultActor)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
			SetStateChange(OwnerComp, AIState::MOVE);
			return;
		}
	}

	//핵심은 플레이어를 찾아내는것.
	// GetGlobalCharacter(OwnerComp)->GetLevel()->;


	return;
}