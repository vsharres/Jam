// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "PaperFlipbookComponent.h"
#include "Public/Agents/Agent.h"


AAgent::AAgent(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{
	Stats = FAgentStats();
	Agent_Type = EAgentType::GRUNT;
	AgentAnimState = EAgentAnimState::IDLE;
	AgentFacingState = EAgentFacingState::S;

	this->GetSprite()->SetFlipbook(IdleSAnimation);
}

ALocation* AAgent::GetLocation()
{
	return Cur_Location.Get();
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
	switch (newState)
	{
	case EAgentAnimState::IDLE:
		switch (AgentFacingState)
		{
		case EAgentFacingState::N:
			this->GetSprite()->SetFlipbook(IdleNAnimation);
			break;
		case EAgentFacingState::NW:
			this->GetSprite()->SetFlipbook(IdleNWAnimation);
			break;
		case EAgentFacingState::W:
			this->GetSprite()->SetFlipbook(IdleWAnimation);
			break;
		case EAgentFacingState::SW:
			this->GetSprite()->SetFlipbook(IdleSWAnimation);
			break;
		case EAgentFacingState::S:
			this->GetSprite()->SetFlipbook(IdleSAnimation);
			break;
		case EAgentFacingState::SE:
			this->GetSprite()->SetFlipbook(IdleSEAnimation);
			break;
		case EAgentFacingState::E:
			this->GetSprite()->SetFlipbook(IdleEAnimation);
			break;
		case EAgentFacingState::NE:
			this->GetSprite()->SetFlipbook(IdleNEAnimation);
			break;
		default:
			this->GetSprite()->SetFlipbook(IdleSAnimation);
			break;
		}
		break;
	case EAgentAnimState::MOVING_N:
		this->GetSprite()->SetFlipbook(MoveNAnimation);
		break;
	case EAgentAnimState::MOVING_NW:
		this->GetSprite()->SetFlipbook(MoveNWAnimation);
		break;
	case EAgentAnimState::MOVING_W:
		this->GetSprite()->SetFlipbook(MoveWAnimation);
		break;
	case EAgentAnimState::MOVING_SW:
		this->GetSprite()->SetFlipbook(MoveSWAnimation);
		break;
	case EAgentAnimState::MOVING_S:
		this->GetSprite()->SetFlipbook(MoveSAnimation);
		break;
	case EAgentAnimState::MOVING_SE:
		this->GetSprite()->SetFlipbook(MoveSEAnimation);
		break;
	case EAgentAnimState::MOVING_E:
		this->GetSprite()->SetFlipbook(MoveEAnimation);
		break;
	case EAgentAnimState::MOVING_NE:
		this->GetSprite()->SetFlipbook(MoveNEAnimation);
		break;
	default:
		this->GetSprite()->SetFlipbook(IdleSAnimation);
		break;
	}

	AgentAnimState = newState;
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();

	Database_Ref = AStatementDatabase::GetStatementDatabase(this);
}

void AAgent::Tick(float DeltaSeconds)
{
	UpdateFlipbook();

	Super::Tick(DeltaSeconds);
}


void AAgent::OnDamaged(float Damage)
{

}

void AAgent::InitializeAgent()
{
	//Get statements from file and add them in the database, initialize behavior if AI and update faction.
}

void AAgent::UpdateFlipbook()
{
	if (this->GetVelocity().Size() > MIN_DELTA_VEL)
	{
		if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 10.0f ||
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 350.0f)
		{
			this->AgentFacingState = EAgentFacingState::SE;
			SetAnimState(EAgentAnimState::MOVING_SE);
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 260.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 280.0f)
		{
			this->AgentFacingState = EAgentFacingState::NE;
			SetAnimState(EAgentAnimState::MOVING_NE);
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 80.0f &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 100.0f)
		{
			SetAnimState(EAgentAnimState::MOVING_SW);
			this->AgentFacingState = EAgentFacingState::SW;
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 170.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 190.0f)
		{
			SetAnimState(EAgentAnimState::MOVING_NW);
			this->AgentFacingState = EAgentFacingState::NW;
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 215.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 235.0f)
		{
			SetAnimState(EAgentAnimState::MOVING_N);
			this->AgentFacingState = EAgentFacingState::N;
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 125.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 145.0f)
		{
			SetAnimState(EAgentAnimState::MOVING_W);
			this->AgentFacingState = EAgentFacingState::W;
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 35.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 55.0f)
		{
			SetAnimState(EAgentAnimState::MOVING_S);
			this->AgentFacingState = EAgentFacingState::S;
		}
		else if (this->GetVelocity().ToOrientationRotator().Clamp().Yaw >= 305.0f  &&
			this->GetVelocity().ToOrientationRotator().Clamp().Yaw <= 325.0f)
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