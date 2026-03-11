#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameSettings.generated.h"

UCLASS()
class THEQUESTFORELDORADO_API UGameSettings : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

	// UPROPERTY(meta = (BindWidget))
	// UButton* CreateSession;
	
	// UFUNCTION()
	// void OnCreateSession();
};
