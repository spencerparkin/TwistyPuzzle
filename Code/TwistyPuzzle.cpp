// TwistyPuzzle.cpp

#include "TwistyPuzzle.h"
#include <Surface.h>
#include <ListFunctions.h>

//---------------------------------------------------------------------------------
//                                  TwistyPuzzle
//---------------------------------------------------------------------------------

TwistyPuzzle::TwistyPuzzle( void )
{
}

/*virtual*/ TwistyPuzzle::~TwistyPuzzle( void )
{
	Clear();
}

void TwistyPuzzle::Clear( void )
{
	_3DMath::FreeList< Face >( faceList );
	_3DMath::FreeList< CutShape >( cutShapeList );
}

void TwistyPuzzle::SetType( Type type )
{
	Clear();

	this->type = type;

	switch( type )
	{
		case CLASSIC_2x2x2:
		case CLASSIC_3x3x3:
		case CLASSIC_4x4x4:
		case BUBBLOID_3x3x4:
		case BUBBLOID_3x4x4:
		case CURVEY_COPTER:
		case REX_CUBE:
		{
			break;
		}
	}
}

void TwistyPuzzle::Render( void )
{
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::Face
//---------------------------------------------------------------------------------

TwistyPuzzle::Face::Face( void )
{
	tessellationNeeded = true;
}

TwistyPuzzle::Face::~Face( void )
{
}

//---------------------------------------------------------------------------------
//                               TwistyPuzzle::CutShape
//---------------------------------------------------------------------------------

TwistyPuzzle::CutShape::CutShape( void )
{
	rotationDivisor = 1.0;
	rotationAngle = 0.0;

	surface = nullptr;
}

TwistyPuzzle::CutShape::~CutShape( void )
{
	delete surface;
}

void TwistyPuzzle::CutShape::CutAndCapture( FaceList& faceList )
{
}

// TwistyPuzzle.cpp