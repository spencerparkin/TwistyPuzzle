// ShaderProgram.h

#pragma once

#include <wx/string.h>
#include <wx/glcanvas.h>
#include <Vector.h>

class ShaderProgram
{
public:

	ShaderProgram( void );
	virtual ~ShaderProgram( void );

	bool Load( const wxString& shaderName );
	bool Unload( void );

	bool Bind( void );
	bool Unbind( void );

	bool SetUniformVector( const wxString& uniformName, const _3DMath::Vector& vector );
	bool SetUniformFloat( const wxString& uniformName, double value );

private:

	bool MakeShader( const wxString& shaderName, GLuint& shader, GLenum shaderType );

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
};

// ShaderProgram.h