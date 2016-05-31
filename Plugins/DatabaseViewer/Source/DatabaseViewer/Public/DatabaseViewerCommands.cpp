// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DatabaseViewerPrivatePCH.h"
#include "DatabaseViewerCommands.h"

#define LOCTEXT_NAMESPACE "FDatabaseViewerModule"

void FDatabaseViewerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "DatabaseViewer", "Execute DatabaseViewer action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
