#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TheQuestforElDorado/Interfaces/LookInterface.h"
#include "Expeditioner.generated.h"

class UEnhancedInputComponent;

UCLASS()
class THEQUESTFORELDORADO_API AExpeditioner : public APawn
{
	GENERATED_BODY()
	
	ILookInterface* LookInterface;
	
protected:
	virtual void BeginPlay() override;

public:	
	AExpeditioner();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveToField(AActor* Observer);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Expeditioner;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* CameraPlace;

	UFUNCTION(Server, Reliable)
	void ServerMoveActor(FVector NewLocation);
};
