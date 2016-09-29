// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "JamLibrary.h"
#include "Statement.h"
#include "StatementDatabase.h"
#include "JAMLevelScript.h"

#define COLLISION_FADEOBJECT ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_AGENT ECollisionChannel::ECC_GameTraceChannel2

#define TRACE_SPHERERADIUS_DEFAULT 15.0f

#define TILE_L1W1_EXTENT FVector(50.0f,50.0f,50.0f)
#define TILE_L2W1_EXTENT FVector(100.0f,50.0f,50.0f)
#define TILE_L2W2_EXTENT FVector(100.0f,100.0f,50.0f)

#define TOPDOWN_ROTATION FRotator(0.0f,00.0f,-90.0f)
#define SHADOW_ROTATION FRotator(0.0f,-30.0f,0.0f)

DECLARE_LOG_CATEGORY_EXTERN(AgentLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(DatabaseLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(StatementLog, Log, All);


