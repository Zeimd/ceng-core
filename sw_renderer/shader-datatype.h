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