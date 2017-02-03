// Cuboid3x3x3Base.cpp

#include "Cuboid3x3x3Base.h"
#include <Surface.h>
#include <Plane.h>
#include <Polygon.h>

wxIMPLEMENT_ABSTRACT_CLASS( Cuboid3x3x3Base, TwistyPuzzle );

Cuboid3x3x3Base::Cuboid3x3x3Base( int negX, int posX, int negY, int posY, int negZ, int posZ )
{
	this->negX = negX;
	this->posX = posX;
	this->negY = negY;
	this->posY = posY;
	this->negZ = negZ;
	this->posZ = posZ;
}

/*virtual*/ Cuboid3x3x3Base::~Cuboid3x3x3Base( void )
{
	Clear();
}

/*virtual*/ void Cuboid3x3x3Base::Clear( void )
{
	TwistyPuzzle::Clear();
}

/*virtual*/ void Cuboid3x3x3Base::Reset( void )
{
	_3DMath::LinearTransform transform;

	transform.Identity();
	MakeHead( transform, posY );

	transform.SetRotation( _3DMath::Vector( 1.0, 0.0, 0.0 ), M_PI );
	MakeHead( transform, negY );

	transform.SetRotation( _3DMath::Vector( 1.0, 0.0, 0.0 ), M_PI / 2.0 );
	MakeHead( transform, posZ );

	transform.SetRotation( _3DMath::Vector( 1.0, 0.0, 0.0 ), -M_PI / 2.0 );
	MakeHead( transform, negZ );

	transform.SetRotation( _3DMath::Vector( 0.0, 0.0, 1.0 ), -M_PI / 2.0 );
	MakeHead( transform, posX );

	transform.SetRotation( _3DMath::Vector( 0.0, 0.0, 1.0 ), M_PI / 2.0 );
	MakeHead( transform, negX );
}

void Cuboid3x3x3Base::MakeHead( const _3DMath::LinearTransform& linearTransform, int extrusion )
{
	double sideLength = 5.0;

	FaceList newFaceList;

	double extraHeight = double( extrusion ) * sideLength / 3.0;

	Face* face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) ); 
	face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
	newFaceList.push_back( face );

	if( extraHeight > 0.0 )
	{
		face = new Face( new _3DMath::Polygon() );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) );
		newFaceList.push_back( face );

		face = new Face( new _3DMath::Polygon() );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
		newFaceList.push_back( face );

		face = new Face( new _3DMath::Polygon() );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0, sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, sideLength / 2.0 ) );
		newFaceList.push_back( face );

		face = new Face( new _3DMath::Polygon() );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( -sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
		face->polygon->vertexArray->push_back( _3DMath::Vector( sideLength / 2.0, sideLength / 2.0 + extraHeight, -sideLength / 2.0 ) );
		newFaceList.push_back( face );
	}

	_3DMath::AffineTransform affineTransform;
	affineTransform.linearTransform = linearTransform;
	affineTransform.translation.Set( 0.0, 0.0, 0.0 );

	while( newFaceList.size() > 0 )
	{
		FaceList::iterator iter = newFaceList.begin();
		Face* face = *iter;
		newFaceList.erase( iter );
		face->polygon->Transform( affineTransform );

		_3DMath::Plane plane;
		face->polygon->GetPlane( plane );

		if( plane.normal.IsEqualTo( _3DMath::Vector( 0.0, 0.0, 1.0 ) ) )
			face->color = orange;
		else if( plane.normal.IsEqualTo( _3DMath::Vector( 0.0, 0.0, -1.0 ) ) )
			face->color = red;
		else if( plane.normal.IsEqualTo( _3DMath::Vector( 1.0, 0.0, 1.0 ) ) )
			face->color = green;
		else if( plane.normal.IsEqualTo( _3DMath::Vector( -1.0, 0.0, 0.0 ) ) )
			face->color = blue;
		else if( plane.normal.IsEqualTo( _3DMath::Vector( 0.0, 1.0, 0.0 ) ) )
			face->color = white;
		else if( plane.normal.IsEqualTo( _3DMath::Vector( 0.0, -1.0, 0.0 ) ) )
			face->color = yellow;

		faceList.push_back( face );
	}

	for( int i = 0; i <= extrusion; i++ )
	{
		_3DMath::Vector center;
		center.Set( 0.0, sideLength / 6.0 + double( extrusion ) * sideLength / 3.0, 0.0 );

		_3DMath::Plane plane;
		plane.SetCenterAndNormal( center, _3DMath::Vector( 0.0, 1.0, 0.0 ) );
		plane.Transform( affineTransform );

		_3DMath::Line axisOfRotation;
		axisOfRotation.center.Set( 0.0, 0.0, 0.0 );
		axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
		axisOfRotation.Transform( affineTransform );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( plane );
		cutShape->axisOfRotation = axisOfRotation;
		cutShape->vectorLength = 4.0 + double( extrusion );
		cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
		cutShapeList.push_back( cutShape );
	}
}

// TODO: The cut-shape may need a virtual method: CanBeRotated().  This might also handle puzzles that lock up when jumbled
//       a certain way?  (If we could detect that.)  The easiest way to detect that would be to pre-cut a puzzle, then only
//       let a cut-shape rotate if it doesn't cut anything.
/*virtual*/ bool Cuboid3x3x3Base::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );
}

// Cuboid3x3x3Base.cpp