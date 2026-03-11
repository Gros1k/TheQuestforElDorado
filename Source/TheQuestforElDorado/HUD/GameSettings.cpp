#include "GameSettings.h"
#include "Components/Button.h"

bool UGameSettings::Initialize()
{
	bool Success = Super::Initialize();
	
	if (!Success)
	{
		return false;
	}
	
	// if (CreateSession)
	// {
	// 	CreateSession->OnClicked.AddDynamic(this, &ThisClass::OnCreateSession);
	// }
	
	return true;
}