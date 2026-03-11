#include "PauseMenu.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	
	if (!Success)
	{
		return false;
	}
	
	if (Resume)
	{
		Resume->OnClicked.AddDynamic(this, &ThisClass::OnResume);
	}
	if (Settings)
	{
		Settings->OnClicked.AddDynamic(this, &ThisClass::OnSettings);
	}
	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &ThisClass::OnExit);
	}
	
	return true;
}

void UPauseMenu::OnResume()
{
	
}

void UPauseMenu::OnSettings()
{
	
}

void UPauseMenu::OnExit()
{

}
