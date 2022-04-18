// Copyright JosaiProduction. All Rights Reserved.
#include "CoreMinimal.h"
#include "SquirrelNoise.h"

/**
 * Implements squirrel noise 5 based RNG
 */
struct FSquirrelRandomStream
{
	/**
	 * Default constructor, setting initial seed and current seed to 0
	 */
	FSquirrelRandomStream()
		:m_initialSeed(0)
		,m_currentSeed(0)
	{
	}

	/**
	 * Creates and initializes a new random squirrel stream with a specified seed
	 * 
	 * @param seed The seed to set initially
	 */
	FSquirrelRandomStream(int32 seed)
		:m_initialSeed(seed)
		,m_currentSeed(seed)
	{
	}

	/**
	 * returns the next integer of the random stream
	 * 
	 * @return random number of the stream
	 */
	int32 GetInt() const
	{
		MutateSeed();
		return m_currentSeed;
	}

	/**
	 * returns the next random float number of the stream in range [0, 1]
	 * 
	 * @return random fraction.
	 */
	template<typename T>
	T GetFraction() const
	{
		static_assert(std::is_floating_point<T>());
		MutateSeed();
		return USquirrelNoiseFunctionLibrary::GetRange<T>(m_currentSeed, TNumericLimits<uint32>::Min(), TNumericLimits<uint32>::Max());
	}

	/**
	 * Mutates the seed to the next value
	 */
	void MutateSeed() const
	{
		m_currentSeed = USquirrelNoiseFunctionLibrary::Get1DNoise(m_currentSeed);
	}

	/**
	 * returns the initial seed of the stream
	 * 
	 * @return The initial seed
	 */
	int32 GetInitialSeed() const
	{
		return m_initialSeed;
	}

	/**
	 * returns the current seed
	 * 
	 * @return The current seed
	 */
	uint32 GetCurrentSeed() const
	{
		return m_currentSeed;
	}

	/**
	 * resets the current seed to the initial seed
	 */
	void ResetSeedToInitial()
	{
		m_currentSeed = m_initialSeed;
	}

	/**
	 * resets the seed to a value
	 */
	void ResetSeed(int32 seed = 0)
	{
		m_initialSeed = seed;
		m_currentSeed = seed;
	}

private:
	int32 m_initialSeed;
	/**
	 * mutable current seed to mutate the seed inside the getter.
	 */
	mutable uint32 m_currentSeed;
};