// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyEnums.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JTH_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		TPSAniState AniState = TPSAniState::Idle;

	TMap<TPSAniState, class UAnimMontage*> AllAnimations;

	UFUNCTION()
		void MontageEnd(UAnimMontage* Anim, bool _Inter);

	// 애님인스턴용 Tick과 BeginPlay

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;
};
