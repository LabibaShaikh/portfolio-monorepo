#pragma once

#include "CoreMinimal.h"
#include "SWApolloTypes.h"
#include "SWApolloSim.generated.h"

UENUM(BlueprintType)
enum class ERunStatus : uint8
{
    Running,
    Won,
    Lost
};

USTRUCT(BlueprintType)
struct FTurnResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FGameState Before;
    UPROPERTY(BlueprintReadWrite) FGameState After;

    UPROPERTY(BlueprintReadWrite) FString IncidentId;
    UPROPERTY(BlueprintReadWrite) FString ActionId;
    UPROPERTY(BlueprintReadWrite) FString OrdealId; // empty if none

    UPROPERTY(BlueprintReadWrite) ERunStatus Status = ERunStatus::Running;
    UPROPERTY(BlueprintReadWrite) FString StatusReason;
};

UCLASS()
class USWApolloSim : public UObject
{
    GENERATED_BODY()

public:
    // Loaded content
    TArray<FIncidentCard> Incidents;
    TArray<FActionDef> Actions;
    TArray<FOrdealDef> Ordeals;

    // Current run
    FGameState State;
    int32 IncidentIndex = 0;

    // RNG
    FRandomStream Rng;

    bool LoadAllFromContentJson(const FString& IncidentsPath, const FString& ActionsPath, FString& OutError);

    void StartNewRun(int32 Seed);

    // Choose an action by Id (must exist). Advances one turn.
    FTurnResult StepTurn(const FString& ActionId);

private:
    const FIncidentCard* GetNextIncident();
    const FActionDef* FindAction(const FString& ActionId) const;
    const FOrdealDef* MaybeTriggerOrdeal();

    bool CheckActionAllowed(const FActionDef& Action, FString& OutWhyNot) const;

    void ApplyDelta(const FDelta& D);
    void ApplyAction(const FActionDef& Action);
    void ApplyIncident(const FIncidentCard& Incident);
    void ApplyOrdeal(const FOrdealDef& Ordeal);

    void ApplyDerivedRulesFromFlags(const FIncidentCard& Incident);

    void UpdateDayFromTurn();
    void EvaluateWinLose(ERunStatus& OutStatus, FString& OutReason) const;
};
