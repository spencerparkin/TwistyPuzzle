// ShaderProgram.cpp

#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Application.h"
#include "Frame.h"
#include <gl/GL.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>

ShaderProgram::ShaderProgram( void )
{
	program = 0;
	fragmentShader = 0;
	vertexShader = 0;
}

/*virtual*/ ShaderProgram::~ShaderProgram( void )
{
	( void )Unload();
}

bool ShaderProgram::Load( const wxString& shaderName )
{
	bool success = false;

	do
	{
		if( program )
			break;

		if( !MakeShader( shaderName, vertexShader, GL_VERTEX_SHADER ) )
			break;

		if( !MakeShader( shaderName, fragmentShader, GL_FRAGMENT_SHADER ) )
			break;

		program = glCreateProgram();
		if( !program )
			break;

		if( vertexShader )
			glAttachShader( program, vertexShader );

		if( fragmentShader )
			glAttachShader( program, fragmentShader );

		GLint status;
		glGetProgramiv( program, GL_LINK_STATUS, &status );
		if( status == GL_FALSE )
		{
			char infoBuffer[ 1024 ];
			GLsizei length;
			glGetProgramInfoLog( program, sizeof( infoBuffer ), &length, infoBuffer );
			wxMessageBox( "Failed to link program " + shaderName + ": " + wxString( infoBuffer ), "Error", wxICON_ERROR | wxCENTRE, wxGetApp().GetFrame() );
			return false;
		}

		success = true;
	}
	while( false );

	if( !success )
		Unload();

	return success;
}

bool ShaderProgram::MakeShader( const wxString& shaderName, GLuint& shader, GLenum shaderType )
{
	shader = 0;

	wxString shaderExt;
	if( shaderType == GL_VERTEX_SHADER )
		shaderExt = "v";
	else if( shaderType == GL_FRAGMENT_SHADER )
		shaderExt = "f";
	else
		return false;

	wxString shaderFile = wxGetApp().ResolveRelativeResourcePath( "Data/Shaders/" + shaderName + "." + shaderExt + ".glsl" );
	wxFileName fileName( shaderFile );
	if( fileName.Exists() )
	{
		wxFile file( shaderFile );
		wxString shaderCode;
		if( !file.ReadAll( &shaderCode ) )
			return false;

		shader = glCreateShader( shaderType );
		if( !shader )
			return false;

		glCompileShader( shader );

		GLint status;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
		if( status == GL_FALSE )
		{
			char infoBuffer[ 1024 ];
			GLsizei length;
			glGetShaderInfoLog( shader, sizeof( infoBuffer ), &length, infoBuffer );
			wxMessageBox( "Failed to compile shader " + shaderName + "." + shaderExt + ": " + wxString( infoBuffer ), "Error", wxICON_ERROR | wxCENTRE, wxGetApp().GetFrame() );
			return false;
		}
	}

	return true;
}

bool ShaderProgram::Unload( void )
{
	if( program )
		glDeleteProgram( program );

	if( vertexShader && glIsShader( vertexShader ) )
		glDeleteShader( vertexShader );

	if( fragmentShader && glIsShader( fragmentShader ) )
		glDeleteShader( fragmentShader );

	program = 0;
	vertexShader = 0;
	fragmentShader = 0;

	return true;
}

bool ShaderProgram::Bind( void )
{
	return true;
}

bool ShaderProgram::Unbind( void )
{
	return true;
}

bool ShaderProgram::SetUniformVector( const wxString& uniformName, const _3DMath::Vector& vector )
{
	return true;
}

// ShaderProgram.cpp