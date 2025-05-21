/*****************************************************************************
*
* shader-float4.h
*
* By Jari Korkala 4/2013
*
* Vector[4] that avoids the creation of temporary copies.
*
*****************************************************************************/

#ifndef CENG_SHADER_DATATYPE_H
#define CENG_SHADER_DATATYPE_H

#include <vector>

#include "crender-base.h"
#include "pshader-input.h"

#include "texture-unit.h"

#include "cr-shader-view.h"

namespace Ceng::Shader
{
	void PS_MOV_FLOAT4_FLOAT4_X86_SSE(void *dest,void *source);

	void PS_MUL_FLOAT4_LOCAL_FLOAT_X86_SSE(void *dest,void *source);

	void PS_MUL_FLOAT4_FLOAT4_X86_SSE(void *dest,void *source);
	void PS_MUL_FLOAT4_FLOAT_X86_SSE(void *dest,void *source);

	struct alignas(16) SOAVecBool
	{
		union
		{
			Ceng::BOOL arr[4];
			struct
			{
				Ceng::BOOL a;
				Ceng::BOOL b;
				Ceng::BOOL c;
				Ceng::BOOL d;
			};
		};

		inline SOAVecBool()
		{

		}

		inline SOAVecBool(const SOAVecBool& source)
			: a(source.a), b(source.b), c(source.c), d(source.d)
		{

		}

		inline SOAVecBool(const bool x)
			: a(x), b(x), c(x), d(x)
		{

		}

		inline SOAVecBool(const Ceng::BOOL x)
			: a(x), b(x), c(x), d(x)
		{

		}

		inline SOAVecBool(Ceng::BOOL a, Ceng::BOOL b, Ceng::BOOL c, Ceng::BOOL d)
			: a(a), b(b), c(c), d(d)
		{

		}

		inline SOAVecBool(bool a, bool b, bool c, bool d)
			: a(a), b(b), c(c), d(d)
		{

		}

		inline SOAVecBool& operator = (const bool x)
		{
			a = x;
			b = x;
			c = x;
			d = x;
				
			return *this;
		}

		inline SOAVecBool& operator = (const Ceng::BOOL x)
		{
			a = x;
			b = x;
			c = x;
			d = x;

			return *this;
		}

		inline SOAVecBool operator == (const bool value)
		{
			return { a == value, b == value, c == value, d == value };
		}

		inline SOAVecBool operator != (const bool value)
		{
			return { a != value, b != value, c != value, d != value };
		}

		inline SOAVecBool operator == (const Ceng::BOOL value)
		{
			return { a == value, b == value, c == value, d == value };
		}

		inline SOAVecBool operator != (const Ceng::BOOL value)
		{
			return { a != value, b != value, c != value, d != value };
		}
	};

	inline SOAVecBool operator == (const SOAVecBool& left, const SOAVecBool& right)
	{
		return { left.a == right.a, left.b == right.b , left.c == right.c , left.d == right.d };
	}

	inline SOAVecBool operator != (const SOAVecBool& left, const SOAVecBool& right)
	{
		return { left.a != right.a, left.b != right.b , left.c != right.c , left.d != right.d };
	}

	class alignas(16) SOAVecFloat
	{
	public:
		union
		{
			Ceng::FLOAT32 arr[4];
			struct
			{
				Ceng::FLOAT32 a;
				Ceng::FLOAT32 b;
				Ceng::FLOAT32 c;
				Ceng::FLOAT32 d;
			};
		};			

	public:

		inline SOAVecFloat()
		{

		}

		inline SOAVecFloat(Ceng::FLOAT32 a, Ceng::FLOAT32 b, Ceng::FLOAT32 c, Ceng::FLOAT32 d)
			: a(a), b(b), c(c),d (d)
		{
				
		}

		inline SOAVecFloat(Ceng::FLOAT32 a)
			: a(a),b(a),c(a),d(a)
		{

		}

		inline SOAVecFloat& operator += (const SOAVecFloat& other)
		{
			a += other.a;
			b += other.b;
			c += other.c;
			d += other.d;				

			return *this;
		}

		inline SOAVecFloat& operator -= (const SOAVecFloat& other)
		{
			a -= other.a;
			b -= other.b;
			c -= other.c;
			d -= other.d;

			return *this;
		}

		inline SOAVecFloat& operator *= (const SOAVecFloat& other)
		{
			a *= other.a;
			b *= other.b;
			c *= other.c;
			d *= other.d;

			return *this;
		}

		inline SOAVecFloat& operator /= (const SOAVecFloat& other)
		{
			a /= other.a;
			b /= other.b;
			c /= other.c;
			d /= other.d;

			return *this;
		}

	};

	inline SOAVecFloat operator + (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a + y.a, x.b + y.b, x.c + y.c, x.d + y.d };
	}

	inline SOAVecFloat operator - (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a - y.a, x.b - y.b, x.c - y.c, x.d - y.d };
	}

	inline SOAVecFloat operator * (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a * y.a, x.b * y.b, x.c * y.c, x.d * y.d };
	}

	inline SOAVecFloat operator / (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a / y.a, x.b / y.b, x.c / y.c, x.d / y.d };
	}

	inline SOAVecBool operator == (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a == y.a, x.b == y.b, x.c == y.c, x.d == y.d };
	}

	inline SOAVecBool operator != (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a != y.a, x.b != y.b, x.c != y.c, x.d != y.d };
	}

	inline SOAVecBool operator < (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a < y.a, x.b < y.b, x.c < y.c, x.d < y.d };
	}

	inline SOAVecBool operator <= (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a <= y.a, x.b <= y.b, x.c <= y.c, x.d <= y.d };
	}

	inline SOAVecBool operator > (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a > y.a, x.b > y.b, x.c > y.c, x.d > y.d };
	}

	inline SOAVecBool operator >= (const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { x.a >= y.a, x.b >= y.b, x.c >= y.c, x.d >= y.d };
	}

	class alignas(16) Bool
	{
	public:
		SOAVecBool x;

		inline Bool()
		{

		}

		inline Bool(const SOAVecBool& source)
			: x(source)
		{

		}

		inline Bool(Ceng::BOOL a, Ceng::BOOL b, Ceng::BOOL c, Ceng::BOOL d)
			: x(a, b, c, d)
		{

		}

		inline Bool(bool a, bool b, bool c, bool d)
			: x(a,b,c,d)
		{
				
		}

		inline Bool(bool a)
			: x(a)
		{

		}

		inline Bool& operator = (const bool a)
		{				
			x = a;
			return *this;
		}

		inline Bool& operator = (const Ceng::BOOL a)
		{
			x = a;
			return *this;
		}

			
	};

	inline Bool operator == (const Bool& left, const Bool& right)
	{
		return left.x == right.x;
	}

	inline Bool operator != (const Bool& left, const Bool& right)
	{
		return left.x != right.x;
	}

	class alignas(16) Bool2
	{
	public:
		SOAVecBool x;
		SOAVecBool y;

		inline Bool2()
		{

		}

		inline Bool2(const SOAVecBool& x, const SOAVecBool& y)
			: x(x), y(y)
		{

		}

		inline Bool2(bool a, bool b)
			: x(a), y(b)
		{

		}
	};

	inline Bool2 operator == (const Bool2& left, const Bool2& right)
	{
		return { left.x == right.x, left.y == right.y };
	}

	inline Bool2 operator != (const Bool2& left, const Bool2& right)
	{
		return { left.x != right.x, left.y != right.y };
	}

	class alignas(16) Bool3
	{
	public:
		SOAVecBool x;
		SOAVecBool y;
		SOAVecBool z;

		inline Bool3()
		{

		}

		inline Bool3(const SOAVecBool& x, const SOAVecBool& y, const SOAVecBool& z)
			: x(x), y(y), z(z)
		{

		}

		inline Bool3(bool a, bool b, bool c)
			: x(a), y(b), z(c)
		{

		}
	};

	class alignas(16) Bool4
	{
	public:
		SOAVecBool x;
		SOAVecBool y;
		SOAVecBool z;
		SOAVecBool w;

		inline Bool4()
		{

		}

		inline Bool4(const SOAVecBool& x, const SOAVecBool& y, const SOAVecBool& z, const SOAVecBool& w)
			: x(x), y(y), z(z), w(w)
		{

		}

		inline Bool4(bool a, bool b, bool c, bool d)
			: x(a), y(b), z(c), w(d)
		{

		}
	};

	inline Bool4 operator == (const Bool4& left, const Bool4& right)
	{
		return { left.x == right.x, left.y == right.y, left.z == right.z, left.w == right.w };
	}

	inline Bool4 operator != (const Bool4& left, const Bool4& right)
	{
		return { left.x != right.x, left.y != right.y, left.z != right.z, left.w != right.w };
	}


	class Float2;
	class Float3;
	class Float4;

	class SwizzledFloat;
	class SwizzledFloat2;
	class SwizzledFloat3;
	class SwizzledFloat4;

	class SampleTexture2D;

	class alignas(16) Float
	{
	public:
		SOAVecFloat x;

	public:
		inline Float()
		{

		}

		inline Float(const SOAVecFloat& source)
			: x(source)
		{
				
		}

		inline Float(Ceng::FLOAT32 a)
			: x(a)
		{

		}

		inline Float& operator= (const Float& other)
		{
			x = other.x;
			return *this;
		}

		Float& operator= (const Float2& other);

		Float& operator= (const Float3& other);

		Float& operator= (const Float4& other);

		Float& operator= (const SwizzledFloat& other);

		inline Float& operator = (const CR_PixelShaderInput& source)
		{
			source.MoveToFloat(&x);
			return *this;
		}

		inline Float& operator += (const Float& other)
		{
			x += other.x;

			return *this;
		}

		inline Float& operator -= (const Float& other)
		{
			x -= other.x;

			return *this;
		}

		inline Float& operator *= (const Float& other)
		{
			x *= other.x;

			return *this;
		}
			
		inline Float& operator /= (const Float& other)
		{
			x /= other.x;

			return *this;
		}


	};

	inline Float operator + (const Float& a, const Float& b)
	{
		return a.x + b.x;
	}

	inline Float operator - (const Float& a, const Float& b)
	{
		return a.x - b.x;
	}

	inline Float operator * (const Float& a, const Float& b)
	{
		return a.x * b.x;
	}

	inline Float operator / (const Float& a, const Float& b)
	{
		return a.x / b.x;
	}

	inline Bool operator == (const Float& a, const Float& b)
	{
		return a.x == b.x;
	}

	inline Bool operator != (const Float& a, const Float& b)
	{
		return a.x != b.x;
	}

	inline Bool operator < (const Float& a, const Float& b)
	{
		return a.x < b.x;
	}

	inline Bool operator > (const Float& a, const Float& b)
	{
		return a.x > b.x;
	}

	inline Bool operator <= (const Float& a, const Float& b)
	{
		return a.x <= b.x;
	}

	inline Bool operator >= (const Float& a, const Float& b)
	{
		return a.x >= b.x;
	}

	class alignas(16) Float2
	{
	public:
		SOAVecFloat _x;
		SOAVecFloat _y;

	public:
		inline Float2()
		{

		}

		inline Float2(const SOAVecFloat& a, const SOAVecFloat& b)
			: _x(a), _y(b)
		{

		}

		inline Float2(Ceng::FLOAT32 a, Ceng::FLOAT32 b)
			: _x(a), _y(b)
		{

		}

		inline Float2& operator= (const Float& other)
		{
			_x = other.x;
			_y = 0.0f;

			return *this;
		}

		inline Float2& operator= (const Float2& other)
		{
			_x = other._x;
			_y = other._y;

			return *this;
		}

		Float2& operator= (const Float3& other);

		Float2& operator= (const Float4& other);

		Float2& operator= (const SwizzledFloat2& other);

		inline Float2& operator = (const CR_PixelShaderInput& source)
		{
			source.MoveToFloat2(&_x);
			return *this;
		}

		inline Float2& operator += (const Float2& other)
		{
			_x += other._x;
			_y += other._y;

			return *this;
		}

		inline Float2& operator -= (const Float2& other)
		{
			_x -= other._x;
			_y -= other._y;

			return *this;
		}

		inline Float2& operator *= (const Float2& other)
		{
			_x *= other._x;
			_y *= other._y;

			return *this;
		}

		inline Float2& operator /= (const Float2& other)
		{
			_x /= other._x;
			_y /= other._y;

			return *this;
		}

		SwizzledFloat x();
		SwizzledFloat y();

		SwizzledFloat2 xx();
		SwizzledFloat2 xy();
		SwizzledFloat2 yx();
		SwizzledFloat2 yy();
	};

	inline Float2 operator + (const Float2& a, const Float2& b)
	{
		return { a._x + b._x, a._y + b._y };
	}

	inline Float2 operator - (const Float2& a, const Float2& b)
	{
		return { a._x - b._x, a._y - b._y };
	}

	inline Float2 operator * (const Float2& a, const Float2& b)
	{
		return  { a._x * b._x, a._y * b._y };
	}

	inline Float2 operator / (const Float2& a, const Float2& b)
	{
		return  { a._x / b._x, a._y / b._y };
	}

	inline Bool2 operator == (const Float2& a, const Float2& b)
	{
		return  { a._x == b._x, a._y == b._y };
	}

	inline Bool2 operator != (const Float2& a, const Float2& b)
	{
		return { a._x != b._x, a._y != b._y };
	}

	inline Bool2 operator < (const Float2& a, const Float2& b)
	{
		return { a._x < b._x, a._y < b._y };
	}

	inline Bool2 operator > (const Float2& a, const Float2& b)
	{
		return { a._x > b._x, a._y > b._y };
	}

	inline Bool2 operator <= (const Float2& a, const Float2& b)
	{
		return { a._x <= b._x, a._y <= b._y };
	}

	inline Bool2 operator >= (const Float2& a, const Float2& b)
	{
		return { a._x >= b._x, a._y >= b._y };
	}

	class alignas(16) Float3
	{
	public:
		SOAVecFloat _x;
		SOAVecFloat _y;
		SOAVecFloat _z;

	public:

		inline Float3()
		{

		}

		inline Float3(const SOAVecFloat& x, const SOAVecFloat& y, const SOAVecFloat& z)
			: _x(x), _y(y), _z(z)
		{

		}

		inline Float3(Ceng::FLOAT32 x, Ceng::FLOAT32 y, Ceng::FLOAT32 z)
			: _x(x), _y(y), _z(z)
		{

		}

		inline Float3& operator= (const Float& other)
		{
			_x = other.x;
			_y = 0.0f;
			_z = 0.0f;

			return *this;
		}

		inline Float3& operator= (const Float2& other)
		{
			_x = other._x;
			_y = other._y;
			_z = 0.0f;

			return *this;
		}

		inline Float3& operator= (const Float3& other)
		{
			_x = other._x;
			_y = other._y;
			_z = other._z;

			return *this;
		}

		Float3& operator= (const Float4& other);

		inline Float3& operator = (const CR_PixelShaderInput& source)
		{
			source.MoveToFloat3(&_x);
			return *this;
		}

		inline Float3& operator += (const Float3& other)
		{
			_x += other._x;
			_y += other._y;
			_z += other._z;

			return *this;
		}

		inline Float3& operator -= (const Float3& other)
		{
			_x -= other._x;
			_y -= other._y;
			_z -= other._z;

			return *this;
		}

		inline Float3& operator *= (const Float3& other)
		{
			_x *= other._x;
			_y *= other._y;
			_z *= other._z;

			return *this;
		}

		inline Float3& operator /= (const Float3& other)
		{
			_x /= other._x;
			_y /= other._y;
			_z /= other._z;

			return *this;
		}

		Float3& operator= (const SwizzledFloat3& other);

		SwizzledFloat x();
		SwizzledFloat y();
		SwizzledFloat z();

		SwizzledFloat2 xx();
		SwizzledFloat2 xy();
		SwizzledFloat2 xz();

		SwizzledFloat2 yx();
		SwizzledFloat2 yy();
		SwizzledFloat2 yz();

		SwizzledFloat2 zx();
		SwizzledFloat2 zy();
		SwizzledFloat2 zz();

		SwizzledFloat3 xxx();
		SwizzledFloat3 xxy();
		SwizzledFloat3 xxz();

		SwizzledFloat3 xyx();
		SwizzledFloat3 xyy();
		SwizzledFloat3 xyz();

		SwizzledFloat3 xzx();
		SwizzledFloat3 xzy();
		SwizzledFloat3 xzz();

		SwizzledFloat3 yxx();
		SwizzledFloat3 yxy();
		SwizzledFloat3 yxz();

		SwizzledFloat3 yyx();
		SwizzledFloat3 yyy();
		SwizzledFloat3 yyz();

		SwizzledFloat3 yzx();
		SwizzledFloat3 yzy();
		SwizzledFloat3 yzz();

		SwizzledFloat3 zxx();
		SwizzledFloat3 zxy();
		SwizzledFloat3 zxz();

		SwizzledFloat3 zyx();
		SwizzledFloat3 zyy();
		SwizzledFloat3 zyz();

		SwizzledFloat3 zzx();
		SwizzledFloat3 zzy();
		SwizzledFloat3 zzz();
		
	};

	inline Float3 operator + (const Float3& a, const Float3& b)
	{
		return { a._x + b._x, a._y + b._y, a._z + b._z };
	}

	inline Float3 operator - (const Float3& a, const Float3& b)
	{
		return { a._x - b._x, a._y - b._y, a._z - b._z };
	}

	inline Float3 operator * (const Float3& a, const Float3& b)
	{
		return  { a._x * b._x, a._y * b._y, a._z * b._z };
	}

	inline Float3 operator / (const Float3& a, const Float3& b)
	{
		return  { a._x / b._x, a._y / b._y, a._z / b._z };
	}

	inline Bool3 operator == (const Float3& a, const Float3& b)
	{
		return  { a._x == b._x, a._y == b._y, a._z == b._z };
	}

	inline Bool3 operator != (const Float3& a, const Float3& b)
	{
		return { a._x != b._x, a._y != b._y, a._z != b._z };
	}

	inline Bool3 operator < (const Float3& a, const Float3& b)
	{
		return { a._x < b._x, a._y < b._y, a._z < b._z };
	}

	inline Bool3 operator > (const Float3& a, const Float3& b)
	{
		return { a._x > b._x, a._y > b._y, a._z > b._z };
	}

	inline Bool3 operator <= (const Float3& a, const Float3& b)
	{
		return { a._x <= b._x, a._y <= b._y, a._z <= b._z };
	}

	inline Bool3 operator >= (const Float3& a, const Float3& b)
	{
		return { a._x >= b._x, a._y >= b._y, a._z >= b._z };
	}

	class alignas(16) Float4
	{
	public:
		SOAVecFloat _x;
		SOAVecFloat _y;
		SOAVecFloat _z;
		SOAVecFloat _w;

	public:
		inline Float4()
		{

		}

		inline Float4(const SOAVecFloat& x, const SOAVecFloat& y, const SOAVecFloat& z, const SOAVecFloat& w)
			: _x(x), _y(y), _z(z), _w(w)
		{

		}

		inline Float4(Ceng::FLOAT32 x, Ceng::FLOAT32 y, Ceng::FLOAT32 z, Ceng::FLOAT32 w)
			: _x(x), _y(y), _z(z), _w(w)
		{

		}

		inline Float4& operator= (const Float& other)
		{
			_x = other.x;
			_y = 0.0f;
			_z = 0.0f;
			_w = 1.0f;

			return *this;
		}

		inline Float4& operator= (const Float2& other)
		{
			_x = other._x;
			_y = other._y;
			_z = 0.0f;
			_w = 1.0f;

			return *this;
		}

		inline Float4& operator= (const Float3& other)
		{
			_x = other._x;
			_y = other._y;
			_z = other._z;
			_w = 1.0f;

			return *this;
		}

		inline Float4& operator= (const Float4& other)
		{
			_x = other._x;
			_y = other._y;
			_z = other._z;
			_w = other._w;

			return *this;
		}


		inline Float4& operator = (const CR_PixelShaderInput& source)
		{
			source.MoveToFloat4(&_x);
			return *this;
		}

		inline Float4& operator += (const Float4& other)
		{
			_x += other._x;
			_y += other._y;
			_z += other._z;
			_w += other._w;

			return *this;
		}

		inline Float4& operator -= (const Float4& other)
		{
			_x -= other._x;
			_y -= other._y;
			_z -= other._z;
			_w -= other._w;

			return *this;
		}

		inline Float4& operator *= (const Float4& other)
		{
			_x *= other._x;
			_y *= other._y;
			_z *= other._z;
			_w *= other._w;

			return *this;
		}

		inline Float4& operator /= (const Float4& other)
		{
			_x /= other._x;
			_y /= other._y;
			_z /= other._z;
			_w /= other._w;

			return *this;
		}

		Float4& operator = (const SampleTexture2D& source);

		Float4& operator = (const SwizzledFloat4& source);

		SwizzledFloat x();
		SwizzledFloat y();
		SwizzledFloat z();
		SwizzledFloat w();

		SwizzledFloat2 xx();
		SwizzledFloat2 xy();
		SwizzledFloat2 xz();
		SwizzledFloat2 xw();

		SwizzledFloat2 yx();
		SwizzledFloat2 yy();
		SwizzledFloat2 yz();
		SwizzledFloat2 yw();

		SwizzledFloat2 zx();
		SwizzledFloat2 zy();
		SwizzledFloat2 zz();
		SwizzledFloat2 zw();

		SwizzledFloat2 wx();
		SwizzledFloat2 wy();
		SwizzledFloat2 wz();
		SwizzledFloat2 ww();

		SwizzledFloat3 xxx();
		SwizzledFloat3 xxy();
		SwizzledFloat3 xxz();
		SwizzledFloat3 xxw();

		SwizzledFloat3 xyx();
		SwizzledFloat3 xyy();
		SwizzledFloat3 xyz();
		SwizzledFloat3 xyw();

		SwizzledFloat3 xzx();
		SwizzledFloat3 xzy();
		SwizzledFloat3 xzz();
		SwizzledFloat3 xzw();

		SwizzledFloat3 xwx();
		SwizzledFloat3 xwy();
		SwizzledFloat3 xwz();
		SwizzledFloat3 xww();

		SwizzledFloat3 yxx();
		SwizzledFloat3 yxy();
		SwizzledFloat3 yxz();
		SwizzledFloat3 yxw();

		SwizzledFloat3 yyx();
		SwizzledFloat3 yyy();
		SwizzledFloat3 yyz();
		SwizzledFloat3 yyw();

		SwizzledFloat3 yzx();
		SwizzledFloat3 yzy();
		SwizzledFloat3 yzz();
		SwizzledFloat3 yzw();

		SwizzledFloat3 ywx();
		SwizzledFloat3 ywy();
		SwizzledFloat3 ywz();
		SwizzledFloat3 yww();

		SwizzledFloat3 zxx();
		SwizzledFloat3 zxy();
		SwizzledFloat3 zxz();
		SwizzledFloat3 zxw();

		SwizzledFloat3 zyx();
		SwizzledFloat3 zyy();
		SwizzledFloat3 zyz();
		SwizzledFloat3 zyw();

		SwizzledFloat3 zzx();
		SwizzledFloat3 zzy();
		SwizzledFloat3 zzz();
		SwizzledFloat3 zzw();

		SwizzledFloat3 zwx();
		SwizzledFloat3 zwy();
		SwizzledFloat3 zwz();
		SwizzledFloat3 zww();

		SwizzledFloat3 wxx();
		SwizzledFloat3 wxy();
		SwizzledFloat3 wxz();
		SwizzledFloat3 wxw();

		SwizzledFloat3 wyx();
		SwizzledFloat3 wyy();
		SwizzledFloat3 wyz();
		SwizzledFloat3 wyw();

		SwizzledFloat3 wzx();
		SwizzledFloat3 wzy();
		SwizzledFloat3 wzz();
		SwizzledFloat3 wzw();

		SwizzledFloat3 wwx();
		SwizzledFloat3 wwy();
		SwizzledFloat3 wwz();
		SwizzledFloat3 www();

		// swizzles x---

		SwizzledFloat4 xxxx();
		SwizzledFloat4 xxxy();
		SwizzledFloat4 xxxz();
		SwizzledFloat4 xxxw();

		SwizzledFloat4 xxyx();
		SwizzledFloat4 xxyy();
		SwizzledFloat4 xxyz();
		SwizzledFloat4 xxyw();

		SwizzledFloat4 xxzx();
		SwizzledFloat4 xxzy();
		SwizzledFloat4 xxzz();
		SwizzledFloat4 xxzw();

		SwizzledFloat4 xxwx();
		SwizzledFloat4 xxwy();
		SwizzledFloat4 xxwz();
		SwizzledFloat4 xxww();

		SwizzledFloat4 xyxx();
		SwizzledFloat4 xyxy();
		SwizzledFloat4 xyxz();
		SwizzledFloat4 xyxw();

		SwizzledFloat4 xyyx();
		SwizzledFloat4 xyyy();
		SwizzledFloat4 xyyz();
		SwizzledFloat4 xyyw();

		SwizzledFloat4 xyzx();
		SwizzledFloat4 xyzy();
		SwizzledFloat4 xyzz();
		SwizzledFloat4 xyzw();

		SwizzledFloat4 xywx();
		SwizzledFloat4 xywy();
		SwizzledFloat4 xywz();
		SwizzledFloat4 xyww();

		SwizzledFloat4 xzxx();
		SwizzledFloat4 xzxy();
		SwizzledFloat4 xzxz();
		SwizzledFloat4 xzxw();

		SwizzledFloat4 xzyx();
		SwizzledFloat4 xzyy();
		SwizzledFloat4 xzyz();
		SwizzledFloat4 xzyw();

		SwizzledFloat4 xzzx();
		SwizzledFloat4 xzzy();
		SwizzledFloat4 xzzz();
		SwizzledFloat4 xzzw();

		SwizzledFloat4 xzwx();
		SwizzledFloat4 xzwy();
		SwizzledFloat4 xzwz();
		SwizzledFloat4 xzww();

		SwizzledFloat4 xwxx();
		SwizzledFloat4 xwxy();
		SwizzledFloat4 xwxz();
		SwizzledFloat4 xwxw();

		SwizzledFloat4 xwyx();
		SwizzledFloat4 xwyy();
		SwizzledFloat4 xwyz();
		SwizzledFloat4 xwyw();

		SwizzledFloat4 xwzx();
		SwizzledFloat4 xwzy();
		SwizzledFloat4 xwzz();
		SwizzledFloat4 xwzw();

		SwizzledFloat4 xwwx();
		SwizzledFloat4 xwwy();
		SwizzledFloat4 xwwz();
		SwizzledFloat4 xwww();

		// swizzles y---

		SwizzledFloat4 yxxx();
		SwizzledFloat4 yxxy();
		SwizzledFloat4 yxxz();
		SwizzledFloat4 yxxw();

		SwizzledFloat4 yxyx();
		SwizzledFloat4 yxyy();
		SwizzledFloat4 yxyz();
		SwizzledFloat4 yxyw();

		SwizzledFloat4 yxzx();
		SwizzledFloat4 yxzy();
		SwizzledFloat4 yxzz();
		SwizzledFloat4 yxzw();

		SwizzledFloat4 yxwx();
		SwizzledFloat4 yxwy();
		SwizzledFloat4 yxwz();
		SwizzledFloat4 yxww();

		SwizzledFloat4 yyxx();
		SwizzledFloat4 yyxy();
		SwizzledFloat4 yyxz();
		SwizzledFloat4 yyxw();

		SwizzledFloat4 yyyx();
		SwizzledFloat4 yyyy();
		SwizzledFloat4 yyyz();
		SwizzledFloat4 yyyw();

		SwizzledFloat4 yyzx();
		SwizzledFloat4 yyzy();
		SwizzledFloat4 yyzz();
		SwizzledFloat4 yyzw();

		SwizzledFloat4 yywx();
		SwizzledFloat4 yywy();
		SwizzledFloat4 yywz();
		SwizzledFloat4 yyww();

		SwizzledFloat4 yzxx();
		SwizzledFloat4 yzxy();
		SwizzledFloat4 yzxz();
		SwizzledFloat4 yzxw();

		SwizzledFloat4 yzyx();
		SwizzledFloat4 yzyy();
		SwizzledFloat4 yzyz();
		SwizzledFloat4 yzyw();

		SwizzledFloat4 yzzx();
		SwizzledFloat4 yzzy();
		SwizzledFloat4 yzzz();
		SwizzledFloat4 yzzw();

		SwizzledFloat4 yzwx();
		SwizzledFloat4 yzwy();
		SwizzledFloat4 yzwz();
		SwizzledFloat4 yzww();

		SwizzledFloat4 ywxx();
		SwizzledFloat4 ywxy();
		SwizzledFloat4 ywxz();
		SwizzledFloat4 ywxw();

		SwizzledFloat4 ywyx();
		SwizzledFloat4 ywyy();
		SwizzledFloat4 ywyz();
		SwizzledFloat4 ywyw();

		SwizzledFloat4 ywzx();
		SwizzledFloat4 ywzy();
		SwizzledFloat4 ywzz();
		SwizzledFloat4 ywzw();

		SwizzledFloat4 ywwx();
		SwizzledFloat4 ywwy();
		SwizzledFloat4 ywwz();
		SwizzledFloat4 ywww();

		// swizzles z---

		SwizzledFloat4 zxxx();
		SwizzledFloat4 zxxy();
		SwizzledFloat4 zxxz();
		SwizzledFloat4 zxxw();

		SwizzledFloat4 zxyx();
		SwizzledFloat4 zxyy();
		SwizzledFloat4 zxyz();
		SwizzledFloat4 zxyw();

		SwizzledFloat4 zxzx();
		SwizzledFloat4 zxzy();
		SwizzledFloat4 zxzz();
		SwizzledFloat4 zxzw();

		SwizzledFloat4 zxwx();
		SwizzledFloat4 zxwy();
		SwizzledFloat4 zxwz();
		SwizzledFloat4 zxww();

		SwizzledFloat4 zyxx();
		SwizzledFloat4 zyxy();
		SwizzledFloat4 zyxz();
		SwizzledFloat4 zyxw();

		SwizzledFloat4 zyyx();
		SwizzledFloat4 zyyy();
		SwizzledFloat4 zyyz();
		SwizzledFloat4 zyyw();

		SwizzledFloat4 zyzx();
		SwizzledFloat4 zyzy();
		SwizzledFloat4 zyzz();
		SwizzledFloat4 zyzw();

		SwizzledFloat4 zywx();
		SwizzledFloat4 zywy();
		SwizzledFloat4 zywz();
		SwizzledFloat4 zyww();

		SwizzledFloat4 zzxx();
		SwizzledFloat4 zzxy();
		SwizzledFloat4 zzxz();
		SwizzledFloat4 zzxw();

		SwizzledFloat4 zzyx();
		SwizzledFloat4 zzyy();
		SwizzledFloat4 zzyz();
		SwizzledFloat4 zzyw();

		SwizzledFloat4 zzzx();
		SwizzledFloat4 zzzy();
		SwizzledFloat4 zzzz();
		SwizzledFloat4 zzzw();

		SwizzledFloat4 zzwx();
		SwizzledFloat4 zzwy();
		SwizzledFloat4 zzwz();
		SwizzledFloat4 zzww();

		SwizzledFloat4 zwxx();
		SwizzledFloat4 zwxy();
		SwizzledFloat4 zwxz();
		SwizzledFloat4 zwxw();

		SwizzledFloat4 zwyx();
		SwizzledFloat4 zwyy();
		SwizzledFloat4 zwyz();
		SwizzledFloat4 zwyw();

		SwizzledFloat4 zwzx();
		SwizzledFloat4 zwzy();
		SwizzledFloat4 zwzz();
		SwizzledFloat4 zwzw();

		SwizzledFloat4 zwwx();
		SwizzledFloat4 zwwy();
		SwizzledFloat4 zwwz();
		SwizzledFloat4 zwww();

		// swizzles w---

		SwizzledFloat4 wxxx();
		SwizzledFloat4 wxxy();
		SwizzledFloat4 wxxz();
		SwizzledFloat4 wxxw();

		SwizzledFloat4 wxyx();
		SwizzledFloat4 wxyy();
		SwizzledFloat4 wxyz();
		SwizzledFloat4 wxyw();

		SwizzledFloat4 wxzx();
		SwizzledFloat4 wxzy();
		SwizzledFloat4 wxzz();
		SwizzledFloat4 wxzw();

		SwizzledFloat4 wxwx();
		SwizzledFloat4 wxwy();
		SwizzledFloat4 wxwz();
		SwizzledFloat4 wxww();

		SwizzledFloat4 wyxx();
		SwizzledFloat4 wyxy();
		SwizzledFloat4 wyxz();
		SwizzledFloat4 wyxw();

		SwizzledFloat4 wyyx();
		SwizzledFloat4 wyyy();
		SwizzledFloat4 wyyz();
		SwizzledFloat4 wyyw();

		SwizzledFloat4 wyzx();
		SwizzledFloat4 wyzy();
		SwizzledFloat4 wyzz();
		SwizzledFloat4 wyzw();

		SwizzledFloat4 wywx();
		SwizzledFloat4 wywy();
		SwizzledFloat4 wywz();
		SwizzledFloat4 wyww();

		SwizzledFloat4 wzxx();
		SwizzledFloat4 wzxy();
		SwizzledFloat4 wzxz();
		SwizzledFloat4 wzxw();

		SwizzledFloat4 wzyx();
		SwizzledFloat4 wzyy();
		SwizzledFloat4 wzyz();
		SwizzledFloat4 wzyw();

		SwizzledFloat4 wzzx();
		SwizzledFloat4 wzzy();
		SwizzledFloat4 wzzz();
		SwizzledFloat4 wzzw();

		SwizzledFloat4 wzwx();
		SwizzledFloat4 wzwy();
		SwizzledFloat4 wzwz();
		SwizzledFloat4 wzww();

		SwizzledFloat4 wwxx();
		SwizzledFloat4 wwxy();
		SwizzledFloat4 wwxz();
		SwizzledFloat4 wwxw();

		SwizzledFloat4 wwyx();
		SwizzledFloat4 wwyy();
		SwizzledFloat4 wwyz();
		SwizzledFloat4 wwyw();

		SwizzledFloat4 wwzx();
		SwizzledFloat4 wwzy();
		SwizzledFloat4 wwzz();
		SwizzledFloat4 wwzw();

		SwizzledFloat4 wwwx();
		SwizzledFloat4 wwwy();
		SwizzledFloat4 wwwz();
		SwizzledFloat4 wwww();

		/*
		inline Float4& Float4::operator *= (const Float &other)
		{
			(*call_mul_varying_float)((void*)dataAddress,(void*)other.dataAddress);
			return *this;
		}

		inline Float4& Float4::operator *= (const Float4 &other)
		{
			(*call_mul_varying_float4)((void*)dataAddress,(void*)other.dataAddress);
			return *this;
		}

		inline Float4& Float4::operator *= (const FLOAT32 &other)
		{
			(*call_mul_local_float)((void*)dataAddress,(void*)&other);
			return *this;
		}

		inline Float4& Float4::operator /= (const Float4 &other)
		{
			return *this;
		}
		*/

	public:

		static void (*call_mov_float4)(void *dest,void *source);

		static void (*call_mul_varying_float4)(void *dest,void *source);
		static void (*call_mul_local_float)(void *dest,void *source);
			
		static void (*call_mul_varying_float)(void *dest,void *source);

			
	};

	class SampleTexture2D
	{
	public:

		TextureUnit *unit;
		Shader::Float2 *uv;

		void *dataAddress;

		//std::vector<TextureUnit> *textureUnits;

	public:

		SampleTexture2D() : unit(nullptr),uv(nullptr), dataAddress(nullptr)
		{
		}

		//SampleTexture2D& operator()(const Ceng::UINT32 index, Shader::Float2 &uv);
		SampleTexture2D& operator()(TextureUnit &texture, Shader::Float2 &uv);

		void SampleToFloat4(void *destBuffer) const;
	};

	class SwizzledFloat
	{
	public:
		SOAVecFloat* base;
		Ceng::UINT32 a;

	public:

		inline SwizzledFloat(SOAVecFloat* base, Ceng::UINT32 a)
			: base(base), a(a)
		{

		}

		inline SwizzledFloat& operator = (Ceng::FLOAT32 x)
		{
			base[a] = x;
			return *this;
		}

		inline SwizzledFloat& operator = (const Float& source)
		{
			base[a] = source.x;
			return *this;
		}

		inline SwizzledFloat& operator = (const SwizzledFloat& source)
		{
			base[a] = source.base[source.a];
			return *this;
		}

		inline operator Float() const
		{
			return *base;
		}
	};

	class SwizzledFloat2
	{
	public:
		SOAVecFloat* base;
		Ceng::UINT32 a;
		Ceng::UINT32 b;

	public:

		inline SwizzledFloat2(SOAVecFloat* base, Ceng::UINT32 a, Ceng::UINT32 b)
			: base(base), a(a), b(b)
		{

		}

		inline SwizzledFloat2& operator = (const Float2& source)
		{
			if (base == &source._x)
			{
				SOAVecFloat temp[2];

				temp[0] = source._x;
				temp[1] = source._y;

				base[a] = temp[0];
				base[b] = temp[1];
			}
			else
			{
				base[a] = source._x;
				base[b] = source._y;
			}

			return *this;
		}

		inline SwizzledFloat2& operator = (const SwizzledFloat2& source)
		{
			if (base == source.base)
			{
				SOAVecFloat temp[2];

				temp[0] = base[0];
				temp[1] = base[1];

				base[a] = temp[source.a];
				base[b] = temp[source.b];
			}
			else
			{
				base[a] = source.base[source.a];
				base[b] = source.base[source.b];
			}
			
			return *this;
		}

		inline operator Float() const
		{
			return *base;
		}

		inline operator Float2() const
		{
			return { base[a],base[b] };
		}
	};

	class SwizzledFloat3
	{
	public:
		SOAVecFloat* base;
		Ceng::UINT32 a;
		Ceng::UINT32 b;
		Ceng::UINT32 c;

	public:

		inline SwizzledFloat3(SOAVecFloat* base, Ceng::UINT32 a, Ceng::UINT32 b, Ceng::UINT32 c)
			: base(base), a(a), b(b), c(c)
		{

		}

		inline SwizzledFloat3& operator = (const Float3& source)
		{
			if (base == &source._x)
			{
				SOAVecFloat temp[3];

				temp[0] = source._x;
				temp[1] = source._y;
				temp[2] = source._z;

				base[a] = temp[0];
				base[b] = temp[1];
				base[c] = temp[2];
			}
			else
			{
				base[a] = source._x;
				base[b] = source._y;
				base[c] = source._z;
			}			

			return *this;
		}

		inline SwizzledFloat3& operator = (const SwizzledFloat3& source)
		{
			if (base == source.base)
			{
				SOAVecFloat temp[3];

				temp[0] = base[0];
				temp[1] = base[1];
				temp[2] = base[2];

				base[a] = temp[source.a];
				base[b] = temp[source.b];
				base[c] = temp[source.c];
			}
			else
			{
				base[a] = source.base[source.a];
				base[b] = source.base[source.b];
				base[c] = source.base[source.c];
			}			

			return *this;
		}

		inline operator Float() const
		{
			return *base;
		}

		inline operator Float2() const
		{
			return { base[a],base[b] };
		}

		inline operator Float3() const
		{
			return { base[a],base[b], base[c] };
		}
	};

	class SwizzledFloat4
	{
	public:
		SOAVecFloat* base;
		Ceng::UINT32 a;
		Ceng::UINT32 b;
		Ceng::UINT32 c;
		Ceng::UINT32 d;

	public:

		inline SwizzledFloat4(SOAVecFloat* base, Ceng::UINT32 a, Ceng::UINT32 b, Ceng::UINT32 c, Ceng::UINT32 d)
			: base(base), a(a), b(b), c(c), d(d)
		{

		}

		inline SwizzledFloat4& operator = (const Float4& source)
		{
			if (base == &source._x)
			{
				SOAVecFloat temp[4];

				temp[0] = source._x;
				temp[1] = source._y;
				temp[2] = source._z;
				temp[3] = source._w;

				base[a] = temp[0];
				base[b] = temp[1];
				base[c] = temp[2];
				base[d] = temp[3];
			}
			else
			{
				base[a] = source._x;
				base[b] = source._y;
				base[c] = source._z;
				base[d] = source._w;
			}			

			return *this;
		}

		inline SwizzledFloat4& operator = (const SwizzledFloat4& source)
		{
			if (base == source.base)
			{
				SOAVecFloat temp[4];

				temp[0] = base[0];
				temp[1] = base[1];
				temp[2] = base[2];
				temp[3] = base[3];

				base[a] = temp[source.a];
				base[b] = temp[source.b];
				base[c] = temp[source.c];
				base[d] = temp[source.d];
			}
			else
			{
				base[a] = source.base[source.a];
				base[b] = source.base[source.b];
				base[c] = source.base[source.c];
				base[d] = source.base[source.d];
			}			

			return *this;
		}

		inline operator Float() const
		{
			return *base;
		}

		inline operator Float2() const
		{
			return { base[a],base[b] };
		}

		inline operator Float3() const
		{
			return { base[a],base[b], base[c] };
		}

		inline operator Float4() const
		{
			return { base[a],base[b], base[c], base[d]};
		}
	};

	//**********************************************************
	// Shader::Float methods

	inline Float& Float::operator= (const Float2& other)
	{
		x = other._x;
		return *this;
	}

	inline Float& Float::operator= (const Float3& other)
	{
		x = other._x;
		return *this;
	}

	inline Float& Float::operator= (const Float4& other)
	{
		x = other._x;
		return *this;
	}

	inline Float& Float::operator= (const SwizzledFloat& other)
	{
		x = *other.base;
		return *this;			
	}

	//**********************************************************
	// Shader::Float2 methods

	inline Float2& Float2::operator= (const Float3& other)
	{
		_x = other._x;
		_y = other._y;

		return *this;
	}

	inline Float2& Float2::operator= (const Float4& other)
	{
		_x = other._x;
		_y = other._y;

		return *this;
	}

	inline Float2& Float2::operator= (const SwizzledFloat2& other)
	{
		if (other.base == &_x)
		{
			SOAVecFloat temp[2];

			temp[0] = _x;
			temp[1] = _y;

			_x = temp[other.a];
			_y = temp[other.b];
		}
		else
		{
			_x = other.base[other.a];
			_y = other.base[other.b];
		}		

		return *this;
	}

	inline SwizzledFloat Float2::x() 
	{
		return SwizzledFloat(&_x, 0);
	}

	inline SwizzledFloat Float2::y() 
	{
		return SwizzledFloat(&_y, 1);
	}

	inline SwizzledFloat2 Float2::xx() 
	{
		return SwizzledFloat2(&_x,0,0);
	}

	inline SwizzledFloat2 Float2::xy() 
	{
		return SwizzledFloat2(&_x, 0, 1);
	}

	inline SwizzledFloat2 Float2::yx() 
	{
		return SwizzledFloat2(&_x, 1, 0);
	}

	inline SwizzledFloat2 Float2::yy() 
	{
		return SwizzledFloat2(&_x, 1, 1);
	}

	//**********************************************************
	// Shader::Float3 methods

	inline Float3& Float3::operator= (const Float4& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;

		return *this;
	}

	inline Float3& Float3::operator= (const SwizzledFloat3& other)
	{
		if (other.base == &_x)
		{
			SOAVecFloat temp[3];

			temp[0] = _x;
			temp[1] = _y;
			temp[2] = _z;

			_x = temp[other.a];
			_y = temp[other.b];
			_z = temp[other.c];
		}
		else
		{
			_x = other.base[other.a];
			_y = other.base[other.b];
			_z = other.base[other.c];
		}

		return *this;
	}

	inline SwizzledFloat Float3::x()
	{
		return SwizzledFloat(&_x, 0);
	}

	inline SwizzledFloat Float3::y()
	{
		return SwizzledFloat(&_y, 1);
	}

	inline SwizzledFloat Float3::z()
	{
		return SwizzledFloat(&_z, 2);
	}

	inline SwizzledFloat2 Float3::xx()
	{
		return SwizzledFloat2(&_x,0,0);
	}

	inline SwizzledFloat2 Float3::xy()
	{
		return SwizzledFloat2(&_x, 0, 1);
	}

	inline SwizzledFloat2 Float3::xz()
	{
		return SwizzledFloat2(&_x, 0, 2);
	}

	inline SwizzledFloat2 Float3::yx()
	{
		return SwizzledFloat2(&_x, 1, 0);
	}

	inline SwizzledFloat2 Float3::yy()
	{
		return SwizzledFloat2(&_x, 1, 1);
	}

	inline SwizzledFloat2 Float3::yz()
	{
		return SwizzledFloat2(&_x, 1, 2);
	}

	inline SwizzledFloat2 Float3::zx()
	{
		return SwizzledFloat2(&_x, 2, 0);
	}

	inline SwizzledFloat2 Float3::zy()
	{
		return SwizzledFloat2(&_x, 2, 1);
	}

	inline SwizzledFloat2 Float3::zz()
	{
		return SwizzledFloat2(&_x, 2, 2);
	}

	inline SwizzledFloat3 Float3::xxx()
	{
		return SwizzledFloat3(&_x, 0, 0, 0);
	}

	inline SwizzledFloat3 Float3::xxy()
	{
		return SwizzledFloat3(&_x, 0, 0, 1);
	}

	inline SwizzledFloat3 Float3::xxz()
	{
		return SwizzledFloat3(&_x, 0, 0, 2);
	}

	inline SwizzledFloat3 Float3::xyx()
	{
		return SwizzledFloat3(&_x, 0, 1, 0);
	}

	inline SwizzledFloat3 Float3::xyy()
	{
		return SwizzledFloat3(&_x, 0, 1, 1);
	}

	inline SwizzledFloat3 Float3::xyz()
	{
		return SwizzledFloat3(&_x, 0, 1, 2);
	}

	inline SwizzledFloat3 Float3::xzx()
	{
		return SwizzledFloat3(&_x, 0, 2, 0);
	}

	inline SwizzledFloat3 Float3::xzy()
	{
		return SwizzledFloat3(&_x, 0, 2, 1);
	}

	inline SwizzledFloat3 Float3::xzz()
	{
		return SwizzledFloat3(&_x, 0, 2, 2);
	}

	inline SwizzledFloat3 Float3::yxx()
	{
		return SwizzledFloat3(&_x, 1, 0, 0);
	}

	inline SwizzledFloat3 Float3::yxy()
	{
		return SwizzledFloat3(&_x, 1, 0, 1);
	}

	inline SwizzledFloat3 Float3::yxz()
	{
		return SwizzledFloat3(&_x, 1, 0, 2);
	}

	inline SwizzledFloat3 Float3::yyx()
	{
		return SwizzledFloat3(&_x, 1, 1, 0);
	}

	inline SwizzledFloat3 Float3::yyy()
	{
		return SwizzledFloat3(&_x, 1, 1, 1);
	}

	inline SwizzledFloat3 Float3::yyz()
	{
		return SwizzledFloat3(&_x, 1, 1, 2);
	}

	inline SwizzledFloat3 Float3::yzx()
	{
		return SwizzledFloat3(&_x, 1, 2, 0);
	}

	inline SwizzledFloat3 Float3::yzy()
	{
		return SwizzledFloat3(&_x, 1, 2, 1);
	}

	inline SwizzledFloat3 Float3::yzz()
	{
		return SwizzledFloat3(&_x, 1, 2, 2);
	}

	inline SwizzledFloat3 Float3::zxx()
	{
		return SwizzledFloat3(&_x, 2, 0, 0);
	}

	inline SwizzledFloat3 Float3::zxy()
	{
		return SwizzledFloat3(&_x, 2, 0, 1);
	}

	inline SwizzledFloat3 Float3::zxz()
	{
		return SwizzledFloat3(&_x, 2, 0, 2);
	}

	inline SwizzledFloat3 Float3::zyx()
	{
		return SwizzledFloat3(&_x, 2, 1, 0);
	}

	inline SwizzledFloat3 Float3::zyy()
	{
		return SwizzledFloat3(&_x, 2, 1, 1);
	}

	inline SwizzledFloat3 Float3::zyz()
	{
		return SwizzledFloat3(&_x, 2, 1, 2);
	}

	inline SwizzledFloat3 Float3::zzx()
	{
		return SwizzledFloat3(&_x, 2, 2, 0);
	}

	inline SwizzledFloat3 Float3::zzy()
	{
		return SwizzledFloat3(&_x, 2, 2, 1);
	}

	inline SwizzledFloat3 Float3::zzz()
	{
		return SwizzledFloat3(&_x, 2, 2, 2);
	}

	//**********************************************************
	// Shader::Float4 methods		

	inline Float4& Float4::operator = (const SampleTexture2D& source)
	{
		(*call_mov_float4)((void*)&_x, (void*)source.dataAddress);
		return *this;
	}

	inline Float4& Float4::operator = (const SwizzledFloat4& source)
	{
		if (source.base == &_x)
		{
			SOAVecFloat temp[4];

			temp[0] = _x;
			temp[1] = _y;
			temp[2] = _z;
			temp[3] = _w;

			_x = temp[source.a];
			_y = temp[source.b];
			_z = temp[source.c];
			_w = temp[source.d];
		}
		else
		{
			_x = source.base[source.a];
			_y = source.base[source.b];
			_z = source.base[source.c];
			_w = source.base[source.d];
		}

		return *this;
	}

	inline SwizzledFloat Float4::x()
	{

	}

	inline SwizzledFloat Float4::y()
	{

	}

	inline SwizzledFloat Float4::z()
	{

	}

	inline SwizzledFloat Float4::w()
	{

	}

	inline SwizzledFloat2 Float4::xx()
	{

	}

	inline SwizzledFloat2 Float4::xy()
	{

	}

	inline SwizzledFloat2 Float4::xz()
	{

	}

	inline SwizzledFloat2 Float4::xw()
	{

	}

	inline SwizzledFloat2 Float4::yx()
	{

	}

	inline SwizzledFloat2 Float4::yy()
	{

	}

	inline SwizzledFloat2 Float4::yz()
	{

	}

	inline SwizzledFloat2 Float4::yw()
	{

	}

	inline SwizzledFloat2 Float4::zx()
	{

	}

	inline SwizzledFloat2 Float4::zy()
	{

	}

	inline SwizzledFloat2 Float4::zz()
	{

	}

	inline SwizzledFloat2 Float4::zw()
	{
		
	}

	inline SwizzledFloat2 Float4::wx()
	{

	}

	inline SwizzledFloat2 Float4::wy()
	{

	}

	inline SwizzledFloat2 Float4::wz()
	{

	}

	inline SwizzledFloat2 Float4::ww()
	{

	}

	inline SwizzledFloat3 Float4::xxx()
	{

	}

	inline SwizzledFloat3 Float4::xxy()
	{

	}

	inline SwizzledFloat3 Float4::xxz()
	{

	}

	inline SwizzledFloat3 Float4::xxw()
	{

	}

	inline SwizzledFloat3 Float4::xyx()
	{

	}

	inline SwizzledFloat3 Float4::xyy()
	{

	}

	inline SwizzledFloat3 Float4::xyz()
	{

	}

	inline SwizzledFloat3 Float4::xyw()
	{

	}

	inline SwizzledFloat3 Float4::xzx()
	{

	}

	inline SwizzledFloat3 Float4::xzy()
	{

	}

	inline SwizzledFloat3 Float4::xzz()
	{

	}

	inline SwizzledFloat3 Float4::xzw()
	{

	}

	inline SwizzledFloat3 Float4::xwx()
	{

	}

	inline SwizzledFloat3 Float4::xwy()
	{

	}

	inline SwizzledFloat3 Float4::xwz()
	{

	}

	inline SwizzledFloat3 Float4::xww()
	{

	}

	inline SwizzledFloat3 Float4::yxx()
	{

	}

	inline SwizzledFloat3 Float4::yxy()
	{

	}

	inline SwizzledFloat3 Float4::yxz()
	{

	}

	inline SwizzledFloat3 Float4::yxw()
	{

	}

	inline SwizzledFloat3 Float4::yyx()
	{

	}

	inline SwizzledFloat3 Float4::yyy()
	{

	}

	inline SwizzledFloat3 Float4::yyz()
	{

	}

	inline SwizzledFloat3 Float4::yyw()
	{

	}

	inline SwizzledFloat3 Float4::yzx()
	{

	}

	inline SwizzledFloat3 Float4::yzy()
	{

	}

	inline SwizzledFloat3 Float4::yzz()
	{

	}

	inline SwizzledFloat3 Float4::yzw()
	{

	}

	inline SwizzledFloat3 Float4::ywx()
	{

	}

	inline SwizzledFloat3 Float4::ywy()
	{

	}

	inline SwizzledFloat3 Float4::ywz()
	{

	}

	inline SwizzledFloat3 Float4::yww()
	{

	}		

	inline SwizzledFloat3 Float4::zxx()
	{

	}

	inline SwizzledFloat3 Float4::zxy()
	{

	}

	inline SwizzledFloat3 Float4::zxz()
	{

	}

	inline SwizzledFloat3 Float4::zxw()
	{

	}

	inline SwizzledFloat3 Float4::zyx()
	{

	}

	inline SwizzledFloat3 Float4::zyy()
	{

	}

	inline SwizzledFloat3 Float4::zyz()
	{

	}

	inline SwizzledFloat3 Float4::zyw()
	{

	}

	inline SwizzledFloat3 Float4::zzx()
	{

	}

	inline SwizzledFloat3 Float4::zzy()
	{

	}

	inline SwizzledFloat3 Float4::zzz()
	{

	}

	inline SwizzledFloat3 Float4::zzw()
	{

	}

	inline SwizzledFloat3 Float4::zwx()
	{

	}

	inline SwizzledFloat3 Float4::zwy()
	{

	}

	inline SwizzledFloat3 Float4::zwz()
	{

	}

	inline 	SwizzledFloat3 Float4::zww()
	{

	}

	inline SwizzledFloat3 Float4::wxx()
	{

	}

	inline SwizzledFloat3 Float4::wxy()
	{

	}

	inline SwizzledFloat3 Float4::wxz()
	{

	}

	inline SwizzledFloat3 Float4::wxw()
	{

	}

	inline SwizzledFloat3 Float4::wyx()
	{

	}

	inline SwizzledFloat3 Float4::wyy()
	{

	}

	inline SwizzledFloat3 Float4::wyz()
	{

	}

	inline SwizzledFloat3 Float4::wyw()
	{

	}

	inline SwizzledFloat3 Float4::wzx()
	{

	}

	inline SwizzledFloat3 Float4::wzy()
	{

	}

	inline SwizzledFloat3 Float4::wzz()
	{

	}

	inline SwizzledFloat3 Float4::wzw()
	{

	}

	inline SwizzledFloat3 Float4::wwx()
	{

	}

	inline SwizzledFloat3 Float4::wwy()
	{

	}

	inline SwizzledFloat3 Float4::wwz()
	{

	}

	inline SwizzledFloat3 Float4::www()
	{

	}

	// swizzles x---

	inline SwizzledFloat4 Float4::xxxx()
	{

	}

	inline SwizzledFloat4 Float4::xxxy()
	{

	}

	inline SwizzledFloat4 Float4::xxxz()
	{

	}

	inline 	SwizzledFloat4 Float4::xxxw()
	{

	}

	inline SwizzledFloat4 Float4::xxyx()
	{

	}

	inline SwizzledFloat4 Float4::xxyy()
	{

	}

	inline SwizzledFloat4 Float4::xxyz()
	{

	}

	inline SwizzledFloat4 Float4::xxyw()
	{

	}

	inline SwizzledFloat4 Float4::xxzx()
	{

	}

	inline SwizzledFloat4 Float4::xxzy()
	{

	}

	inline SwizzledFloat4 Float4::xxzz()
	{

	}

	inline SwizzledFloat4 Float4::xxzw()
	{

	}

	inline SwizzledFloat4 Float4::xxwx()
	{

	}

	inline SwizzledFloat4 Float4::xxwy()
	{

	}

	inline SwizzledFloat4 Float4::xxwz()
	{

	}

	inline SwizzledFloat4 Float4::xxww()
	{

	}

	inline SwizzledFloat4 Float4::xyxx()
	{

	}

	inline SwizzledFloat4 Float4::xyxy()
	{

	}

	inline SwizzledFloat4 Float4::xyxz()
	{

	}

	inline SwizzledFloat4 Float4::xyxw()
	{

	}

	inline SwizzledFloat4 Float4::xyyx()
	{

	}

	inline SwizzledFloat4 Float4::xyyy()
	{

	}

	inline SwizzledFloat4 Float4::xyyz()
	{

	}

	inline SwizzledFloat4 Float4::xyyw()
	{

	}

	inline SwizzledFloat4 Float4::xyzx()
	{

	}

	inline SwizzledFloat4 Float4::xyzy()
	{

	}

	inline SwizzledFloat4 Float4::xyzz()
	{

	}

	inline SwizzledFloat4 Float4::xyzw()
	{

	}

	inline SwizzledFloat4 Float4::xywx()
	{

	}

	inline SwizzledFloat4 Float4::xywy()
	{

	}

	inline SwizzledFloat4 Float4::xywz()
	{

	}

	inline SwizzledFloat4 Float4::xyww()
	{

	}

	inline SwizzledFloat4 Float4::xzxx()
	{

	}

	inline SwizzledFloat4 Float4::xzxy()
	{

	}

	inline SwizzledFloat4 Float4::xzxz()
	{

	}

	inline SwizzledFloat4 Float4::xzxw()
	{

	}

	inline SwizzledFloat4 Float4::xzyx()
	{

	}

	inline SwizzledFloat4 Float4::xzyy()
	{

	}

	inline SwizzledFloat4 Float4::xzyz()
	{

	}

	inline SwizzledFloat4 Float4::xzyw()
	{

	}

	inline SwizzledFloat4 Float4::xzzx()
	{

	}

	inline SwizzledFloat4 Float4::xzzy()
	{

	}

	inline SwizzledFloat4 Float4::xzzz()
	{

	}

	inline SwizzledFloat4 Float4::xzzw()
	{

	}

	inline 	SwizzledFloat4 Float4::xzwx()
	{

	}

	inline SwizzledFloat4 Float4::xzwy()
	{

	}

	inline SwizzledFloat4 Float4::xzwz()
	{

	}

	inline SwizzledFloat4 Float4::xzww()
	{

	}

	inline SwizzledFloat4 Float4::xwxx()
	{

	}

	inline SwizzledFloat4 Float4::xwxy()
	{

	}

	inline SwizzledFloat4 Float4::xwxz()
	{

	}

	inline SwizzledFloat4 Float4::xwxw()
	{

	}

	inline SwizzledFloat4 Float4::xwyx()
	{

	}

	inline SwizzledFloat4 Float4::xwyy()
	{

	}

	inline SwizzledFloat4 Float4::xwyz()
	{

	}

	inline SwizzledFloat4 Float4::xwyw()
	{

	}

	inline SwizzledFloat4 Float4::xwzx()
	{

	}

	inline SwizzledFloat4 Float4::xwzy()
	{

	}

	inline SwizzledFloat4 Float4::xwzz()
	{

	}

	inline SwizzledFloat4 Float4::xwzw()
	{

	}

	inline SwizzledFloat4 Float4::xwwx()
	{

	}

	inline SwizzledFloat4 Float4::xwwy()
	{

	}

	inline SwizzledFloat4 Float4::xwwz()
	{

	}

	inline SwizzledFloat4 Float4::xwww()
	{

	}

	// swizzles y---

	inline SwizzledFloat4 Float4::yxxx()
	{

	}

	inline SwizzledFloat4 Float4::yxxy()
	{

	}

	inline SwizzledFloat4 Float4::yxxz()
	{

	}

	inline SwizzledFloat4 Float4::yxxw()
	{

	}

	inline SwizzledFloat4 Float4::yxyx()
	{

	}

	inline SwizzledFloat4 Float4::yxyy()
	{

	}

	inline SwizzledFloat4 Float4::yxyz()
	{

	}

	inline SwizzledFloat4 Float4::yxyw()
	{

	}

	inline SwizzledFloat4 Float4::yxzx()
	{

	}

	inline SwizzledFloat4 Float4::yxzy()
	{

	}

	inline SwizzledFloat4 Float4::yxzz()
	{

	}

	inline SwizzledFloat4 Float4::yxzw()
	{

	}

	inline SwizzledFloat4 Float4::yxwx()
	{

	}

	inline SwizzledFloat4 Float4::yxwy()
	{

	}

	inline SwizzledFloat4 Float4::yxwz()
	{

	}

	inline SwizzledFloat4 Float4::yxww()
	{

	}

	inline SwizzledFloat4 Float4::yyxx()
	{

	}

	inline SwizzledFloat4 Float4::yyxy()
	{

	}

	inline SwizzledFloat4 Float4::yyxz()
	{

	}

	inline SwizzledFloat4 Float4::yyxw()
	{

	}

	inline SwizzledFloat4 Float4::yyyx()
	{

	}

	inline SwizzledFloat4 Float4::yyyy()
	{

	}

	inline SwizzledFloat4 Float4::yyyz()
	{

	}

	inline SwizzledFloat4 Float4::yyyw()
	{

	}

	inline SwizzledFloat4 Float4::yyzx()
	{

	}

	inline SwizzledFloat4 Float4::yyzy()
	{

	}

	inline SwizzledFloat4 Float4::yyzz()
	{

	}

	inline SwizzledFloat4 Float4::yyzw()
	{

	}

	inline SwizzledFloat4 Float4::yywx()
	{

	}

	inline SwizzledFloat4 Float4::yywy()
	{

	}

	inline SwizzledFloat4 Float4::yywz()
	{

	}

	inline SwizzledFloat4 Float4::yyww()
	{

	}

	inline SwizzledFloat4 Float4::yzxx()
	{

	}

	inline SwizzledFloat4 Float4::yzxy()
	{

	}

	inline SwizzledFloat4 Float4::yzxz()
	{

	}

	inline SwizzledFloat4 Float4::yzxw()
	{

	}

	inline SwizzledFloat4 Float4::yzyx()
	{

	}

	inline SwizzledFloat4 Float4::yzyy()
	{

	}

	inline SwizzledFloat4 Float4::yzyz()
	{

	}

	inline SwizzledFloat4 Float4::yzyw()
	{

	}

	inline SwizzledFloat4 Float4::yzzx()
	{

	}

	inline SwizzledFloat4 Float4::yzzy()
	{

	}

	inline SwizzledFloat4 Float4::yzzz()
	{

	}

	inline SwizzledFloat4 Float4::yzzw()
	{

	}

	inline SwizzledFloat4 Float4::yzwx()
	{

	}

	inline SwizzledFloat4 Float4::yzwy()
	{

	}

	inline SwizzledFloat4 Float4::yzwz()
	{

	}

	inline SwizzledFloat4 Float4::yzww()
	{

	}

	inline SwizzledFloat4 Float4::ywxx()
	{

	}

	inline SwizzledFloat4 Float4::ywxy()
	{

	}

	inline SwizzledFloat4 Float4::ywxz()
	{

	}

	inline SwizzledFloat4 Float4::ywxw()
	{

	}

	inline SwizzledFloat4 Float4::ywyx()
	{

	}

	inline SwizzledFloat4 Float4::ywyy()
	{

	}

	inline SwizzledFloat4 Float4::ywyz()
	{

	}

	inline SwizzledFloat4 Float4::ywyw()
	{

	}

	inline SwizzledFloat4 Float4::ywzx()
	{

	}

	inline SwizzledFloat4 Float4::ywzy()
	{

	}

	inline SwizzledFloat4 Float4::ywzz()
	{

	}

	inline SwizzledFloat4 Float4::ywzw()
	{

	}

	inline SwizzledFloat4 Float4::ywwx()
	{

	}

	inline 	SwizzledFloat4 Float4::ywwy()
	{

	}

	inline SwizzledFloat4 Float4::ywwz()
	{

	}

	inline SwizzledFloat4 Float4::ywww()
	{

	}

	// swizzles z---

	inline SwizzledFloat4 Float4::zxxx()
	{

	}

	inline SwizzledFloat4 Float4::zxxy()
	{

	}

	inline SwizzledFloat4 Float4::zxxz()
	{

	}

	inline SwizzledFloat4 Float4::zxxw()
	{

	}

	inline SwizzledFloat4 Float4::zxyx()
	{

	}

	inline SwizzledFloat4 Float4::zxyy()
	{

	}

	inline SwizzledFloat4 Float4::zxyz()
	{

	}

	inline SwizzledFloat4 Float4::zxyw()
	{

	}

	inline SwizzledFloat4 Float4::zxzx()
	{

	}

	inline SwizzledFloat4 Float4::zxzy()
	{

	}

	inline SwizzledFloat4 Float4::zxzz()
	{

	}

	inline SwizzledFloat4 Float4::zxzw()
	{

	}

	inline SwizzledFloat4 Float4::zxwx()
	{

	}

	inline SwizzledFloat4 Float4::zxwy()
	{

	}

	inline SwizzledFloat4 Float4::zxwz()
	{

	}

	inline 	SwizzledFloat4 Float4::zxww()
	{

	}

	inline SwizzledFloat4 Float4::zyxx()
	{

	}

	inline SwizzledFloat4 Float4::zyxy()
	{

	}

	inline SwizzledFloat4 Float4::zyxz()
	{

	}

	inline SwizzledFloat4 Float4::zyxw()
	{

	}

	inline SwizzledFloat4 Float4::zyyx()
	{

	}

	inline SwizzledFloat4 Float4::zyyy()
	{

	}

	inline SwizzledFloat4 Float4::zyyz()
	{

	}

	inline SwizzledFloat4 Float4::zyyw()
	{

	}

	inline SwizzledFloat4 Float4::zyzx()
	{

	}

	inline SwizzledFloat4 Float4::zyzy()
	{

	}

	inline SwizzledFloat4 Float4::zyzz()
	{

	}

	inline SwizzledFloat4 Float4::zyzw()
	{

	}

	inline SwizzledFloat4 Float4::zywx()
	{

	}

	inline SwizzledFloat4 Float4::zywy()
	{

	}

	inline SwizzledFloat4 Float4::zywz()
	{

	}

	inline SwizzledFloat4 Float4::zyww()
	{

	}

	inline SwizzledFloat4 Float4::zzxx()
	{

	}

	inline SwizzledFloat4 Float4::zzxy()
	{

	}

	inline SwizzledFloat4 Float4::zzxz()
	{

	}

	inline SwizzledFloat4 Float4::zzxw()
	{

	}

	inline SwizzledFloat4 Float4::zzyx()
	{

	}

	inline SwizzledFloat4 Float4::zzyy()
	{

	}

	inline SwizzledFloat4 Float4::zzyz()
	{

	}

	inline SwizzledFloat4 Float4::zzyw()
	{

	}

	inline SwizzledFloat4 Float4::zzzx()
	{

	}

	inline SwizzledFloat4 Float4::zzzy()
	{

	}

	inline SwizzledFloat4 Float4::zzzz()
	{

	}

	inline SwizzledFloat4 Float4::zzzw()
	{

	}

	inline SwizzledFloat4 Float4::zzwx()
	{

	}

	inline SwizzledFloat4 Float4::zzwy()
	{

	}

	inline SwizzledFloat4 Float4::zzwz()
	{

	}

	inline SwizzledFloat4 Float4::zzww()
	{

	}

	inline SwizzledFloat4 Float4::zwxx()
	{

	}

	inline SwizzledFloat4 Float4::zwxy()
	{

	}

	inline SwizzledFloat4 Float4::zwxz()
	{

	}

	inline SwizzledFloat4 Float4::zwxw()
	{

	}

	inline SwizzledFloat4 Float4::zwyx()
	{

	}

	inline SwizzledFloat4 Float4::zwyy()
	{

	}

	inline SwizzledFloat4 Float4::zwyz()
	{

	}
		
	inline SwizzledFloat4 Float4::zwyw()
	{

	}

	inline SwizzledFloat4 Float4::zwzx()
	{

	}

	inline SwizzledFloat4 Float4::zwzy()
	{

	}

	inline SwizzledFloat4 Float4::zwzz()
	{

	}

	inline SwizzledFloat4 Float4::zwzw()
	{

	}

	inline SwizzledFloat4 Float4::zwwx()
	{

	}

	inline SwizzledFloat4 Float4::zwwy()
	{

	}

	inline SwizzledFloat4 Float4::zwwz()
	{

	}

	inline SwizzledFloat4 Float4::zwww()
	{

	}

	// swizzles w---

	inline SwizzledFloat4 Float4::wxxx()
	{

	}

	inline SwizzledFloat4 Float4::wxxy()
	{

	}

	inline SwizzledFloat4 Float4::wxxz()
	{

	}

	inline SwizzledFloat4 Float4::wxxw()
	{

	}

	inline SwizzledFloat4 Float4::wxyx()
	{

	}

	inline SwizzledFloat4 Float4::wxyy()
	{

	}

	inline SwizzledFloat4 Float4::wxyz()
	{

	}

	inline SwizzledFloat4 Float4::wxyw()
	{

	}

	inline SwizzledFloat4 Float4::wxzx()
	{

	}

	inline SwizzledFloat4 Float4::wxzy()
	{

	}

	inline SwizzledFloat4 Float4::wxzz()
	{

	}

	inline SwizzledFloat4 Float4::wxzw()
	{

	}

	inline SwizzledFloat4 Float4::wxwx()
	{

	}

	inline SwizzledFloat4 Float4::wxwy()
	{

	}

	inline SwizzledFloat4 Float4::wxwz()
	{

	}

	inline SwizzledFloat4 Float4::wxww()
	{

	}

	inline SwizzledFloat4 Float4::wyxx()
	{

	}

	inline SwizzledFloat4 Float4::wyxy()
	{

	}

	inline SwizzledFloat4 Float4::wyxz()
	{

	}

	inline SwizzledFloat4 Float4::wyxw()
	{

	}

	inline SwizzledFloat4 Float4::wyyx()
	{

	}

	inline SwizzledFloat4 Float4::wyyy()
	{

	}

	inline SwizzledFloat4 Float4::wyyz()
	{

	}

	inline SwizzledFloat4 Float4::wyyw()
	{

	}

	inline SwizzledFloat4 Float4::wyzx()
	{

	}

	inline SwizzledFloat4 Float4::wyzy()
	{

	}

	inline SwizzledFloat4 Float4::wyzz()
	{

	}

	inline SwizzledFloat4 Float4::wyzw()
	{

	}

	inline SwizzledFloat4 Float4::wywx()
	{

	}

	inline SwizzledFloat4 Float4::wywy()
	{

	}

	inline SwizzledFloat4 Float4::wywz()
	{

	}

	inline SwizzledFloat4 Float4::wyww()
	{

	}

	inline SwizzledFloat4 Float4::wzxx()
	{

	}

	inline SwizzledFloat4 Float4::wzxy()
	{

	}

	inline SwizzledFloat4 Float4::wzxz()
	{

	}

	inline SwizzledFloat4 Float4::wzxw()
	{

	}

	inline SwizzledFloat4 Float4::wzyx()
	{

	}

	inline SwizzledFloat4 Float4::wzyy()
	{

	}

	inline SwizzledFloat4 Float4::wzyz()
	{

	}

	inline SwizzledFloat4 Float4::wzyw()
	{

	}

	inline SwizzledFloat4 Float4::wzzx()
	{

	}

	inline SwizzledFloat4 Float4::wzzy()
	{

	}

	inline SwizzledFloat4 Float4::wzzz()
	{

	}

	inline SwizzledFloat4 Float4::wzzw()
	{

	}

	inline SwizzledFloat4 Float4::wzwx()
	{

	}

	inline SwizzledFloat4 Float4::wzwy()
	{

	}

	inline SwizzledFloat4 Float4::wzwz()
	{

	}

	inline SwizzledFloat4 Float4::wzww()
	{

	}

	inline SwizzledFloat4 Float4::wwxx()
	{

	}

	inline SwizzledFloat4 Float4::wwxy()
	{

	}

	inline SwizzledFloat4 Float4::wwxz()
	{

	}

	inline SwizzledFloat4 Float4::wwxw()
	{

	}

	inline SwizzledFloat4 Float4::wwyx()
	{

	}

	inline SwizzledFloat4 Float4::wwyy()
	{

	}

	inline SwizzledFloat4 Float4::wwyz()
	{

	}

	inline SwizzledFloat4 Float4::wwyw()
	{

	}

	inline SwizzledFloat4 Float4::wwzx()
	{

	}

	inline SwizzledFloat4 Float4::wwzy()
	{

	}

	inline SwizzledFloat4 Float4::wwzz()
	{

	}

	inline SwizzledFloat4 Float4::wwzw()
	{

	}

	inline SwizzledFloat4 Float4::wwwx()
	{

	}

	inline SwizzledFloat4 Float4::wwwy()
	{

	}

	inline SwizzledFloat4 Float4::wwwz()
	{

	}

	inline SwizzledFloat4 Float4::wwww()
	{

	}

	//**********************************************************
	// SampleTexture2D methods

	inline SampleTexture2D& SampleTexture2D::operator()(TextureUnit &texture, Shader::Float2 &uv)
	{
		unit = &texture;
		this->uv = &uv;

		//texture.view->Sample2D(uv, texture.sampler, (Ceng::FLOAT32*)dataAddress);

		return *this;
	}

	inline void SampleTexture2D::SampleToFloat4(void *destBuffer) const
	{
		unit->view->Sample2D(*uv, unit->sampler, (Ceng::FLOAT32*)destBuffer);
	}

}; // namespace Ceng::Shader

#endif // Include guard