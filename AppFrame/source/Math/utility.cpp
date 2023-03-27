#include <random>
#include <cmath>
#include "vector4.h"
#include "utility.h"

namespace
{
	std::random_device seed_gen;
	std::mt19937_64 random( seed_gen() );
}

namespace math
{
	int utility::get_random( const int min,const int max )
	{
		std::uniform_int_distribution<int>  distr( min,max );
		return distr( random );
	}

}
