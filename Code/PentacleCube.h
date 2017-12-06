// PentacleCube.h

#pragma once

#include "TwistyPuzzle.h"

class PentacleCube : public TwistyPuzzle
{
public:

	wxDECLARE_DYNAMIC_CLASS( PentacleCube );

	PentacleCube( void );
	virtual ~PentacleCube( void );

	virtual void Reset( void ) override;
	virtual bool ApplyCutShapeWithRotation( CutShape* cutShape, const Rotation* rotation ) override;
	virtual bool LoadFromXml( const wxXmlDocument& xmlDocument ) override;
	virtual bool SaveToXml( wxXmlDocument& xmlDocument ) const override;
};

// PentacleCube.h
