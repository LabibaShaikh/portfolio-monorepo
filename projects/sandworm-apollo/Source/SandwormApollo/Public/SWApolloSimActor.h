#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWApolloSim.h"
#include "SWApolloSimActor.generated.h"

UCLASS()
class ASWApolloSimActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category="SandwormApollo") int32 Seed = 1337;

    // Relative to Content folder (e.g., "Data/incidents.json")
    UPROPERTY(EditAnywhere, Category="SandwormApollo") FString IncidentsJson = TEXT("Data/incidents.json");
    UPROPERTY(EditAnywhere, Category="SandwormApollo") FString ActionsJson   = TEXT("Data/actions.json");

    UPROPERTY(EditAnywhere, Category="SandwormApollo") int32 DebugTurnsToRun = 6;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY() USWApolloSim* Sim = nullptr;
};
