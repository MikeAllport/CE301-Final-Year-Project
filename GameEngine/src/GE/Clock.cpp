#include <gepch.h>
#include "Clock.h"

namespace GE
{
	Clock::Clock()
	{
		reset();
	}

	uint64 Clock::timeDiffMS(Clock& other)
	{
		return other.epochMS - epochMS;
	}

	void Clock::reset()
	{
		std::chrono::system_clock clock = std::chrono::system_clock();
		time = clock.now();
		epochMS = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
	}
}