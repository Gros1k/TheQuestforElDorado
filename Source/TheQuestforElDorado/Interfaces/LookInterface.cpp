#include "LookInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheQuestforElDorado/Includes/Define.h"

AActor* ILookInterface::Look(AActor* Observer)
{
	//miejsca gdzie patrzy aktor
	/**/const FVector Start = Observer->GetActorLocation();
	/**/const FVector End = Start + Observer->GetActorRotation().Vector() * 10000.0f;
	//
	
	//stworzenie aktorów do ignorowania i dodaniu do nich tego aktora
	/**/TArray<AActor*> ActorToIgnore;
	//
	
	FHitResult BoxHit;	//rezultat trafienia
   
	UKismetSystemLibrary::BoxTraceSingle(	//sprawdzianie czy patrzy na jakieś pole
		Observer,
		Start,
		End,
		FVector(2, 2, 2),
		Observer->GetActorRotation(),
		TraceTypeQuery1,
		false,
		ActorToIgnore,
		EDrawDebugTrace::None,
		BoxHit,
		true,
		FColor::Red
		);
	
	if (BoxHit.GetActor() != nullptr)
	{
		return BoxHit.GetActor();
	}
	return nullptr;
}
