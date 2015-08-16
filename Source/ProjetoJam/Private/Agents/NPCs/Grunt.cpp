// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Grunt.h"

AGrunt::AGrunt(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	Agent_Type = EAgentType::GRUNT;
}
