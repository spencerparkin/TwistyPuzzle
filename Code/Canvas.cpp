// Canvas.cpp

#include "Canvas.h"
#include "TwistyPuzzle.h"
#include "Application.h"
#include "GLRenderer.h"
#include <gl/GLU.h>
#include <HandleObject.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	selectedObjectHandle = 0;
	eyeDistance = 20.0;
	mouseDragging = false;

	context = nullptr;
	renderer = new GLRenderer();

	Bind( wxEVT_PAINT, &Canvas::OnPaint, this );
	Bind( wxEVT_SIZE, &Canvas::OnSize, this );
	Bind( wxEVT_RIGHT_DOWN, &Canvas::OnMouseRightDown, this );
	Bind( wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this );
	Bind( wxEVT_LEFT_UP, &Canvas::OnMouseLeftUp, this );
	Bind( wxEVT_MOTION, &Canvas::OnMouseMotion, this );
	Bind( wxEVT_MOUSE_CAPTURE_LOST, &Canvas::OnMouseCaptureLost, this );
	Bind( wxEVT_MOUSEWHEEL, &Canvas::OnMouseWheel, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
	delete renderer;
}

void Canvas::OnMouseRightDown( wxMouseEvent& event )
{
	wxPoint mousePos = event.GetPosition();
	selectedObjectHandle = 0;
	Render( GL_SELECT, &mousePos, &selectedObjectHandle );
	Refresh();
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

void Canvas::Render( GLenum renderMode, wxPoint* mousePos /*= nullptr*/, int* objectHandle /*= nullptr*/ )
{
	BindContext();

	if( objectHandle )
		*objectHandle = 0;

	int hitBufferSize = 0;
	unsigned int* hitBuffer = nullptr;

	if( renderMode == GL_SELECT )
	{
		hitBufferSize = 512;
		hitBuffer = new unsigned int[ hitBufferSize ];
		glSelectBuffer( hitBufferSize, hitBuffer );
		glRenderMode( GL_SELECT );
		glInitNames();
		glPushName(0);
	}

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
	glShadeModel( GL_SMOOTH );

	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	double aspectRatio = double( viewport[2] ) / double( viewport[3] );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	if( renderMode == GL_SELECT && mousePos )
	{
		GLdouble x = mousePos->x;
		GLdouble y = GLdouble( viewport[3] ) - GLdouble( mousePos->y );
		GLdouble w = 2.0;
		GLdouble h = 2.0;
		gluPickMatrix( x, y, w, h, viewport );
	}

	gluPerspective( 70.0, aspectRatio, 0.1, 1000.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, eyeDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	wxGetApp().GetPuzzle()->Render( *renderer, transform, renderMode, selectedObjectHandle );

	glFlush();

	if( renderMode == GL_RENDER )
		SwapBuffers();
	else if( renderMode == GL_SELECT )
	{
		int hitCount = glRenderMode( GL_RENDER );

		if( objectHandle )
		{
			*objectHandle = 0;
			unsigned int* hitRecord = hitBuffer;
			float smallestZ = 0.0;
			for( int i = 0; i < hitCount; i++ )
			{
				unsigned int nameCount = hitRecord[0];
				float minZ = float( hitRecord[1] ) / float( 0x7FFFFFFFF );
				if( nameCount == 1 )
				{
					if( !*objectHandle || minZ < smallestZ )
					{
						smallestZ = minZ;
						*objectHandle = ( signed )hitRecord[3];
					}
				}
				hitRecord += 3 + nameCount;
			}
		}

		delete[] hitBuffer;
	}
}

void Canvas::OnPaint( wxPaintEvent& event )
{
	Render( GL_RENDER );
}

void Canvas::OnSize( wxSizeEvent& event )
{
	wxSize size = event.GetSize();
	glViewport( 0, 0, size.GetWidth(), size.GetHeight() );

	Refresh();
}

void Canvas::OnMouseWheel( wxMouseEvent& event )
{
	if( selectedObjectHandle )
	{
		double wheelDelta = event.GetWheelDelta();
		double wheelRotation = event.GetWheelRotation();
		int wheelClicks = int( wheelRotation / wheelDelta );

		TwistyPuzzle::Rotation::Direction direction = TwistyPuzzle::Rotation::DIR_CW;
		if( wheelClicks < 0 )
		{
			direction = TwistyPuzzle::Rotation::DIR_CCW;
			wheelClicks = -wheelClicks;
		}

		TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation( selectedObjectHandle, direction, wheelClicks );
		wxGetApp().GetPuzzle()->EnqueueRotation( rotation );
	}
}

void Canvas::Animate( void )
{
	timeKeeper.MarkCurrentTime();

	if( wxGetApp().GetPuzzle()->ProcessRotationQueue( timeKeeper ) )
		Refresh();
}

void Canvas::BindContext( void )
{
	if( !context )
		context = new wxGLContext( this );

	SetCurrent( *context );
}

// Canvas.cpp