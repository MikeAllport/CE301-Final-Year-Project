#ifndef GE_PRECOMP_H
#define GE_PRECOMP_H

//#define _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define DBG_NEW new
//#endif

#include <stdio.h>
#include <glad/glad.h>

// cpp specific includes
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <numeric>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>

// project specific includes
#include "GE/Logger.h"
#include <glm.hpp>
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"

// constants
const double M_PI = 2 * acos(0.0);

// typedefs
typedef uint32_t uint32; 
typedef unsigned __int64 uint64;

//Assertion and opengl error checking macros
#ifdef GE_DEBUG
#define DEBUGBREAK __debugbreak()
#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GE_ASSERT(x, ...) x
#endif

// handy macros used throughout
#define STRINGY(x) std::to_string(x)
#define MKP(x, y) std::make_pair(x, y)
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#include <iostream>

// functions used throughout
glm::fvec4 getMat4Column(glm::mat4& toGet, int column);
glm::mat4 setMat4Column(glm::mat4 matToSet, glm::fvec4& colToSet, int column);
glm::fvec4 getMat4Row(glm::mat4& toGet, int row);
glm::mat4 setMat4Row(glm::mat4 matToSet, glm::fvec4& colToSet, int row);


#endif // !GE_PRECOMP_H
