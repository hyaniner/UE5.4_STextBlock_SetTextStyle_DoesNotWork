// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReproduceStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FReproduceStyle::StyleInstance = nullptr;

void FReproduceStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FReproduceStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FReproduceStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ReproduceStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FReproduceStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ReproduceStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Reproduce")->GetBaseDir() / TEXT("Resources"));

	Style->Set("Reproduce.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	const FString EngineSlateContentDir = FPaths::EngineContentDir() / TEXT("Slate");
	const FString EngineEditorSlateContentDir = FPaths::EngineContentDir() / TEXT("Editor/Slate");
	
	Style->SetCoreContentRoot(EngineSlateContentDir);
	Style->SetContentRoot(EngineEditorSlateContentDir);
	
	FTextBlockStyle BaseTextBlockStyle = FCoreStyle::Get().GetWidgetStyle< FTextBlockStyle >("NormalText");

	Style->Set( "ReproduceStyle.InitialStyle", FTextBlockStyle(BaseTextBlockStyle)
		.SetColorAndOpacity(FSlateColor(FColor::Black))
	);
	
	FSlateBorderBrush* DottedUnderline = new BORDER_BRUSH("Old/HyperlinkDotted", FMargin(0.f, 0.f, 0.f, 3.f / 16.0f));
	Style->Set( "ReproduceStyle.DottedUnderlineBrush", DottedUnderline);
	
	FSlateBorderBrush* NotDottedUnderline = new BORDER_BRUSH("Old/HyperlinkUnderline", FMargin(0.f, 0.f, 0.f, 3.f / 16.0f));
	Style->Set( "ReproduceStyle.NotDottedUnderlineBrush", NotDottedUnderline);

	Style->Set( "ReproduceStyle.DottedUnderlineAndBlue", FTextBlockStyle(BaseTextBlockStyle)
		.SetUnderlineBrush(*DottedUnderline)
		.SetColorAndOpacity(FSlateColor(FColor::Blue))
	);
	
	Style->Set( "ReproduceStyle.NotDottedUnderlineAndRed", FTextBlockStyle(BaseTextBlockStyle)
		.SetUnderlineBrush(*NotDottedUnderline)
		.SetColorAndOpacity(FSlateColor(FColor::Red))
	);

	return Style;
}

void FReproduceStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FReproduceStyle::Get()
{
	return *StyleInstance;
}
