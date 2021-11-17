#ifndef GE_SHADER
#define GE_SHADER

#include "gepch.h"
#include "glad/glad.h"
#include "glm.hpp"


namespace GE::Graphics
{
	typedef struct {
		GLenum			type;
		std::string		fileContents;
	} ShaderInfo ;

	// simple parse helper function to parse a file and return string
	inline std::string parseFile(std::string& shaderFN);

	class Shader
	{
	public:
		Shader(const std::string& vertexFn, const std::string fragmentFN);
		Shader(const Shader& other);
		~Shader();
		void bind() const;
		void unbind() const;
		// uniform creation/getter functions
		void setUniform1i(const std::string& name, int first);
		void setUniform1iv(const std::string& name, int first, int second[]);
		void setUniform1F(const std::string& name, float first);
		void setUniform3fv(const std::string& name, const GLfloat* value);
		void setUniform4F(const std::string& name, float first, float second, float third, float fourth);
		void setUniformMat4F(const std::string& name, const glm::mat4& matrix);
		void setUniformMat4Fv(const std::string& name, const GLfloat* value);
		void setUniform1ui64ARB(const std::string& name, const uint64 val);
		void setIntArray(const std::string& name, int* values, uint32 count);
		uint32 getID() { return progID; };
	private:
		uint32 progID;
		std::string vertexFn, fragmentFN;
		const std::string path = "res\\shaders\\";
		// uniform cache
		std::unordered_map<std::string, int> uniforms;
		// creates the program on the gpu, combination of shaders to be used
		void makeShaderProgram(const ShaderInfo shaders[]);

		// allocates and compiles space for shader on GPU, needs to be done for all shaders
		// used in shader program i.e vertex, fragment, tessellation 
		uint32 makeShader(const ShaderInfo& info);

		// utility function for checking shader compilation/linking errors.
		void checkCompileErrors(uint32 shader, GLenum typ);
		void init();

		int getUniformLoc(const std::string& name);
	};
}
#endif // !GE_SHADER
