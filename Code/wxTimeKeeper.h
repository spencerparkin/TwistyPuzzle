// wxTimeKeeper.h

#include <TimeKeeper.h>

class wxTimeKeeper : public _3DMath::TimeKeeper
{
public:
    wxTimeKeeper( void );
    virtual ~wxTimeKeeper( void );

    virtual double AskSystemForCurrentTimeMilliseconds( void ) override;
};

// wxTimeKeeper.h