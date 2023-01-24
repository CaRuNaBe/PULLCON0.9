#include <random>
#include <cmath>
#include "vector4.h"
#include "utility.h"

namespace
{
	std::random_device seed_gen;
	std::mt19937_64 random(seed_gen());
}

namespace math
{
	int utility::get_random(const int min,const int max)
	{
		std::uniform_int_distribution<int>  distr(min,max);
		return distr(random);
	}

	// ��̒l�̑傫���l���擾
	template <typename T>
	T Max(const T& a,const T& b)
	{
		return (a < b ? b : a);
	}
	// ��̒l�̏������l���擾
	template <typename T>
	T Min(const T& a,const T& b)
	{
		return (a < b ? a : b);
	}
	// ��̒l�̊ԂŃN�����v����
	template <typename T>
	T Clamp(const T& value,const T& lower,const T& upper)
	{
		return Min(upper,Max(lower,value));
	}
}
