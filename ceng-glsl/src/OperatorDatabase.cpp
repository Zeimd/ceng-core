#include "OperatorDatabase.h"

namespace Ceng
{
	namespace GLSL
	{
		const OperatorDatabase operatorDatabase
		{
			// Binary operators
			{		
				{
					{BasicType::ts_int, BinaryOperator::add, BasicType::ts_int},
					{OperationValidity::valid}
				},
		
				{
					{BasicType::ts_int, BinaryOperator::sub, BasicType::ts_int},
					{OperationValidity::valid}
				},
			
				{
					{BasicType::ts_int, BinaryOperator::mul, BasicType::ts_int},
					{OperationValidity::valid}
				},
		
				{
					{BasicType::ts_int, BinaryOperator::div, BasicType::ts_int},
					{OperationValidity::valid}
				},
		
				{
					{BasicType::ts_int, BinaryOperator::mod, BasicType::ts_int},
					{OperationValidity::valid}
				},
		
				{
					{BasicType::ts_int, BinaryOperator::left_shift, BasicType::ts_int},
					{OperationValidity::valid}
				},
		
				{
					{BasicType::ts_int, BinaryOperator::right_shift, BasicType::ts_int},
					{OperationValidity::valid}
				},

				{
					{BasicType::ts_int, BinaryOperator::bitwise_and, BasicType::ts_int},
					{OperationValidity::valid}
				},

				{
					{BasicType::ts_int, BinaryOperator::bitwise_or, BasicType::ts_int},
					{OperationValidity::valid}
				},

				{
					{BasicType::ts_int, BinaryOperator::bitwise_xor, BasicType::ts_int},
					{OperationValidity::valid}
				},

			},

			// Unary operators
			{
			}
		};
	}
}

using namespace Ceng::GLSL;
