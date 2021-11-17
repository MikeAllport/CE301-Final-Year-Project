#include "gepch.h"
#include "KeyEvent.h"

namespace GE
{
	// creates key mapping
	std::unordered_map<int, std::pair<Keys, std::string>> KeyMap::codes = {
	{32, MKP(Keys::SPACE_BAR, "SPACE_BAR")},
	{39, MKP(Keys::APOSTROPHE, "APOSTROPHE")},
	{44, MKP(Keys::COMMA, "COMMA")},
	{45, MKP(Keys::MINUS, "MINUS")},
	{46, MKP(Keys::PERIOD, "PERIOD")},
	{47, MKP(Keys::SLASH, "FORWARD_SLASH")},
	{48, MKP(Keys::KEY_0, "KEY_0")},
	{49, MKP(Keys::KEY_1, "KEY_1")},
	{50, MKP(Keys::KEY_2, "KEY_2")},
	{51, MKP(Keys::KEY_3, "KEY_3")},
	{52, MKP(Keys::KEY_4, "KEY_4")},
	{53, MKP(Keys::KEY_5, "KEY_5")},
	{54, MKP(Keys::KEY_6, "KEY_6")},
	{55, MKP(Keys::KEY_7, "KEY_7")},
	{56, MKP(Keys::KEY_8, "KEY_8")},
	{57, MKP(Keys::KEY_9, "KEY_9")},
	{59, MKP(Keys::SEMI_COLON, "SEMI_COLON")},
	{61, MKP(Keys::EQUALS, "EQUALS")},
	{65, MKP(Keys::A, "A")}, 
	{66, MKP(Keys::B, "B")}, 
	{67, MKP(Keys::C, "C")},
	{68, MKP(Keys::D, "D")}, 
	{69, MKP(Keys::E, "E")}, 
	{70, MKP(Keys::F, "F")},
	{71, MKP(Keys::G, "G")}, 
	{72, MKP(Keys::H, "H")}, 
	{73, MKP(Keys::I, "I")},
	{74, MKP(Keys::J, "J")}, 
	{75, MKP(Keys::K, "K")}, 
	{76, MKP(Keys::L, "L")},
	{77, MKP(Keys::M, "M")}, 
	{78, MKP(Keys::N, "N")},
	{79, MKP(Keys::O, "O")},
	{80, MKP(Keys::P, "P")}, 
	{81, MKP(Keys::Q, "Q")}, 
	{82, MKP(Keys::R, "R")},
	{83, MKP(Keys::S, "S")}, 
	{84, MKP(Keys::T, "T")}, 
	{85, MKP(Keys::U, "U")},
	{86, MKP(Keys::V, "v")}, 
	{87, MKP(Keys::W, "W")}, 
	{88, MKP(Keys::X, "X")},
	{89, MKP(Keys::Y, "Y")}, 
	{90, MKP(Keys::Z, "Z")}, 
	{91, MKP(Keys::LEFT_BRACKET, "[")},
	{92, MKP(Keys::BACKSLASH, "BACKSLASH")}, 
	{93, MKP(Keys::RIGHT_BRACKET, "]")},
	{96, MKP(Keys::GRAVE_ACCENT, "GRAVE_ACCENT '`'")}, 
	{256, MKP(Keys::ESCAPE, "ESCAPE")},
	{257, MKP(Keys::ENTER, "ENTER")}, 
	{258, MKP(Keys::TAB, "TAB")},
	{259, MKP(Keys::BACKSPACE, "BACKSPACE")},
	{260, MKP(Keys::INSERT, "INSERT")},
	{261, MKP(Keys::DELETEK, "DELETE")},
	{262, MKP(Keys::RIGHT, "RIGHT")},
	{263, MKP(Keys::LEFT, "LEFT")}, 
	{264, MKP(Keys::DOWN, "DOWN")},
	{265, MKP(Keys::UP, "UP")},
	{340, MKP(Keys::LEFT_SHIFT, "LEFT_SHIFT")},
	{341, MKP(Keys::LEFT_CTRL, "LEFT_CTRL")},
	{342, MKP(Keys::LEFT_ALT, "LEFT_ALT")},
	{344, MKP(Keys::RIGHT_SHIFT, "RIGHT_SHIFT")},
	{345, MKP(Keys::RIGHT_CTRL, "RIGHT_CTRL")},
	{346, MKP(Keys::RIGHT_ALT, "RIGHT_ALT")}
	};

	KeyEvent::KeyEvent(const int key, const EventType& type)
		: Event(type, EventCategory::Keyboard)
	{
		std::pair<Keys, std::string> keyPressed = KeyMap::getPair(key);
		this->keyPressed = keyPressed.first;
		this->keyName = keyPressed.second;
	}

	Keys KeyEvent::whatKey()
	{
		return keyPressed;
	}

	std::string KeyEvent::toString() const
	{
		return "KeyEvent: key = " + keyName;
	}
}
