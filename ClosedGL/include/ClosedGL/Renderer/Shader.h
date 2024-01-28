#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader {
	
	public:

		Shader();
		~Shader();

		void bind() const;
		void unbind() const;

		void fromFile(const std::string& path);

		void setUniform1i(const std::string& var, int a) const;
		void setUniform1f(const std::string& var, float a) const;
		void setUniformIntArray(const std::string& var, int* data, uint32_t count) const;
		void setUniformFloatArray(const std::string& var, float* data, uint32_t count) const;
		void setUniformVec2(const std::string& var, const glm::vec2& v) const;
		void setUniformVec3(const std::string& var, const glm::vec3& v) const;
		void setUniformVec4(const std::string& var, const glm::vec4& v) const;
		void setUniformMatrix2(const std::string& var, const glm::mat2& m) const;
		void setUniformMatrix3(const std::string& var, const glm::mat3& m) const;
		void setUniformMatrix4(const std::string& var, const glm::mat4& m) const;

		void setSources(std::string vertex, std::string fragment);

		unsigned int program() const { return mProgram; }

	private:

		unsigned int mProgram;

};
