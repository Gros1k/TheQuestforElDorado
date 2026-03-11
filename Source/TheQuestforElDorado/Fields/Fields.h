#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheQuestforElDorado/Attributes/FieldAttributes.h"
#include "Fields.generated.h"

UCLASS()
class THEQUESTFORELDORADO_API AFields : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AFields();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Field;
	
	UPROPERTY(VisibleAnywhere)
	UFieldAttributes* Attributes;
};
