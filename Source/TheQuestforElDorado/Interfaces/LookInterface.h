#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LookInterface.generated.h"

UINTERFACE(MinimalAPI)
class ULookInterface : public UInterface
{
	GENERATED_BODY()
};

class THEQUESTFORELDORADO_API ILookInterface
{
	GENERATED_BODY()
	
public:
	AActor* Look(AActor* Observer);
};
