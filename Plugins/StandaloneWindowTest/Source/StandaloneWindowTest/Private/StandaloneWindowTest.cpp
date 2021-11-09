// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowTest.h"
#include "StandaloneWindowTestStyle.h"
#include "StandaloneWindowTestCommands.h"
#include "LevelEditor.h"
#include "Quests.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Engine/Selection.h"

static const FName StandaloneWindowTestTabName("StandaloneWindowTest");

#define LOCTEXT_NAMESPACE "FStandaloneWindowTestModule"

void FStandaloneWindowTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWindowTestStyle::Initialize();
	FStandaloneWindowTestStyle::ReloadTextures();

	FStandaloneWindowTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowTestTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowTestTabTitle", "StandaloneWindowTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FLevelEditorModule & LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FStandaloneWindowTestModule::AddMenuExtension));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FStandaloneWindowTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowTestStyle::Shutdown();

	FStandaloneWindowTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowTestTabName);
}

TSharedRef<SDockTab> FStandaloneWindowTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText Text = FText::FromString(TEXT("Get Quests"));
	FText QuestDescription = FText::FromString(TEXT("Quest Description: "));
	FText Description = FText::FromString(TEXT("здесь будет описание квеста: "));
	
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FStandaloneWindowTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("StandaloneWindowTest.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				//SNew(STextBlock)
				//.Text(WidgetText)
				SNew(SButton)
				.OnClicked_Raw(this, &FStandaloneWindowTestModule::GetQuests)
				[
					SNew(STextBlock)
					.Text(Text)					
				]
				
				
		    ]

		    
		];

}

void FStandaloneWindowTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowTestTabName);
}

void FStandaloneWindowTestModule::AddMenuExtension(FMenuBuilder& Build)
{
	Build.AddMenuEntry(FStandaloneWindowTestCommands::Get().OpenPluginWindow);
}

FReply FStandaloneWindowTestModule::GetQuests()
{
	
	if(GEditor)
	{
		for (FSelectionIterator Iter((GEditor->GetSelectedActorIterator())); Iter; ++Iter)
		{
			//AQuests* Quests = Cast<AQuests>(Cast<AActor>(*Iter));
			AActor* Actor = Cast<AActor>(*Iter);


			if (Actor)
			{
				AQuests * Quests = Cast<AQuests>(Actor);
				
				FText Description = Quests->GetDescription();
			}

			/*if (Quests)
			{
				FText FL = Quests->Description;
				UE_LOG (LogTemp, Warning, TEXT("Qusest %s, Desription %s"),Quests->GetName(), Quests->Description);
			}*/
		}		
	}
	
	return FReply::Handled();
}

void FStandaloneWindowTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowTestModule, StandaloneWindowTest)