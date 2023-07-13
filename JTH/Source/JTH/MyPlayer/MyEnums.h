#pragma once

#include "CoreMinimal.h"

// �ִϸ��̼ǿ� �����Ұų�
// ĳ���Ϳ� ������ �ų�?

// UMETA�� �� �ɼǸ��� ������ �ٸ��� ���ټ� �ֽ��ϴ�.

UENUM(BlueprintType)
enum class TPSAniState : uint8
{
	None UMETA(DisplayName = "������"),
	Idle UMETA(DisplayName = "���ֱ�"),
	LeftMove UMETA(DisplayName = "�����̵�"),
	RightMove UMETA(DisplayName = "�������̵�"),
	ForwardMove UMETA(DisplayName = "�������̵�"),
	BackwardMove UMETA(DisplayName = "�ڷ��̵�"),
	Jump UMETA(DisplayName = "����"),
	Attack UMETA(DisplayName = "����"),
};