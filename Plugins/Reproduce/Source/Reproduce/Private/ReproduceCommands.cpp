// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReproduceCommands.h"

#define LOCTEXT_NAMESPACE "FReproduceModule"

void FReproduceCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Reproduce", "Bring up Reproduce window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
