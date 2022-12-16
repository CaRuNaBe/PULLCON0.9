#include <cmath>
#include "vector4.h"
#include "matrix44.h"

namespace math {
	vector4::vector4 ()
	{
		x = 0.0; y = 0.0; z = 0.0; w = 1.0;
	}

	void vector4::set (const vector4& vector)
	{
		x = vector.get_x ();
		y = vector.get_y ();
		z = vector.get_z ();
		w = vector.get_w ();
	}

	void vector4::set (const float x, const float y, const float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void vector4::add (const vector4& vector)
	{
		x += vector.get_x ();
		y += vector.get_y ();
		z += vector.get_z ();
	}

	void vector4::add (const float x, const float y, const float z)
	{
		this->x += x;
		this->y += y;
		this->z += z;
	}

	const float vector4::lenght () const
	{
		return sqrt (x * x + y * y + z * z);
	}

	//���K��
	void vector4::normalized ()
	{
		auto len = lenght ();
		// �덷�����Ȃ�[���Ƃ݂Ȃ��B
		if(std::abs(len) < std::numeric_limits<float>::epsilon())
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		} else
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}
	const vector4 vector4::Getnormalize () const
	{
		auto len = lenght ();
		auto nx = 0.0f;
		auto ny = 0.0f;
		auto nz = 0.0f;
		// �덷�����Ȃ�[���Ƃ݂Ȃ��B
		if(std::abs(len) < std::numeric_limits<float>::epsilon())
		{
			 nx = 0.0f;
			 ny = 0.0f;
			 nz = 0.0f;
		} else
		{
			 nx = x / len;
			 ny = y / len;
			 nz = z / len;
		}
		return vector4 (nx, ny, nz);
	}

	const float vector4::dot (const vector4& rhs) const
	{
		return x * rhs.get_x () + y * rhs.get_y () + z * rhs.get_z ();
	}

	const vector4 vector4::cross (const vector4& rhs) const
	{
		auto cx = y * rhs.get_z () - z * rhs.get_y ();
		auto cy = z * rhs.get_x () - x * rhs.get_z ();
		auto cz = x * rhs.get_y () - y * rhs.get_x ();

		return vector4 (cx, cy, cz);
	}

	const vector4 vector4::operator +(const vector4& rhs) const
	{
		return vector4 (x + rhs.get_x (), y + rhs.get_y (), z + rhs.get_z ());
	}

	const vector4 vector4::operator -(const vector4& rhs) const
	{
		return vector4 (x - rhs.get_x (), y - rhs.get_y (), z - rhs.get_z ());
	}

	const vector4 vector4::operator *(const float rhs) const
	{
		return vector4 (x * rhs, y * rhs, z * rhs);
	}

	const vector4 vector4::operator /(const float rhs) const
	{
		return vector4 (x / rhs, y / rhs, z / rhs);
	}

	const vector4 vector4::operator *(const matrix44 rhs) const
	{
		auto mx = x * rhs.get_value (0, 0)
			+ y * rhs.get_value (1, 0)
			+ z * rhs.get_value (2, 0)
			+ rhs.get_value (3, 0);

		auto my = x * rhs.get_value (0, 1)
			+ y * rhs.get_value (1, 1)
			+ z * rhs.get_value (2, 1)
			+ rhs.get_value (3, 1);

		auto mz = x * rhs.get_value (0, 2)
			+ y * rhs.get_value (1, 2)
			+ z * rhs.get_value (2, 2)
			+ rhs.get_value (3, 2);

		auto mw = x * rhs.get_value (0, 3)
			+ y * rhs.get_value (1, 3)
			+ z * rhs.get_value (2, 3)
			+ rhs.get_value (3, 3);

		return vector4 (mx, my, mz, mw);
	}

} // math
