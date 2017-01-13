// GLRenderer.cpp

#include "GLRenderer.h"
#include <wx/glcanvas.h>

GLRenderer::GLRenderer( void )
{
}

/*virtual*/ GLRenderer::~GLRenderer( void )
{
}

/*virtual*/ void GLRenderer::BeginDrawMode( DrawMode drawMode )
{
	GLenum mode = GL_POINTS;

	switch( drawMode )
	{
		case DRAW_MODE_POINTS:			mode = GL_POINTS;			break;
		case DRAW_MODE_LINES:			mode = GL_LINES;			break;
		case DRAW_MODE_TRIANGLES:		mode = GL_TRIANGLES;		break;
		case DRAW_MODE_QUADS:			mode = GL_QUADS;			break;
		case DRAW_MODE_LINE_STRIP:		mode = GL_LINE_STRIP;		break;
		case DRAW_MODE_LINE_LOOP:		mode = GL_LINE_LOOP;		break;
		case DRAW_MODE_TRIANGLE_STRIP:	mode = GL_TRIANGLE_STRIP;	break;
		case DRAW_MODE_TRIANGLE_FAN:	mode = GL_TRIANGLE_FAN;		break;
		case DRAW_MODE_QUAD_STRIP:		mode = GL_QUAD_STRIP;		break;
		case DRAW_MODE_POLYGON:			mode = GL_POLYGON;			break;
	}

	glBegin( mode );
}

/*virtual*/ void GLRenderer::EndDrawMode( void )
{
	glEnd();
}

/*virtual*/ void GLRenderer::IssueVertex( const _3DMath::Vertex& vertex, int vertexFlags )
{
	if( vertexFlags & VTX_FLAG_TEXCOORDS )
		glTexCoord2d( vertex.texCoords.x, vertex.texCoords.y );

	if( vertexFlags & VTX_FLAG_NORMAL )
		glNormal3d( vertex.normal.x, vertex.normal.y, vertex.normal.z );

	if( vertexFlags & VTX_FLAG_COLOR )
		glColor4d( vertex.color.x, vertex.color.y, vertex.color.z, vertex.alpha );

	if( vertexFlags & VTX_FLAG_POSITION )
		glVertex3d( vertex.position.x, vertex.position.y, vertex.position.z );
}

/*virtual*/ void GLRenderer::Color( const _3DMath::Vector& color, double alpha )
{
	glColor4d( color.x, color.y, color.z, alpha );
}

// GLRenderer.cpp