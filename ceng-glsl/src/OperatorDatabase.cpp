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

OperatorDatabase::OperatorDatabase(std::unordered_map<keytype, OperationInfo, TupleHash<int, int, int>> binaryOperations,
	std::unordered_map<keytype, OperationInfo, TupleHash<int, int, int>> unaryOperations)
	: binaryOperations(binaryOperations), unaryOperations(unaryOperations)
{

}


OperationInfo OperatorDatabase::Check(BasicType::value first, BinaryOperator::value op, BasicType::value second)
{
	BasicTypeInfo a = GetTypeInfo(first);
	BasicTypeInfo b = GetTypeInfo(second);

	if (a.category == BasicTypeCategory::matrix)
	{
		switch (op)
		{
		case BinaryOperator::add:
		case BinaryOperator::sub:
			if (a == b)
			{
				return { OperationValidity::valid };
			}

			return { OperationValidity::invalid };

		case BinaryOperator::mul:

			if (b.category == BasicTypeCategory::matrix)
			{
				if (a.width == b.height)
				{
					return { OperationValidity::valid };
				}

				return { OperationValidity::invalid };
			}			

			if (b.category == BasicTypeCategory::vector)
			{
				if (a.width == b.width)
				{
					return { OperationValidity::valid };
				}

				return { OperationValidity::invalid };
			}

			if (b.category == BasicTypeCategory::scalar)
			{
				return { OperationValidity::valid };
			}

		default:

			return { OperationValidity::invalid };
		}
	}

	if (a.category == BasicTypeCategory::vector)
	{
		if (b.category == BasicTypeCategory::matrix)
		{
			return { OperationValidity::invalid };
		}

		switch (op)
		{
		case BinaryOperator::add:
		case BinaryOperator::sub:
		case BinaryOperator::mul:
		case BinaryOperator::div:
		case BinaryOperator::mod:

			if (b.category == BasicTypeCategory::vector)
			{
				if (a.width == b.width)
				{
					return { OperationValidity::valid };
				}

				return { OperationValidity::invalid };
			}
			
			if (b.category == BasicTypeCategory::scalar)
			{
				return { OperationValidity::valid };
			}

			return { OperationValidity::invalid };
		default:
			return { OperationValidity::invalid };
		}
	}

	if (a.category == BasicTypeCategory::scalar)
	{
		if (b.category == BasicTypeCategory::scalar)
		{
			return { OperationValidity::valid };
		}

		if (b.category == BasicTypeCategory::vector || b.category == BasicTypeCategory::matrix)
		{
			if (op == BinaryOperator::mul)
			{
				return { OperationValidity::valid };
			}

			return { OperationValidity::invalid };
		}
	}

	return {OperationValidity::invalid};
}
