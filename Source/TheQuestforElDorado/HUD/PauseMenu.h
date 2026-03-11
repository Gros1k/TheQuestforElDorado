#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenu.generated.h"

UCLASS()
class THEQUESTFORELDORADO_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Resume;
	UPROPERTY(meta = (BindWidget))
	UButton* Settings;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit;
	
	UFUNCTION()
	void OnResume();
	UFUNCTION()
	void OnSettings();
	UFUNCTION()
	void OnExit();
	
};
