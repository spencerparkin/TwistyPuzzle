// wxTimeKeeper.cpp

#include "wxTimeKeeper.h"
#include <wx/time.h>

wxTimeKeeper::wxTimeKeeper( void )
{
}

/*virtual*/ wxTimeKeeper::~wxTimeKeeper( void )
{
}

/*virtual*/ double wxTimeKeeper::AskSystemForCurrentTimeMilliseconds( void )
{
	double millis = wxGetUTCTimeMillis().ToDouble();
	return millis;
}

// wxTimeKeeper.cpp