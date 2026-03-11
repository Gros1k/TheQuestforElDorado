#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FieldAttributes.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEQUESTFORELDORADO_API UFieldAttributes : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UFieldAttributes();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	int Jungle = 0;
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	int Village = 0;
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	int River = 0;
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	int Camp = 0;
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	int Rubble = 0;
	UPROPERTY(EditAnywhere, Category="Field Attribiutes")
	bool Mountain = false;
};
