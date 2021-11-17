#ifndef GE_KEYS
#define GE_KEYS

#include "GE/Events/Event.h"
/**
* Keys purpose is to act as a base class to all key events recording what key was pressed
*/
namespace GE
{
	/**
	* Keys is an enumeration of valid key input that could be used in game
	*/
	enum Keys
	{
		SPACE_BAR = 32, APOSTROPHE = 39, COMMA = 44, MINUS = 45, PERIOD = 46, SLASH = 47,
		SEMI_COLON = 59, EQUALS = 61,

		LEFT_BRACKET = 91, BACKSLASH = 92, RIGHT_BRACKET = 93, GRAVE_ACCENT = 96,
		ESCAPE = 256, ENTER = 257, TAB = 258, BACKSPACE = 259, INSERT = 260, DELETEK = 261, RIGHT = 262, 
		LEFT = 263, DOWN = 264, UP = 265,


		KEY_0 = 48, KEY_1 = 49, KEY_2 = 50, KEY_3 = 51, KEY_4 = 52, KEY_5 = 53, KEY_6 = 54, 
		KEY_7 = 55, KEY_8 = 56, KEY_9 = 57, 
		//NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, 
		//NUM_7, NUM_8, NUM_9,
		
		A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73, J = 74, K = 75, L = 76,
		M = 77, N = 78, O= 79, P = 80, Q = 81, R = 82, S = 83, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90,

		LEFT_SHIFT = 340, RIGHT_SHIFT = 344, LEFT_ALT = 342, RIGHT_ALT = 346,
		LEFT_CTRL = 341, RIGHT_CTRL = 345,

		INVALID = -1
	};

	/*
	* KeyMap basic stuct to hold key mapping of ints to Keys and string value
	* with getter function
	*/
	struct KeyMap
	{
		static std::unordered_map<int, std::pair<Keys, std::string>> codes;
		static std::pair<Keys, std::string> getPair(const int key)
		{
			if (codes.find(key) == codes.end())
				return std::make_pair(Keys::INVALID, "INVALID");
			else
				return codes[key];
		}
	};

	class KeyEvent :
		public Event
	{
	public: 
		Keys whatKey();
		virtual std::string toString() const override;
	protected:
		KeyEvent(const int key, const EventType& type);
		Keys keyPressed;
		std::string keyName;
	};
}
#endif // !GE_KEYS

