// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "../Global/GlobalGameInstance.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	// Character Movement Setting
	
	JumpMaxHoldTime = 0.0f;

	// �𸮾��� ������Ʈ��°��� ������� �����ڿ����� ����� �ִ�.
	// �� ������ �ִµ� �ӷ¶����̴�. 
	// �𸮾��� �ӷ¶����� ������ �����ڿ����� ������Ʈ�� �ް� �����.
	// CDO������ �����ؾ� �Ѵ�.
	// CreateDefaultObject�Դϴ�.
	// ������� �������� �Դϴ�.

	// �����ڿ��� ������Ʈ�� ����� ����� ������ �Լ��� ����ϸ� �ȴ�.

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	// � �ٸ� �θ𿡰� ���� ���δٴ� �̾߱Ⱑ �˴ϴ�.
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("B_R_Weapon"));


	// �𸮾󿡰� �� �̸Ž� ����� ����Ұž�.
	// �����ڿ����� �����ϴ�.

	// WeaponArrays.Add();

	/* {
		// �Ž��� ���ڴٰ� �ϴ°�.
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Test/Static/2Hand-Sword.2Hand-Sword'"));

		if (true == MeshLoader.Succeeded())
		{
			WeaponArrays.Add(MeshLoader.Object);
		}
	}*/

	/* {
		// �Ž��� ���ڴٰ� �ϴ°�.
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));

		if (true == MeshLoader.Succeeded())
		{
			WeaponArrays.Add(MeshLoader.Object);
		}
	}
	*/

	// CDO���� ���Ŀ� �������Ʈ �ʱ�ȭ�� �̷������ �Ǵµ�.
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	JumpMaxCount = 1;

	GetWorld()->GetAuthGameMode();
	UGlobalGameInstance* Inst = GetGameInstance<UGlobalGameInstance>();

	//WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Weapon")));
	//WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Cube")));

	//WeaponMesh->SetStaticMesh(WeaponArrays[0]);

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// ������ ������ ����?
		// DefaultPawn_MoveForward �߰��Ǵ°� ��
		// ����θ� �ϰ� �ֽ��ϴ�.
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJumpAxis", EKeys::E, -1.f));


		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));
	}

	// Ű�� �Լ��� �����մϴ�.
	// �� Ű�� ������ �� �Լ��� ����������ε�.
	// ���϶��� �ϴ� ��� ���������.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AMyCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("PlayerJumpAxis", this, &AMyCharacter::JumpAxis);

	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMyCharacter::AttackAction);
	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMyCharacter::JumpAction);
}

void AMyCharacter::MoveRight(float Val)
{
	if (AniState == TPSAniState::Attack || AniState == TPSAniState::Jump)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// ���� �� ȸ���� �����ͼ� y�࿡ �ش��ϴ� �຤�͸� ������ �̴ϴ�.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			AniState = Val > 0.f ? TPSAniState::RightMove : TPSAniState::LeftMove;
			return;
		}
	}
	else
	{
		if (AniState == TPSAniState::RightMove || AniState == TPSAniState::LeftMove)
		{
			AniState = TPSAniState::Idle;
		}
	}
}

void AMyCharacter::MoveForward(float Val)
{
	if (AniState == TPSAniState::Attack || AniState == TPSAniState::Jump)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			// ��Ʈ�ѷ��� �⺻������
			// charcter �ϳ��� �پ� �ֽ��ϴ�.
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// �̰� ������ ���Դϴ�.
			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			// ž������̸� �ٸ��� ������ �Ǵµ�.
			// ������ TPS�� �ϰ� �ֱ� ������ ��Ʈ�ѷ��� ȸ���̳� ������ ȸ���̳� ���ƿ�.
			// AddMovementInput(GetActorForwardVector(), Val);

			AniState = Val > 0.f ? TPSAniState::ForwardMove : TPSAniState::BackwardMove;
			return;
		}
	}
	else
	{
		if (AniState == TPSAniState::ForwardMove || AniState == TPSAniState::BackwardMove)
		{
			AniState = TPSAniState::Idle;
		}
	}

	// �̷� ������ �Լ� �� static�Լ��� �ǹ��Ѵ�.
	// AEGLOBAL::DebugPrint("AAAAAAA");
}


void AMyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}


void AMyCharacter::JumpAxis(float Rate)
{
	if (0.0f == Rate)
	{
		if (true == AxisJump)
		{
			StopJumping();
			AxisJump = false;
		}
		return;
	}

	AxisJump = true;
	Jump();
}

void AMyCharacter::JumpAction()
{
	// JumpCurrentCount
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, JumpCurrentCount);
	Jump();

	AniState = TPSAniState::Jump;
}

void AMyCharacter::AttackAction()
{
	// �����Ʈ ������Ʈ�� ���ؼ� �Ѵ�.
	// GetMovementComponent()

	// PlayMontage();

	AniState = TPSAniState::Attack;
}

void AMyCharacter::AnimationTick()
{
	//class UAnimMontage* Montage = AllAnimations[AniState];

	//if (nullptr == Montage)
	//{
	//	return;
	//}

	//if (false == GetMesh()->GetAnimInstance()->Montage_IsPlaying(Montage))
	//{
	//	GetMesh()->GetAnimInstance()->Montage_Play(Montage, 1.0f);
	//}
}
//
//void ATPSCharacter::MontageEnd(UAnimMontage* Anim, bool _Inter)
//{
//	// Anim ����� ��Ÿ��
//	if (AllAnimations[TPSAniState::Attack] == Anim)
//	{
//		AniState = TPSAniState::Idle;
//		GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
//	}
//
//	if (AllAnimations[TPSAniState::Jump] == Anim)
//	{
//		AniState = TPSAniState::Idle;
//		GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
//	}
//
//	
//
//	// �� ���η� ������������ Ȯ���ؾ� �մϴ�.
//	int a = 0;
//}
