// Permutation.h

#pragma once

#include <map>
#include <list>
#include <vector>

class Permutation
{
public:

	Permutation( void );
	~Permutation( void );

	typedef std::map< int, int > Bijection;

	struct Stats
	{
		int smallestInput, largestInput;
		int smallestOutput, largestOutput;
	};

	bool IsValid( void ) const;
	bool IsEven( void ) const;
	bool IsOdd( void ) const;
	bool IsIdentity( void ) const;
	bool IsEqualTo( const Permutation& permutation ) const;
	bool CommutesWith( const Permutation& permutation ) const;
	int Order( void ) const;
	int MapCount( void ) const;
	int Evaluate( int i ) const;
	void CalcStats( Stats& stats ) const;
	void Multiply( const Permutation& permutationA, const Permutation& permutationB );
	void Concatinate( const Permutation& permutation );
	void Prune( void ) const;
	void MakeCopy( Permutation& permutation ) const;
	bool MakeInverse( Permutation& permutation ) const;

	Bijection bijection;
};

// Permutation.h