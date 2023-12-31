// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"

#include "GlobalGameInstance.generated.h"

/**
 *
 */
UCLASS()
class JTH_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UGlobalGameInstance();
	~UGlobalGameInstance();

	UStaticMesh* GetMesh(FName _Name);

	struct FMonsterData* GetMonsterData(FName _Name);

private:
	UPROPERTY()
		UDataTable* TestTable;

	UPROPERTY()
		UDataTable* MeshDatas;

	UPROPERTY()
		UDataTable* MonsterDatas;

	TArray<UStaticMesh*> Arrmesh;

};

