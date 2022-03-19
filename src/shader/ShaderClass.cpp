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