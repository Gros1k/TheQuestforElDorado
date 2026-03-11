#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plate.generated.h"

UCLASS()
class THEQUESTFORELDORADO_API APlate : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	APlate();
	virtual void Tick(float DeltaTime) override;

};
