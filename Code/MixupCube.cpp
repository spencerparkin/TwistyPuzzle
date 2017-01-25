// MixupCube.cpp

#include "MixupCube.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( MixupCube, TwistyPuzzle );

MixupCube::MixupCube( void )
{
}

/*virtual*/ MixupCube::~MixupCube( void )
{
}

/*virtual*/ void MixupCube::Reset( void )
{
	Clear();

	double radius = 5.0;

	MakeBox( radius * 2.0, radius * 2.0, radius * 2.0 );

	double distance = radius * tan( M_PI / 8.0 );

	char label = 'A';

	for( int i = 0; i < 6; i++ )
	{
		_3DMath::Vector center, normal;

		switch( i / 2 )
		{
			case 0: normal.Set( 1.0, 0.0, 0.0 ); break;
			case 1: normal.Set( 0.0, 1.0, 0.0 ); break;
			case 2: normal.Set( 0.0, 0.0, 1.0 ); break;
		}

		if( i % 2 )
			normal.Negate();

		center = center + normal * distance;

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal ) );
		cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->label = label++;
		cutShapeList.push_back( cutShape );

		MixupLayerCutShape* mixupCutShape = new MixupLayerCutShape();
		mixupCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal * -1.0 ) );
		mixupCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( center * -1.0, normal ) );
		mixupCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
		mixupCutShape->axisOfRotation.normal = normal;
		mixupCutShape->axisOfRotation.center = center;
		mixupCutShape->label = label++;
		cutShapeList.push_back( mixupCutShape );
	}

	SetupDynamicLabelUsingCutShapeList();
}

MixupLayerCutShape::MixupLayerCutShape( void )
{
}

/*virtual*/ MixupLayerCutShape::~MixupLayerCutShape( void )
{
}

// This is somewhat of a hack to compensate for the lack of
// sophistication had by the polygon split algorithm.  It can't
// do splits that result in more than two polygons.
/*virtual*/ void MixupLayerCutShape::CutAndCapture( TwistyPuzzle::FaceList& faceList, TwistyPuzzle::FaceList& capturedFaceList, double eps /*= EPSILON*/ )
{
	CutShape::CutAndCapture( faceList, capturedFaceList, eps );

	_3DMath::Surface* tempSurface = surface;
	surface = additionalSurface;

	CutShape::CutAndCapture( faceList, capturedFaceList, eps );

	surface = tempSurface;

	capturedFaceList.clear();

	for( TwistyPuzzle::FaceList::const_iterator iter = faceList.cbegin(); iter != faceList.cend(); iter++ )
	{
		TwistyPuzzle::Face* face = *iter;
		
		bool capturedA = face->IsCapturedBySurface( surface, _3DMath::Surface::OUTSIDE );
		bool capturedB = face->IsCapturedBySurface( additionalSurface, _3DMath::Surface::OUTSIDE );

		if( capturedA && capturedB )
			capturedFaceList.push_back( face );
	}
}

// MixupCube.cpp