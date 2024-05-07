// Copyright Epic Games, Inc. All Rights Reserved.

#include "Reproduce.h"
#include "ReproduceStyle.h"
#include "ReproduceCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ReproduceTabName("Reproduce");

#define LOCTEXT_NAMESPACE "FReproduceModule"

void FReproduceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FReproduceStyle::Initialize();
	FReproduceStyle::ReloadTextures();

	FReproduceCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FReproduceCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FReproduceModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FReproduceModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ReproduceTabName, FOnSpawnTab::CreateRaw(this, &FReproduceModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FReproduceTabTitle", "Reproduce"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FReproduceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FReproduceStyle::Shutdown();

	FReproduceCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ReproduceTabName);
}

TSharedRef<SDockTab> FReproduceModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	TSharedRef<STextBlock> NotSimpleTextBlock = SNew(STextBlock)
	.SimpleTextMode(false)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.InitialStyle"))
	.Text(INVTEXT("NotSimple"))	
	;

	NotSimpleTextBlock->SetOnMouseEnter(FNoReplyPointerEventHandler::CreateStatic(&FReproduceModule::OnMouseEnterTextBlock, NotSimpleTextBlock));
	NotSimpleTextBlock->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateStatic(&FReproduceModule::OnMouseLeaveTextBlock, NotSimpleTextBlock));

	TSharedRef<STextBlock> SimpleTextBlock = SNew(STextBlock)
	.SimpleTextMode(true)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.InitialStyle"))
	.Text(INVTEXT("Simple"))
	;

	SimpleTextBlock->SetOnMouseEnter(FNoReplyPointerEventHandler::CreateStatic(&FReproduceModule::OnMouseEnterTextBlock, SimpleTextBlock));
	SimpleTextBlock->SetOnMouseLeave(FSimpleNoReplyPointerEventHandler::CreateStatic(&FReproduceModule::OnMouseLeaveTextBlock, SimpleTextBlock));

	
	TSharedRef<STextBlock> ExampleNotSimpleDottedUnderlineAndRed = SNew(STextBlock)
	.SimpleTextMode(false)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.DottedUnderlineAndBlue"))
	.Text(INVTEXT("[A] Example NotSimple\nDotted Underline Blue"))	
	;

	TSharedRef<STextBlock> ExampleNotSimpleNotDottedUnderlineAndBlue = SNew(STextBlock)
	.SimpleTextMode(false)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.NotDottedUnderlineAndRed"))
	.Text(INVTEXT("[B] Example NotSimple\nNotDotted Underline Red"))	
	;

	TSharedRef<STextBlock> ExampleSimpleDottedUnderlineAndRed = SNew(STextBlock)
	.SimpleTextMode(true)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.DottedUnderlineAndBlue"))
	.Text(INVTEXT("[C] Example Simple\nDotted Underline Blue"))
	;
	
	TSharedRef<STextBlock> ExampleSimpleNotDottedUnderlineAndBlue = SNew(STextBlock)
	.SimpleTextMode(true)
	.TextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.NotDottedUnderlineAndRed"))
	.Text(INVTEXT("[D] Example Simple\nNotDotted Underline Red"))
	;

	
	TSharedRef<SDockTab> Result = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::Foreground))
							[
								NotSimpleTextBlock
							]
						]
					]
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::ForegroundHover))
							[
								ExampleNotSimpleDottedUnderlineAndRed
							]
						]
					]
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::Foreground))
							[
								ExampleNotSimpleNotDottedUnderlineAndBlue
							]
						]
					]
				]
				+SVerticalBox::Slot()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::ForegroundHover))
							[
								SimpleTextBlock
							]
						]	
					]
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::Foreground))
							[
								ExampleSimpleDottedUnderlineAndRed
							]
						]
					]
					+SHorizontalBox::Slot()
					[
						SNew(SBox)
						.HeightOverride(50.0f)
						.WidthOverride(200.0f)					
						[
							SNew(SBorder)
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
							.BorderBackgroundColor(FSlateColor(FStyleColors::ForegroundHover))
							[
								ExampleSimpleNotDottedUnderlineAndBlue
							]
						]
					]
				]
			]
		];

	return Result;
}

void FReproduceModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ReproduceTabName);
}

void FReproduceModule::OnMouseEnterTextBlock(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, const TSharedRef<STextBlock> InTextBlock)
{
	InTextBlock->SetTextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.NotDottedUnderlineAndRed"));
	InTextBlock->SetText(INVTEXT("MouseEnter"));
}

void FReproduceModule::OnMouseLeaveTextBlock(const FPointerEvent& InPointerEvent, const TSharedRef<STextBlock> InTextBlock)
{
	InTextBlock->SetTextStyle(&FReproduceStyle::Get().GetWidgetStyle<FTextBlockStyle>("ReproduceStyle.DottedUnderlineAndBlue"));
	InTextBlock->SetText(INVTEXT("MouseLeave"));
}

void FReproduceModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FReproduceCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FReproduceCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FReproduceModule, Reproduce)