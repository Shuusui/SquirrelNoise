#include "CoreMinimal.h"

struct FSquirrelRandomStream
{
	FSquirrelRandomStream()
		:m_initialSeed(0)
		,m_currentSeed(0)
		,m_position(0)
	{
	}

	FSquirrelRandomStream(int32 seed)
		:m_initialSeed(seed)
		,m_currentSeed(seed)
		,m_position(0)
	{

	}
	void SetCurrentPosition(int32 position)
	{
		m_position = position;
	}

	int32 GetCurrentPosition() const
	{
		return m_position;
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

	void ResetSeed(uint32 seed = 0, int32 position = 0)
	{
		m_initialSeed = seed;
		m_currentSeed = seed;
		m_position = position;
	}

private:
	int32 m_initialSeed;
	int32 m_position;
	uint32 m_currentSeed;
};