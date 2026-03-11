#pragma once

#define PRINTBOOL(bool) if(GEngine){GEngine->AddOnScreenDebugMessage(1,30.f,FColor::Cyan, FString(bool ? TEXT("true") : TEXT("false")));}   //wypisywanie bool
#define PRINT(type, x) if(GEngine){GEngine->AddOnScreenDebugMessage(1,30.f,FColor::Cyan, FString::Printf(TEXT(type), x));}  //wypisywanie zmiennej o podanym typie
#define PRINTTEXT(text) if(GEngine){GEngine->AddOnScreenDebugMessage(1,30.f,FColor::Cyan, text);}   //wypisywanie stringa
#define PRINTVECTOR(vector) if(GEngine){GEngine->AddOnScreenDebugMessage(1,30.f,FColor::Cyan, FString::Printf(TEXT("X = %f, Y = %f, Z = %f"), vector.X, vector.Y, vector.Z));}	//wypisanie wektora
#define PRINTROTATOR(rotator) if(GEngine){GEngine->AddOnScreenDebugMessage(1,30.f,FColor::Cyan, FString::Printf(TEXT("Pitch = %f, Yaw = %f, Roll = %f"), rotator.Pitch, rotator.Yaw, rotator.Roll));}	//wypisanie rotacji

#define TOSTACK(Cards) Cards->ServerMoveActor(Stack->GetComponentLocation()); Cards->ServerRotateActor(FRotator(Stack->GetComponentRotation().Pitch + 180.f, Stack->GetComponentRotation().Yaw, Stack->GetComponentRotation().Roll));
#define TOUSED(Cards) Cards->ServerMoveActor(FVector(Used->GetComponentLocation().X, Used->GetComponentLocation().Y, Used->GetComponentLocation().Z + OwningPlayer->GetPlayerState<AMultiplayerState>()->CardsUsed.Num())); Cards->ServerRotateActor(Used->GetComponentRotation());
#define CHANGESIDE(Cards) Cards->ServerRotateActor(FRotator(Cards->GetActorRotation().Pitch + 180.f, Cards->GetActorRotation().Yaw, Cards->GetActorRotation().Roll));
#define CARDUP(Card) Card->ServerMoveActor(Card->GetActorLocation() - Card->GetActorRightVector() * 30.f);
#define CARDDOWN(Card) Card->ServerMoveActor(Card->GetActorLocation() + Card->GetActorRightVector() * 30.f);