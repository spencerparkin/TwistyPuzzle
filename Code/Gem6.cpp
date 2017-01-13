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

	//_3DMath::TriangleMesh mesh;

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

				mesh.vertexArray->push_back( point );
				vectorArray.push_back( point );
			}
		}
	}

	_3DMath::Vector vector( 1.0, 1.0, 1.0 );
	vector.Scale( majorRadius / vector.Length() );
	mesh.AddSymmetricVertices( vector );

	mesh.FindConvexHull();

	_3DMath::PolygonList polygonFaceList;
	mesh.GeneratePolygonFaceList( polygonFaceList );

	int i = 0;

	for( _3DMath::PolygonList::iterator iter = polygonFaceList.begin(); iter != polygonFaceList.end(); iter++ )
	{
		_3DMath::Polygon* polygon = *iter;
		Face* face = new Face( polygon );
		face->color = ColorTable( i++ );
		faceList.push_back( face );
	}
}

/*virtual*/ void Gem6::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, bool renderAxisLabels )
{
	/*glColor3f( 1.f, 1.f, 1.f );
	glPointSize( 5.f );
	glBegin( GL_POINTS );
	for( int i = 0; i < vectorArray.size(); i++ )
	{
		_3DMath::Vector point = vectorArray[i];
		transform.Transform( point );
		glVertex3f( point.x, point.y, point.z );
	}
	glEnd();

	TwistyPuzzle::Render( renderer, transform, renderMode, selectedObjectHandle, renderAxisLabels );*/

	renderer.DrawTriangleMesh( mesh, _3DMath::Renderer::DRAW_TRIANGLES, &transform );
}

// Gem6.cpp