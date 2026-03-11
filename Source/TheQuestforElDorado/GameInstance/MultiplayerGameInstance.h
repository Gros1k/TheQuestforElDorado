#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerGameInstance.generated.h"

class AMultiplayerState;
class AMultiplayerGameState;
class APlayers;

UCLASS()
class THEQUESTFORELDORADO_API UMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	void CreateGameSession(APlayers* Player);
	void JoinGameSession();
	
	IOnlineSessionPtr OnlineSessionInterface;
	
	IOnlineSubsystem* OnlineSubsystem;
	
	UPROPERTY()
	TArray<APlayerController*> Players;

protected:
	
	virtual void Init() override;
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
private:
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	
};
