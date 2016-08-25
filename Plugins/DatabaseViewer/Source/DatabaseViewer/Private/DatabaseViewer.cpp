// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DatabaseViewerPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "DatabaseViewerStyle.h"
#include "DatabaseViewerCommands.h"

#include "LevelEditor.h"

static const FName DatabaseViewerTabName("DatabaseViewer");

#define LOCTEXT_NAMESPACE "FDatabaseViewerModule"

void FDatabaseViewerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDatabaseViewerStyle::Initialize();
	FDatabaseViewerStyle::ReloadTextures();

	FDatabaseViewerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDatabaseViewerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FDatabaseViewerModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FDatabaseViewerModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FDatabaseViewerModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FDatabaseViewerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FDatabaseViewerStyle::Shutdown();

	FDatabaseViewerCommands::Unregister();
}

void FDatabaseViewerModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FDatabaseViewerModule::PluginButtonClicked()")),
							FText::FromString(TEXT("DatabaseViewer.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FDatabaseViewerModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FDatabaseViewerCommands::Get().PluginAction);
}

void FDatabaseViewerModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FDatabaseViewerCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDatabaseViewerModule, DatabaseViewer)