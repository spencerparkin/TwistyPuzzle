// CurvyCopterBase.cpp

#include "CurvyCopterBase.h"
#include <Surface.h>
#include <Sphere.h>

wxIMPLEMENT_ABSTRACT_CLASS( CurvyCopterBase, TwistyPuzzle );

CurvyCopterBase::CurvyCopterBase( void )
{
}

/*virtual*/ CurvyCopterBase::~CurvyCopterBase( void )
{
	Clear();
}

/*virtual*/ void CurvyCopterBase::Clear( void )
{
	TwistyPuzzle::Clear();

	while( jumbleMap.size() > 0 )
	{
		JumbleMap::iterator iter = jumbleMap.begin();
		Jumble* jumble = iter->second;
		delete jumble;
		jumbleMap.erase( iter );
	}
}

/*virtual*/ void CurvyCopterBase::Reset( void )
{
	Clear();

	SetupStandardDynamicEdgeTurningBoxLabels();

	MakeBox( 10.0, 10.0, 10.0 );

	CutShape* cutShapeA = new CutShape();
	cutShapeA->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 5.0, 5.0, 0.0 ) );
	cutShapeA->rotationAngleForSingleTurn = M_PI;
	cutShapeA->axisOfRotation.normal.Set( 1.0, 1.0, 0.0 );
	cutShapeA->axisOfRotation.normal.Normalize();
	cutShapeA->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeA );

	CutShape* cutShapeB = new CutShape();
	cutShapeB->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( -5.0, 5.0, 0.0 ) );
	cutShapeB->rotationAngleForSingleTurn = M_PI;
	cutShapeB->axisOfRotation.normal.Set( -1.0, 1.0, 0.0 );
	cutShapeB->axisOfRotation.normal.Normalize();
	cutShapeB->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeB );

	CutShape* cutShapeC = new CutShape();
	cutShapeC->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 0.0, 5.0, 5.0 ) );
	cutShapeC->rotationAngleForSingleTurn = M_PI;
	cutShapeC->axisOfRotation.normal.Set( 0.0, 1.0, 1.0 );
	cutShapeC->axisOfRotation.normal.Normalize();
	cutShapeC->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeC );

	CutShape* cutShapeD = new CutShape();
	cutShapeD->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 0.0, 5.0, -5.0 ) );
	cutShapeD->rotationAngleForSingleTurn = M_PI;
	cutShapeD->axisOfRotation.normal.Set( 0.0, 1.0, -1.0 );
	cutShapeD->axisOfRotation.normal.Normalize();
	cutShapeD->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeD );

	CutShape* cutShapeE = new CutShape();
	cutShapeE->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 5.0, -5.0, 0.0 ) );
	cutShapeE->rotationAngleForSingleTurn = M_PI;
	cutShapeE->axisOfRotation.normal.Set( 1.0, -1.0, 0.0 );
	cutShapeE->axisOfRotation.normal.Normalize();
	cutShapeE->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeE );

	CutShape* cutShapeF = new CutShape();
	cutShapeF->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( -5.0, -5.0, 0.0 ) );
	cutShapeF->rotationAngleForSingleTurn = M_PI;
	cutShapeF->axisOfRotation.normal.Set( -1.0, -1.0, 0.0 );
	cutShapeF->axisOfRotation.normal.Normalize();
	cutShapeF->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeF );

	CutShape* cutShapeG = new CutShape();
	cutShapeG->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 0.0, -5.0, 5.0 ) );
	cutShapeG->rotationAngleForSingleTurn = M_PI;
	cutShapeG->axisOfRotation.normal.Set( 0.0, -1.0, 1.0 );
	cutShapeG->axisOfRotation.normal.Normalize();
	cutShapeG->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeG );

	CutShape* cutShapeH = new CutShape();
	cutShapeH->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 0.0, -5.0, -5.0 ) );
	cutShapeH->rotationAngleForSingleTurn = M_PI;
	cutShapeH->axisOfRotation.normal.Set( 0.0, -1.0, -1.0 );
	cutShapeH->axisOfRotation.normal.Normalize();
	cutShapeH->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeH );

	CutShape* cutShapeI = new CutShape();
	cutShapeI->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( -5.0, 0.0, -5.0 ) );
	cutShapeI->rotationAngleForSingleTurn = M_PI;
	cutShapeI->axisOfRotation.normal.Set( -1.0, 0.0, -1.0 );
	cutShapeI->axisOfRotation.normal.Normalize();
	cutShapeI->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeI );

	CutShape* cutShapeJ = new CutShape();
	cutShapeJ->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 5.0, 0.0, -5.0 ) );
	cutShapeJ->rotationAngleForSingleTurn = M_PI;
	cutShapeJ->axisOfRotation.normal.Set( 1.0, 0.0, -1.0 );
	cutShapeJ->axisOfRotation.normal.Normalize();
	cutShapeJ->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeJ );

	CutShape* cutShapeK = new CutShape();
	cutShapeK->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( -5.0, 0.0, 5.0 ) );
	cutShapeK->rotationAngleForSingleTurn = M_PI;
	cutShapeK->axisOfRotation.normal.Set( -1.0, 0.0, 1.0 );
	cutShapeK->axisOfRotation.normal.Normalize();
	cutShapeK->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeK );

	CutShape* cutShapeL = new CutShape();
	cutShapeL->surface = MakeCutSphereSurfaceForEdge( _3DMath::Vector( 5.0, 0.0, 5.0 ) );
	cutShapeL->rotationAngleForSingleTurn = M_PI;
	cutShapeL->axisOfRotation.normal.Set( 1.0, 0.0, 1.0 );
	cutShapeL->axisOfRotation.normal.Normalize();
	cutShapeL->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeL );

	PopulateJumbleMap();
}

/*virtual*/ CurvyCopterBase::CutShape* CurvyCopterBase::GetEdgeCutShapeByLetter( char letter )
{
	int count = letter - 'A';
	for( CutShapeList::iterator iter = cutShapeList.begin(); iter != cutShapeList.end(); iter++ )
	{
		CutShape* cutShape = *iter;
		if( count == 0 )
			return cutShape;
		count--;
	}
	return nullptr;
}

void CurvyCopterBase::PopulateJumbleMap( void )
{
	Jumble* jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('D')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('L')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('J')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('C')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('A')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('C')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('I')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('K')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('D')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('B')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('K')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('A')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('L')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('B')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('C')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('J')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('B')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('A')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('I')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('D')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('G')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('J')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('L')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('H')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('E')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('K')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('H')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('G')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('I')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('F')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('L')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('F')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('K')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('E')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('G')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('I')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('E')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('J')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('F')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('H')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('D')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('F')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('B')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('H')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('I')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('A')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('H')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('E')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('D')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('J')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('B')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('G')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('C')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('F')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('K')->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('E')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('C')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('G')->GetHandle() );
	jumble->adjCutShapeHandles.push_back( GetEdgeCutShapeByLetter('A')->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( GetEdgeCutShapeByLetter('L')->GetHandle(), jumble ) );
}

// TODO: How do you jumble if you're using the command-line interface?
/*virtual*/ bool CurvyCopterBase::SpecialAction( double wheelClicks, int selectedObjectHandle, int type )
{
	_3DMath::HandleObject* object = _3DMath::HandleObject::Dereference( selectedObjectHandle );
	if( !object )
		return false;

	CutShape* cutShape = dynamic_cast< CutShape* >( object );
	if( !cutShape )
		return false;

	JumbleMap::iterator iter = jumbleMap.find( cutShape->GetHandle() );
	if( iter == jumbleMap.end() )
		return false;

	EnqueueJumble( iter, type );
	return true;
}

void CurvyCopterBase::EnqueueJumble( JumbleMap::iterator iter, int flags )
{
	int cutShapeHandle = iter->first;
	const Jumble* jumble = iter->second;

	int adjCutShapes[2] = { 0, 0 };
	Rotation::Direction rotDir = Rotation::DIR_CW;

	if( ( flags & 0x00000001 ) == 0 )
	{
		adjCutShapes[0] = jumble->adjCutShapeHandles[0];
		adjCutShapes[1] = jumble->adjCutShapeHandles[1];
		rotDir = Rotation::DIR_CW;
	}
	else
	{
		adjCutShapes[0] = jumble->adjCutShapeHandles[2];
		adjCutShapes[1] = jumble->adjCutShapeHandles[3];
		rotDir = Rotation::DIR_CCW;
	}

	double jumbleTurnAmount = CalcJumbleTurnAmount();

	if( ( flags & 0x00000002 ) != 0 )
	{
		EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, jumbleTurnAmount, Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( cutShapeHandle, Rotation::DIR_CCW, 1.0, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, -jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, -jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN ) );
	}
	else if( ( flags & 0x00000004 ) != 0 )
	{
		EnqueueRotation( new Rotation( cutShapeHandle, rotDir, -jumbleTurnAmount, Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( cutShapeHandle, Rotation::DIR_CCW, 1.0, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, -jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, -jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN | Rotation::FLAG_FORWARD_AGAIN ) );
		EnqueueRotation( new Rotation( cutShapeHandle, rotDir, jumbleTurnAmount, Rotation::FLAG_BACK_AGAIN ) );
	}
}

/*virtual*/ void CurvyCopterBase::EnqueueRandomRotations( _3DMath::Random& random, int rotationCount )
{
	while( rotationCount > 0 )
	{
		if( random.Integer( 0, 3 ) )
			TwistyPuzzle::EnqueueRandomRotations( random, 1 );
		else
		{
			int i = random.Integer( 0, jumbleMap.size() - 1 );
			JumbleMap::iterator iter = jumbleMap.begin();
			while( i > 0 )
			{
				iter++;
				i--;
			}

			EnqueueJumble( iter, random.Integer( 1, 3 ) );
		}

		rotationCount--;
	}
}

// CurvyCopterBase.cpp