#pragma once

#include "CoreMinimal.h"

// �ִϸ��̼ǿ� �����Ұų�
// ĳ���Ϳ� ������ �ų�?

// UMETA�� �� �ɼǸ��� ������ �ٸ��� ���ټ� �ֽ��ϴ�.

UENUM(BlueprintType)
enum class TPSAniState : uint8
{
	None UMETA(DisplayName = "MyPlayerNone"),
	Idle UMETA(DisplayName = "MyPlayerIdle"),
	LeftMove UMETA(DisplayName = "MyPlayerLft"),
	RightMove UMETA(DisplayName = "MyPlayerRgt"),
	ForwardMove UMETA(DisplayName = "MyPlayerFwd"),
	BackwardMove UMETA(DisplayName = "MyPlayerBkr"),
	Jump UMETA(DisplayName = "MyPlayerJp"),
	Attack UMETA(DisplayName = "MyPlayerAt"),
};