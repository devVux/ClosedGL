#include "pch.h"
#include "Shader.h"

#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

Shader::Shader() {
	mProgram = glCreateProgram();
}

Shader::~Shader() {
	glDeleteProgram(mProgram);
}

void Shader::bind() const {
	glUseProgram(mProgram);
}

void Shader::unbind() const {
	glUseProgram(0);
}

// TODO: statica?
// TODO: controlla il fs se parente o no la directory
void Shader::fromFile(const std::string& path) {
	//std::string s = fs::current_path().string();

	//std::ifstream file(s.append('/' + path));
	std::ifstream file(path);
	
	if (!fs::exists(path)) {
		file.close();
		assert(false && "Scrivi bene il nome del shader file.");
	}

	std::string content((std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()));


	file.close();

	const size_t vertexLoc = content.find("@vertex");
	const size_t fragmentLoc = content.find("@fragment");
	
	assert(vertexLoc != std::string::npos);
	assert(fragmentLoc != std::string::npos);

	// "@vertex".length = 7
	// "@fragment".length = 9
	const std::string vertexSrc(content.substr(vertexLoc + 7, fragmentLoc - vertexLoc - 7));
	const std::string fragmentSrc(content.substr(fragmentLoc + 9));
	
	setSources(vertexSrc, fragmentSrc);

}

void Shader::setUniform1i(const std::string& var, int a) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	glUniform1i(location, a);
}

void Shader::setUniform1f(const std::string& var, float a) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	glUniform1f(location, a);
}

void Shader::setUniformIntArray(const std::string& var, int* data, uint32_t count) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	glUniform1iv(location, count, data);
}

void Shader::setUniformFloatArray(const std::string& var, float* data, uint32_t count) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	glUniform1fv(location, count, data);
}

void Shader::setUniformVec2(const std::string& var, const glm::vec2& v) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniform2fv(location, 1, (GLfloat*) &v);
}

void Shader::setUniformVec3(const std::string& var, const glm::vec3& v) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniform3fv(location, 1, (GLfloat*) &v);
}

void Shader::setUniformVec4(const std::string& var, const glm::vec4& v) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniform4fv(location, 1, (GLfloat*) &v);
}

void Shader::setUniformMatrix2(const std::string& var, const glm::mat2& m) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniformMatrix2fv(location, 1, GL_FALSE, (GLfloat*) &m);
}

void Shader::setUniformMatrix3(const std::string& var, const glm::mat3& m) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*) &m);
}

void Shader::setUniformMatrix4(const std::string& var, const glm::mat4& m) const {
	int location = glGetUniformLocation(mProgram, reinterpret_cast<const GLchar*>(var.c_str()));
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*) &m);
}

void Shader::setSources(std::string vertex, std::string fragment) {

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = (const GLchar*) vertex.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		ERRORE("Error in vertex shader:\n" + std::string(infoLog));

		delete[] infoLog;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*) fragment.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

<<<<<<< Updated upstream
		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		ERRORE("Error in fragment shader");

		// In this simple program, we'll just leave
		return;
=======
		FATAL("Error in fragment shader:\n" + std::string(infoLog));
		
		delete[] infoLog;
>>>>>>> Stashed changes
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	GLuint program = glCreateProgram();
	mProgram = program;

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*) &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

}
