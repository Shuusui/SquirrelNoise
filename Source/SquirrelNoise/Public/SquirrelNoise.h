// Copyright JosaiProduction. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SquirrelNoise.generated.h"

/**
 * Implements squirrel noise function library based on squirrel noise 5. 
 */
UCLASS(meta=(ScriptName="SquirrelNoiseLibrary"))
class USquirrelNoiseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Returns a pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @param value The value the random number is based on. Use same value but different seeds to get different results.
	 * @param seed The seed of the random value
	 * @return Squirrel noise based random number generated.
	 */
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

	/**
	 * Takes 2d values and returns pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @param posX The X value of the 2d position
	 * @param posY The Y value of the 2d position
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	UFUNCTION(BlueprintCallable, Category="Math|Noise", meta = (DisplayName = "Get 2D noise"))
	static int32 Get2DNoise(int32 posX, int32 posY, int32 seed = 0)
	{
		constexpr int32 PRIME_NUMBER = 198491317;
		return Get1DNoise(posX + (PRIME_NUMBER * posY), seed);
	}

	/**
	 * Takes a FIntPoint and returns pseudo-random and deterministic random number based on the value and the seed.
	 * 
	 * @param point The point to use as the 2d position.
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 2D noise (FVector2D)"))
	static int32 Get2DPointNoise(const FIntPoint& point, int32 seed = 0)
	{
		return Get2DNoise(point.X, point.Y, seed);
	}

	/**
	 * Takes 3d values and returns pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @param posX The X value of the 3d position
	 * @param posY The Y value of the 3d position
	 * @param posZ The Z value of the 3d position
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 3D noise"))
	static int32 Get3DNoise(int32 posX, int32 posY, int32 posZ, int32 seed = 0)
	{
		constexpr int32 PRIME_NUMBER1 = 198491317;
		constexpr int32 PRIME_NUMBER2 = 6542989;
		return Get1DNoise(posX + (PRIME_NUMBER1 * posY) + (PRIME_NUMBER2 * posZ), seed);
	}

	/**
	 * Takes a 3d value and returns pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @param v The 3d int-vector to use
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 3D noise (FIntVector)"))
	static int32 Get3DPointNoise(const FIntVector& v, int32 seed = 0)
	{
		return Get3DNoise(v.X, v.Y, v.Z, seed);
	}

	/**
	 * Takes 4d values and returns pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @oaram posX The X value of the 4d position
	 * @param posY The Y value of the 4d position
	 * @param posZ The Z value of the 4d position
	 * @param posW The W value of the 4d position
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise", meta=(DisplayName="Get 4D noise"))
	static int32 Get4DNoise(int32 posX, int32 posY, int32 posZ, int32 posW, int32 seed)
	{
		constexpr int32 PRIME_NUMBER1 = 198491317;
		constexpr int32 PRIME_NUMBER2 = 6542989;
		constexpr int32 PRIME_NUMBER3 = 357239;
		return Get1DNoise(posX + (PRIME_NUMBER1 * posY) + (PRIME_NUMBER2 * posZ) + (PRIME_NUMBER3 * posW), seed);
	}

	/**
	 * Takes a 4d int vector and returns pseudo-random and deterministic number based on the value and the seed.
	 * 
	 * @param v The 4d int vector to use
	 * @param seed The seed for the pseudo-random number
	 * 
	 * @return The random number
	 */
	static int32 Get4DPointNoise(const FIntVector4& v, int32 seed = 0)
	{
		return Get4DNoise(v.X, v.Y, v.Z, v.W, seed);
	}

	/**
	 * Takes a value and returns a pseudo-random and deterministic float value in between range [0, 1]
	 * 
	 * @param value The integer the random number should be based on 
	 * @param seed The seed for the random number
	 * 
	 * @return A float in range [0, 1]
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise")
	static float GetFloat(int32 value, int32 seed = 0)
	{
		return GetFraction<float>(value, seed);
	}

	/**
	 * Takes a value and returns a pseudo-random and deterministic double value in between range [0, 1]
	 *
	 * @param value The integer the random number should be based on
	 * @param seed The seed for the random number
	 *
	 * @return A double in range [0, 1]
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Noise")
	static double GetDouble(int32 value, int32 seed = 0)
	{
		return GetFraction<double>(value, seed);
	}

	/**
	 * Takes a value and returns a pseudo-random and deterministic value of type T in between range [0, 1] 
	 * make sure T is of floating point type (i.e. float, double, long double)
	 * 
	 * @param value The value the pseudo-random number is based on
	 * @param seed The seed to use for the pseudo-random number
	 * 
	 * @return The scaled pseudo-random number in range [0, 1]
	 */
	template<typename T>
	T static GetFraction(int32 value, int32 seed = 0)
	{
		static_assert(std::is_floating_point_v<T>);
		return GetRange<T>(Get1DNoise(value, seed), TNumericLimits<uint32>::Min(), TNumericLimits<uint32>::Max());
	}

	/**
	 * Takes a value and returns and returns a scaled number in between min and max
	 * make sure T is of floating point type (i.e. float, double, long double)
	 * 
	 * @param value The value to scale between min and max
	 * @param min The min of the scaled value
	 * @param max The max of the scaled value
	 * 
	 * @return The scaled value in range [min, max]
	 */
	template<typename T> 
	T static GetRange(int32 value, uint32 min, uint32 max)
	{
		static_assert(std::is_floating_point_v<T>);
		return static_cast<T>(value - min) / (max - min);
	}
};
