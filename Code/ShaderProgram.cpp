// ShaderProgram.cpp

#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Application.h"
#include "Frame.h"
#include <wx/glcanvas.h>
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

		glLinkProgram( program );

		GLint status;
		glGetProgramiv( program, GL_LINK_STATUS, &status );
		if( status == GL_FALSE )
		{
			GLint logLength = 0;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
			if( logLength > 0 )
			{
				char* infoBuffer = new char[ logLength + 1 ];
				glGetProgramInfoLog( program, logLength, nullptr, infoBuffer );
				wxMessageBox( "Failed to link program " + shaderName + ": " + wxString( infoBuffer ), "Error", wxICON_ERROR | wxCENTRE, wxGetApp().GetFrame() );
				delete[] infoBuffer;
			}

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

		const char* shaderCodeCStr = ( const char* )shaderCode.c_str();
		GLint shaderCodeLen = shaderCode.Length();
		glShaderSource( shader, 1, &shaderCodeCStr, &shaderCodeLen );
		glCompileShader( shader );

		GLint status;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
		if( status == GL_FALSE )
		{
			char infoBuffer[ 1024 ];
			glGetShaderInfoLog( shader, sizeof( infoBuffer ), nullptr, infoBuffer );
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
	if( !glIsProgram( program ) )
		return false;

	glUseProgram( program );
	return true;
}

bool ShaderProgram::Unbind( void )
{
	glUseProgram(0);
	return true;
}

bool ShaderProgram::SetUniformVector( const wxString& uniformName, const _3DMath::Vector& vector )
{
	GLint location = glGetUniformLocation( program, ( const char* )uniformName.c_str() );
	if( location < 0 )
		return false;

	glUniform3f( location, ( float )vector.x, ( float )vector.y, ( float )vector.z );

	GLenum error = glGetError();
	if( error == GL_INVALID_OPERATION )
		return false;

	return true;
}

bool ShaderProgram::SetUniformVectorArray( const wxString& uniformName, const _3DMath::Vector* vectorArray, int vectorCount )
{
	GLint location = glGetUniformLocation( program, ( const char* )uniformName.c_str() );
	if( location < 0 )
		return false;

	float* floatArray = new float[ 3 * vectorCount ];
	int j = 0;
	for( int i = 0; i < vectorCount; i++ )
	{
		floatArray[ j++ ] = ( float )vectorArray[i].x;
		floatArray[ j++ ] = ( float )vectorArray[i].y;
		floatArray[ j++ ] = ( float )vectorArray[i].z;
	}

	glUniform3fv( location, vectorCount, floatArray );

	delete[] floatArray;

	GLenum error = glGetError();
	if( error == GL_INVALID_OPERATION )
		return false;

	return true;
}

bool ShaderProgram::SetUniformFloat( const wxString& uniformName, double value )
{
	GLint location = glGetUniformLocation( program, ( const char* )uniformName.c_str() );
	if( location < 0 )
		return false;

	glUniform1f( location, ( float )value );

	GLenum error = glGetError();
	if( error == GL_INVALID_OPERATION )
		return false;

	return true;
}

bool ShaderProgram::SetUniformFloatArray( const wxString& uniformName, const double* valueArray, int valueCount )
{
	GLint location = glGetUniformLocation( program, ( const char* )uniformName.c_str() );
	if( location < 0 )
		return false;

	float* floatArray = new float[ valueCount ];
	for( int i = 0; i < valueCount; i++ )
		floatArray[i] = ( float )valueArray[i];

	glUniform1fv( location, valueCount, floatArray );

	delete[] floatArray;

	GLenum error = glGetError();
	if( error == GL_INVALID_OPERATION )
		return false;

	return true;
}

bool ShaderProgram::SetUniformInt( const wxString& uniformName, int value )
{
	GLint location = glGetUniformLocation( program, ( const char* )uniformName.c_str() );
	if( location < 0 )
		return false;

	glUniform1i( location, value );

	GLenum error = glGetError();
	if( error == GL_INVALID_OPERATION )
		return false;

	return true;
}

// ShaderProgram.cpp