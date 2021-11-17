#ifndef GE_OBJECT
#define GE_OBJECT

#include "gepch.h"
/**
* Object is a pure abstract class to be implemented by all classes with common
* class features such as toString, similar to java's implementation
*/

namespace GE
{
	class Object
	{
	public:
		friend std::ostream& operator<<(std::ostream& o, const Object& d)
		{
			o << d.toString();
			return o;
		};
		virtual std::string toString() const = 0;
	};
}
#endif // !GE_OBJECT
