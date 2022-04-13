#include "CoreMinimal.h"
#include "SquirrelNoise.h"

struct FSquirrelRandomStream
{
	FSquirrelRandomStream()
		:m_initialSeed(0)
		,m_currentSeed(0)
	{
	}

	FSquirrelRandomStream(int32 seed)
		:m_initialSeed(seed)
		,m_currentSeed(seed)
	{

	}

	int32 GetInt() const
	{
		MutateSeed();
		return m_currentSeed;
	}

	float GetFraction() const
	{
		MutateSeed();
		return 
	}

	void MutateSeed() const
	{
		m_currentSeed = USquirrelNoiseFunctionLibrary::Get1DNoise(m_currentSeed++);
	}

	int32 GetInitialSeed() const
	{
		return m_initialSeed;
	}

	uint32 GetCurrentSeed() const
	{
		return m_currentSeed;
	}

	void ResetSeedToInitial()
	{
		m_currentSeed = m_initialSeed;
	}

	void ResetSeed(int32 seed = 0)
	{
		m_initialSeed = seed;
		m_currentSeed = seed;
	}

private:
	int32 m_initialSeed;
	mutable uint32 m_currentSeed;
};