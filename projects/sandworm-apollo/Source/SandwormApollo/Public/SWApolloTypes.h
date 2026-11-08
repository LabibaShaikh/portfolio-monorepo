#pragma once

#include "CoreMinimal.h"
#include "SWApolloTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) int32 Turn = 1;        // 1..12
    UPROPERTY(BlueprintReadWrite) int32 Day = 1;         // optional alias; can map Day = (Turn-1)/2 + 1
    UPROPERTY(BlueprintReadWrite) int32 Seed = 1337;

    UPROPERTY(BlueprintReadWrite) float Infection = 20.f;   // 0..100
    UPROPERTY(BlueprintReadWrite) float Mutation  = 10.f;   // 0..100
    UPROPERTY(BlueprintReadWrite) float Power     = 75.f;   // 0..100
    UPROPERTY(BlueprintReadWrite) float Integrity = 85.f;   // 0..100
    UPROPERTY(BlueprintReadWrite) float Trust     = 60.f;   // 0..100

    UPROPERTY(BlueprintReadWrite) float Countermeasure = 0.f; // 0..100 (required to win)

    void ClampAll()
    {
        Infection = FMath::Clamp(Infection, 0.f, 100.f);
        Mutation  = FMath::Clamp(Mutation,  0.f, 100.f);
        Power     = FMath::Clamp(Power,     0.f, 100.f);
        Integrity = FMath::Clamp(Integrity, 0.f, 100.f);
        Trust     = FMath::Clamp(Trust,     0.f, 100.f);
        Countermeasure = FMath::Clamp(Countermeasure, 0.f, 100.f);
    }
};

USTRUCT(BlueprintType)
struct FIncidentEvidence
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FString Vitals;
    UPROPERTY(BlueprintReadWrite) FString Lab;
    UPROPERTY(BlueprintReadWrite) FString Environment;
    UPROPERTY(BlueprintReadWrite) FString Comms;
};

USTRUCT(BlueprintType)
struct FIncidentFlags
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) bool bSensorCompromised = false;
    UPROPERTY(BlueprintReadWrite) bool bAirborneRisk = false;
    UPROPERTY(BlueprintReadWrite) bool bMutationSpike = false;
    UPROPERTY(BlueprintReadWrite) bool bContainmentBreach = false;
};

USTRUCT(BlueprintType)
struct FDelta
{
    GENERATED_BODY()

    // Generic deltas applied by incidents/actions/ordeals
    UPROPERTY(BlueprintReadWrite) float Infection = 0.f;
    UPROPERTY(BlueprintReadWrite) float Mutation  = 0.f;
    UPROPERTY(BlueprintReadWrite) float Power     = 0.f;
    UPROPERTY(BlueprintReadWrite) float Integrity = 0.f;
    UPROPERTY(BlueprintReadWrite) float Trust     = 0.f;
    UPROPERTY(BlueprintReadWrite) float Countermeasure = 0.f;
};

USTRUCT(BlueprintType)
struct FIncidentCard
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FString Id;
    UPROPERTY(BlueprintReadWrite) FString Title;
    UPROPERTY(BlueprintReadWrite) FString Narrative;

    UPROPERTY(BlueprintReadWrite) FIncidentEvidence Evidence;
    UPROPERTY(BlueprintReadWrite) FIncidentFlags Flags;

    // Optional: direct simulation impact of this incident card
    UPROPERTY(BlueprintReadWrite) FDelta Effects;
};

USTRUCT(BlueprintType)
struct FActionCost
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) float Power = 0.f;
    UPROPERTY(BlueprintReadWrite) float Trust = 0.f;
};

USTRUCT(BlueprintType)
struct FActionPrereqs
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) float MinPower = 0.f;
    UPROPERTY(BlueprintReadWrite) float MinIntegrity = 0.f;
    UPROPERTY(BlueprintReadWrite) float MinTrust = 0.f;
};

USTRUCT(BlueprintType)
struct FActionDef
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FString Id;
    UPROPERTY(BlueprintReadWrite) FString Label;

    UPROPERTY(BlueprintReadWrite) FActionCost Cost;
    UPROPERTY(BlueprintReadWrite) FDelta Effects;
    UPROPERTY(BlueprintReadWrite) FActionPrereqs Prereqs;
};

USTRUCT(BlueprintType)
struct FOrdealDef
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite) FString Id;
    UPROPERTY(BlueprintReadWrite) FString Title;
    UPROPERTY(BlueprintReadWrite) FString Narrative;
    UPROPERTY(BlueprintReadWrite) FDelta Effects;

    // Trigger rules
    UPROPERTY(BlueprintReadWrite) int32 MinTurn = 1;
    UPROPERTY(BlueprintReadWrite) int32 MaxTurn = 12;
    UPROPERTY(BlueprintReadWrite) float Chance = 0.15f; // per turn, if in range
};
