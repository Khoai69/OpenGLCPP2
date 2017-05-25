#pragma once

class  ShaderProgram
{
public:
	 ShaderProgram();
	 ShaderProgram(const char* vs, const char * fs);
	 ShaderProgram(const char* vs, const char * fs, const char* program_name);
	 GLuint Create(const char* vs, const char * fs);
	~ ShaderProgram();

	GLuint				GetID()							{ return m_programid; }
	void				SetName(const char* name)		{ m_programName = name; }
	std::string			GetName()						{ return m_programName; }

private:
	GLuint				m_programid;
	std::string			m_programName;
	GLuint				LoadShader(GLenum type, const char * filename);
	GLuint				LoadProgram(GLuint vertexShader, GLuint fragmentShader);
};

