#include "AagPlayGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

AagPlayGameMode::AagPlayGameMode()
	:
	GenerationTime(30.f), CurGeneration(1)
{
}

void AagPlayGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float PrevTime = CurGenerationTime;
	CurGenerationTime -= DeltaSeconds;
	
}

void AagPlayGameMode::GameStart()
{
}

void AagPlayGameMode::GenerationStart()
{
	CurGenerationTime = GenerationTime;
	
	SpawnFish();
	IncreaseGeneration();
}

void AagPlayGameMode::GenerationEnd()
{
}

void AagPlayGameMode::IncreaseGeneration()
{
	CurGeneration += 1;
	OnGenerationChanged.Broadcast(CurGeneration);
}

void AagPlayGameMode::SpawnFish()
{
	APlayerStart* StartPoint = GetPlayerStartPoint();
	if(StartPoint == nullptr || GetWorld() == nullptr) [[unlikely]]
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	APawn* FishPawn = GetWorld()->SpawnActor<APawn>(StartPoint->GetActorLocation(), StartPoint->GetActorRotation(), SpawnParameters);
	if(FishPawn)
	{
		
	}
}

APlayerStart* AagPlayGameMode::GetPlayerStartPoint()
{
	APlayerStart* FoundPlayerStart = nullptr;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (IsValid(PlayerStart))
		{
			FoundPlayerStart = PlayerStart;
			break;
		}
	}
	return FoundPlayerStart;
}
