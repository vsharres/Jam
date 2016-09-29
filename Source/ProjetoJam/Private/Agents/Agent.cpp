// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "PaperFlipbookComponent.h"
#include "StatementDatabase.h"
#include "StatementsComponent.h"
#include "Agent.h"

AAgent::AAgent(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
	Stats = FAgentStats();
	Agent_Type = EAgentType::GRUNT;
	AgentAnimState = EAgentAnimState::IDLE;
	AgentFacingState = EAgentFacingState::DOWN;

	StatementsComponent = Initializer.CreateDefaultSubobject<UStatementsComponent>(this, TEXT("Statements"));

	ShadowFlipbook = Initializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("ShadowSprite"));

	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	ShadowFlipbook->AttachToComponent(RootComponent, Rules);

	ShadowFlipbook->SetHiddenInGame(true);
	ShadowFlipbook->SetVisibility(false);
	ShadowFlipbook->SetCastShadow(true);
	ShadowFlipbook->bCastHiddenShadow = true;

	GetSprite()->SetRelativeRotation(TOPDOWN_ROTATION);
	//ShadowFlipbook->SetRelativeRotation(SHADOW_ROTATION);

	GetSprite()->SetFlipbook(IdleDownAnimation);
	ShadowFlipbook->SetFlipbook(IdleDownAnimation);

	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Agent")));

}

FName AAgent::GetAgentName()
{
	return AgentName;
}

EAgentAnimState AAgent::GetAnimState()
{
	return AgentAnimState;
}

EAgentFacingState AAgent::GetFacingState()
{
	return AgentFacingState;
}

void AAgent::SetFacingState(EAgentFacingState newState)
{
	float CurFrameTime = this->GetSprite()->GetPlaybackPosition();

	switch (newState)
	{
	case EAgentFacingState::UP:
		GetSprite()->SetFlipbook(IdleUpAnimation);
		ShadowFlipbook->SetFlipbook(IdleUpAnimation);
		break;
	case EAgentFacingState::LEFT:
		GetSprite()->SetFlipbook(IdleLeftAnimation);
		ShadowFlipbook->SetFlipbook(IdleLeftAnimation);
		break;
	case EAgentFacingState::DOWN:
		GetSprite()->SetFlipbook(IdleDownAnimation);
		ShadowFlipbook->SetFlipbook(IdleDownAnimation);
		break;
	case EAgentFacingState::RIGHT:
		GetSprite()->SetFlipbook(IdleRightAnimation);
		ShadowFlipbook->SetFlipbook(IdleRightAnimation);
		break;
	default:
		GetSprite()->SetFlipbook(IdleDownAnimation);
		ShadowFlipbook->SetFlipbook(IdleDownAnimation);
		break;
	}

	GetSprite()->SetPlaybackPosition(CurFrameTime, true);
	ShadowFlipbook->SetPlaybackPosition(CurFrameTime, true);

	AgentFacingState = newState;

}

void AAgent::SetAnimState(EAgentAnimState newState)
{
	float CurFrameTime = this->GetSprite()->GetPlaybackPosition();

	switch (newState)
	{
	case EAgentAnimState::IDLE:
		switch (AgentFacingState)
		{
		case EAgentFacingState::UP:
			GetSprite()->SetFlipbook(IdleUpAnimation);
			ShadowFlipbook->SetFlipbook(IdleUpAnimation);
			break;
		case EAgentFacingState::LEFT:
			GetSprite()->SetFlipbook(IdleLeftAnimation);
			ShadowFlipbook->SetFlipbook(IdleLeftAnimation);
			break;
		case EAgentFacingState::DOWN:
			GetSprite()->SetFlipbook(IdleDownAnimation);
			ShadowFlipbook->SetFlipbook(IdleDownAnimation);
			break;
		case EAgentFacingState::RIGHT:
			GetSprite()->SetFlipbook(IdleRightAnimation);
			ShadowFlipbook->SetFlipbook(IdleRightAnimation);
			break;
		default:
			GetSprite()->SetFlipbook(IdleDownAnimation);
			ShadowFlipbook->SetFlipbook(IdleDownAnimation);
			break;
		}
		break;
	case EAgentAnimState::MOVING_UP:
		GetSprite()->SetFlipbook(MoveUpAnimation);
		ShadowFlipbook->SetFlipbook(MoveUpAnimation);
		break;
	case EAgentAnimState::MOVING_LEFT:
		GetSprite()->SetFlipbook(MoveLeftAnimation);
		ShadowFlipbook->SetFlipbook(MoveLeftAnimation);
		break;
	case EAgentAnimState::MOVING_DOWN:
		GetSprite()->SetFlipbook(MoveDownAnimation);
		ShadowFlipbook->SetFlipbook(MoveDownAnimation);
		break;
	case EAgentAnimState::MOVING_RIGHT:
		GetSprite()->SetFlipbook(MoveRightAnimation);
		ShadowFlipbook->SetFlipbook(MoveRightAnimation);
		break;
	default:
		GetSprite()->SetFlipbook(IdleDownAnimation);
		ShadowFlipbook->SetFlipbook(IdleDownAnimation);
		break;
	}

	GetSprite()->SetPlaybackPosition(CurFrameTime, true);
	ShadowFlipbook->SetPlaybackPosition(CurFrameTime, true);

	AgentAnimState = newState;
}

void AAgent::Tick(float DeltaSeconds)
{
	UpdateFlipbook();

	Super::Tick(DeltaSeconds);
}

void AAgent::OnDamaged(float Damage)
{
	Stats.Cur_Life -= Damage;
	if (Stats.Cur_Life <= 0.0f)
	{
		Stats.Cur_Life = 0.0f;
		Kill();
	}
}

void AAgent::PostInitializeComponents()
{
	AssignProperties();
	Super::PostInitializeComponents();
}

void AAgent::SaveState()
{

}

void AAgent::AssignProperties()
{
	UDataTable* AgentsDataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/Characters/AgentsData.AgentsData"), NULL, LOAD_None, NULL);

	if (AgentsDataTable)
	{
		static const FString ContextString(TEXT("GENERAL"));

		FAgentData* AgentData = AgentsDataTable->FindRow<FAgentData>(AgentName, ContextString);

		if (AgentData)
		{
			Stats.Max_Life = AgentData->Max_Life;
			Stats.Cur_Life = Stats.Max_Life;
			Stats.Speed = AgentData->Speed;
		}
	}

}

void AAgent::Kill()
{

}

void AAgent::UpdateFlipbook()
{
	if (GetVelocity().Size() > MIN_DELTA_VEL)
	{

		if (AgentAnimState != EAgentAnimState::MOVING_UP &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw > MIN_UP_ANGLE  &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw <= MAX_UP_ANGLE)
		{
			AgentFacingState = EAgentFacingState::UP;
			SetAnimState(EAgentAnimState::MOVING_UP);
		}
		else if (AgentAnimState != EAgentAnimState::MOVING_LEFT &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw > MIN_LEFT_ANGLE  &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw <= MAX_LEFT_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::LEFT;
			SetAnimState(EAgentAnimState::MOVING_LEFT);
		}
		else if (AgentAnimState != EAgentAnimState::MOVING_DOWN &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw > MIN_DOWN_ANGLE  &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw <= MAX_DOWN_ANGLE)
		{
			AgentFacingState = EAgentFacingState::DOWN;
			SetAnimState(EAgentAnimState::MOVING_DOWN);
		}
		else if (AgentAnimState != EAgentAnimState::MOVING_RIGHT &&
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw > MIN_RIGHT_ANGLE ||
			GetVelocity().ToOrientationRotator().Clamp().Yaw - GetActorRotation().Clamp().Yaw <= MAX_RIGHT_ANGLE)
		{
			AgentFacingState = EAgentFacingState::RIGHT;
			SetAnimState(EAgentAnimState::MOVING_RIGHT);
		}
	}
	else
	{
		if (AgentAnimState != EAgentAnimState::IDLE)
		{
			SetAnimState(EAgentAnimState::IDLE);
		}
	}
}

void AAgent::MoveRight(float input)
{
	FVector amount = FVector(1.0f, 0.0f, 0.0f) * Stats.Speed * input;
	GetCharacterMovement()->AddInputVector(amount);
}

void AAgent::MoveUp(float input)
{
	FVector amount = FVector(0.0f, -1.0f, 0.0f)* Stats.Speed * input;
	GetCharacterMovement()->AddInputVector(amount);
}