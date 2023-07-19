#pragma once

#include "CoreMinimal.h"

// 애니메이션에 집중할거냐
// 캐릭터에 집중할 거냐?

// UMETA는 각 옵션마다 설정을 다르게 해줄수 있습니다.

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