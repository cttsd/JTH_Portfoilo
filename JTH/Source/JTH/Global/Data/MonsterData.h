#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include <Global/GlobalEnums.h>
#include "MonsterData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct JTH_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

		FMonsterData() {}
	~FMonsterData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ATT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UBehaviorTree* AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TMap<AIState, class UAnimMontage*> MapAnimation;

};