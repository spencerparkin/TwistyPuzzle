// SquareOne.cpp

#include "SquareOne.h"

wxIMPLEMENT_DYNAMIC_CLASS( SquareOne, TwistyPuzzle );

SquareOne::SquareOne( void )
{
	topCutShapeHandle = 0;
	bottomCutShapeHandle = 0;
	rightCutShapeHandle = 0;
	leftCutShapeHandle = 0;

	wedgeAngleDelta = 2.0 * M_PI / 12.0;

	topWedgeSizeArray = new WedgeSizeArray();
	bottomWedgeSizeArray = new WedgeSizeArray();
}

/*virtual*/ SquareOne::~SquareOne( void )
{
	delete topWedgeSizeArray;
	delete bottomWedgeSizeArray;
}

/*virtual*/ void SquareOne::Reset( void )
{
	Clear();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 1.5, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = wedgeAngleDelta;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	topCutShapeHandle = cutShape->GetHandle();

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -1.5, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = wedgeAngleDelta;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	bottomCutShapeHandle = cutShape->GetHandle();

	_3DMath::Vector normal( sin( wedgeAngleDelta / 2.0 ), 0.0, cos( wedgeAngleDelta / 2.0 ) );

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal = normal;
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	rightCutShapeHandle = cutShape->GetHandle();

	normal.Negate();

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 0.0, 0.0 ), normal ) );
	cutShape->rotationAngleForSingleTurn = M_PI;
	cutShape->axisOfRotation.normal = normal;
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	leftCutShapeHandle = cutShape->GetHandle();

	topWedgeSizeArray->push_back(2);
	topWedgeSizeArray->push_back(1);
	topWedgeSizeArray->push_back(2);
	topWedgeSizeArray->push_back(1);
	topWedgeSizeArray->push_back(2);
	topWedgeSizeArray->push_back(1);
	topWedgeSizeArray->push_back(2);
	topWedgeSizeArray->push_back(1);

	topRight = 0;
	topLeft = 4;

	bottomWedgeSizeArray->push_back(1);
	bottomWedgeSizeArray->push_back(2);
	bottomWedgeSizeArray->push_back(1);
	bottomWedgeSizeArray->push_back(2);
	bottomWedgeSizeArray->push_back(1);
	bottomWedgeSizeArray->push_back(2);
	bottomWedgeSizeArray->push_back(1);
	bottomWedgeSizeArray->push_back(2);

	bottomRight = 0;
	bottomLeft = 4;
}

/*virtual*/ bool SquareOne::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	int delta = 1;
	if( rotation->direction == Rotation::DIR_CCW )
		delta = -1;

	int rotationCount = int( rotation->turnCount );
	if( rotationCount < 0 )
		rotationCount *= -1;

	if( topCutShapeHandle == cutShape->GetHandle() )
	{
		int totalSize = RotateIndices( topRight, topLeft, *topWedgeSizeArray, delta, rotationCount );
		cutShape->rotationAngleForSingleTurn = wedgeAngleDelta * double( totalSize );
	}
	else if( bottomCutShapeHandle = cutShape->GetHandle() )
	{
		int totalSize = RotateIndices( bottomRight, bottomLeft, *bottomWedgeSizeArray, delta, rotationCount );
		cutShape->rotationAngleForSingleTurn = wedgeAngleDelta * double( totalSize );
	}
	else if( rightCutShapeHandle == cutShape->GetHandle() || leftCutShapeHandle == cutShape->GetHandle() )
	{
		WedgeSizeArray* newTopWedgeSizeArray = new WedgeSizeArray();
		WedgeSizeArray* newBottomWedgeSizeArray = new WedgeSizeArray();

		int newTopRight = 0;
		int newBottomRight = 0;

		if( rightCutShapeHandle == cutShape->GetHandle() )
		{
			for( int i = bottomRight; i != bottomLeft; i = Wrap( i + 1, ( signed )bottomWedgeSizeArray->size() ) )
				newTopWedgeSizeArray->push_back( ( *bottomWedgeSizeArray )[i] );

			newTopRight = ( signed )newTopWedgeSizeArray->size();

			for( int i = topRight; i != topLeft; i = Wrap( i + 1, ( signed )topWedgeSizeArray->size() ) )
				newTopWedgeSizeArray->push_back( ( *topWedgeSizeArray )[i] );

			for( int i = topRight; i != topLeft; i = Wrap( i + 1, ( signed )topWedgeSizeArray->size() ) )
				newBottomWedgeSizeArray->push_back( ( *topWedgeSizeArray )[i] );

			newBottomRight = ( signed )newBottomWedgeSizeArray->size();

			for( int i = bottomRight; i != bottomLeft; i = Wrap( i + 1, ( signed )bottomWedgeSizeArray->size() ) )
				newBottomWedgeSizeArray->push_back( ( *bottomWedgeSizeArray )[i] );
		}
		else if( leftCutShapeHandle == cutShape->GetHandle() )
		{
			for( int i = topLeft; i != topRight; i = Wrap( i + 1, ( signed )topWedgeSizeArray->size() ) )
				newTopWedgeSizeArray->push_back( ( *topWedgeSizeArray )[i] );

			newTopRight = ( signed )newTopWedgeSizeArray->size();

			for( int i = bottomRight; i != bottomLeft; i = Wrap( i + 1, ( signed )bottomWedgeSizeArray->size() ) )
				newTopWedgeSizeArray->push_back( ( *bottomWedgeSizeArray )[i] );

			for( int i = bottomLeft; i != bottomRight; i = Wrap( i + 1, ( signed )bottomWedgeSizeArray->size() ) )
				newBottomWedgeSizeArray->push_back( ( *bottomWedgeSizeArray )[i] );

			newBottomRight = ( signed )newBottomWedgeSizeArray->size();

			for( int i = topRight; i != topLeft; i = Wrap( i + 1, ( signed )topWedgeSizeArray->size() ) )
				newBottomWedgeSizeArray->push_back( ( *topWedgeSizeArray )[i] );
		}

		delete topWedgeSizeArray;
		delete bottomWedgeSizeArray;

		topWedgeSizeArray = newTopWedgeSizeArray;
		bottomWedgeSizeArray = newBottomWedgeSizeArray;

		topLeft = 0;
		topRight = newTopRight;
		bottomLeft = 0;
		bottomRight = newBottomRight;
	}

	return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );
}

/*virtual*/ TwistyPuzzle::Rotation* SquareOne::CalculateNearestRotation( CutShape* cutShape, double rotationAngle )
{
	if( rightCutShapeHandle == cutShape->GetHandle() || leftCutShapeHandle == cutShape->GetHandle() )
		return TwistyPuzzle::CalculateNearestRotation( cutShape, rotationAngle );

	return nullptr;
}

int SquareOne::RotateIndices( int& right, int& left, const WedgeSizeArray& wedgeSizeArray, int delta, int rotationCount )
{
	int originalRight = right;

	for( int i = 0; i < rotationCount; i++ )
	{
		int balance = 0;

		MoveIndex( right, balance, wedgeSizeArray, delta, SIDE_RIGHT );
	
		while( balance != 0 )
		{
			if( balance < 0 )
				MoveIndex( left, balance, wedgeSizeArray, delta, SIDE_LEFT );
			else if( balance > 0 )
				MoveIndex( right, balance, wedgeSizeArray, delta, SIDE_RIGHT );
		}
	}

	int totalSize = 0;
	int i = originalRight;
	while( i != right )
	{
		totalSize += wedgeSizeArray[i];
		i = Wrap( i + delta, ( signed )wedgeSizeArray.size() );
	}

	return totalSize;
}

void SquareOne::MoveIndex( int& index, int& balance, const WedgeSizeArray& wedgeSizeArray, int delta, Side side )
{
	if( delta > 0 )
	{
		if( side == SIDE_RIGHT )
			balance -= wedgeSizeArray[ index ];
		else if( side == SIDE_LEFT )
			balance += wedgeSizeArray[ index ];
	}

	index = Wrap( index + delta, ( signed )wedgeSizeArray.size() );

	if( delta < 0 )
	{
		if( side == SIDE_RIGHT )
			balance += wedgeSizeArray[ index ];
		else if( side == SIDE_LEFT )
			balance -= wedgeSizeArray[ index ];
	}
}

/*static*/ int SquareOne::Wrap( int i, int modulus )
{
	i %= modulus;
	if( i < 0 )
		i += modulus;
	return i;
}

// SquareOne.cpp