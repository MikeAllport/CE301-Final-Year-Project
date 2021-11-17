#ifndef GAME_CLOCK
#define GAME_CLOCK

#include <chrono>
namespace GE
{
	/**
	* Clocks purpose is a simple class to contain the time at which a clock was created,
	* alongside method to reset to the now time, and compare the time difference in milliseconds
	* between itself and another clock
	*/
	class Clock
	{
	public:
		Clock();
		/**
		* timeDiffMS's purpose is to calculate the time difference between this and another clock
		*
		* args:
		*	Clock& other - the other clock to be compared against
		* returns:
		*	uint64 (long) - the time difference between the two clocks
		*/
		uint64 timeDiffMS(Clock& other);

		/**
		* reset's purpose is as said, resets the current time to system_clock.now()
		*/
		void reset();
		uint64 epochMS;
	private:
		// simple variables to store this instances time
		std::chrono::time_point<std::chrono::system_clock> time;
	};
}
#endif