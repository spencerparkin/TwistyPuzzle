// Canvas.cpp

#include "Canvas.h"
#include "TwistyPuzzle.h"
#include "Application.h"
#include "GLRenderer.h"
#include "Frame.h"
//#include <gl/GLU.h>
#include <HandleObject.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	selectedObjectHandle = 0;
	eyeDistance = 20.0;
	mouseDragMode = DRAG_MODE_NONE;
	grip = nullptr;
	axisSelectMode = AXIS_SELECT_MANUAL;
	renderAxisLabels = true;
#if defined LINUX
	timeOfLastWheelClickSeconds = 0.0;
#endif

	context = nullptr;
	renderer = new GLRenderer();

	Bind( wxEVT_PAINT, &Canvas::OnPaint, this );
	Bind( wxEVT_SIZE, &Canvas::OnSize, this );
	Bind( wxEVT_RIGHT_DOWN, &Canvas::OnMouseRightDown, this );
	Bind( wxEVT_RIGHT_UP, &Canvas::OnMouseRightUp, this );
	Bind( wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this );
	Bind( wxEVT_LEFT_UP, &Canvas::OnMouseLeftUp, this );
	Bind( wxEVT_MIDDLE_DOWN, &Canvas::OnMouseMiddleDown, this );
	Bind( wxEVT_MIDDLE_UP, &Canvas::OnMouseMiddleUp, this );
	Bind( wxEVT_MOTION, &Canvas::OnMouseMotion, this );
	Bind( wxEVT_MOUSE_CAPTURE_LOST, &Canvas::OnMouseCaptureLost, this );
	Bind( wxEVT_MOUSEWHEEL, &Canvas::OnMouseWheel, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
	delete renderer;
	delete grip;
}

void Canvas::OnMouseRightDown( wxMouseEvent& event )
{
	wxPoint mousePos = event.GetPosition();
	selectedObjectHandle = 0;
	Render( GL_SELECT, &mousePos, &selectedObjectHandle );
	Refresh();
	mouseDragMode = DRAG_MODE_ROTATE_FACES;
	mouseDragLastPos = mousePos;
	mouseDragClickPos = mousePos;
	CaptureMouse();

	TwistyPuzzle::CutShape* cutShape = dynamic_cast< TwistyPuzzle::CutShape* >( _3DMath::HandleObject::Dereference( selectedObjectHandle ) );
	if( cutShape )
	{
		wxString text;
		if( !cutShape->label.empty() )
			text = "Selected rotation axis labeled: " + cutShape->label;
		wxGetApp().GetFrame()->GetStatusBar()->SetStatusText( text );
	}

	if( grip )
	{
		delete grip;
		grip = nullptr;
	}
}

void Canvas::OnMouseRightUp( wxMouseEvent& event )
{
	if( grip )
	{
		//grip->CommitRotation( this );
		delete grip;
		grip = nullptr;
	}

	mouseDragMode = DRAG_MODE_NONE;
	ReleaseMouse();
}

void Canvas::OnMouseLeftDown( wxMouseEvent& event )
{
	mouseDragMode = DRAG_MODE_ORIENT_PUZZLE;
	mouseDragLastPos = event.GetPosition();
	CaptureMouse();
}

void Canvas::OnMouseLeftUp( wxMouseEvent& event )
{
	mouseDragMode = DRAG_MODE_NONE;
	if( HasCapture() )
		ReleaseMouse();
}

void Canvas::OnMouseMiddleDown( wxMouseEvent& event )
{
	mouseDragMode = DRAG_MODE_ORIENT_PUZZLE;
	mouseDragLastPos = event.GetPosition();
	CaptureMouse();
}

void Canvas::OnMouseMiddleUp( wxMouseEvent& event )
{
	mouseDragMode = DRAG_MODE_NONE;
	if( HasCapture() )
		ReleaseMouse();
}

void Canvas::OnMouseMotion( wxMouseEvent& event )
{
	mouseDragCurrentPos = event.GetPosition();
	wxPoint mouseDragDelta = mouseDragCurrentPos - mouseDragLastPos;
	mouseDragLastPos = mouseDragCurrentPos;

	switch( mouseDragMode )
	{
		case DRAG_MODE_ORIENT_PUZZLE:
		{
			double rotationRate = 0.01;
			double xAngle = rotationRate * double( mouseDragDelta.y );
			double yAngle = rotationRate * double( mouseDragDelta.x );

			_3DMath::Vector xAxis( 1.0, 0.0, 0.0 );
			_3DMath::Vector yAxis( 0.0, 1.0, 0.0 );

			_3DMath::AffineTransform rotation;

			rotation.linearTransform.SetRotation( xAxis, xAngle );
			transform.Concatinate( rotation );

			rotation.linearTransform.SetRotation( yAxis, yAngle );
			transform.Concatinate( rotation );

			TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

			if( axisSelectMode == AXIS_SELECT_AUTO )
			{
				_3DMath::Vector zAxis( 0.0, 0.0, 1.0 );
				TwistyPuzzle::CutShape* cutShape = puzzle->FindCutShapeNearestDirection( zAxis, transform );
				if( cutShape )
					selectedObjectHandle = cutShape->GetHandle();
			}

			puzzle->UpdateCutShapeLabels( transform );

			Refresh();
			break;
		}
		case DRAG_MODE_ROTATE_FACES:
		{
			if( !grip )
				grip = new Grip();

			if( !grip->PartiallyRotate( this ) )
			{
				// TODO: Re-render in select mode?
			}

			break;
		}
		case DRAG_MODE_NONE:
		{
			break;
		}
	}
}

void Canvas::OnMouseCaptureLost( wxMouseCaptureLostEvent& event )
{
	if( grip )
	{
		delete grip;
		grip = nullptr;
	}

	mouseDragMode = DRAG_MODE_NONE;
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

	wxGetApp().GetPuzzle()->Render( *renderer, transform, renderMode, selectedObjectHandle, renderAxisLabels );

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
	if( context )
	{
		wxSize size = event.GetSize();
		glViewport( 0, 0, size.GetWidth(), size.GetHeight() );

		Refresh();
	}
}

void Canvas::OnMouseWheel( wxMouseEvent& event )
{
	double wheelDelta = event.GetWheelDelta();
	double wheelRotation = event.GetWheelRotation();
	int wheelClicks = int( wheelRotation / wheelDelta );

	if( event.ShiftDown() && !event.AltDown() )
	{
		double scale = 1.1;
		if( wheelClicks < 0 )
		{
			scale = 0.9;
			wheelClicks *= -1;
		}

		while( wheelClicks > 0 )
		{
			eyeDistance *= scale;
			wheelClicks--;
		}

		Refresh();
	}
	else if( selectedObjectHandle )
	{
#if defined LINUX
		// GTK is sending an extraneous wheel event.  One is for "smooth" wheel clicks,
		// the other is for normal wheel clicks.  From the wxWidgets perspective, I can't
		// differentiate between the two types of events.  Sigh...  So, as a bit of a hack
		// to prevent the unwanted event, I'm going to bail here unless the rotation queue
		// is empty.  Ugh...and unless enough time has gone by.
		if( wxGetApp().GetPuzzle()->rotationQueue.size() > 0 )
			return;

		double currentTimeSeconds = timeKeeper.GetCurrentTimeSeconds();
		double timeSinceLastWheelClickSeconds = currentTimeSeconds - timeOfLastWheelClickSeconds;
		if( timeSinceLastWheelClickSeconds < 0.5 )
			return;

		timeOfLastWheelClickSeconds = currentTimeSeconds;
#endif

		TwistyPuzzle::Rotation::Direction direction = TwistyPuzzle::Rotation::DIR_CW;
		if( wheelClicks < 0 )
		{
			direction = TwistyPuzzle::Rotation::DIR_CCW;
			wheelClicks = -wheelClicks;
		}

		if( event.AltDown() )
			wxGetApp().GetPuzzle()->SpecialAction( wheelClicks, selectedObjectHandle, event.ShiftDown() );
		else
		{
			TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation( selectedObjectHandle, direction, wheelClicks );
			wxGetApp().GetPuzzle()->EnqueueRotation( rotation );
		}
	}
}

void Canvas::SetRenderAxisLabels( bool renderAxisLabels )
{
	this->renderAxisLabels = renderAxisLabels;
	wxGetApp().GetPuzzle()->UpdateCutShapeLabels( transform );
	Refresh();
}

void Canvas::Animate( void )
{
	timeKeeper.MarkCurrentTime();

	if( !grip )
	{
		if( wxGetApp().GetPuzzle()->ProcessRotationQueue( timeKeeper ) )
			Refresh();
	}
}

void Canvas::BindContext( void )
{
	if( !context )
		context = new wxGLContext( this );

	SetCurrent( *context );
}

Canvas::Grip::Grip( void )
{
}

Canvas::Grip::~Grip( void )
{
}

int Canvas::Grip::DetermineCutShapeAndRotation( Canvas* canvas, double& rotationAngle )
{
	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();
	if( !puzzle )
		return 0;

	// This handle could become invalid due to a cut and capture operation we perform during gripping.
	_3DMath::HandleObject* object = _3DMath::HandleObject::Dereference( canvas->selectedObjectHandle );
	TwistyPuzzle::Face* face = dynamic_cast< TwistyPuzzle::Face* >( object );
	if( !face )
		return 0;

	wxPoint mouseDragDelta = canvas->mouseDragCurrentPos - canvas->mouseDragClickPos;
	_3DMath::Vector mouseVector( mouseDragDelta.x, -mouseDragDelta.y, 0.0 );
	mouseVector.Scale( 1.0 );		// This would be some sort of pixels to space-units conversion.

	_3DMath::AffineTransform transformInverse;
	_3DMath::LinearTransform normalTransform;

	// This may simplify to just the transpose.
	canvas->transform.GetInverse( transformInverse );
	transformInverse.linearTransform.GetNormalTransform( normalTransform );

	normalTransform.Transform( mouseVector );

	_3DMath::Vector unitMouseVector;
	mouseVector.GetNormalized( unitMouseVector );

	double smallestDot = 1.0;
	TwistyPuzzle::CutShape* bestCutShape = nullptr;

	_3DMath::Plane plane;
	face->polygon->GetPlane( plane );

	for( TwistyPuzzle::CutShapeList::iterator iter = puzzle->cutShapeList.begin(); iter != puzzle->cutShapeList.end(); iter++ )
	{
		TwistyPuzzle::CutShape* cutShape = *iter;
		if( face->IsCapturedByCutShape( cutShape ) )
		{
			if( fabs( cutShape->axisOfRotation.normal.AngleBetween( plane.normal ) - M_PI / 2.0 ) < M_PI / 4.0 )
			{
				double dot = cutShape->axisOfRotation.normal.Dot( unitMouseVector );
				if( fabs( dot ) < fabs( smallestDot ) )
				{
					smallestDot = dot;
					bestCutShape = cutShape;
				}
			}
		}
	}

	if( bestCutShape )
	{
		rotationAngle = mouseVector.Length() / 50.0;

		_3DMath::LinearTransform linearTransform;
		linearTransform.xAxis = unitMouseVector;
		linearTransform.yAxis = bestCutShape->axisOfRotation.normal;
		linearTransform.zAxis.Set( 0.0, 0.0, 1.0 );

		transformInverse.Transform( linearTransform.zAxis );

		double det = linearTransform.Determinant();
		if( det < 0.0 )
			rotationAngle = -rotationAngle;
	
		return bestCutShape->GetHandle();
	}

	return 0;
}

bool Canvas::Grip::PartiallyRotate( Canvas* canvas )
{
	double rotationAngle = 0.0;
	int cutShapeHandle = DetermineCutShapeAndRotation( canvas, rotationAngle );
	if( !cutShapeHandle )
		return false;

	TwistyPuzzle::CutShape* cutShape = dynamic_cast< TwistyPuzzle::CutShape* >( _3DMath::HandleObject::Dereference( cutShapeHandle ) );
	if( cutShape )
	{
		TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

		TwistyPuzzle::FaceList capturedFaceList;
		cutShape->CutAndCapture( puzzle->faceList, capturedFaceList );

		for( TwistyPuzzle::FaceList::iterator iter = puzzle->faceList.begin(); iter != puzzle->faceList.end(); iter++ )
		{
			TwistyPuzzle::Face* face = *iter;
			face->rotationAngleForAnimation = 0.0;
		}

		for( TwistyPuzzle::FaceList::iterator iter = capturedFaceList.begin(); iter != capturedFaceList.end(); iter++ )
		{
			TwistyPuzzle::Face* face = *iter;
			face->rotationAngleForAnimation = rotationAngle;
			face->axisOfRotation = cutShape->axisOfRotation;
		}

		canvas->Refresh();
	}

	return true;
}

bool Canvas::Grip::CommitRotation( Canvas* canvas )
{
	double rotationAngle = 0.0;
	int cutShapeHandle = DetermineCutShapeAndRotation( canvas, rotationAngle );
	if( !cutShapeHandle )
		return false;

	TwistyPuzzle::CutShape* cutShape = dynamic_cast< TwistyPuzzle::CutShape* >( _3DMath::HandleObject::Dereference( cutShapeHandle ) );
	if( cutShape )
	{
		TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

		TwistyPuzzle::Rotation* rotation = puzzle->CalculateNearestRotation( cutShape, rotationAngle );
		if( rotation )
			puzzle->EnqueueRotation( rotation );

		// TODO: May need to process queue once here before painting occurs?

		canvas->Refresh();
	}

	return false;
}

// Canvas.cpp