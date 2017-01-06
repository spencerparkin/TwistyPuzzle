// Permutation.cpp

#include "Permutation.h"
#include <Defines.h>

Permutation::Permutation( void )
{
}

Permutation::~Permutation( void )
{
}

bool Permutation::IsValid( void ) const
{
	Bijection map;

	for( Bijection::const_iterator iter = bijection.cbegin(); iter != bijection.cend(); iter++ )
	{
		Bijection::iterator mapIter = map.find( iter->second );
		if( mapIter != map.end() )
			return false;

		map.insert( std::pair< int, int >( iter->second, 0 ) );
	}

	return true;
}

bool Permutation::IsEven( void ) const
{
	// TODO: How do we do this again?  Do we have to write it all out as disjoint 2-cycles?
	//       Can we compute this from the sizes of each disjoint cycle?
	return false;
}

bool Permutation::IsOdd( void ) const
{
	return !IsEven();
}

bool Permutation::IsIdentity( void ) const
{
	return( MapCount() == 0 ? true : false );
}

bool Permutation::IsEqualTo( const Permutation& permutation ) const
{
	permutation.Prune();
	Prune();

	if( bijection.size() != permutation.bijection.size() )
		return false;

	for( Bijection::const_iterator iterA = bijection.cbegin(); iterA != bijection.cend(); iterA++ )
	{
		Bijection::const_iterator iterB = permutation.bijection.find( iterA->first );
		if( iterB == permutation.bijection.cend() || iterB->second != iterA->second )
			return false;
	}

	return true;
}

bool Permutation::CommutesWith( const Permutation& permutation ) const
{
	Permutation productA, productB, productC;
	Permutation thisInv, permutationInv;

	MakeInverse( thisInv );
	permutation.MakeInverse( permutationInv );

	productA.Multiply( *this, permutation );
	productB.Multiply( thisInv, permutationInv );
	productC.Multiply( productA, productB );

	return productC.IsIdentity();
}

bool Permutation::MakeInverse( Permutation& permutation ) const
{
	if( IsValid() )
		return false;

	Prune();
	permutation.bijection.clear();
	for( Bijection::const_iterator iter = bijection.cbegin(); iter != bijection.cend(); iter++ )
		permutation.bijection.insert( std::pair< int, int >( iter->second, iter->first ) );

	return true;
}

void Permutation::MakeCopy( Permutation& permutation ) const
{
	Prune();
	permutation.bijection.clear();
	for( Bijection::const_iterator iter = bijection.cbegin(); iter != bijection.cend(); iter++ )
		permutation.bijection.insert( std::pair< int, int >( iter->first, iter->second ) );
}

int Permutation::Order( void ) const
{
	Permutation copy;
	MakeCopy( copy );

	std::vector< int > disjointCycleSizesArray;

	while( copy.bijection.size() > 0 )
	{
		Bijection::iterator iter = copy.bijection.begin();
		int i = iter->first;
		copy.bijection.erase( iter );

		int disjointCycleSize = 1;

		int j = i;
		while( true )
		{
			j = Evaluate(j);
			if( j == i )
				break;
			else
			{
				disjointCycleSize++;
				copy.bijection.erase(j);
			}
		}

		if( disjointCycleSize != 1 )
			disjointCycleSizesArray.push_back( disjointCycleSize );
	}

	if( disjointCycleSizesArray.size() == 0 )
		return 1;

	std::vector< int > marchArray;
	for( int i = 0; i < ( signed )disjointCycleSizesArray.size(); i++ )
		marchArray.push_back( disjointCycleSizesArray[i] );

	while( true )
	{
		int i_smallest = -1;
		int i_largest = -1;

		for( int i = 0; i < ( signed )marchArray.size(); i++ )
		{
			if( i_smallest == -1 || marchArray[ i_smallest ] > marchArray[i] )
				i_smallest = i;
			if( i_largest == -1 || marchArray[ i_largest ] < marchArray[i] )
				i_largest = i;
		}

		if( marchArray[ i_smallest ] == marchArray[ i_largest ] )
			return marchArray[ i_smallest ];

		marchArray[ i_smallest ] += disjointCycleSizesArray[ i_smallest ];
	}
	
	return -1;
}

int Permutation::MapCount( void ) const
{
	Prune();
	return bijection.size();
}

void Permutation::Prune( void ) const
{
	Bijection::iterator iter = const_cast< Bijection* >( &bijection )->begin();
	while( iter != bijection.end() )
	{
		Bijection::iterator nextIter = iter;
		nextIter++;

		if( iter->first == iter->second )
			const_cast< Bijection* >( &bijection )->erase( iter );

		iter = nextIter;
	}
}

int Permutation::Evaluate( int i ) const
{
	Bijection::const_iterator iter = bijection.find(i);
	if( iter == bijection.end() )
		return i;
	return iter->second;
}

void Permutation::CalcStats( Stats& stats ) const
{
	Prune();
	
	stats.smallestInput = -1;
	stats.largestInput = -1;
	stats.smallestOutput = -1;
	stats.largestOutput = -1;

	for( Bijection::const_iterator iter = bijection.cbegin(); iter != bijection.cend(); iter++ )
	{
		if( stats.smallestInput == -1 || stats.smallestInput > iter->second )
			stats.smallestInput = iter->first;
		if( stats.largestInput == -1 || stats.largestInput < iter->second )
			stats.largestInput = iter->first;
		if( stats.smallestOutput == -1 || stats.smallestOutput > iter->first )
			stats.smallestOutput = iter->second;
		if( stats.largestOutput == -1 || stats.largestOutput < iter->first )
			stats.largestOutput = iter->second;
	}
}

void Permutation::Multiply( const Permutation& permutationA, const Permutation& permutationB )
{
	Stats statsA, statsB;

	permutationA.CalcStats( statsA );
	permutationB.CalcStats( statsB );

	int min = MIN( statsA.smallestInput, statsB.smallestInput );
	int max = MAX( statsA.largestInput, statsB.largestInput );

	bijection.clear();

	for( int i = min; i <= max; i++ )
	{
		int j = permutationB.Evaluate( permutationA.Evaluate(i) );
		if( i != j )
			bijection.insert( std::pair< int, int >( i, j ) );
	}
}

void Permutation::Concatinate( const Permutation& permutation )
{
	Permutation product;
	product.Multiply( *this, permutation );
	product.MakeCopy( *this );
}

// Permutation.cpp