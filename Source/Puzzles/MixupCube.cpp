// MixupCube.cpp

#include "Application.h"
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

		DoubleSurfaceCutShape* doubleSurfaceCutShape = new DoubleSurfaceCutShape();
		doubleSurfaceCutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( center, normal * -1.0 ) );
		doubleSurfaceCutShape->additionalSurface = new _3DMath::PlaneSurface( _3DMath::Plane( center * -1.0, normal ) );
		doubleSurfaceCutShape->rotationAngleForSingleTurn = M_PI / 4.0;
		doubleSurfaceCutShape->axisOfRotation.normal = normal;
		doubleSurfaceCutShape->axisOfRotation.center = center;
		doubleSurfaceCutShape->label = label++;
		doubleSurfaceCutShape->captureSide = _3DMath::Surface::OUTSIDE;
		cutShapeList.push_back( doubleSurfaceCutShape );

		switch( i / 2 )
		{
			case 0:
			{
				// +X middle slice
				Permutation xSlicePermutation;
				uint xSliceArrayA[] = { 14, 2, 46, 34, 92, 88, 78, 66 };
				xSlicePermutation.DefineCycleArray( xSliceArrayA, 8 );
				uint xSliceArrayB[] = { 13, 39, 45, 81, 95, 71, 77, 7 };
				xSlicePermutation.DefineCycleArray( xSliceArrayB, 8 );
				uint xSliceArrayC[] = { 15, 1, 47, 33, 93, 87, 79, 65 };
				xSlicePermutation.DefineCycleArray( xSliceArrayC, 8 );
				uint xSliceArrayD[] = { 12, 40, 44, 82, 94, 72, 76, 8 };
				xSlicePermutation.DefineCycleArray( xSliceArrayD, 8 );

				if( i % 2 == 0 )
				{
					// +X
					cutShape->ccwPermutation.DefineCycle( 28, 29, 30, 31 );
					cutShape->ccwPermutation.DefineCycle( 16, 19, 22, 25 );
					cutShape->ccwPermutation.DefineCycle( 17, 20, 23, 26 );
					cutShape->ccwPermutation.DefineCycle( 18, 21, 24, 27 );
					cutShape->ccwPermutation.DefineCycle( 38, 80, 70, 6 );
					cutShape->ccwPermutation.DefineCycle( 37, 91, 69, 5 );
					cutShape->ccwPermutation.DefineCycle( 36, 90, 68, 4 );
					cutShape->ccwPermutation.DefineCycle( 35, 89, 67, 3 );

					doubleSurfaceCutShape->ccwPermutation.SetCopy( xSlicePermutation );
				}
				else
				{
					// -X
					cutShape->ccwPermutation.DefineCycle( 60, 61, 62, 63 );
					cutShape->ccwPermutation.DefineCycle( 48, 51, 54, 57 );
					cutShape->ccwPermutation.DefineCycle( 49, 52, 55, 58 );
					cutShape->ccwPermutation.DefineCycle( 50, 53, 56, 59 );
					cutShape->ccwPermutation.DefineCycle( 32, 0, 64, 86 );
					cutShape->ccwPermutation.DefineCycle( 43, 11, 75, 85 );
					cutShape->ccwPermutation.DefineCycle( 42, 10, 74, 84 );
					cutShape->ccwPermutation.DefineCycle( 41, 9, 73, 83 );

					doubleSurfaceCutShape->ccwPermutation.SetInverse( xSlicePermutation );
				}

				break;
			}
			case 1:
			{
				// +Y middle slice
				Permutation ySlicePermutation;
				uint ySliceArrayA[] = { 18, 30, 69, 79, 56, 60, 43, 45 };
				ySlicePermutation.DefineCycleArray( ySliceArrayA, 8 );
				uint ySliceArrayB[] = { 36, 29, 23, 78, 74, 63, 49, 44 };
				ySlicePermutation.DefineCycleArray( ySliceArrayB, 8 );
				uint ySliceArrayC[] = { 17, 31, 68, 76, 55, 61, 42, 46 };
				ySlicePermutation.DefineCycleArray( ySliceArrayC, 8 );
				uint ySliceArrayD[] = { 37, 28, 24, 77, 75, 62, 50, 47 };
				ySlicePermutation.DefineCycleArray( ySliceArrayD, 8 );

				if( i % 2 == 0 )
				{
					// +Y
					cutShape->ccwPermutation.DefineCycle( 12, 13, 14, 15 );
					cutShape->ccwPermutation.DefineCycle( 0, 3, 6, 9 );
					cutShape->ccwPermutation.DefineCycle( 1, 4, 7, 10 );
					cutShape->ccwPermutation.DefineCycle( 2, 5, 8, 11 );
					cutShape->ccwPermutation.DefineCycle( 41, 16, 67, 54 );
					cutShape->ccwPermutation.DefineCycle( 40, 27, 66, 53 );
					cutShape->ccwPermutation.DefineCycle( 39, 26, 65, 52 );
					cutShape->ccwPermutation.DefineCycle( 38, 25, 64, 51 );

					doubleSurfaceCutShape->ccwPermutation.SetCopy( ySlicePermutation );
				}
				else
				{
					// -Y
					cutShape->ccwPermutation.DefineCycle( 92, 93, 94, 95 );
					cutShape->ccwPermutation.DefineCycle( 80, 83, 86, 89 );
					cutShape->ccwPermutation.DefineCycle( 81, 84, 87, 90 );
					cutShape->ccwPermutation.DefineCycle( 82, 85, 88, 91 );
					cutShape->ccwPermutation.DefineCycle( 35, 48, 73, 22 );
					cutShape->ccwPermutation.DefineCycle( 34, 59, 72, 21 );
					cutShape->ccwPermutation.DefineCycle( 33, 58, 71, 20 );
					cutShape->ccwPermutation.DefineCycle( 32, 57, 70, 19 );

					doubleSurfaceCutShape->ccwPermutation.SetInverse( ySlicePermutation );
				}

				break;
			}
			case 2:
			{
				// +Z middle slice
				Permutation zSlicePermutation;
				uint zSliceArrayA[] = { 29, 27, 13, 11, 61, 59, 93, 91 };
				zSlicePermutation.DefineCycleArray( zSliceArrayA, 8 );
				uint zSliceArrayB[] = { 28, 4, 12, 52, 60, 84, 92, 20 };
				zSlicePermutation.DefineCycleArray( zSliceArrayB, 8 );
				uint zSliceArrayC[] = { 30, 26, 14, 10, 62, 58, 94, 90 };
				zSlicePermutation.DefineCycleArray( zSliceArrayC, 8 );
				uint zSliceArrayD[] = { 31, 5, 15, 53, 63, 85, 95, 21 };
				zSlicePermutation.DefineCycleArray( zSliceArrayD, 8 );

				if( i % 2 == 0 )
				{
					// +Z
					cutShape->ccwPermutation.DefineCycle( 44, 45, 46, 47 );
					cutShape->ccwPermutation.DefineCycle( 32, 35, 38, 41 );
					cutShape->ccwPermutation.DefineCycle( 33, 36, 39, 42 );
					cutShape->ccwPermutation.DefineCycle( 34, 37, 40, 43 );
					cutShape->ccwPermutation.DefineCycle( 83, 19, 3, 51 );
					cutShape->ccwPermutation.DefineCycle( 82, 18, 2, 50 );
					cutShape->ccwPermutation.DefineCycle( 81, 17, 1, 49 );
					cutShape->ccwPermutation.DefineCycle( 80, 16, 0, 48 );

					doubleSurfaceCutShape->ccwPermutation.SetCopy( zSlicePermutation );
				}
				else
				{
					// -Z
					cutShape->ccwPermutation.DefineCycle( 76, 77, 78, 79 );
					cutShape->ccwPermutation.DefineCycle( 64, 67, 70, 73 );
					cutShape->ccwPermutation.DefineCycle( 65, 68, 71, 74 );
					cutShape->ccwPermutation.DefineCycle( 66, 69, 72, 75 );
					cutShape->ccwPermutation.DefineCycle( 9, 25, 89, 57 );
					cutShape->ccwPermutation.DefineCycle( 8, 24, 88, 56 );
					cutShape->ccwPermutation.DefineCycle( 7, 23, 87, 55 );
					cutShape->ccwPermutation.DefineCycle( 6, 22, 86, 54 );

					doubleSurfaceCutShape->ccwPermutation.SetInverse( zSlicePermutation );
				}

				break;
			}
		}
	}

	SetupDynamicLabelsUsingCutShapeList();
}

/*virtual*/ wxString MixupCube::LocateStabChainFile( void ) const
{
	return wxGetApp().ResolveRelativeResourcePath( "Data/StabChains/MixupCube.txt" );
}

// MixupCube.cpp