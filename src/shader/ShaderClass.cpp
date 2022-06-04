#include"ShaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if(in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
	else
	{
		std::cout << "Failed to load" << std::endl;
	}
    throw(errno);
}

Shader::Shader(const char* vertexfile, const char* fragmentshader)
{
    std::string VertexCode = get_file_contents(vertexfile);
    std::string FragmentCode = get_file_contents(fragmentshader);

    const char* VertexSource = VertexCode.c_str();
    const char* FragmentSource = FragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &VertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &FragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexfile, const char* fragmentshader, const char* geometryshader)
{
    std::string VertexCode = get_file_contents(vertexfile);
    std::string FragmentCode = get_file_contents(fragmentshader);
    std::string GeometryCode = get_file_contents(geometryshader);

    const char* VertexSource = VertexCode.c_str();
    const char* FragmentSource = FragmentCode.c_str();
    const char* GeometrySource = GeometryCode.c_str();

    // Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &VertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &FragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT");

	// Create Fragment Shader Object and get its reference
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(geometryShader, 1, &GeometrySource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(geometryShader);
	CompileErrors(geometryShader, "GEOMETRY");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glAttachShader(ID, geometryShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}
void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::UpdateUniform(const char* name, const glm::mat4 matrix)
{
	GLint Location = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::CompileErrors(unsigned int shader, const char* type)
{
	GLint HasCompiled;
	char InfoLog[1024];
	if(type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &HasCompiled);
		if(HasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
			std::cout << "SHADER_COMPILATION_ERROR for : " << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &HasCompiled);
		if(HasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, InfoLog);
			std::cout << "SHADER_LINKING_ERROR for : " << type << "\n" << std::endl;
		}
	}
}

void Shader::SetInt(const char* name, int value)
{
	UpdateUniformInt(name, value);
}

void Shader::SetIntArray(const char* name, int* values, uint32_t count)
{
	UpdateUniformIntArray(name, values, count);
}

void Shader::SetFloat(const char* name, float value)
{
	UpdateUniformFloat(name, value);
}

void Shader::SetFloat2(const char* name, const glm::vec2& value)
{
	UpdateUniformFloat2(name, value);
}

void Shader::SetFloat3(const char* name, const glm::vec3& value)
{
	UpdateUniformFloat3(name, value);
}

void Shader::SetFloat4(const char* name, const glm::vec4& value)
{
	UpdateUniformFloat4(name, value);
}

void Shader::SetMat3(const char* name, const glm::mat3& value)
{
	UpdateUniformMat3(name, value);
}

void Shader::SetMat4(const char* name, const glm::mat4& value)
{
	UpdateUniformMat4(name, value);
}

void Shader::UpdateUniformInt(const char* name, int value)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform1i(location, value);
}

void Shader::UpdateUniformIntArray(const char* name, int* values, uint32_t count)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform1iv(location, count, values);
}

void Shader::UpdateUniformFloat(const char* name, float value)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform1f(location, value);
}

void Shader::UpdateUniformFloat2(const char* name, const glm::vec2& value)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform2f(location, value.x, value.y);
}

void Shader::UpdateUniformFloat3(const char* name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::UpdateUniformFloat4(const char* name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::UpdateUniformMat3(const char* name, const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UpdateUniformMat4(const char* name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}