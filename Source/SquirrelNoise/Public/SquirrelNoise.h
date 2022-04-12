// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SquirrelNoise.generated.h"

UCLASS()
class USquirrelNoiseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
	static int32 Squirrel(int32 value, int32 seed = 0)
	{
		uint32 noiseBit1 = 0xd2a80a3f;
		uint32 noiseBit2 = 0xa884f197;
		uint32 noiseBit3 = 0x6C736F4B;
		uint32 noiseBit4 = 0xB79F3ABB;
		uint32 noiseBit5 = 0x1b56c4f5;

		uint32 mangledBits = value;
		mangledBits *= noiseBit1;
		mangledBits += seed;
		mangledBits ^= mangledBits >> 9;
		mangledBits += noiseBit2;
		mangledBits ^= mangledBits >> 11;
		mangledBits *= noiseBit3;
		mangledBits ^= mangledBits >> 13;
		mangledBits += noiseBit4;
		mangledBits ^= mangledBits >> 15;
		mangledBits *= noiseBit5;
		mangledBits ^= mangledBits >> 17;

		return mangledBits;
	}
};

