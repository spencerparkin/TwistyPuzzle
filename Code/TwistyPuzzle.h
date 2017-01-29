// TwistyPuzzle.h

#pragma once

#include <wx/glcanvas.h>
#include <wx/xml/xml.h>
#include <Vector.h>
#include <Polygon.h>
#include <AffineTransform.h>
#include <Renderer.h>
#include <HandleObject.h>
#include <Line.h>
#include <LineSegment.h>
#include <TimeKeeper.h>
#include <Surface.h>
#include <Random.h>
#include <map>

// TODO: It would be interesting if we based a puzzle off of, say, cone-shaped cut objects.
//       This would require that we trace out parts of conic sections.  Calculus methods would be in order?

class ShaderProgram;

class TwistyPuzzle : public wxObject
{
public:

	class CutShape;

	wxDECLARE_ABSTRACT_CLASS( TwistyPuzzle );

	TwistyPuzzle( void );
	virtual ~TwistyPuzzle( void );

	bool Load( const wxString& file );
	bool Save( const wxString& file ) const;

	virtual bool LoadFromXml( const wxXmlDocument& xmlDocument );
	virtual bool SaveToXml( wxXmlDocument& xmlDocument ) const;

	static TwistyPuzzle* AllocateUsingFile( const wxString& file );

	virtual void Clear( void );
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, bool renderAxisLabels, bool renderBorders );
	virtual void RenderStats( const _3DMath::TimeKeeper& timeKeeper );
	virtual void Reset( void ) = 0;
	virtual bool SpecialAction( double wheelClicks, int selectedObjectHandle, bool shiftDown );
	virtual void UpdateCutShapeLabels( const _3DMath::AffineTransform& transform );

	void SetupStandardDynamicFaceTurningBoxLabels( double radius = 10.0 );
	void SetupStandardDynamicCornerTurningBoxLabels( double radius = 10.0 );
	void SetupStandardDynamicEdgeTurningBoxLabels( double radius = 10.0 );
	void SetupDynamicLabelUsingCutShape( const CutShape* cutShape );
	void SetupDynamicLabelUsingCutShapeList( void );

	class Rotation
	{
	public:

		enum Direction { DIR_CW, DIR_CCW };
		enum Flags
		{
			FLAG_HISTORY			= 0x00000001,
			FLAG_BACK_AGAIN			= 0x00000002,
			FLAG_FORWARD_AGAIN		= 0x00000004,
		};

		Rotation( int cutShapeHandle, Direction direction = DIR_CW, double turnCount = 1.0, int flags = 0 );
		~Rotation( void );

		int cutShapeHandle;
		Direction direction;
		double turnCount;
		int flags;
		double newRotationSpeedCoeficient;
	};

	typedef std::list< Rotation* > RotationList;

	virtual Rotation* CalculateNearestRotation( CutShape* cutShape );
	virtual void EnqueueRandomRotations( _3DMath::Random& random, int rotationCount );
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation );
	virtual double GetCutAndCaptureEpsilon( void ) { return EPSILON; }

	// Compute and return a sequence of rotations that gets us closer, if
	// not all the way, to the solved state of the puzzle.  The method is
	// called until an empty list is returned.
	virtual void IncrementallySolve( RotationList& rotationList ) const;
	virtual bool SolveSupported( void ) const { return false; }

	void EnqueueRotation( Rotation* rotation );
	bool ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper );

	class Face : public _3DMath::HandleObject
	{
	public:

		Face( _3DMath::Polygon* polygon );
		~Face( void );

		void UpdateTessellationIfNeeded( void );
		void Render( _3DMath::Renderer& renderer, GLenum renderMode, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform, ShaderProgram* shaderProgram ) const;
		bool IsCapturedByCutShape( CutShape* cutShape ) const;
		bool IsCapturedBySurface( _3DMath::Surface* surface, _3DMath::Surface::Side captureSide ) const;
		bool Save( wxXmlNode* xmlFaceNode ) const;
		bool Load( const wxXmlNode* xmlFaceNode );

		_3DMath::Vector color;
		_3DMath::Polygon* polygon;
		int boundCutShapeHandle;
		bool tessellationNeeded;
	};

	typedef std::list< Face* > FaceList;

	class CutShape : public _3DMath::HandleObject
	{
	public:

		CutShape( void );
		virtual ~CutShape( void );

		virtual void CutAndCapture( FaceList& faceList, FaceList& capturedFaceList, double eps = EPSILON );

		_3DMath::Surface* surface;
		_3DMath::Line axisOfRotation;
		_3DMath::Surface::Side captureSide;
		double rotationAngleForSingleTurn;
		double rotationAngleForAnimation;
		double vectorLength;
		wxString label;		// These can be statically or dynamically assigned.
	};

	typedef std::list< CutShape* > CutShapeList;

	CutShape* FindCutShapeWithLabel( const wxString& label );
	CutShape* FindCutShapeNearestDirection( const _3DMath::Vector& direction, const _3DMath::AffineTransform& transform, TwistyPuzzle::CutShapeList::iterator* foundIter = nullptr );
	wxString FindLabelForCutShape( const CutShape* cutShape, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform );

	void MakeBox( double width, double height, double depth );

	enum Polyhedron
	{
		HEXADRON,
		OCTAHEDRON,
		ICOSAHEDRON,
		DODECAHEDRON,
		TETRAHEDRON,
		TRUNCATED_TETRAHEDRON,
		TRUNCATED_OCTAHEDRON,
	};

	void MakePolyhedron( Polyhedron polyhedron, double radius, _3DMath::TriangleMesh* triangleMesh = nullptr );

	static bool SaveVector( const wxString& name, wxXmlNode* xmlNode, const _3DMath::Vector& vector );
	static bool LoadVector( const wxString& name, const wxXmlNode* xmlNode, _3DMath::Vector& vector );
	static bool SaveNumber( const wxString& name, wxXmlNode* xmlNode, double number );
	static bool LoadNumber( const wxString& name, const wxXmlNode* xmlNode, double& number );

	static _3DMath::Vector ColorTable( int index );

	static _3DMath::Vector red, green, blue, magenta, cyan, yellow;
	static _3DMath::Vector orange, maroon, white, pink, lime, indigo;
	static _3DMath::Vector lightseagrean, turquoiseblue, eggshell, firebrick;
	static _3DMath::Vector olivedrab, salmon, brown, aquamarine;

	void GoForward( void );
	void GoBackward( void );

	void AddHistory( Rotation* newRotation );

	bool CanGoForward( void );
	bool CanGoBackward( void );

	void CollectAdjacentEdges( const Face* face, _3DMath::LineSegmentList& lineSegmentList ) const;

	typedef std::map< std::string, _3DMath::Vector > LabelMap;

	FaceList faceList;
	CutShapeList cutShapeList;
	RotationList rotationQueue;
	double rotationSpeedCoeficient;
	mutable bool needsSaving;
	RotationList rotationHistory;
	RotationList::iterator rotationHistoryIter;
	LabelMap labelMap;
	ShaderProgram* shaderProgram;
};

// TwistyPuzzle.h