#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

class UMultiplayerGameInstance;

UCLASS()
class THEQUESTFORELDORADO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CreateSession;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinSession;
	UPROPERTY(meta = (BindWidget))
	UButton* Settings;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit;
	
	UFUNCTION()
	void OnCreateSession();
	UFUNCTION()
	void OnJoinSession();
	UFUNCTION()
	void OnSettings();
	UFUNCTION()
	void OnExit();
	
	UPROPERTY()
	UMultiplayerGameInstance* GameInstance;
};
