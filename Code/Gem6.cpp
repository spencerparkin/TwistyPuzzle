// Gem6.cpp

#include "Gem6.h"
#include <Surface.h>
#include <Plane.h>
#include <Function.h>

wxIMPLEMENT_DYNAMIC_CLASS( Gem6, TwistyPuzzle );

Gem6::Gem6( void )
{
}

/*virtual*/ Gem6::~Gem6( void )
{
}

/*virtual*/ void Gem6::Reset( void )
{
	Clear();

	double K = ( 1.0 - sqrt( 2.0 ) / 2.0 ) / 2.0;

	_3DMath::Quadratic quadratic;
	quadratic.A = 1.0 + K * K;
	quadratic.B = 2.0 * K * ( 1.0 - K );
	quadratic.C = K * ( K - 2.0 );

	_3DMath::Function::RealArray realArray;
	quadratic.FindZeros( realArray );

	wxASSERT( realArray.size() == 2 );

	double root = realArray[0];
	if( root < 0.0 || root > 1.0 )
		root = realArray[1];

	wxASSERT( 0.0 <= root && root <= 1.0 );

	double angle = asin( root );

	double majorRadius = 10.0;
	double minorRadius = _3DMath::Vector( majorRadius * cos( angle ), majorRadius * sin( angle ), 0.0 ).Distance( _3DMath::Vector( 0.0, majorRadius, 0.0 ) ) / 2.0;

	_3DMath::TriangleMesh mesh;

	double e1 = minorRadius * sqrt( 2.0 * ( 1.0 - sqrt( 2.0 ) / 2.0 ) );
	double e2 = majorRadius * sqrt( 2.0 * ( 1.0 - cos( angle ) ) );
	double error = e1 - e2;

	double lengthToCircleCenter = sqrt( majorRadius * majorRadius - minorRadius * minorRadius );

	for( int i = 0; i < 2; i++ )
	{
		double scalar = ( i == 0 ) ? 1.0 : -1.0;

		for( int j = 0; j < 3; j++ )
		{
			_3DMath::AffineTransform affineTransform;

			switch(j)
			{
				case 0:
				{
					affineTransform.linearTransform.zAxis.Set( scalar, 0.0, 0.0 );
					affineTransform.linearTransform.yAxis.Set( 0.0, 1.0, 0.0 );
					break;
				}
				case 1:
				{
					affineTransform.linearTransform.zAxis.Set( 0.0, scalar, 0.0 );
					affineTransform.linearTransform.yAxis.Set( 0.0, 0.0, 1.0 );
					break;
				}
				case 2:
				{
					affineTransform.linearTransform.zAxis.Set( 0.0, 0.0, scalar );
					affineTransform.linearTransform.yAxis.Set( 1.0, 0.0, 0.0 );
					break;
				}
			}

			affineTransform.linearTransform.xAxis.Cross( affineTransform.linearTransform.yAxis, affineTransform.linearTransform.zAxis );
			affineTransform.translation = affineTransform.linearTransform.zAxis * lengthToCircleCenter;

			for( int k = 0; k < 8; k++ )
			{
				angle = ( 2.0 * M_PI ) * ( double(k) / 8.0 );

				_3DMath::Vector point( minorRadius * cos( angle ), minorRadius * sin( angle ), 0.0 );
				affineTransform.Transform( point );

				double length = point.Length();

				_3DMath::Vertex vertex;
				vertex.position = point;
				vertex.color.Set( 1.0, 0.0, 0.0 );
				mesh.vertexArray->push_back( vertex );
			}
		}
	}

	_3DMath::Triangle triangle;
	triangle.vertex[0].Set( lengthToCircleCenter, 0.0, minorRadius );
	triangle.vertex[1].Set( minorRadius, 0.0, lengthToCircleCenter );
	triangle.vertex[2].Set( minorRadius * cos( M_PI / 4.0 ), minorRadius * sin( M_PI / 4.0 ), lengthToCircleCenter );

	_3DMath::Plane plane;
	triangle.GetPlane( plane );

	_3DMath::Line line( _3DMath::Vector( 0.0, 0.0, 0.0 ), _3DMath::Vector( 1.0, 1.0, 1.0 ) );
	_3DMath::Vector intersectionPoint;
	plane.Intersect( line, intersectionPoint );

	double length = intersectionPoint.Length();

	_3DMath::Vector vertex( 1.0, 1.0, 1.0 );
	vertex.Scale( length / vertex.Length() );
	mesh.AddSymmetricVertices( vertex );

	mesh.FindConvexHull();

	_3DMath::PolygonList polygonFaceList;
	mesh.GeneratePolygonFaceList( polygonFaceList );

	int i = 0;

	_3DMath::PlaneList planeList;

	for( _3DMath::PolygonList::iterator iter = polygonFaceList.begin(); iter != polygonFaceList.end(); iter++ )
	{
		_3DMath::Polygon* polygon = *iter;
		Face* face = new Face( polygon );
		face->color = ColorTable( i++ );
		faceList.push_back( face );

		// TODO: I don't think the cut-planes are being positioned exactly right.
		if( polygon->vertexArray->size() == 5 )
		{
			_3DMath::Vector center;
			polygon->GetCenter( center );

			_3DMath::Plane plane;
			_3DMath::Vector normal;

			normal.x = ( center.x > 0.0 ) ? 1.0 : -1.0;
			normal.y = 0.0;
			normal.z = 0.0;

			plane.SetCenterAndNormal( center, normal );
			AddPlaneIfNotFound( planeList, plane );

			normal.x = 0.0;
			normal.y = ( center.y > 0.0 ) ? 1.0 : -1.0;
			normal.z = 0.0;

			plane.SetCenterAndNormal( center, normal );
			AddPlaneIfNotFound( planeList, plane );

			normal.x = 0.0;
			normal.y = 0.0;
			normal.z = ( center.z > 0.0 ) ? 1.0 : -1.0;

			plane.SetCenterAndNormal( center, normal );
			AddPlaneIfNotFound( planeList, plane );
		}
	}

	for( _3DMath::PlaneList::iterator iter = planeList.begin(); iter != planeList.end(); iter++ )
	{
		const _3DMath::Plane& plane = *iter;

		_3DMath::Vector center;
		plane.GetCenter( center );

		CutShape* cutShape = new CutShape();
		cutShape->surface = new _3DMath::PlaneSurface( plane );

		double length = center.Length();
		if( length < 4.0 )
			cutShape->rotationAngleForSingleTurn = M_PI / 2.0;
		else
			cutShape->rotationAngleForSingleTurn = M_PI / 4.0;

		cutShape->axisOfRotation.normal = plane.normal;
		cutShape->axisOfRotation.center = center;
		cutShapeList.push_back( cutShape );
	}
}

/*virtual*/ bool Gem6::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	if( !TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation ) )
		return false;

	// An improvement in accuracy would unnecessitate this bit of code.
	FaceList::iterator iter = faceList.begin();
	while( iter != faceList.end() )
	{
		FaceList::iterator nextIter = iter;
		nextIter++;

		Face* face = *iter;
		face->UpdateTessellationIfNeeded();
		double area = face->polygon->GetArea();
		if( area < 0.3 )
		{
			delete face;
			faceList.erase( iter );
		}

		iter = nextIter;
	}

	return true;
}

/*static*/ void Gem6::AddPlaneIfNotFound( _3DMath::PlaneList& planeList, const _3DMath::Plane& newPlane )
{
	for( _3DMath::PlaneList::iterator iter = planeList.begin(); iter != planeList.end(); iter++ )
	{
		const _3DMath::Plane& plane = *iter;
		if( plane.IsEqualTo( newPlane, 0.01 ) )
			return;
	}

	planeList.push_back( newPlane );
}

// Gem6.cpp