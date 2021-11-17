#include "gepch.h"
#include "Shader.h"

namespace GE::Graphics
{
	inline std::string parseFile(const std::string& file)
	{
		{
			std::ifstream fs(file);
			if (!fs.is_open())
			{
				GE_FATAL("Failed to load file when initializing shaders {0}", file);
				exit(1); 
			}
			std::stringstream ss;
			std::string line;
			while (std::getline(fs, line))
			{
				ss << line << "\n";
			}
			return ss.str();
		};
	}

	Shader::Shader(const std::string& vertexFn, const std::string fragmentFN):
		vertexFn(vertexFn),
		fragmentFN(fragmentFN)
	{
		init();
	}

	Shader::Shader(const Shader& other):
		vertexFn(other.vertexFn),
		fragmentFN(other.fragmentFN),
		uniforms()
	{
		init();
	}

	void Shader::makeShaderProgram(const ShaderInfo shaders[])
	{
		progID = glCreateProgram();
		uint32 vs = makeShader(shaders[0]);
		uint32 fs = makeShader(shaders[1]);
		glAttachShader(progID, vs);
		glAttachShader(progID, fs);
		glLinkProgram(progID);
		checkCompileErrors(progID, GL_PROGRAM);
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	uint32 Shader::makeShader(const ShaderInfo& shader)
	{
		GLuint shaderId = glCreateShader(shader.type);
		if (shaderId == GL_FALSE)
		{
			GE_INFO("Shader initialization error");
			exit(1);
		}
		const GLchar* shaderChar = shader.fileContents.c_str();
		glShaderSource(shaderId, 1, &shaderChar, NULL);
		glCompileShader(shaderId);

		// checks whether compiled or not, if not outputs message log
		GLint compiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
		checkCompileErrors(shaderId, shader.type);
		return shaderId;
	}

	void Shader::bind() const
	{
		glUseProgram(progID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		unbind();
		glDeleteProgram(progID);
	}

	void Shader::checkCompileErrors(uint32 shader, GLenum type)
	{
		GLint success;
		GLint maxLength = 0;
		GLchar* infoLog = new GLchar[maxLength];
		switch (type)
		{
		case GL_PROGRAM:
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				GE_WARN("Error linking program {0}\n{1}", type, infoLog);
			}
			else
				GE_INFO("Shader program compiled and loaded successfully");
			break;
		default:
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				GE_WARN("Error compiling shader {0}\n{1}", type, infoLog);
			}
			break;
		}
		delete[] infoLog;
	}

	void Shader::init()
	{
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, parseFile(path + vertexFn) },
			{ GL_FRAGMENT_SHADER, parseFile(path + fragmentFN) }
		};
		makeShaderProgram(shaders);
		GE_INFO("Shader program loaded id: {0}\n vertex file: {1}\n fragment file {2}", progID, path + vertexFn, path + fragmentFN);
	}


	void Shader::setUniform1i(const std::string& name, int first)
	{
		glUniform1i(getUniformLoc(name), first);
	}

	void Shader::setUniform1F(const std::string& name, float first)
	{
		glUniform1f(getUniformLoc(name), first);
	}

	void Shader::setUniform1iv(const std::string& name, int first, int second[])
	{
		glUniform1iv(getUniformLoc(name), first, second);
	}

	void Shader::setUniform3fv(const std::string& name, const GLfloat* value)
	{
		glUniform3fv(getUniformLoc(name), 1, value);
	}

	void Shader::setUniform4F(const std::string& name, float first, float second, float third, float fourth)
	{
		glUniform4f(getUniformLoc(name), first, second, third, fourth);
	}

	void Shader::setUniform1ui64ARB(const std::string& name, const uint64 val)
	{
		glUniformHandleui64vARB(getUniformLoc(name), 1, &val);
	}

	// TODO: replace functionality with own math matrix, or glOrtho
	void Shader::setUniformMat4F(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void Shader::setUniformMat4Fv(const std::string& name, const GLfloat* value)
	{
		glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, value);
	}

	void Shader::setIntArray(const std::string& name, int* values, uint32 count)
	{
		
		glUniform1iv(getUniformLoc(name), count, values);
	}

	int Shader::getUniformLoc(const std::string& name)
	{
		if (uniforms.find(name) != uniforms.end())
		{
			return uniforms[name];
		}
		int location = glGetUniformLocation(progID, name.c_str());
		if (location == -1)
		{
			return location;
		}
		uniforms[name] = location;
		return location;
	}
}
