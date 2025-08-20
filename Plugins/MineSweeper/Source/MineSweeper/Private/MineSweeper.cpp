// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeper.h"
#include "MineSweeperStyle.h"
#include "MineSweeperCommands.h"
#include "SMineSweeperWidget.h"

#include "Field/FieldSystemNoiseAlgo.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"

static const FName MineSweeperTabName("MineSweeper");

#define LOCTEXT_NAMESPACE "FMineSweeperModule"

void FMineSweeperModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMineSweeperStyle::Initialize();
	FMineSweeperStyle::ReloadTextures();

	FMineSweeperCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMineSweeperCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMineSweeperModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMineSweeperModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MineSweeperTabName, FOnSpawnTab::CreateRaw(this, &FMineSweeperModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMineSweeperTabTitle", "MineSweeper"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMineSweeperModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMineSweeperStyle::Shutdown();

	FMineSweeperCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MineSweeperTabName);
}

TSharedRef<SDockTab> FMineSweeperModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SMineSweeperWidget)
		];
}

void FMineSweeperModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MineSweeperTabName);
}

void FMineSweeperModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMineSweeperCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(
					FMineSweeperCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMineSweeperModule, MineSweeper)