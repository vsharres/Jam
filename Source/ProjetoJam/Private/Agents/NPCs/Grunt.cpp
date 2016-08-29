// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Grunt.h"

AGrunt::AGrunt(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Agent_Type = EAgentType::GRUNT;
}

void AGrunt::InitializeAgent()
{
	AJAMLevelScript* Level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (Level)
	{
		Level->OnSaveGame.AddDynamic(this, &AGrunt::SaveState);
	}


	Super::InitializeAgent();
}

void AGrunt::Interact()
{

}

void AGrunt::SaveState()
{

}


