#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheQuestforElDorado/Includes/Define.h"
#include "TheQuestforElDorado/Main/Players.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	
	if (!Success)
	{
		return false;
	}
	
	if (CreateSession)
	{
		CreateSession->OnClicked.AddDynamic(this, &ThisClass::OnCreateSession);
	}
	if (JoinSession)
	{
		JoinSession->OnClicked.AddDynamic(this, &ThisClass::OnJoinSession);
	}
	if (Settings)
	{
		Settings->OnClicked.AddDynamic(this, &ThisClass::OnSettings);
	}
	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &ThisClass::OnExit);
	}
	
	GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance());
	
	return true;
}

void UMainMenu::OnCreateSession()
{
	if (!Cast<APlayers>(GetOwningPlayerPawn())) return;
	
	if (GameInstance)
	{
		GameInstance->CreateGameSession(Cast<APlayers>(GetOwningPlayerPawn()));
	}
}

void UMainMenu::OnJoinSession()
{
	if (GameInstance)
	{
		GameInstance->JoinGameSession();
	}
}

void UMainMenu::OnSettings()
{
	PRINTTEXT("Settings")
}

void UMainMenu::OnExit()
{
	UKismetSystemLibrary::QuitGame
	(
		GetWorld(),
		GetOwningPlayer(),
		EQuitPreference::Quit,
		false
	);
}
