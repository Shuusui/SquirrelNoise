// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SquirrelNoise.generated.h"

UCLASS()
class USquirrelNoiseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math|Noise")
	static int32 Get1DNoise(int32 value, int32 seed = 0)
	{
		constexpr uint32 NOISE_BIT1 = 0xd2a80a3f;
		constexpr uint32 NOISE_BIT2 = 0xa884f197;
		constexpr uint32 NOISE_BIT3 = 0x6C736F4B;
		constexpr uint32 NOISE_BIT4 = 0xB79F3ABB;
		constexpr uint32 NOISE_BIT5 = 0x1b56c4f5;

		uint32 mangledBits = value;
		mangledBits *= NOISE_BIT1;
		mangledBits += seed;
		mangledBits ^= mangledBits >> 9;
		mangledBits += NOISE_BIT2;
		mangledBits ^= mangledBits >> 11;
		mangledBits *= NOISE_BIT3;
		mangledBits ^= mangledBits >> 13;
		mangledBits += NOISE_BIT4;
		mangledBits ^= mangledBits >> 15;
		mangledBits *= NOISE_BIT5;
		mangledBits ^= mangledBits >> 17;

		return mangledBits;
	}

	UFUNCTION(BlueprintCallable, Category="Math|Noise", meta = (DisplayName = "Get 2D noise"))
	static int32 Get2DNoise(int32 posX, int32 posY, int32 seed = 0)
	{
		constexpr int32 PRIME_NUMBER = 198491317;
		return Get1DNoise(posX + (PRIME_NUMBER * posY), seed);
	}

	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 2D noise (FVector2D)"))
	static int32 Get2DNoise(const FIntPoint& point, int32 seed = 0)
	{
		return Get2DNoise(point.X, point.Y, seed);
	}

	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 3D noise"))
	static int32 Get3DNoise(int32 posX, int32 posY, int32 posZ, int32 seed = 0)
	{
		constexpr int32 PRIME_NUMBER1 = 198491317;
		constexpr int32 PRIME_NUMBER2 = 6542989;
		return Get1DNoise(posX + (PRIME_NUMBER1 * posY) + (PRIME_NUMBER2 * posZ), seed);
	}

	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 3D noise (FVector)"))
	static int32 Get3DNoise(const FIntVector& v, int32 seed = 0)
	{
		return Get3DNoise(v.X, v.Y, v.Z, seed);
	}

	UFUNCTION(BlueprintCallable, Category = "Math|Noise")
	static float GetFloat(int32 value, int32 seed = 0)
	{
		return GetFraction<float>(value, seed);
	}

	UFUNCTION(BlueprintCallable, Category = "Math|Noise")
	static double GetDouble(int32 value, int32 seed = 0)
	{
		return GetFraction<double>(value, seed);
	}

	template<typename T>
	T static GetFraction(int32 value, int32 seed = 0)
	{
		return GetRange<T>(Get1DNoise(value, seed), TNumericLimits<int32>::Min(), TNumericLimits<int32>::Max());
	}

	template<typename T> 
	T static GetRange(int32 value, int32 min, int32 max)
	{
		return (value - min) / (max - min);
	}
};
