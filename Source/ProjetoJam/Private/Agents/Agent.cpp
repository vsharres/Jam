// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "PaperFlipbookComponent.h"
#include "StatementDatabase.h"
#include "Agent.h"

AAgent::AAgent(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
	Stats = FAgentStats();
	Agent_Type = EAgentType::GRUNT;
	AgentAnimState = EAgentAnimState::IDLE;
	AgentFacingState = EAgentFacingState::S;

	ShadowFlipbook = Initializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "ShadowSprite");

	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
	ShadowFlipbook->AttachToComponent(RootComponent, Rules);

	ShadowFlipbook->SetHiddenInGame(true);
	ShadowFlipbook->SetVisibility(false);
	ShadowFlipbook->SetCastShadow(true);
	ShadowFlipbook->bCastHiddenShadow = true;

	GetSprite()->SetRelativeRotation(ISOMETRIC_ROTATION);
	ShadowFlipbook->SetRelativeRotation(SHADOW_ROTATION);

	GetSprite()->SetFlipbook(IdleSAnimation);
	ShadowFlipbook->SetFlipbook(IdleSAnimation);

	this->GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Agent")));

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

void AAgent::SetAnimState(EAgentAnimState newState)
{
	float CurFrameTime = this->GetSprite()->GetPlaybackPosition();

	switch (newState)
	{
	case EAgentAnimState::IDLE:
		switch (AgentFacingState)
		{
		case EAgentFacingState::N:
			this->GetSprite()->SetFlipbook(IdleNAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleNAnimation);
			break;
		case EAgentFacingState::NW:
			this->GetSprite()->SetFlipbook(IdleNWAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleNWAnimation);
			break;
		case EAgentFacingState::W:
			this->GetSprite()->SetFlipbook(IdleWAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleWAnimation);
			break;
		case EAgentFacingState::SW:
			this->GetSprite()->SetFlipbook(IdleSWAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleSWAnimation);
			break;
		case EAgentFacingState::S:
			this->GetSprite()->SetFlipbook(IdleSAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleSAnimation);
			break;
		case EAgentFacingState::SE:
			this->GetSprite()->SetFlipbook(IdleSEAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleSEAnimation);
			break;
		case EAgentFacingState::E:
			this->GetSprite()->SetFlipbook(IdleEAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleEAnimation);
			break;
		case EAgentFacingState::NE:
			this->GetSprite()->SetFlipbook(IdleNEAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleNEAnimation);
			break;
		default:
			this->GetSprite()->SetFlipbook(IdleSAnimation);
			this->ShadowFlipbook->SetFlipbook(IdleSAnimation);
			break;
		}
		break;
	case EAgentAnimState::MOVING_N:
		this->GetSprite()->SetFlipbook(MoveNAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveNAnimation);
		break;
	case EAgentAnimState::MOVING_NW:
		this->GetSprite()->SetFlipbook(MoveNWAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveNWAnimation);
		break;
	case EAgentAnimState::MOVING_W:
		this->GetSprite()->SetFlipbook(MoveWAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveWAnimation);
		break;
	case EAgentAnimState::MOVING_SW:
		this->GetSprite()->SetFlipbook(MoveSWAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveSWAnimation);
		break;
	case EAgentAnimState::MOVING_S:
		this->GetSprite()->SetFlipbook(MoveSAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveSAnimation);
		break;
	case EAgentAnimState::MOVING_SE:
		this->GetSprite()->SetFlipbook(MoveSEAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveSEAnimation);
		break;
	case EAgentAnimState::MOVING_E:
		this->GetSprite()->SetFlipbook(MoveEAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveEAnimation);
		break;
	case EAgentAnimState::MOVING_NE:
		this->GetSprite()->SetFlipbook(MoveNEAnimation);
		this->ShadowFlipbook->SetFlipbook(MoveNEAnimation);
		break;
	default:
		this->GetSprite()->SetFlipbook(IdleSAnimation);
		this->ShadowFlipbook->SetFlipbook(IdleSAnimation);
		break;
	}

	this->GetSprite()->SetPlaybackPosition(CurFrameTime, true);
	this->ShadowFlipbook->SetPlaybackPosition(CurFrameTime, true);

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
	UDataTable* AgentsDataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/Databases/Agents/AgentsData.AgentsData"), NULL, LOAD_None, NULL);

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
	if (this->GetVelocity().Size() > MIN_DELTA_VEL)
	{
		if (this->AgentAnimState != EAgentAnimState::MOVING_SE &&
			(this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MIN_SE_ANGLE ||
				this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MAX_SE_ANGLE))
		{
			this->AgentFacingState = EAgentFacingState::SE;
			SetAnimState(EAgentAnimState::MOVING_SE);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_NE &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_NE_ANGLE &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_NE_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::NE;
			SetAnimState(EAgentAnimState::MOVING_NE);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_SW &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_SW_ANGLE&&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_SW_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::SW;
			SetAnimState(EAgentAnimState::MOVING_SW);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_NW &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_NW_ANGLE  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_NW_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::NW;
			SetAnimState(EAgentAnimState::MOVING_NW);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_N &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_N_ANGLE  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_N_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::N;
			SetAnimState(EAgentAnimState::MOVING_N);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_W &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_W_ANGLE  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_W_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::W;
			SetAnimState(EAgentAnimState::MOVING_W);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_S &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_S_ANGLE  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_S_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::S;
			SetAnimState(EAgentAnimState::MOVING_S);
		}
		else if (this->AgentAnimState != EAgentAnimState::MOVING_E &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw > MIN_E_ANGLE &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw - this->GetActorRotation().Clamp().Yaw <= MAX_E_ANGLE)
		{
			this->AgentFacingState = EAgentFacingState::E;
			SetAnimState(EAgentAnimState::MOVING_E);
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
	FVector amount = FVector(FMath::Cos(FMath::DegreesToRadians(45.0f)), -FMath::Sin(FMath::DegreesToRadians(45.0f)), 0.0f) * Stats.Speed * input;
	GetCharacterMovement()->AddInputVector(amount);
}

void AAgent::MoveUp(float input)
{
	FVector amount = FVector(FMath::Sin(FMath::DegreesToRadians(45.0f)), FMath::Cos(FMath::DegreesToRadians(45.0f)), 0.0f) * -Stats.Speed * input;
	GetCharacterMovement()->AddInputVector(amount);
}