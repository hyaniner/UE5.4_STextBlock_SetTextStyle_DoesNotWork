// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ReproduceStyle.h"

class FReproduceCommands : public TCommands<FReproduceCommands>
{
public:

	FReproduceCommands()
		: TCommands<FReproduceCommands>(TEXT("Reproduce"), NSLOCTEXT("Contexts", "Reproduce", "Reproduce Plugin"), NAME_None, FReproduceStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};