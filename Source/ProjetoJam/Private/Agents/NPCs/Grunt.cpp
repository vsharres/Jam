// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Grunt.h"

AGrunt::AGrunt(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Agent_Type = EAgentType::GRUNT;
}


void AGrunt::Interact()
{

}

void AGrunt::SaveState()
{

}

void AGrunt::PostInitializeComponents()
{
	AJAMLevelScript* Level = Cast<AJAMLevelScript>(GetLevel()->GetLevelScriptActor());

	if (Level && !Level->OnAgentSpawned.Contains(this, "SaveState"))
	{
		Level->OnSaveGame.AddDynamic(this, &AGrunt::SaveState);
	}

	Super::PostInitializeComponents();
}

