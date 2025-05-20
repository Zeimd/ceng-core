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

namespace Ceng
{
	namespace Shader
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
				: a(0.0f),b(0.0f),c(0.0f),d(0.0f)
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

			inline Bool(Ceng::BOOL a, Ceng::BOOL b, Ceng::BOOL c, Ceng::BOOL d)
				: x(a, b, c, d)
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
			return left == right;
		}

		inline Bool operator != (const Bool& left, const Bool& right)
		{
			return left != right;
		}

		class Float2;
		class Float3;
		class Float4;

		class SampleTexture2D;

		template<class T>
		class alignas(16) Basic_SOA_Single
		{

		};

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

			inline Float(Ceng::FLOAT32 a, Ceng::FLOAT32 b, Ceng::FLOAT32 c, Ceng::FLOAT32 d)
				: x(a,b,c,d)
			{
			
			}

			inline Float& operator= (const Float& other)
			{
				x = other.x;
				return *this;
			}

			inline Float& operator= (const Float2& other)
			{
				x = other.x;
				return *this;
			}

			inline Float& operator= (const Float3& other)
			{
				x = other.x;
				return *this;
			}

			inline Float& operator= (const Float4& other)
			{
				x = other.x;
				return *this;
			}


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
			SOAVecFloat x;
			SOAVecFloat y;

		public:
			inline Float2()
			{

			}

			inline Float2(const SOAVecFloat& x, const SOAVecFloat& y)
				: x(x), y(y)
			{

			}

			inline Float2(Ceng::FLOAT32 a, Ceng::FLOAT32 b, Ceng::FLOAT32 c, Ceng::FLOAT32 d)
				: x(a, b, c, d)
			{

			}

			inline Float2& operator= (const Float& other)
			{
				x = other.x;
				y = 0.0f;

				return *this;
			}

			inline Float2& operator= (const Float2& other)
			{
				x = other.x;
				y = other.y;

				return *this;
			}

			inline Float2& operator= (const Float3& other)
			{
				x = other.x;
				y = other.y;

				return *this;
			}

			inline Float2& operator= (const Float4& other)
			{
				x = other.x;
				y = other.y;

				return *this;
			}


			inline Float2& operator = (const CR_PixelShaderInput& source)
			{
				source.MoveToFloat2(&x);
				return *this;
			}

			inline Float2& operator += (const Float2& other)
			{
				x += other.x;
				y += other.y;

				return *this;
			}

			inline Float2& operator -= (const Float2& other)
			{
				x -= other.x;
				y -= other.y;

				return *this;
			}

			inline Float2& operator *= (const Float2& other)
			{
				x *= other.x;
				y *= other.y;

				return *this;
			}

			inline Float2& operator /= (const Float2& other)
			{
				x /= other.x;
				y /= other.y;

				return *this;
			}
		};

		inline Float2 operator + (const Float2& a, const Float2& b)
		{
			return { a.x + b.x, a.y + b.y };
		}

		inline Float2 operator - (const Float2& a, const Float2& b)
		{
			return { a.x - b.x, a.y - b.y };
		}

		inline Float2 operator * (const Float2& a, const Float2& b)
		{
			return  { a.x * b.x, a.y * b.y };
		}

		inline Float2 operator / (const Float2& a, const Float2& b)
		{
			return  { a.x / b.x, a.y / b.y };
		}

		inline Bool2 operator == (const Float2& a, const Float2& b)
		{
			return  { a.x == b.x, a.y == b.y };
		}

		inline Bool2 operator != (const Float2& a, const Float2& b)
		{
			return { a.x != b.x, a.y != b.y };
		}

		inline Bool2 operator < (const Float2& a, const Float2& b)
		{
			return { a.x < b.x, a.y < b.y };
		}

		inline Bool2 operator > (const Float2& a, const Float2& b)
		{
			return { a.x > b.x, a.y > b.y };
		}

		inline Bool2 operator <= (const Float2& a, const Float2& b)
		{
			return { a.x <= b.x, a.y <= b.y };
		}

		inline Bool2 operator >= (const Float2& a, const Float2& b)
		{
			return { a.x >= b.x, a.y >= b.y };
		}

		class alignas(16) Float3
		{
		public:
			SOAVecFloat x;
			SOAVecFloat y;
			SOAVecFloat z;

		public:
		}


		class alignas(16) Float4
		{
		public:
			SOAVecFloat x;
			SOAVecFloat y;
			SOAVecFloat z;
			SOAVecFloat w;

		public:
			Float4();
			//Float4(const Float4 &other);

			Float4& operator = (const Float4 &other);

			Float4& operator = (const CR_PixelShaderInput &source);

			Float4& operator = (const SampleTexture2D &source);

			Float4& operator += (const Float4 &other);
			Float4& operator -= (const Float4 &other);

			/**
			 * Multiply by varying scalar.
			 */
			Float4& operator *= (const Shader::Float &other);

			Float4& operator *= (const Float4 &other);
			
			/**
			 * Multiply by local scalar.
			 */
			Float4& operator *= (const FLOAT32 &other);

			Float4& operator /= (const Float4 &other);

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

		//************************************************************
		// Shader::Float2 methods

		inline Float2::Float2()
		{
			dataAddress = nullptr;
		}

		/*
		inline Float2::Float2(const Float2 &other)
			: dataAddress(other.dataAddress)
		{
		}
		*/

		inline Float2& Float2::operator = (const CR_PixelShaderInput &source)
		{
			source.MoveToFloat2(dataAddress);
			return *this;
		}

		//************************************************************
		// Shader::Float4 methods


		inline Float4::Float4()
		{
			dataAddress = nullptr;
		}

		inline Float4& Float4::operator = (const Float4 &other)
		{
			return *this;
		}

		inline Float4& Float4::operator = (const CR_PixelShaderInput &source)
		{
			source.MoveToFloat4(dataAddress);
			return *this;
		}

		inline Float4& Float4::operator = (const SampleTexture2D &source)
		{
			(*call_mov_float4)((void*)dataAddress, (void*)source.dataAddress);
			return *this;
		}

		inline Float4& Float4::operator += (const Float4 &other)
		{
			return *this;
		}

		inline Float4& Float4::operator -= (const Float4 &other)
		{
			return *this;
		}

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

	}; // namespace Shader

}; // namespace Ceng

#endif // Include guard