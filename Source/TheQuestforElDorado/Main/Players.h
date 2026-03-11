#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheQuestforElDorado/GameInstance/MultiplayerGameInstance.h"
#include "Players.generated.h"

class UMainMenu;
class ATargetPoint;
class AMultiplayerGameState;
class AMultiplayerState;
class AMarket;

UCLASS()
class THEQUESTFORELDORADO_API APlayers : public ACharacter
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

public:	
	
	APlayers();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void SpawnPlatesAndExpeditioners();
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void Choose();
	void EndTurn();
	void ToPlate();
	void ToExpeditioner();
	void ToMarket();
	
	UPROPERTY()
	AMarket* Market;
	
	UPROPERTY()
	UMultiplayerGameInstance* GameInstance;
	
	UPROPERTY()
	AMultiplayerGameState* GameState;
	
	UPROPERTY()
	AMultiplayerState* MultiplayerState;

	bool bInMatch = false;
	
	UPROPERTY()
	TArray<AActor*> TargetPoints;
	
	TArray<FString> Colors = {"Gold", "Blue", "Red", "White"};
	
	UPROPERTY()
	TArray<APlayers*> Players;
	
	UPROPERTY(EditDefaultsOnly, Category = "Plates")
	TArray<TSubclassOf<AActor>> Plates;
	UPROPERTY(EditDefaultsOnly, Category = "Expeditioners")
	TArray<TSubclassOf<AActor>> Expeditioners;
	UPROPERTY(EditDefaultsOnly, Category = "Barriers")
	TArray<TSubclassOf<AActor>> Barriers;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UMainMenu> MenuClass;
	
	UPROPERTY()
	UMainMenu* Menu;
};
