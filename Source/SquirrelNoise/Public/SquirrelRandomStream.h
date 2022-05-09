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
		:m_position(0)
		,m_seed(0)
	{
	}

	/**
	 * Creates and initializes a new random squirrel stream with a specified seed
	 * 
	 * @param seed The seed to set initially
	 */
	FSquirrelRandomStream(int32 seed)
		:m_position(0)
		,m_seed(seed)
	{
	}

	/**
	 * returns the next integer of the random stream
	 * 
	 * @return random number of the stream
	 */
	int32 GetInt() const
	{
		NextPosition();
		return USquirrelNoiseFunctionLibrary::Get1DNoise(m_position, m_seed);
	}

	/**
	 * returns the next random float number of the stream in range [0, 1]
	 * 
	 * @return random fraction.
	 */
	template<typename T> 
	T GetFraction() const
	{
		static_assert(std::is_floating_point_v<T>);
		NextPosition();
		return USquirrelNoiseFunctionLibrary::GetFraction<T>(m_position, m_seed);
	}

	/**
	 * Increments the position
	 */
	void NextPosition() const
	{
		m_position++;
	}

	/**
	 * returns the current seed
	 * 
	 * @return The current seed
	 */
	uint32 GetSeed() const
	{
		return m_seed;
	}

	/**
	* returns the current position of the stream
	* 
	* @return The current position
	*/
	uint32 GetCurrentPosition() const
	{
		return m_position;
	}

	/**
	 * Resets the position back to 0 to restart the stream.
	 */
	void ResetPosition()
	{
		m_position = 0;
	}

private:
	/* mutable to cover const getter functions as well, where it would be legit to get a random number from the stream */
	mutable uint32 m_position;
	uint32 m_seed;
};