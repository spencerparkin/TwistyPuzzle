// Canvas.cpp

#include "Canvas.h"
#include "TwistyPuzzle.h"
#include "Application.h"
#include "GLRenderer.h"
#include <gl/GLU.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	eyeDistance = 20.0;
	mouseDragging = false;

	context = nullptr;
	renderer = new GLRenderer();

	Bind( wxEVT_PAINT, &Canvas::OnPaint, this );
	Bind( wxEVT_SIZE, &Canvas::OnSize, this );
	Bind( wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this );
	Bind( wxEVT_LEFT_UP, &Canvas::OnMouseLeftUp, this );
	Bind( wxEVT_MOTION, &Canvas::OnMouseMotion, this );
	Bind( wxEVT_MOUSE_CAPTURE_LOST, &Canvas::OnMouseCaptureLost, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
	delete renderer;
}

void Canvas::OnMouseLeftDown( wxMouseEvent& event )
{
	mouseDragging = true;
	mouseDragLastPos = event.GetPosition();
	CaptureMouse();
}

void Canvas::OnMouseLeftUp( wxMouseEvent& event )
{
	mouseDragging = false;
	ReleaseCapture();
}

void Canvas::OnMouseMotion( wxMouseEvent& event )
{
	if( mouseDragging )
	{
		wxPoint mouseCurrentPos = event.GetPosition();
		wxPoint mouseDelta = mouseCurrentPos - mouseDragLastPos;
		mouseDragLastPos = mouseCurrentPos;

		double rotationRate = 0.01;
		double xAngle = rotationRate * double( mouseDelta.y );
		double yAngle = rotationRate * double( mouseDelta.x );

		_3DMath::Vector xAxis( 1.0, 0.0, 0.0 );
		_3DMath::Vector yAxis( 0.0, 1.0, 0.0 );

		_3DMath::AffineTransform rotation;

		rotation.linearTransform.SetRotation( xAxis, xAngle );
		transform.Concatinate( rotation );

		rotation.linearTransform.SetRotation( yAxis, yAngle );
		transform.Concatinate( rotation );

		Refresh();
	}
}

void Canvas::OnMouseCaptureLost( wxMouseCaptureLostEvent& event )
{
	mouseDragging = false;
}

void Canvas::OnPaint( wxPaintEvent& event )
{
	BindContext();

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	double aspectRatio = double( viewport[2] ) / double( viewport[3] );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspectRatio, 0.1, 1000.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, eyeDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	wxGetApp().GetPuzzle()->Render( *renderer, transform );

	glFlush();

	SwapBuffers();
}

void Canvas::OnSize( wxSizeEvent& event )
{
	wxSize size = event.GetSize();
	glViewport( 0, 0, size.GetWidth(), size.GetHeight() );

	Refresh();
}

void Canvas::BindContext( void )
{
	if( !context )
		context = new wxGLContext( this );

	SetCurrent( *context );
}

// Canvas.cpp