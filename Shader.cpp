#include "Shader.h"

//When created, parse the shader into it's vertex and fragment parts, then run createShader to set our RendererID.
Shader::Shader(const std::string& filePath) : m_FilePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

//Delete the rendererID
Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

GLuint Shader::getUniformID(std::string name)
{
    return m_UniformLocationCache[name];
}

//This will read through the shader text file given as filepath and certain things in it to determine when the shader code starts, and what is the fragment and vertex shaders.
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    //Set filepath to be an ifstream, so it can be used in getline()
    std::ifstream stream(filepath);

    //Enumerate the shader type for easier understanding.
    enum class shaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;

    //Read through the shader file and store each line into line. ss stores the shaders. ss[0] being vertex and ss[1] being fragment. The shader file must include these shader type headers.
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = shaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = shaderType::FRAGMENT;
            }
        }
        else
        {
            //This stores the lines into ss which keeps the fragment and vertex shaders.
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

//This compiles the shader program into a usable program for gl calls.
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) // or !result
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

//Attaches the shaders to this program.
unsigned int Shader::CreateShader(const std::string& vertShader, const std::string& fragShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::setUniformLocations() {
    int count;
    GLsizei actualLen;
    GLint size;
    GLenum type;
    char* name;
    int maxUniformListLength;
    unsigned int loc;

    //Get how many active uniforms there are and print to console.
    glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count);
    printf("There are %d active Uniforms\n", count);

    // Get the length of the longest named uniform 
    glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformListLength);

    //Allocate space for the uniform's name 
    name = (char*)malloc(sizeof(char) * maxUniformListLength);


    for (int i = 0; i < count; ++i) {
        //Get the name of the ith uniform
        glGetActiveUniform(m_RendererID, i, maxUniformListLength, &actualLen, &size, &type, name);
        //Get the (unsigned int) loc for this uniform
        loc = glGetUniformLocation(m_RendererID, name);
        std::string uniformName = name;
        m_UniformLocationCache[uniformName] = loc;

        //Print uniform locations to console.
        printf("\"%s\" loc:%d\n", uniformName.c_str(), m_UniformLocationCache[uniformName]);
    }
    //Free the previously allocated space for the uniform's name.
    free(name);
}