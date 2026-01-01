// FlowerCopter.cpp

#include "FlowerCopter.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( FlowerCopter, CurvyCopterBase );

FlowerCopter::FlowerCopter( void )
{
}

/*virtual*/ FlowerCopter::~FlowerCopter( void )
{
}

/*virtual*/ void FlowerCopter::Reset( void )
{
	Clear();

	double t = tan( M_PI / 8.0 );

	double L = 10.0;
	double D = L * sqrt( 2.0 ) * ( 1.0 + t*t ) / ( 4.0 * t );
	double x = D / sqrt( 2.0 );
	double y = L / 2.0 - x;
	double sphereRadius = sqrt( x*x + y*y );

	MakeBox( L, L, L );

	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			double a = ( ( j & 1 ) == 0 ) ? 1.0 : -1.0;
			double b = ( ( j & 2 ) == 0 ) ? 1.0 : -1.0;

			_3DMath::Vector normal;
			if( i == 0 )
				normal.Set( a, b, 0.0 );
			else if( i == 1 )
				normal.Set( 0.0, a, b );
			else if( i == 2 )
				normal.Set( a, 0.0, b );

			normal.Normalize();

			_3DMath::Vector sphereCenter = normal * D;

			CutShape* cutShape = new CutShape();
			cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( sphereCenter, sphereRadius ) );
			cutShape->rotationAngleForSingleTurn = M_PI;
			cutShape->axisOfRotation.normal = normal;
			cutShape->captureSide = _3DMath::Surface::INSIDE;
			cutShapeList.push_back( cutShape );
		}
	}

	D = L * sqrt( 3.0 ) * ( 1.0 + t*t ) / ( 4.0 * ( 1.0 - t ) );
	x = D / sqrt( 3.0 );
	y = L / 2.0 - x;
	sphereRadius = sqrt( 2.0*x*x + y*y );

	for( int i = 0; i < 8; i++ )
	{
		_3DMath::Vector normal;

		normal.x = ( i & 1 ) ? -1.0 : 1.0;
		normal.y = ( i & 2 ) ? -1.0 : 1.0;
		normal.z = ( i & 4 ) ? -1.0 : 1.0;

		normal.Normalize();

		_3DMath::Vector sphereCenter = normal * D;

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( sphereCenter, sphereRadius ) );
		cutShape->rotationAngleForSingleTurn = 2.0 * M_PI / 3.0;
		cutShape->axisOfRotation.normal = normal;
		cutShape->captureSide = _3DMath::Surface::INSIDE;
		cutShapeList.push_back( cutShape );
	}

	PopulateJumbleMap();
}

/*virtual*/ FlowerCopter::CutShape* FlowerCopter::GetEdgeCutShapeByLetter( char letter )
{
	// Admittedly, this is really, really, really silly.
	std::map< char, int > letterMap;
	letterMap.insert( std::pair< char, char >( 'A', 'A' ) );
	letterMap.insert( std::pair< char, char >( 'B', 'B' ) );
	letterMap.insert( std::pair< char, char >( 'E', 'C' ) );
	letterMap.insert( std::pair< char, char >( 'F', 'D' ) );
	letterMap.insert( std::pair< char, char >( 'C', 'E' ) );
	letterMap.insert( std::pair< char, char >( 'G', 'F' ) );
	letterMap.insert( std::pair< char, char >( 'D', 'G' ) );
	letterMap.insert( std::pair< char, char >( 'H', 'H' ) );
	letterMap.insert( std::pair< char, char >( 'L', 'I' ) );
	letterMap.insert( std::pair< char, char >( 'K', 'J' ) );
	letterMap.insert( std::pair< char, char >( 'J', 'K' ) );
	letterMap.insert( std::pair< char, char >( 'I', 'L' ) );

	letter = letterMap.find( letter )->second;

	return CurvyCopterBase::GetEdgeCutShapeByLetter( letter );
}

/*virtual*/ double FlowerCopter::CalcJumbleTurnAmount( void )
{
	// The calculation we're making here is exactly the same as that made for the CurvyCopter 1.
	double ppr_radius = 2.8867513459481282;
	_3DMath::Vector ppr_center( 1.6666666666666667, 1.6666666666666667, -1.6666666666666667 );
	_3DMath::Vector ppr_normal( 0.57735026918962573, 0.57735026918962573, -0.57735026918962573 );

	_3DMath::Vector vertex = ppr_center + ppr_normal * ppr_radius;
	_3DMath::Vector origin( 0.0, 0.0, 0.0 );
	_3DMath::Vector pivot( 5.0, 0.0, 0.0 );

	double angle = ( vertex - pivot ).AngleBetween( origin - pivot );
	double amount = angle / M_PI;
	return amount;
}

// FlowerCopter.cpp