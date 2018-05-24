// DreidelCube.cpp

#include "DreidelCube.h"

#include "Application.h"
#include <Surface.h>
#include <Plane.h>

wxIMPLEMENT_DYNAMIC_CLASS( DreidelCube, TwistyPuzzle );

DreidelCube::DreidelCube( void )
{
}

/*virtual*/ DreidelCube::~DreidelCube( void )
{
}

/*virtual*/ void DreidelCube::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* rightCutShape = new CutShape();
	rightCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 5.0 - 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 0.0, 0.0 ) ) );
	rightCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	rightCutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	rightCutShape->label = 'R';
	cutShapeList.push_back( rightCutShape );

	CutShape* leftCutShape = new CutShape();
	leftCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( -5.0 + 10.0 / 3.0, 0.0, 0.0 ), _3DMath::Vector( -1.0, 0.0, 0.0 ) ) );
	leftCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	leftCutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	leftCutShape->label = 'L';
	cutShapeList.push_back( leftCutShape );

	CutShape* upCutShape = new CutShape();
	upCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 5.0 - 10.0 / 3.0, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	upCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	upCutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	upCutShape->label = 'U';
	cutShapeList.push_back( upCutShape );

	CutShape* downCutShape = new CutShape();
	downCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -5.0 + 10 / 3.0, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	downCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	downCutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	downCutShape->label = 'D';
	cutShapeList.push_back( downCutShape );

	CutShape* frontCutShape = new CutShape();
	frontCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 5.0 - 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, 1.0 ) ) );
	frontCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	frontCutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	frontCutShape->label = 'F';
	cutShapeList.push_back( frontCutShape );

	CutShape* backCutShape = new CutShape();
	backCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, -5.0 + 10.0 / 3.0 ), _3DMath::Vector( 0.0, 0.0, -1.0 ) ) );
	backCutShape->rotationAngleForSingleTurn = M_PI / 2.0;
	backCutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	backCutShape->label = 'B';
	cutShapeList.push_back( backCutShape );

	char label = 'a';

	for( int i = 0; i < 2; i++ )
	{
		for( int j = 0; j < 2; j++ )
		{
			for( int k = 0; k < 2; k++ )
			{
				_3DMath::Vector normal;
				normal.x = ( i == 0 ) ? -1.0 : 1.0;
				normal.y = ( j == 0 ) ? -1.0 : 1.0;
				normal.z = ( k == 0 ) ? -1.0 : 1.0;
				normal.Normalize();

				_3DMath::Vector center = normal * _3DMath::Vector( 5.0, 5.0, 5.0 ).Length();
				
				double radius = sqrt( 2.0 ) * 10.0 / 3.0;

				CutShape* cutShape = new CutShape();
				cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( center, radius ) );
				cutShape->rotationAngleForSingleTurn = M_PI / 3.0;
				cutShape->axisOfRotation.normal = normal;
				cutShape->captureSide = _3DMath::Surface::INSIDE;
				cutShape->label = label++;
				cutShapeList.push_back( cutShape );
			}
		}
	}

	SetupDynamicLabelsUsingCutShapeList();
}

// DreidelCube.cpp