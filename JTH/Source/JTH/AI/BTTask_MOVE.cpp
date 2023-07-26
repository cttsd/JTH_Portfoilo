// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MOVE.h"
#include <Global/GlobalCharacter.h>
#include <AI/AICon.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_MOVE::UBTTask_MOVE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MOVE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::MOVE);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_MOVE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (nullptr == TargetActor)
	{
		SetStateChange(OwnerComp, AIState::RETURN);
		return;
	}

	{
		FVector TargetPos = TargetActor->GetActorLocation();
		FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
		Dir.Normalize();

		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DelataSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else {
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}



	{
		FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		FVector TargetPos = TargetActor->GetActorLocation();

		FVector Dir = TargetPos - PawnPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));


		// 충분히 근접했다.
		if (AttackRange >= Dir.Size())
		{
			SetStateChange(OwnerComp, AIState::ATTACK);
			return;
		}

	}

}

