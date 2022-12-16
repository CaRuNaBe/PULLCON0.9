#pragma once

namespace math {
	class matrix44;

	class vector4
	{
	public:
		// コンストラクタ
		vector4();
		vector4(float x, float y, float z) : x(x), y(y), z(z), w(1.0)
		{}
		vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
		{}
		vector4(int x, int y, int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)), w(1.0)
		{}
		vector4(int x, int y, int z, int w) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)), w(static_cast<float>(w))
		{}
		vector4(const vector4&) = default; // コピー
		vector4(vector4&&) = default; // ムーブ

		// デストラクタ
		virtual ~vector4() = default;

		vector4& operator =(const vector4&) = default; // コピー
		vector4& operator =(vector4&&) = default; // ムーブ

		const vector4 operator +(const vector4& rhs) const;
		const vector4 operator -(const vector4& rhs) const;

		const vector4 operator *(const float rhs) const;
		const vector4 operator /(const float rhs) const;

		const vector4 operator *(const matrix44 rhs) const;

		void set(const vector4& vector);
		void set(const float x, const float y, const float z);

		void add(const vector4& vector);
		void add(const float x, const float y, const float z);

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
