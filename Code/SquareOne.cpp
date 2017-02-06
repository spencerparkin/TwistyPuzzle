// SquareOne.cpp

#include "SquareOne.h"
#include <wx/debug.h>

wxIMPLEMENT_DYNAMIC_CLASS( SquareOne, TwistyPuzzle );

SquareOne::SquareOne( void )
{
	topCutShapeHandle = 0;
	bottomCutShapeHandle = 0;
	rightCutShapeHandle = 0;
	leftCutShapeHandle = 0;

	wedgeAngle = M_PI / 6.0;

	topRight = nullptr;
	topLeft = nullptr;
	bottomRight = nullptr;
	bottomLeft = nullptr;

	wedgeArray = nullptr;
}

/*virtual*/ SquareOne::~SquareOne( void )
{
}

/*virtual*/ void SquareOne::Clear( void )
{
	TwistyPuzzle::Clear();

	delete[] wedgeArray;
	wedgeArray = nullptr;
}

/*virtual*/ void SquareOne::Reset( void )
{
	Clear();

	SetupStandardDynamicFaceTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, 1.5, 0.0 ), _3DMath::Vector( 0.0, 1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = 0.0;
	cutShape->axisOfRotation.normal.Set( 0.0, 1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	topCutShapeHandle = cutShape->GetHandle();

	cutShape = new CutShape();
	cutShape->surface = new _3DMath::PlaneSurface( _3DMath::Plane( _3DMath::Vector( 0.0, -1.5, 0.0 ), _3DMath::Vector( 0.0, -1.0, 0.0 ) ) );
	cutShape->rotationAngleForSingleTurn = 0.0;
	cutShape->axisOfRotation.normal.Set( 0.0, -1.0, 0.0 );
	cutShape->captureSide = _3DMath::Surface::OUTSIDE;
	cutShapeList.push_back( cutShape );
	bottomCutShapeHandle = cutShape->GetHandle();

	_3DMath::Vector normal( cos( wedgeAngle / 2.0 ), 0.0, -sin( wedgeAngle / 2.0 ) );

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

	wedgeArray = new Wedge[16];

	for( int i = 0; i < 8; i++ )
	{
		int j = ( i + 1 ) % 8;

		Wedge* prevWedge = &wedgeArray[i];
		Wedge* nextWedge = &wedgeArray[j];

		prevWedge->next = nextWedge;
		nextWedge->prev = prevWedge;

		prevWedge = &wedgeArray[ i + 8 ];
		nextWedge = &wedgeArray[ j + 8 ];

		prevWedge->next = nextWedge;
		nextWedge->prev = prevWedge;
	}

	wedgeArray[0].size = 2;
	wedgeArray[1].size = 1;
	wedgeArray[2].size = 2;
	wedgeArray[3].size = 1;
	wedgeArray[4].size = 2;
	wedgeArray[5].size = 1;
	wedgeArray[6].size = 2;
	wedgeArray[7].size = 1;

	wedgeArray[8].size = 1;
	wedgeArray[9].size = 2;
	wedgeArray[10].size = 1;
	wedgeArray[11].size = 2;
	wedgeArray[12].size = 1;
	wedgeArray[13].size = 2;
	wedgeArray[14].size = 1;
	wedgeArray[15].size = 2;

	topRight = &wedgeArray[0];
	topLeft = &wedgeArray[4];

	bottomRight = &wedgeArray[8];
	bottomLeft = &wedgeArray[12];
}

void SquareOne::SanityCheck( void )
{
	int bigWedgeCount = 0;
	int smallWedgeCount = 0;

	for( int i = 0; i < 16; i++ )
	{
		if( wedgeArray[i].size == 1 )
			smallWedgeCount++;
		else if( wedgeArray[i].size == 2 )
			bigWedgeCount++;
	}

	wxASSERT( bigWedgeCount == 8 );
	wxASSERT( smallWedgeCount == 8 );
}

/*virtual*/ bool SquareOne::ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation )
{
	if( !rotation )
		return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );

	if( cutShape->GetHandle() == topCutShapeHandle || cutShape->GetHandle() == bottomCutShapeHandle )
	{
		Rotation::Direction rotDir = rotation->direction;
		int turnCount = int( rotation->turnCount );
		if( turnCount < 0 )
		{
			turnCount = -turnCount;
			rotDir = ( rotDir == Rotation::DIR_CW ) ? Rotation::DIR_CCW : Rotation::DIR_CW;
		}

		while( turnCount > 0 )
		{
			Rotation* subRotation = new Rotation( rotation->cutShapeHandle, rotDir, 1.0 );

			int totalSize = 0;
			if( cutShape->GetHandle() == topCutShapeHandle )
				totalSize = Advance( topRight, topLeft, rotation->direction );
			else if( cutShape->GetHandle() == bottomCutShapeHandle )
				totalSize = Advance( bottomRight, bottomLeft, rotation->direction );

			cutShape->rotationAngleForSingleTurn = wedgeAngle * double( totalSize );
			bool applied = TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, subRotation );
			delete subRotation;
			if( !applied )
				return false;

			turnCount--;
		}

		SanityCheck();
		return true;
	}
	else if( cutShape->GetHandle() == leftCutShapeHandle || cutShape->GetHandle() == rightCutShapeHandle )
	{
		int turnCount = int( rotation->turnCount );
		if( turnCount < 0 )
			turnCount = -turnCount;

		if( turnCount % 2 == 1 )
		{
			Wedge* topRightPrev = topRight->prev;
			Wedge* topLeftPrev = topLeft->prev;
			Wedge* bottomRightPrev = bottomRight->prev;
			Wedge* bottomLeftPrev = bottomLeft->prev;

			topRightPrev->next = bottomRight;
			bottomRight->prev = topRightPrev;

			bottomLeftPrev->next = topLeft;
			topLeft->prev = bottomLeftPrev;

			topLeftPrev->next = bottomLeft;
			bottomLeft->prev = topLeftPrev;

			bottomRightPrev->next = topRight;
			topRight->prev = bottomRightPrev;

			if( cutShape->GetHandle() == rightCutShapeHandle )
			{
				Wedge* wedge = topRight;
				topRight = bottomRight;
				bottomRight = wedge;
			}
			else if( cutShape->GetHandle() == leftCutShapeHandle )
			{
				Wedge* wedge = topLeft;
				topLeft = bottomLeft;
				bottomLeft = wedge;
			}
		}

		SanityCheck();
		return TwistyPuzzle::ApplyCutShapeWithRotation( cutShape, rotation );
	}

	return false;
}

int SquareOne::Advance( Wedge*& wedgeA, Wedge*& wedgeB, Rotation::Direction direction )
{
	int totalSizeA = 0;
	int totalSizeB = 0;

	AdvanceAndAccumulate( wedgeA, direction, totalSizeA );
	AdvanceAndAccumulate( wedgeB, direction, totalSizeB );

	do
	{
		if( totalSizeA < totalSizeB )
			AdvanceAndAccumulate( wedgeA, direction, totalSizeA );
		else if( totalSizeA > totalSizeB )
			AdvanceAndAccumulate( wedgeB, direction, totalSizeB );
	}
	while( totalSizeA != totalSizeB );

	return totalSizeA;
}

void SquareOne::AdvanceAndAccumulate( Wedge*& wedge, Rotation::Direction direction, int& totalSize )
{
	if( direction == Rotation::DIR_CW )
	{
		totalSize += wedge->size;
		wedge = wedge->next;
	}
	else
	{
		wedge = wedge->prev;
		totalSize += wedge->size;
	}
}

/*virtual*/ TwistyPuzzle::Rotation* SquareOne::CalculateNearestRotation( CutShape* cutShape )
{
	if( rightCutShapeHandle == cutShape->GetHandle() || leftCutShapeHandle == cutShape->GetHandle() )
		return TwistyPuzzle::CalculateNearestRotation( cutShape );

	Wedge* right = nullptr;
	Wedge* left = nullptr;

	if( topCutShapeHandle == cutShape->GetHandle() )
	{
		right = topRight;
		left = topLeft;
	}
	else if( bottomCutShapeHandle == cutShape->GetHandle() )
	{
		right = bottomRight;
		left = bottomLeft;
	}

	int turnCount = 0;
	double rotationAngle = 0.0;
	
	std::vector< double > distanceArray;
	distanceArray.push_back( fabs( rotationAngle - cutShape->rotationAngleForAnimation ) );

	while( true )
	{
		turnCount++;

		if( cutShape->rotationAngleForAnimation > 0.0 )
		{
			int totalSize = Advance( right, left, Rotation::DIR_CCW );
			rotationAngle += wedgeAngle * double( totalSize );
			distanceArray.push_back( fabs( rotationAngle - cutShape->rotationAngleForAnimation ) );
			if( rotationAngle >= cutShape->rotationAngleForAnimation )
				break;
		}
		else
		{
			int totalSize = Advance( right, left, Rotation::DIR_CW );
			rotationAngle -= wedgeAngle * double( totalSize );
			distanceArray.push_back( fabs( rotationAngle - cutShape->rotationAngleForAnimation ) );
			if( rotationAngle <= cutShape->rotationAngleForAnimation )
				break;
		}
	}

	double smallestDistance = -1.0;
	int i;
	for( i = 0; i < ( signed )distanceArray.size(); i++ )
	{
		if( smallestDistance == -1.0 || distanceArray[i] < smallestDistance )
		{
			turnCount = i;
			smallestDistance = distanceArray[i];
		}
	}

	if( turnCount == 0 )
		return nullptr;

	Rotation::Direction rotDir = ( cutShape->rotationAngleForAnimation > 0.0 ) ? Rotation::DIR_CCW : Rotation::DIR_CW;
	Rotation* rotation = new Rotation( cutShape->GetHandle(), rotDir, turnCount );
	return rotation;
}

// SquareOne.cpp