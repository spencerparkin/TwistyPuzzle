// PentacleCube.cpp

#include "PentacleCube.h"
#include "Application.h"
#include <Surface.h>
#include <Plane.h>
#include <Sphere.h>

wxIMPLEMENT_DYNAMIC_CLASS( PentacleCube, TwistyPuzzle );

PentacleCube::PentacleCube( void )
{
}

/*virtual*/ PentacleCube::~PentacleCube( void )
{
}

/*virtual*/ void PentacleCube::Reset( void )
{
	Clear();

	// +Z

	Face* face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->color = ColorTable(6);
	faceList.push_back( face );

	// -Z

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 0.0, -5.0 ) );
	face->color = ColorTable(0);
	faceList.push_back( face );

	// +Y

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, 5.0, 0.0 ) );
	face->color = ColorTable(8);
	faceList.push_back( face );

	// -Y

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->color = ColorTable(5);
	faceList.push_back( face );

	// +X

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	face->color = ColorTable(1);
	faceList.push_back( face );

	// -X

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

	face = new Face( new _3DMath::Polygon() );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 5.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	face->polygon->vertexArray->push_back( _3DMath::Vector( -5.0, 0.0, 0.0 ) );
	face->color = ColorTable(2);
	faceList.push_back( face );

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

	CutShape* cutShape = nullptr;
		
	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 0.0, 5.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, 1.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'f';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 0.0, -5.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 0.0, -1.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'b';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'u';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'd';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( 1.0, 0.0, 0.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'r';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, 0.0 ), 5.0 ) );
	cutShape->rotationAngleForSingleTurn = M_PI / 10.0;
	cutShape->axisOfRotation.normal.Set( -1.0, 0.0, 0.0 );
	cutShape->vectorLength = 12.0;
	cutShape->label = 'l';
	cutShape->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShape );
}

/*virtual*/ bool PentacleCube::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	if( !TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation ) )
		return false;

	// TODO: Keep track of which of the 4 sides is unlocked for every given face.
	//       Reject a rotation if not all 4 adjacent sides are unlocked on the captured face.
	return false;
}

/*virtual*/ bool PentacleCube::LoadFromXml( const wxXmlDocument& xmlDocument )
{
	if( !TwistyPuzzle::LoadFromXml( xmlDocument ) )
		return false;

	//...
	return true;
}

/*virtual*/ bool PentacleCube::SaveToXml( wxXmlDocument& xmlDocument ) const
{
	if( !TwistyPuzzle::SaveToXml( xmlDocument ) )
		return false;

	//...
	return true;
}

// PentacleCube.cpp