#include "SWApolloSimActor.h"

void ASWApolloSimActor::BeginPlay()
{
    Super::BeginPlay();

    Sim = NewObject<USWApolloSim>(this);

    FString Err;
    if (!Sim->LoadAllFromContentJson(IncidentsJson, ActionsJson, Err))
    {
        UE_LOG(LogTemp, Error, TEXT("[SandwormApollo] Load failed: %s"), *Err);
        return;
    }

    Sim->StartNewRun(Seed);

    UE_LOG(LogTemp, Display, TEXT("=== Sandworm Apollo Debug Run (Seed=%d) ==="), Seed);

    for (int32 t = 0; t < DebugTurnsToRun; t++)
    {
        // Pick a random action each turn (validity checked by sim)
        const int32 idx = Sim->Rng.RandRange(0, Sim->Actions.Num() - 1);
        const FString ActionId = Sim->Actions[idx].Id;

        FTurnResult R = Sim->StepTurn(ActionId);

        UE_LOG(LogTemp, Display,
            TEXT("[Turn %d] Incident=%s Action=%s Ordeal=%s | Inf=%.1f Mut=%.1f Pow=%.1f Int=%.1f Trust=%.1f CM=%.1f | Status=%d (%s)"),
            R.Before.Turn,
            *R.IncidentId,
            *R.ActionId,
            *R.OrdealId,
            R.After.Infection, R.After.Mutation, R.After.Power, R.After.Integrity, R.After.Trust, R.After.Countermeasure,
            (int32)R.Status,
            *R.StatusReason
        );

        if (R.Status != ERunStatus::Running)
        {
            UE_LOG(LogTemp, Warning, TEXT("=== Run ended: %s ==="), *R.StatusReason);
            break;
        }
    }
}
