// Canvas.cpp

#include "Canvas.h"
#include "TwistyPuzzle.h"
#include "Application.h"
#include "GLRenderer.h"
#include "Frame.h"
#include <HandleObject.h>
#include <wx/msgdlg.h>
#include <wx/colordlg.h>

int Canvas::attributeList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };

Canvas::Canvas( wxWindow* parent ) : wxGLCanvas( parent, wxID_ANY, attributeList )
{
	foviAngle = 70.0 * M_PI / 180.0;
	selectedObjectHandle = 0;
	eyeDistance = 20.0;
	mouseDragMode = DRAG_MODE_NONE;
	grip = nullptr;
	axisSelectMode = AXIS_SELECT_MANUAL;
	renderFlags = RENDER_AXES | RENDER_AXIS_LABELS | RENDER_BORDERS | RENDER_DYNAMIC_LABELS;
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
	Bind( wxEVT_RIGHT_DCLICK, &Canvas::OnMouseRightDoubleClick, this );
	Bind( wxEVT_CHAR_HOOK, &Canvas::OnKeyDown, this );
}

/*virtual*/ Canvas::~Canvas( void )
{
	delete context;
	delete renderer;
	delete grip;
}

void Canvas::OnKeyDown( wxKeyEvent& event )
{
	if( event.GetKeyCode() == WXK_ALT )
	{
		// Do nothing here.  I'm not sure if this is an issue on Linux, but on
		// Windows, unless I register this callback, pressing the ALT key will
		// change focus from the canvas to the menu-bar.  This is undesirable,
		// because I'm using ALT as a modifier for actions performed in the canvas.
		// When the focus is taken away, I no longer get motion events in the canvas.
	}
	else
	{
		// We didn't handle it.
		event.Skip();
	}
}

void Canvas::OnMouseRightDown( wxMouseEvent& event )
{
	wxPoint mousePos = event.GetPosition();
	selectedObjectHandle = 0;
	Render( GL_SELECT, &mousePos, &selectedObjectHandle );
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

void Canvas::OnMouseRightDoubleClick( wxMouseEvent& event )
{
	wxPoint mousePos = event.GetPosition();
	selectedObjectHandle = 0;
	Render( GL_SELECT, &mousePos, &selectedObjectHandle );
	TwistyPuzzle::Face* face = dynamic_cast< TwistyPuzzle::Face* >( _3DMath::HandleObject::Dereference( selectedObjectHandle ) );
	if( face )
	{
		wxColourData colorData;
		colorData.SetColour( face->GetColor() );

		wxColourDialog colorDialog( wxGetApp().GetFrame(), &colorData );
		if( wxID_OK == colorDialog.ShowModal() )
		{
			face->SetColor( colorDialog.GetColourData().GetColour() );
		}
	}
}

void Canvas::OnMouseRightUp( wxMouseEvent& event )
{
	if( grip )
	{
		grip->CommitPartialRotation( this );
		delete grip;
		grip = nullptr;
	}

	mouseDragMode = DRAG_MODE_NONE;
	if( HasCapture() )
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

			break;
		}
		case DRAG_MODE_ROTATE_FACES:
		{
			if( !grip )
				grip = new Grip();

			if( !grip->PartiallyRotate( this ) )
			{
				// TODO: Re-render in select mode?  Then try to partially rotate again?  Yeah,
				//       I think it would work, but let's not add that complexity for now if
				//       we may not need it.
			}

			break;
		}
		case DRAG_MODE_NONE:
		{
			if( axisSelectMode == AXIS_SELECT_AUTO )
			{
				TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

				GLint viewport[4];
				glGetIntegerv( GL_VIEWPORT, viewport );

				double viewportWidth = double( viewport[2] );
				double viewportHeight = double( viewport[3] );
				double aspectRatio = viewportWidth / viewportHeight;

				double width = 2.0 * eyeDistance * tan( foviAngle / 2.0 );
				double height = width;
				if( aspectRatio > 1.0 )
					width *= aspectRatio;
				else
					height /= aspectRatio;

				_3DMath::Vector vector;
				double lambda = double( mouseDragCurrentPos.x ) / viewportWidth;
				vector.x = -width / 2.0 + lambda * width;
				lambda = double( viewport[3] - 1 - mouseDragCurrentPos.y ) / viewportHeight;
				vector.y = -height / 2.0 + lambda * height;
				vector.z = 0.0;

				_3DMath::Line line;
				line.center.Set( 0.0, 0.0, eyeDistance );
				line.normal.Subtract( vector, line.center );
				line.normal.Normalize();
				
				TwistyPuzzle::CutShape* cutShape = puzzle->FindCutShapeNearestLine( line, transform );
				if( cutShape )
					selectedObjectHandle = cutShape->GetHandle();
			}

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

	TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

	if( renderMode == GL_RENDER )
	{
		Animate();

		if( renderFlags & RENDER_DYNAMIC_LABELS )
			puzzle->UpdateCutShapeLabels( transform );
	}

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

	if( renderFlags & RENDER_STATS )
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		if( aspectRatio > 1.0 )
			gluOrtho2D( 0.0, 10.0 * aspectRatio, 0.0, 10.0 );
		else
			gluOrtho2D( 0.0, 10.0, 0.0, 10.0 / aspectRatio );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		puzzle->RenderStats( timeKeeper );
	}

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

	gluPerspective( foviAngle * 180.0 / M_PI, aspectRatio, 0.1, 1000.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, eyeDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	puzzle->Render( *renderer, transform, renderMode, selectedObjectHandle, renderFlags );

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

		int flags = 0;
		for( int i = 0; i <= 9; i++ )
			if( wxGetKeyState( wxKeyCode( WXK_NUMPAD0 + i ) ) )
				flags |= 1 << i;

		if( flags )
			wxGetApp().GetPuzzle()->SpecialAction( wheelClicks, selectedObjectHandle, flags );
		else
		{
			TwistyPuzzle::Rotation* rotation = new TwistyPuzzle::Rotation( selectedObjectHandle, direction, wheelClicks );
			wxGetApp().GetPuzzle()->EnqueueRotation( rotation );
		}
	}
}

void Canvas::SetRenderFlags( int renderFlags )
{
	this->renderFlags = renderFlags;
}

void Canvas::Animate( void )
{
	timeKeeper.MarkCurrentTime();

	if( !grip )
		wxGetApp().GetPuzzle()->ProcessRotationQueue( timeKeeper );
}

void Canvas::BindContext( void )
{
	bool initGlew = false;

	if( !context )
	{
		context = new wxGLContext( this );
		initGlew = true;
	}

	SetCurrent( *context );

	if( initGlew )
	{
		GLenum error = glewInit();
		if( error != GLEW_OK )
		{
			const GLubyte* errorStr = glewGetErrorString( error );
			wxMessageBox( "Failed to initialize GLEW library: " + wxString( errorStr ), "Error", wxICON_ERROR | wxCENTRE, this );
		}

		if( !GLEW_VERSION_2_0 )
			wxMessageBox( "OpenGL 2.0 or higher is required.", "Error", wxICON_ERROR | wxCENTRE, this );
	}
}

//---------------------------------------------------------------------------------------
//                                      Canvas::Grip
//---------------------------------------------------------------------------------------

Canvas::Grip::Grip( void )
{
}

Canvas::Grip::~Grip( void )
{
}

int Canvas::Grip::DetermineCutShapeAndRotation( Canvas* canvas )
{
	// TODO: If two axes overlap, then we need to choose the one that captures fewer faces.  Is that right?  I want the dogic to work better with the right-click-&-drag interface.
	// TODO: If the face handle goes stale, then we need to reselect.  I want an uncut puzzle to turn better with the right-click-&-drag interface.

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

	_3DMath::LinearTransform normalTransform;
	canvas->transform.linearTransform.GetNormalTransform( normalTransform );

	_3DMath::Plane plane;
	face->polygon->GetPlane( plane );
	plane.Transform( canvas->transform, &normalTransform );

	TwistyPuzzle::CutShape* bestCutShape = nullptr;
	double smallestArcLengthDistance = 0.0;

	for( TwistyPuzzle::CutShapeList::iterator iter = puzzle->cutShapeList.begin(); iter != puzzle->cutShapeList.end(); iter++ )
	{
		TwistyPuzzle::CutShape* cutShape = *iter;
		_3DMath::Vector axisNormal = cutShape->axisOfRotation.normal;
		normalTransform.Transform( axisNormal );
		if( axisNormal.AngleBetween( plane.normal ) > M_PI / 16.0 )
		{
			if( face->IsCapturedByCutShape( cutShape ) )
			{
				_3DMath::Vector rejectedAxisNormal;
				axisNormal.RejectFrom( _3DMath::Vector( 0.0, 0.0, 1.0 ), rejectedAxisNormal );

				double angle = rejectedAxisNormal.AngleBetween( mouseVector );
				double arcLengthDistance = fabs( angle - M_PI / 2.0 );
				if( smallestArcLengthDistance == 0.0 || arcLengthDistance < smallestArcLengthDistance )
				{
					smallestArcLengthDistance = arcLengthDistance;
					bestCutShape = cutShape;
				}
			}
		}
	}

	if( bestCutShape )
	{
		bestCutShape->rotationAngleForAnimation = mouseVector.Length() / 50.0;

		_3DMath::Vector center;
		face->polygon->GetCenter( center );
		canvas->transform.Transform( center );

		_3DMath::Vector intersectionPoint;

		TwistyPuzzle::FaceList::iterator iter = puzzle->faceList.begin();
		while( iter != puzzle->faceList.end() )
		{
			TwistyPuzzle::Face* face = *iter;
			face->polygon->GetPlane( plane );

			if( plane.Intersect( bestCutShape->axisOfRotation, intersectionPoint ) )
				if( face->polygon->ContainsPoint( intersectionPoint ) )
					break;

			iter++;
		}

		if( iter != puzzle->faceList.end() )
		{
			canvas->transform.Transform( intersectionPoint );

			_3DMath::Vector axisNormal = bestCutShape->axisOfRotation.normal;
			normalTransform.Transform( axisNormal );

			_3DMath::LinearTransform linearTransform;
			linearTransform.xAxis = axisNormal;
			linearTransform.yAxis = center - intersectionPoint;
			linearTransform.zAxis = mouseVector;

			double det = linearTransform.Determinant();
			if( det < 0.0 )
				bestCutShape->rotationAngleForAnimation = -bestCutShape->rotationAngleForAnimation;
		}
	
		return bestCutShape->GetHandle();
	}

	return 0;
}

bool Canvas::Grip::PartiallyRotate( Canvas* canvas )
{
	int cutShapeHandle = DetermineCutShapeAndRotation( canvas );
	if( !cutShapeHandle )
		return false;

	TwistyPuzzle::CutShape* cutShape = dynamic_cast< TwistyPuzzle::CutShape* >( _3DMath::HandleObject::Dereference( cutShapeHandle ) );
	if( cutShape )
	{
		TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();
		puzzle->ApplyCutShapeWithRotation( cutShape, nullptr );
	}

	return true;
}

bool Canvas::Grip::CommitPartialRotation( Canvas* canvas )
{
	int cutShapeHandle = DetermineCutShapeAndRotation( canvas );
	if( !cutShapeHandle )
		return false;

	TwistyPuzzle::CutShape* cutShape = dynamic_cast< TwistyPuzzle::CutShape* >( _3DMath::HandleObject::Dereference( cutShapeHandle ) );
	if( cutShape )
	{
		TwistyPuzzle* puzzle = wxGetApp().GetPuzzle();

		TwistyPuzzle::Rotation* rotation = puzzle->CalculateNearestRotation( cutShape );
		if( rotation )
		{
			puzzle->EnqueueRotation( rotation );
			puzzle->DequeueAndProcessNextRotation();
		}
	}

	return false;
}

// Canvas.cpp