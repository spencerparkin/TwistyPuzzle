// TwistyPuzzle.h

#pragma once

#include <Permutation.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <wx/xml/xml.h>
#include <wx/colour.h>
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
	virtual void Render( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform, GLenum renderMode, int selectedObjectHandle, int renderFlags );
	virtual void RenderStats( const _3DMath::TimeKeeper& timeKeeper );
	virtual void Reset( void ) = 0;
	virtual bool SpecialAction( double wheelClicks, int selectedObjectHandle, int flags );
	virtual void UpdateCutShapeLabels( const _3DMath::AffineTransform& transform );

	void SetupStandardDynamicFaceTurningBoxLabels( double radius = 10.0 );
	void SetupStandardDynamicCornerTurningBoxLabels( double radius = 10.0 );
	void SetupStandardDynamicEdgeTurningBoxLabels( double radius = 10.0 );
	void SetupDynamicLabelUsingCutShape( const CutShape* cutShape );
	void SetupDynamicLabelsUsingCutShapeList( void );

	class Rotation
	{
	public:

		enum Direction { DIR_CW, DIR_CCW };
		enum Flags
		{
			FLAG_HISTORY			= 0x00000001,
			FLAG_BACK_AGAIN			= 0x00000002,
			FLAG_FORWARD_AGAIN		= 0x00000004,
			FLAG_PRECUT				= 0x00000008,
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

	virtual bool SupportsSolve( void ) const { return false; }
	virtual bool Solve( RotationList& rotationList ) const;
	virtual wxString LocateStabChainFile( void ) const { return ""; }
	virtual bool TranslatePermutation( const Permutation& permutation, const CompressInfo& compressInfo, RotationList& rotationList ) const;
	virtual Rotation* CalculateNearestRotation( CutShape* cutShape );
	virtual void EnqueueRandomRotations( _3DMath::Random& random, int rotationCount );
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation );
	virtual bool ApplyRotationToPermutation( CutShape* cutShape, const Rotation* rotation );
	virtual double GetCutAndCaptureEpsilon( void ) { return EPSILON; }
	virtual void ApplyingTransformWithRotation( const _3DMath::AffineTransform& transform, const Rotation* rotation ) {}

	void EnqueueRotation( Rotation* rotation );
	void EnqueueRotationList( RotationList& rotationList );
	bool ProcessRotationQueue( const _3DMath::TimeKeeper& timeKeeper );
	bool DequeueAndProcessNextRotation( void );
	void FlushRotationQueue( void );

	void TakeSnapshot( void );
	void ClearAllSnapshotPolylines( void );

	class Face : public _3DMath::HandleObject
	{
	public:

		Face( _3DMath::Polygon* polygon );
		~Face( void );

		void UpdateTessellationIfNeeded( void );
		void Render( _3DMath::Renderer& renderer, GLenum renderMode, const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform, ShaderProgram* shaderProgram ) const;
		bool IsCapturedByCutShape( CutShape* cutShape ) const;
		bool Save( wxXmlNode* xmlFaceNode ) const;
		bool Load( const wxXmlNode* xmlFaceNode );
		wxColour GetColor( void ) const;
		void SetColor( const wxColour& colour );
		void RenderSnapshotSpline( _3DMath::Renderer& renderer, const _3DMath::AffineTransform& transform );

		_3DMath::Vector color;
		_3DMath::Polygon* polygon;
		int boundCutShapeHandle;
		bool tessellationNeeded;
		_3DMath::Vector snapshotPoint;
		_3DMath::VectorArray splinePolylineArray;
	};

	typedef std::list< Face* > FaceList;

	class CutShape : public _3DMath::HandleObject
	{
	public:

		CutShape( void );
		virtual ~CutShape( void );

		virtual bool CutAndCapture( FaceList& faceList, FaceList* capturedFaceList = nullptr, double eps = EPSILON, bool canCut = true );
		virtual bool CapturesFace( const Face* face );

		void GenerateCapturedFaceList( FaceList& faceList, FaceList& capturedFaceList );
		bool CutUsingSurface( FaceList& faceList, _3DMath::Surface* cuttingSurface, double eps = EPSILON, bool canCut = true );
		bool DoesSurfaceCaptureFace( _3DMath::Surface* captureSurface, const Face* face );
		void GetArrowTipPosition( const _3DMath::AffineTransform& transform, const _3DMath::LinearTransform& normalTransform, _3DMath::Vector& point ) const;

		// In most cases, this will work, but for the jumble moves of the CurvyCopter,
		// This will have to be dynamically assigned to the cut-shape objects.
		Permutation ccwPermutation;
		_3DMath::Surface* surface;
		_3DMath::Line axisOfRotation;
		_3DMath::Surface::Side captureSide;
		double rotationAngleForSingleTurn;
		double rotationAngleForAnimation;
		double vectorLength;
		wxString label;		// These can be statically or dynamically assigned.
	};

	typedef std::list< CutShape* > CutShapeList;

	class DoubleSurfaceCutShape : public CutShape
	{
	public:

		DoubleSurfaceCutShape( void );
		virtual ~DoubleSurfaceCutShape( void );

		virtual bool CutAndCapture( FaceList& faceList, TwistyPuzzle::FaceList* capturedFaceList = nullptr, double eps = EPSILON, bool canCut = true ) override;
		virtual bool CapturesFace( const TwistyPuzzle::Face* face ) override;

		_3DMath::Surface* additionalSurface;
	};

	void BindCutShapeToCapturedFaces( CutShape* cutShape, FaceList& capturedFaceList );

	CutShape* FindCutShapeWithLabel( const wxString& label );
	CutShape* FindCutShapeNearestLine( const _3DMath::Line& line, const _3DMath::AffineTransform& transform, TwistyPuzzle::CutShapeList::iterator* foundIter = nullptr );

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
	bool canCut;
	Permutation permutation;
};

// TwistyPuzzle.h
