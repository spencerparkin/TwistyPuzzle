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

	MakeBox( 10.0, 10.0, 10.0 );

	double radius = CutSphereRadius();

	CutShape* cutShapeA = new CutShape();
	cutShapeA->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 5.0, 0.0 ), radius ) );
	cutShapeA->rotationAngleForSingleTurn = M_PI;
	cutShapeA->axisOfRotation.normal.Set( 1.0, 1.0, 0.0 );
	cutShapeA->axisOfRotation.normal.Normalize();
	cutShapeA->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeA );

	CutShape* cutShapeB = new CutShape();
	cutShapeB->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 5.0, 0.0 ), radius ) );
	cutShapeB->rotationAngleForSingleTurn = M_PI;
	cutShapeB->axisOfRotation.normal.Set( -1.0, 1.0, 0.0 );
	cutShapeB->axisOfRotation.normal.Normalize();
	cutShapeB->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeB );

	CutShape* cutShapeC = new CutShape();
	cutShapeC->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, 5.0 ), radius ) );
	cutShapeC->rotationAngleForSingleTurn = M_PI;
	cutShapeC->axisOfRotation.normal.Set( 0.0, 1.0, 1.0 );
	cutShapeC->axisOfRotation.normal.Normalize();
	cutShapeC->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeC );

	CutShape* cutShapeD = new CutShape();
	cutShapeD->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, 5.0, -5.0 ), radius ) );
	cutShapeD->rotationAngleForSingleTurn = M_PI;
	cutShapeD->axisOfRotation.normal.Set( 0.0, 1.0, -1.0 );
	cutShapeD->axisOfRotation.normal.Normalize();
	cutShapeD->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeD );

	CutShape* cutShapeE = new CutShape();
	cutShapeE->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, -5.0, 0.0 ), radius ) );
	cutShapeE->rotationAngleForSingleTurn = M_PI;
	cutShapeE->axisOfRotation.normal.Set( 1.0, -1.0, 0.0 );
	cutShapeE->axisOfRotation.normal.Normalize();
	cutShapeE->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeE );

	CutShape* cutShapeF = new CutShape();
	cutShapeF->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, -5.0, 0.0 ), radius ) );
	cutShapeF->rotationAngleForSingleTurn = M_PI;
	cutShapeF->axisOfRotation.normal.Set( -1.0, -1.0, 0.0 );
	cutShapeF->axisOfRotation.normal.Normalize();
	cutShapeF->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeF );

	CutShape* cutShapeG = new CutShape();
	cutShapeG->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, 5.0 ), radius ) );
	cutShapeG->rotationAngleForSingleTurn = M_PI;
	cutShapeG->axisOfRotation.normal.Set( 0.0, -1.0, 1.0 );
	cutShapeG->axisOfRotation.normal.Normalize();
	cutShapeG->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeG );

	CutShape* cutShapeH = new CutShape();
	cutShapeH->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 0.0, -5.0, -5.0 ), radius ) );
	cutShapeH->rotationAngleForSingleTurn = M_PI;
	cutShapeH->axisOfRotation.normal.Set( 0.0, -1.0, -1.0 );
	cutShapeH->axisOfRotation.normal.Normalize();
	cutShapeH->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeH );

	CutShape* cutShapeI = new CutShape();
	cutShapeI->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, -5.0 ), radius ) );
	cutShapeI->rotationAngleForSingleTurn = M_PI;
	cutShapeI->axisOfRotation.normal.Set( -1.0, 0.0, -1.0 );
	cutShapeI->axisOfRotation.normal.Normalize();
	cutShapeI->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeI );

	CutShape* cutShapeJ = new CutShape();
	cutShapeJ->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, -5.0 ), radius ) );
	cutShapeJ->rotationAngleForSingleTurn = M_PI;
	cutShapeJ->axisOfRotation.normal.Set( 1.0, 0.0, -1.0 );
	cutShapeJ->axisOfRotation.normal.Normalize();
	cutShapeJ->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeJ );

	CutShape* cutShapeK = new CutShape();
	cutShapeK->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( -5.0, 0.0, 5.0 ), radius ) );
	cutShapeK->rotationAngleForSingleTurn = M_PI;
	cutShapeK->axisOfRotation.normal.Set( -1.0, 0.0, 1.0 );
	cutShapeK->axisOfRotation.normal.Normalize();
	cutShapeK->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeK );

	CutShape* cutShapeL = new CutShape();
	cutShapeL->surface = new _3DMath::SphereSurface( _3DMath::Sphere( _3DMath::Vector( 5.0, 0.0, 5.0 ), radius ) );
	cutShapeL->rotationAngleForSingleTurn = M_PI;
	cutShapeL->axisOfRotation.normal.Set( 1.0, 0.0, 1.0 );
	cutShapeL->axisOfRotation.normal.Normalize();
	cutShapeL->captureSide = _3DMath::Surface::INSIDE;
	cutShapeList.push_back( cutShapeL );

	Jumble* jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeD->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeL->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeJ->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeC->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeA->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeC->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeI->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeK->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeD->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeB->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeK->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeA->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeL->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeB->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeC->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeJ->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeB->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeA->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeI->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeD->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeG->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeJ->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeL->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeH->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeE->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeK->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeH->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeG->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeI->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeF->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeL->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeF->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeK->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeE->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeG->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeI->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeE->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeJ->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeF->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeH->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeD->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeF->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeB->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeH->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeI->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeA->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeH->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeE->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeD->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeJ->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeB->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeG->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeC->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeF->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeK->GetHandle(), jumble ) );

	jumble = new Jumble;
	jumble->adjCutShapeHandles.push_back( cutShapeE->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeC->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeG->GetHandle() );
	jumble->adjCutShapeHandles.push_back( cutShapeA->GetHandle() );
	jumbleMap.insert( std::pair< int, Jumble* >( cutShapeL->GetHandle(), jumble ) );
}

/*virtual*/ bool CurvyCopterBase::SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown )
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

	const Jumble* jumble = iter->second;

	int adjCutShapes[2] = { 0, 0 };
	Rotation::Direction rotDir = Rotation::DIR_CW;

	if( !shiftDown )
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

	EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, jumbleTurnAmount ) );
	EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, jumbleTurnAmount ) );
	EnqueueRotation( new Rotation( cutShape->GetHandle(), Rotation::DIR_CCW, 1.0 ) );
	EnqueueRotation( new Rotation( adjCutShapes[0], rotDir, -jumbleTurnAmount ) );
	EnqueueRotation( new Rotation( adjCutShapes[1], rotDir, -jumbleTurnAmount ) );

	return true;
}

// CurvyCopterBase.cpp