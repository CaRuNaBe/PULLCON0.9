#pragma once

namespace math
{
	class matrix44;

	class vector4
	{
	public:
		// �R���X�g���N�^
		vector4();
		vector4(const float x,const float y,const float z): x(x),y(y),z(z),w(1.0)
		{}
		vector4(const float x,const float y,const float z,float w): x(x),y(y),z(z),w(w)
		{}
		vector4(const vector4&) = default; // �R�s�[
		vector4(vector4&&) = default; // ���[�u

		// �f�X�g���N�^
		virtual ~vector4() = default;

		vector4& operator =(const vector4&) = default; // �R�s�[
		vector4& operator =(vector4&&) = default; // ���[�u

		const vector4 operator +(const vector4& rhs) const;
		const vector4 operator -(const vector4& rhs) const;

		const vector4 operator *(const float rhs) const;
		const vector4 operator /(const float rhs) const;

		const vector4 operator *(const matrix44 rhs) const;

		void set(const vector4& vector);
		void set(const float x,const float y,const float z);

		void add(const vector4& vector);
		void add(const float x,const float y,const float z);

		const float get_x() const
		{
			return x;
		}
		const float get_y() const
		{
			return y;
		}
		const float get_z() const
		{
			return z;
		}
		const float get_w() const
		{
			return w;
		}

		const float lenght() const;

		void normalized();
		const vector4 normalize() const;

		const float dot(const vector4& rhs) const;
		const vector4 cross(const vector4& rhs) const;

	private:
		float x;
		float y;
		float z;
		float w;
	};

} // math
