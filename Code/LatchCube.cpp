// LatchCube.cpp

#include "LatchCube.h"

wxIMPLEMENT_DYNAMIC_CLASS( LatchCube, Rubiks3x3x3 );

LatchCube::LatchCube( void )
{
}

/*virtual*/ LatchCube::~LatchCube( void )
{
}

/*virtual*/ bool LatchCube::LoadFromXml( const wxXmlDocument& xmlDocument )
{
	if( !TwistyPuzzle::LoadFromXml( xmlDocument ) )
		return false;

	// TODO: Load constraint data.
	return true;
}

/*virtual*/ bool LatchCube::SaveToXml( wxXmlDocument& xmlDocument ) const
{
	if( !TwistyPuzzle::SaveToXml( xmlDocument ) )
		return false;

	// TODO: Save constraint data.
	return true;
}

/*virtual*/ void LatchCube::Reset( void )
{
	Rubiks3x3x3::Reset();

	constraintList.clear();

	Constraint constraint;

	// -X -> cw
	constraint.direction = Rotation::DIR_CW;
	constraint.location.Set( -2.0, 1.0, 0.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( -2.0, -1.0, 0.0 );
	constraintList.push_back( constraint );

	// +X -> ccw
	constraint.direction = Rotation::DIR_CCW;
	constraint.location.Set( 2.0, 1.0, 0.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( 2.0, -1.0, 0.0 );
	constraintList.push_back( constraint );

	// -Y -> ccw
	constraint.direction = Rotation::DIR_CCW;
	constraint.location.Set( 0.0, -2.0, -1.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( 0.0, -2.0, 1.0 );
	constraintList.push_back( constraint );

	// +Y -> ccw
	constraint.direction = Rotation::DIR_CCW;
	constraint.location.Set( 0.0, 2.0, -1.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( 0.0, 2.0, 1.0 );
	constraintList.push_back( constraint );

	// -Z -> cw
	constraint.direction = Rotation::DIR_CW;
	constraint.location.Set( -1.0, 0.0, -2.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( 1.0, 0.0, -2.0 );
	constraintList.push_back( constraint );

	// +Z -> cw
	constraint.direction = Rotation::DIR_CW;
	constraint.location.Set( -1.0, 0.0, 2.0 );
	constraintList.push_back( constraint );
	constraint.location.Set( 1.0, 0.0, 2.0 );
	constraintList.push_back( constraint );
}

/*virtual*/ void LatchCube::Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, int renderFlags )
{
	Rubiks3x3x3::Render( renderer, transform, renderMode, selectedObjectHandle, renderFlags );

	for( ConstraintList::iterator iter = constraintList.begin(); iter != constraintList.end(); iter++ )
	{
		Constraint& constraint = *iter;

		_3DMath::Vector axis;
		if( constraint.location.x == -2.0 )
			axis.Set( -1.0, 0.0, 0.0 );
		else if( constraint.location.x == 2.0 )
			axis.Set( 1.0, 0.0, 0.0 );
		else if( constraint.location.y == -2.0 )
			axis.Set( 0.0, -1.0, 0.0 );
		else if( constraint.location.y == 2.0 )
			axis.Set( 0.0, 1.0, 0.0 );
		else if( constraint.location.z == -2.0 )
			axis.Set( 0.0, 0.0, -1.0 );
		else if( constraint.location.z == 2.0 )
			axis.Set( 0.0, 0.0, 1.0 );
		else
			continue;

		_3DMath::Vector vector;
		if( constraint.direction == Rotation::DIR_CCW )
			vector.Cross( axis, constraint.location );
		else if( constraint.direction == Rotation::DIR_CW )
			vector.Cross( constraint.location, axis );
		else
			continue;

		double length = 10.0 / 3.0;
		vector.Scale( length / vector.Length() );

		_3DMath::Vector position( constraint.location );
		position.Scale( 10.0 / 3.0 );
		position.AddScale( vector, -0.5 );
		position.AddScale( axis, -10.0 / 6.5 );

		_3DMath::Vector color( 0.5, 0.5, 0.5 );

		_3DMath::LinearTransform normalTransform;
		transform.linearTransform.GetNormalTransform( normalTransform );

		transform.Transform( position );
		normalTransform.Transform( vector );

		renderer.DrawVector( vector, position, color, 1.0, 0.5 );
	}
}

/*virtual*/ bool LatchCube::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	if( rotation && !CanRotate( rotation ) )
		return false;

	return Rubiks3x3x3::ApplyCutShapeWithRotation( cutShape, rotation );
}

/*virtual*/ void LatchCube::ApplyingTransformWithRotation( const _3DMath::AffineTransform& transform, const Rotation* rotation )
{
	CutShape* cutShape = ( CutShape* )CutShape::Dereference( rotation->cutShapeHandle );

	_3DMath::Vector center( cutShape->axisOfRotation.normal );
	center.Scale( 0.5 );

	_3DMath::Plane plane;
	plane.SetCenterAndNormal( center, cutShape->axisOfRotation.normal );

	for( ConstraintList::iterator iter = constraintList.begin(); iter != constraintList.end(); iter++ )
	{
		Constraint& constraint = *iter;
		if( plane.GetSide( constraint.location ) == _3DMath::Plane::SIDE_FRONT )
		{
			transform.Transform( constraint.location );
			constraint.location.x = round( constraint.location.x );
			constraint.location.y = round( constraint.location.y );
			constraint.location.z = round( constraint.location.z );
		}
	}
}

bool LatchCube::CanRotate( const Rotation* rotation ) const
{
	CutShape* cutShape = ( CutShape* )CutShape::Dereference( rotation->cutShapeHandle );
	if( !cutShape )
		return false;

	double eps = 1e-4;

	int offset = 0;
	double target = 0.0;

	if( _3DMath::Vector( -1.0, 0.0, 0.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 0;
		target = -2.0;
	}
	else if( _3DMath::Vector( 1.0, 0.0, 0.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 0;
		target = 2.0;
	}
	else if( _3DMath::Vector( 0.0, -1.0, 0.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 1;
		target = -2.0;
	}
	else if( _3DMath::Vector( 0.0, 1.0, 0.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 1;
		target = 2.0;
	}
	else if( _3DMath::Vector( 0.0, 0.0, -1.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 2;
		target = -2.0;
	}
	else if( _3DMath::Vector( 0.0, 0.0, 1.0 ).IsEqualTo( cutShape->axisOfRotation.normal, eps ) )
	{
		offset = 2;
		target = 2.0;
	}
	else
		return false;

	int ccwCount = 0;
	int cwCount = 0;

	for( ConstraintList::const_iterator iter = constraintList.cbegin(); iter != constraintList.cend(); iter++ )
	{
		const Constraint& constraint = *iter;
		double* component = ( double* )&constraint.location.x;
		if( fabs( component[ offset ] - target ) < eps )
		{
			if( constraint.direction == Rotation::DIR_CCW )
				ccwCount++;
			else if( constraint.direction == Rotation::DIR_CW )
				cwCount++;
		}
	}

	if( ccwCount > 0 && cwCount > 0 )
		return false;

	return true;
}

// LatchCube.cpp