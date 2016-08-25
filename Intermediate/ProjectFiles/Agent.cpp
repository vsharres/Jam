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
	AgentFacingState = EAgentFacingState::DOWN;
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
		case EAgentFacingState::UP:
			this->GetSprite()->SetFlipbook(IdleUpAnimation);
			this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
			break;
		case EAgentFacingState::DOWN:
			this->GetSprite()->SetFlipbook(IdleDownAnimation);
			this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
			break;
		case EAgentFacingState::RIGHT:
			this->GetSprite()->SetFlipbook(IdleRightAnimation);
			this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
			break;
		case EAgentFacingState::LEFT:
			this->GetSprite()->SetFlipbook(IdleRightAnimation);
			this->GetSprite()->SetRelativeRotation(INVERTED_ROTATION);
			break;
		default:
			break;
		}
		break;
	case EAgentAnimState::MOVING_RIGHT:
		this->GetSprite()->SetFlipbook(Move_Right_Animation);
		this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
		break;
	case EAgentAnimState::MOVING_LEFT:
		this->GetSprite()->SetFlipbook(Move_Right_Animation);
		this->GetSprite()->SetRelativeRotation(INVERTED_ROTATION);
		break;
	case EAgentAnimState::MOVING_DOWN:
		this->GetSprite()->SetFlipbook(Move_Down_Animation);
		this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
		break;
	case EAgentAnimState::MOVING_UP:
		this->GetSprite()->SetFlipbook(Move_Up_Animation);
		this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
		break;
	default:
		this->GetSprite()->SetFlipbook(IdleDownAnimation);
		this->GetSprite()->SetRelativeRotation(NORMAL_ROTATION);
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

void AAgent::InitializeAgent()
{
	//Get statements from file and add them in the database, initialize behavior if AI and update faction.
}

void AAgent::UpdateFlipbook()
{
	if (this->GetVelocity().X > MAX_DELTA_VEL && this->GetVelocity().Y < MIN_DELTA_VEL)
	{
		this->AgentFacingState = EAgentFacingState::RIGHT;
		SetAnimState(EAgentAnimState::MOVING_RIGHT);
	}
	else if (this->GetVelocity().X < MIN_DELTA_VEL && this->GetVelocity().Y > MAX_DELTA_VEL)
	{
		this->AgentFacingState = EAgentFacingState::UP;
		SetAnimState(EAgentAnimState::MOVING_UP);
	}
	else if (this->GetVelocity().X < MIN_DELTA_VEL && this->GetVelocity().Y < -MAX_DELTA_VEL)
	{
		SetAnimState(EAgentAnimState::MOVING_DOWN);
		this->AgentFacingState = EAgentFacingState::DOWN;
	}
	else if (this->GetVelocity().X < -MAX_DELTA_VEL && this->GetVelocity().Y < MIN_DELTA_VEL)
	{
		SetAnimState(EAgentAnimState::MOVING_LEFT);
		this->AgentFacingState = EAgentFacingState::LEFT;
	}
	else
	{
		SetAnimState(EAgentAnimState::IDLE);
	}
}

void AAgent::MoveRight(float input)
{
	GetCharacterMovement()->AddInputVector(FVector(input, 0, 0));
}

void AAgent::MoveUp(float input)
{
	GetCharacterMovement()->AddInputVector(FVector(0, input, 0));
}