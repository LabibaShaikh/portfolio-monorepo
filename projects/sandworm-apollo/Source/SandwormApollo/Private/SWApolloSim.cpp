#include "SWApolloSim.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

static bool GetBool(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, bool Default=false)
{
    bool Val = Default;
    if (Obj.IsValid() && Obj->HasTypedField<EJson::Boolean>(Key)) Obj->TryGetBoolField(Key, Val);
    return Val;
}

static float GetNumber(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, float Default=0.f)
{
    double Val = Default;
    if (Obj.IsValid() && Obj->HasField(Key)) Obj->TryGetNumberField(Key, Val);
    return (float)Val;
}

static FString GetString(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, const FString& Default=TEXT(""))
{
    FString Val = Default;
    if (Obj.IsValid() && Obj->HasField(Key)) Obj->TryGetStringField(Key, Val);
    return Val;
}

static FDelta ParseDelta(const TSharedPtr<FJsonObject>& Obj)
{
    FDelta D;
    if (!Obj.IsValid()) return D;
    D.Infection = GetNumber(Obj, TEXT("infection"), 0.f);
    D.Mutation  = GetNumber(Obj, TEXT("mutation"), 0.f);
    D.Power     = GetNumber(Obj, TEXT("power"), 0.f);
    D.Integrity = GetNumber(Obj, TEXT("integrity"), 0.f);
    D.Trust     = GetNumber(Obj, TEXT("trust"), 0.f);
    D.Countermeasure = GetNumber(Obj, TEXT("countermeasure"), 0.f);
    return D;
}

static bool LoadJsonArrayFile(const FString& AbsPath, TArray<TSharedPtr<FJsonValue>>& OutArray, FString& OutError)
{
    FString Raw;
    if (!FFileHelper::LoadFileToString(Raw, *AbsPath))
    {
        OutError = FString::Printf(TEXT("Failed to read file: %s"), *AbsPath);
        return false;
    }

    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Raw);
    if (!FJsonSerializer::Deserialize(Reader, OutArray))
    {
        OutError = FString::Printf(TEXT("Failed to parse JSON array: %s"), *AbsPath);
        return false;
    }
    return true;
}

bool USWApolloSim::LoadAllFromContentJson(const FString& IncidentsPath, const FString& ActionsPath, FString& OutError)
{
    Incidents.Empty();
    Actions.Empty();
    Ordeals.Empty();

    // Content directory note: in packaged builds, reading from Content is not always ideal.
    // For this hackathon slice, use ProjectContentDir + loose JSON files.
    const FString IncAbs = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / IncidentsPath);
    const FString ActAbs = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / ActionsPath);

    // incidents.json must be an array
    {
        TArray<TSharedPtr<FJsonValue>> Arr;
        if (!LoadJsonArrayFile(IncAbs, Arr, OutError)) return false;

        for (const TSharedPtr<FJsonValue>& V : Arr)
        {
            const TSharedPtr<FJsonObject> Obj = V->AsObject();
            if (!Obj.IsValid()) continue;

            FIncidentCard I;
            I.Id        = GetString(Obj, TEXT("id"));
            I.Title     = GetString(Obj, TEXT("title"));
            I.Narrative = GetString(Obj, TEXT("narrative"));

            const TSharedPtr<FJsonObject>* EvidenceObj = nullptr;
            if (Obj->TryGetObjectField(TEXT("evidence"), EvidenceObj) && EvidenceObj && EvidenceObj->IsValid())
            {
                I.Evidence.Vitals      = GetString(*EvidenceObj, TEXT("vitals"));
                I.Evidence.Lab         = GetString(*EvidenceObj, TEXT("lab"));
                I.Evidence.Environment = GetString(*EvidenceObj, TEXT("environment"));
                I.Evidence.Comms       = GetString(*EvidenceObj, TEXT("comms"));
            }

            const TSharedPtr<FJsonObject>* FlagsObj = nullptr;
            if (Obj->TryGetObjectField(TEXT("flags"), FlagsObj) && FlagsObj && FlagsObj->IsValid())
            {
                I.Flags.bSensorCompromised = GetBool(*FlagsObj, TEXT("sensorCompromised"), false);
                I.Flags.bAirborneRisk      = GetBool(*FlagsObj, TEXT("airborneRisk"), false);
                I.Flags.bMutationSpike     = GetBool(*FlagsObj, TEXT("mutationSpike"), false);
                I.Flags.bContainmentBreach = GetBool(*FlagsObj, TEXT("containmentBreach"), false);
            }

            const TSharedPtr<FJsonObject>* EffectsObj = nullptr;
            if (Obj->TryGetObjectField(TEXT("effects"), EffectsObj) && EffectsObj && EffectsObj->IsValid())
            {
                I.Effects = ParseDelta(*EffectsObj);
            }

            Incidents.Add(I);
        }
    }

    // actions.json can include both actions and ordeals in a single object or separate arrays.
    // Here we accept an object: { "actions":[...], "ordeals":[...] }
    {
        FString Raw;
        if (!FFileHelper::LoadFileToString(Raw, *ActAbs))
        {
            OutError = FString::Printf(TEXT("Failed to read file: %s"), *ActAbs);
            return false;
        }

        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Raw);
        TSharedPtr<FJsonObject> Root;
        if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
        {
            OutError = FString::Printf(TEXT("Failed to parse JSON object: %s"), *ActAbs);
            return false;
        }

        // Actions
        const TArray<TSharedPtr<FJsonValue>>* ActionsArr = nullptr;
        if (Root->TryGetArrayField(TEXT("actions"), ActionsArr) && ActionsArr)
        {
            for (const TSharedPtr<FJsonValue>& V : *ActionsArr)
            {
                const TSharedPtr<FJsonObject> Obj = V->AsObject();
                if (!Obj.IsValid()) continue;

                FActionDef A;
                A.Id    = GetString(Obj, TEXT("id"));
                A.Label = GetString(Obj, TEXT("label"));

                const TSharedPtr<FJsonObject>* CostObj = nullptr;
                if (Obj->TryGetObjectField(TEXT("cost"), CostObj) && CostObj && CostObj->IsValid())
                {
                    A.Cost.Power = GetNumber(*CostObj, TEXT("power"), 0.f);
                    A.Cost.Trust = GetNumber(*CostObj, TEXT("trust"), 0.f);
                }

                const TSharedPtr<FJsonObject>* EffObj = nullptr;
                if (Obj->TryGetObjectField(TEXT("effects"), EffObj) && EffObj && EffObj->IsValid())
                {
                    A.Effects = ParseDelta(*EffObj);
                }

                const TSharedPtr<FJsonObject>* PreObj = nullptr;
                if (Obj->TryGetObjectField(TEXT("prereqs"), PreObj) && PreObj && PreObj->IsValid())
                {
                    A.Prereqs.MinPower     = GetNumber(*PreObj, TEXT("minPower"), 0.f);
                    A.Prereqs.MinIntegrity = GetNumber(*PreObj, TEXT("minIntegrity"), 0.f);
                    A.Prereqs.MinTrust     = GetNumber(*PreObj, TEXT("minTrust"), 0.f);
                }

                Actions.Add(A);
            }
        }

        // Ordeals
        const TArray<TSharedPtr<FJsonValue>>* OrdealsArr = nullptr;
        if (Root->TryGetArrayField(TEXT("ordeals"), OrdealsArr) && OrdealsArr)
        {
            for (const TSharedPtr<FJsonValue>& V : *OrdealsArr)
            {
                const TSharedPtr<FJsonObject> Obj = V->AsObject();
                if (!Obj.IsValid()) continue;

                FOrdealDef O;
                O.Id        = GetString(Obj, TEXT("id"));
                O.Title     = GetString(Obj, TEXT("title"));
                O.Narrative = GetString(Obj, TEXT("narrative"));
                O.Effects   = ParseDelta(Obj->GetObjectField(TEXT("effects")));

                O.MinTurn = (int32)GetNumber(Obj, TEXT("minTurn"), 1.f);
                O.MaxTurn = (int32)GetNumber(Obj, TEXT("maxTurn"), 12.f);
                O.Chance  = GetNumber(Obj, TEXT("chance"), 0.15f);

                Ordeals.Add(O);
            }
        }
    }

    if (Incidents.Num() == 0)
    {
        OutError = TEXT("No incidents loaded. Check incidents.json.");
        return false;
    }
    if (Actions.Num() == 0)
    {
        OutError = TEXT("No actions loaded. Check actions.json.");
        return false;
    }

    return true;
}

void USWApolloSim::StartNewRun(int32 Seed)
{
    State = FGameState();
    State.Seed = Seed;
    IncidentIndex = 0;
    Rng.Initialize(Seed);
    UpdateDayFromTurn();
}

const FIncidentCard* USWApolloSim::GetNextIncident()
{
    if (Incidents.Num() == 0) return nullptr;

    // Shuffle-lite: deterministic “random pick without replacement”
    // We permute by swapping current index with a later random index.
    if (IncidentIndex >= Incidents.Num()) IncidentIndex = 0;

    int32 i = IncidentIndex;
    int32 j = Rng.RandRange(IncidentIndex, Incidents.Num() - 1);
    Incidents.Swap(i, j);

    const FIncidentCard* Pick = &Incidents[IncidentIndex];
    IncidentIndex++;
    return Pick;
}

const FActionDef* USWApolloSim::FindAction(const FString& ActionId) const
{
    for (const FActionDef& A : Actions)
    {
        if (A.Id == ActionId) return &A;
    }
    return nullptr;
}

bool USWApolloSim::CheckActionAllowed(const FActionDef& Action, FString& OutWhyNot) const
{
    if (State.Power < Action.Prereqs.MinPower)
    {
        OutWhyNot = TEXT("Not enough Power.");
        return false;
    }
    if (State.Integrity < Action.Prereqs.MinIntegrity)
    {
        OutWhyNot = TEXT("Station Integrity too low.");
        return false;
    }
    if (State.Trust < Action.Prereqs.MinTrust)
    {
        OutWhyNot = TEXT("Trust too low.");
        return false;
    }
    return true;
}

void USWApolloSim::ApplyDelta(const FDelta& D)
{
    State.Infection += D.Infection;
    State.Mutation  += D.Mutation;
    State.Power     += D.Power;
    State.Integrity += D.Integrity;
    State.Trust     += D.Trust;
    State.Countermeasure += D.Countermeasure;
    State.ClampAll();
}

void USWApolloSim::ApplyAction(const FActionDef& Action)
{
    // Costs (always apply)
    State.Power -= Action.Cost.Power;
    State.Trust -= Action.Cost.Trust;
    State.ClampAll();

    // Effects
    ApplyDelta(Action.Effects);
}

void USWApolloSim::ApplyIncident(const FIncidentCard& Incident)
{
    // Base card effects (optional per JSON)
    ApplyDelta(Incident.Effects);

    // Derived rules from flags give “pandemic sim” behavior even if effects are small
    ApplyDerivedRulesFromFlags(Incident);
}

void USWApolloSim::ApplyDerivedRulesFromFlags(const FIncidentCard& Incident)
{
    // Flag-driven extra deltas (simple but meaningful)
    if (Incident.Flags.bAirborneRisk)
    {
        State.Infection += 4.f;
        State.Power     -= 1.f; // filtration strain
    }
    if (Incident.Flags.bContainmentBreach)
    {
        State.Infection += 6.f;
        State.Integrity -= 3.f;
    }
    if (Incident.Flags.bMutationSpike)
    {
        State.Mutation += 6.f;
        State.Trust    -= 1.f;
    }
    if (Incident.Flags.bSensorCompromised)
    {
        State.Trust -= 2.f; // confidence shaken
    }

    // If mutation is high, infection grows faster (selection pressure)
    if (State.Mutation > 60.f)
    {
        State.Infection += 3.f;
    }

    State.ClampAll();
}

const FOrdealDef* USWApolloSim::MaybeTriggerOrdeal()
{
    for (const FOrdealDef& O : Ordeals)
    {
        if (State.Turn < O.MinTurn || State.Turn > O.MaxTurn) continue;

        const float Roll = Rng.FRand(); // 0..1
        if (Roll < O.Chance)
        {
            return &O;
        }
    }
    return nullptr;
}

void USWApolloSim::ApplyOrdeal(const FOrdealDef& Ordeal)
{
    ApplyDelta(Ordeal.Effects);

    // Ordeals also tend to increase mutation pressure slightly
    State.Mutation += 1.f;
    State.ClampAll();
}

void USWApolloSim::UpdateDayFromTurn()
{
    State.Day = ((State.Turn - 1) / 2) + 1;
}

void USWApolloSim::EvaluateWinLose(ERunStatus& OutStatus, FString& OutReason) const
{
    // Lose conditions
    if (State.Infection >= 100.f)
    {
        OutStatus = ERunStatus::Lost;
        OutReason = TEXT("Containment failure: Infection reached 100.");
        return;
    }
    if (State.Integrity <= 0.f)
    {
        OutStatus = ERunStatus::Lost;
        OutReason = TEXT("Station failure: Integrity reached 0.");
        return;
    }
    if (State.Power <= 0.f)
    {
        OutStatus = ERunStatus::Lost;
        OutReason = TEXT("Blackout: Power reached 0.");
        return;
    }
    if (State.Trust <= 0.f)
    {
        OutStatus = ERunStatus::Lost;
        OutReason = TEXT("Trust collapse: crew refuses protocols.");
        return;
    }

    // Win condition at turn 12
    if (State.Turn >= 12 && State.Infection <= 50.f && State.Countermeasure >= 100.f)
    {
        OutStatus = ERunStatus::Won;
        OutReason = TEXT("Stabilized: Countermeasure deployed and infection contained.");
        return;
    }

    OutStatus = ERunStatus::Running;
    OutReason = TEXT("");
}

FTurnResult USWApolloSim::StepTurn(const FString& ActionId)
{
    FTurnResult Result;
    Result.Before = State;

    const FIncidentCard* Incident = GetNextIncident();
    Result.IncidentId = Incident ? Incident->Id : TEXT("");

    const FActionDef* Action = FindAction(ActionId);
    Result.ActionId = ActionId;

    if (!Incident || !Action)
    {
        Result.After = State;
        Result.Status = ERunStatus::Lost;
        Result.StatusReason = TEXT("Invalid incident or action.");
        return Result;
    }

    FString WhyNot;
    if (!CheckActionAllowed(*Action, WhyNot))
    {
        // If action is disallowed, apply a small penalty for indecision and continue.
        State.Trust -= 2.f;
        State.Infection += 2.f;
        State.ClampAll();

        Result.After = State;
        Result.Status = ERunStatus::Running;
        Result.StatusReason = FString::Printf(TEXT("Action blocked: %s"), *WhyNot);
    }
    else
    {
        ApplyIncident(*Incident);
        ApplyAction(*Action);

        // Ordeal check after resolution
        const FOrdealDef* Ordeal = MaybeTriggerOrdeal();
        if (Ordeal)
        {
            Result.OrdealId = Ordeal->Id;
            ApplyOrdeal(*Ordeal);
        }

        // Advance turn
        State.Turn++;
        UpdateDayFromTurn();

        Result.After = State;
        EvaluateWinLose(Result.Status, Result.StatusReason);
    }

    return Result;
}
