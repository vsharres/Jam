// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "DatabaseViewerStyle.h"

class FDatabaseViewerCommands : public TCommands<FDatabaseViewerCommands>
{
public:

	FDatabaseViewerCommands()
		: TCommands<FDatabaseViewerCommands>(TEXT("DatabaseViewer"), NSLOCTEXT("Contexts", "DatabaseViewer", "DatabaseViewer Plugin"), NAME_None, FDatabaseViewerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
