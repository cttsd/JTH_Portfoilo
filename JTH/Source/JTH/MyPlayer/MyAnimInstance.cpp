// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// 나자신이 애님인스턴스입니다.
	// OnMontageEnded.AddDynamic(this, &UTPSAnimInstance::MontageEnd);

	// 아이들       => 공격
	// 브랜드 아웃     블랜드인

	OnMontageBlendingOut.AddDynamic(this, &UMyAnimInstance::MontageEnd);

	// 나를 가진 액터를 여기서 가져옵니다.
	// TPS캐릭터에게 다 세팅을 해줬다.

	AMyCharacter* Chracter = Cast<AMyCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations;
}

// 시작할때 한번 업데이트를 돌려주므로.
void UMyAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	AMyCharacter* Chracter = Cast<AMyCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->AniState;

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
	}
}

void UMyAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	TSubclassOf<UAnimInstance> Inst = UMyAnimInstance::StaticClass();

	AMyCharacter* Chracter = Cast<AMyCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// Anim 종료된 몽타주
	if (AllAnimations[TPSAniState::Attack] == Anim)
	{
		AniState = TPSAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
	}

	if (AllAnimations[TPSAniState::Jump] == Anim)
	{
		AniState = TPSAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
	}

}

