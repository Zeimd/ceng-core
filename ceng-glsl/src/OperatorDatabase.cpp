#include "OperatorDatabase.h"

namespace Ceng
{
	namespace GLSL
	{
		const ConversionTable implicitConversions
		{
			{
				{
					{BasicType::ts_bool, BasicType::ts_bool},	true
				},
				{
					{BasicType::ts_int, BasicType::ts_int},	true
				},
				{
					{BasicType::ts_uint, BasicType::ts_uint}, true
				},
				{
					{BasicType::ts_float, BasicType::ts_float},true
				},
				{
					{BasicType::ts_int, BasicType::ts_float},true
				},
				{
					{BasicType::ts_uint, BasicType::ts_float}, false
				},
			}
		};

		const OperatorDatabase operatorDatabase
		{
			// Binary operators
			{	
				// int-int

				{
					{BasicType::ts_int, BinaryOperator::add}, true
				},
				
				{
					{BasicType::ts_int, BinaryOperator::sub}, true
				},
			
				
				{
					{BasicType::ts_int, BinaryOperator::mul}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::div}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::mod}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::left_shift}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::right_shift}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::bitwise_and}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::bitwise_or}, true
				},
			
				{
					{BasicType::ts_int, BinaryOperator::bitwise_xor}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::less}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::less_eq}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::greater}, true
				},
			
				{
					{BasicType::ts_int, BinaryOperator::greater_eq}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::equal}, true
				},

				{
					{BasicType::ts_int, BinaryOperator::not_equal}, true
				},

				
				{
					{BasicType::ts_int, BinaryOperator::logical_and}, true
				},
		
				{
					{BasicType::ts_int, BinaryOperator::logical_or}, true
				},
				
				{
					{BasicType::ts_int, BinaryOperator::logical_xor}, true
				},
				
				

				// uint

				{
					{BasicType::ts_uint, BinaryOperator::add}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::sub}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::mul}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::div}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::mod}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::left_shift}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::right_shift}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::bitwise_and}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::bitwise_or}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::bitwise_xor}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::less}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::less_eq}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::greater}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::greater_eq}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::equal}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::not_equal}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::logical_and}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::logical_or}, true
				},

				{
					{BasicType::ts_uint, BinaryOperator::logical_xor}, true
				},

				// float

				{
					{BasicType::ts_float, BinaryOperator::add}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::sub}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::mul}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::div}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::mod}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::left_shift}, false
				},

				{
					{BasicType::ts_float, BinaryOperator::right_shift}, false
				},

				{
					{BasicType::ts_float, BinaryOperator::bitwise_and}, false
				},

				{
					{BasicType::ts_float, BinaryOperator::bitwise_or}, false
				},

				{
					{BasicType::ts_float, BinaryOperator::bitwise_xor}, false
				},

				{
					{BasicType::ts_float, BinaryOperator::less}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::less_eq}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::greater}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::greater_eq}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::equal}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::not_equal}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::logical_and}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::logical_or}, true
				},

				{
					{BasicType::ts_float, BinaryOperator::logical_xor}, true
				},

				// bool

				{
					{BasicType::ts_bool, BinaryOperator::add}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::sub}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::mul}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::div}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::mod}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::left_shift}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::right_shift}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::bitwise_and}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::bitwise_or}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::bitwise_xor}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::less}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::less_eq}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::greater}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::greater_eq}, false
				},

				{
					{BasicType::ts_bool, BinaryOperator::equal}, true
				},

				{
					{BasicType::ts_bool, BinaryOperator::not_equal}, true
				},

				{
					{BasicType::ts_bool, BinaryOperator::logical_and}, true
				},

				{
					{BasicType::ts_bool, BinaryOperator::logical_or}, true
				},

				{
					{BasicType::ts_bool, BinaryOperator::logical_xor}, true
				},
				
				
			}
					
		};
	}
}

using namespace Ceng::GLSL;

OperatorDatabase::OperatorDatabase(std::unordered_map<keytype, bool, TupleHash2<int, int>> binaryOperations)
	: binaryOperations(binaryOperations)
{

}

ConversionResult OperatorDatabase::CheckImplicitConversion(BasicType::value source, BasicType::value dest) const
{
	if (source == dest)
	{
		return ConversionResult::not_needed;
	}

	if (source == BasicType::ts_int || source == BasicType::ts_uint)
	{
		if (dest == BasicType::ts_float)
		{
			return ConversionResult::yes;
		}
	}

	if (source == BasicType::ivec2 || source == BasicType::uvec2)
	{
		if (dest == BasicType::vec2)
		{
			return ConversionResult::yes;
		}
	}

	if (source == BasicType::ivec3 || source == BasicType::uvec3)
	{
		if (dest == BasicType::vec3)
		{
			return ConversionResult::yes;
		}
	}

	if (source == BasicType::ivec4 || source == BasicType::uvec4)
	{
		if (dest == BasicType::vec4)
		{
			return ConversionResult::yes;
		}
	}

	return ConversionResult::no;
}

OperationValidity OperatorDatabase::CheckScalarValidity(BasicType::value a, BasicType::value b) const
{
	OperationValidity validity = OperationValidity::invalid;

	ConversionResult leftConversion = CheckImplicitConversion(a, b);

	if (leftConversion == ConversionResult::not_needed)
	{
		return OperationValidity::valid;
	}
	else
	{
		ConversionResult rightConversion = CheckImplicitConversion(b, a);

		if (leftConversion == rightConversion)
		{
			if (leftConversion == ConversionResult::yes)
			{
				validity = OperationValidity::valid;
			}
			else
			{
				return OperationValidity::invalid;
			}
		}
		else
		{
			if (leftConversion == ConversionResult::yes)
			{
				validity = OperationValidity::left_promotion;
			}
			else
			{
				validity = OperationValidity::right_promotion;
			}
		}
	}

	return validity;
}

OperationInfo OperatorDatabase::CheckScalarOperation(BasicTypeInfo& a, BinaryOperator::value op, BasicTypeInfo& b) const
{
	OperationValidity validity = CheckScalarValidity(a.baseType, b.baseType);
	
	auto item = binaryOperations.find({ a.baseType, op });

	if (item == binaryOperations.end())
	{
		return { OperationValidity::invalid };
	}

	return { validity };
}

OperationInfo OperatorDatabase::CheckAssignment(BasicType::value dest, BasicType::value source) const
{
	BasicTypeInfo a = GetTypeInfo(dest);
	BasicTypeInfo b = GetTypeInfo(source);

	if (a.category == BasicTypeCategory::matrix)
	{
		if (b.category == BasicTypeCategory::matrix)
		{
			if (a.width == b.width && a.height == b.height)
			{
				return { OperationValidity::valid };
			}
		}

		return { OperationValidity::invalid };
	}

	if (a.category == BasicTypeCategory::vector)
	{
		if (b.category != BasicTypeCategory::vector)
		{
			return { OperationValidity::invalid };
		}

		if (a.width != b.width)
		{
			return { OperationValidity::invalid };
		}

		ConversionResult res = CheckImplicitConversion(source, dest);

		if (res == ConversionResult::not_needed)
		{
			return { OperationValidity::valid };
		}

		if (res == ConversionResult::no)
		{
			return { OperationValidity::invalid };
		}

		if (res == ConversionResult::yes)
		{
			return { OperationValidity::right_promotion };
		}
	}

	if (a.category == BasicTypeCategory::scalar)
	{
		ConversionResult res = CheckImplicitConversion(source, dest);

		if (res == ConversionResult::not_needed)
		{
			return { OperationValidity::valid };
		}

		if (res == ConversionResult::no)
		{
			return { OperationValidity::invalid };
		}

		if (res == ConversionResult::yes)
		{
			return { OperationValidity::right_promotion };
		}
	}

	return { OperationValidity::invalid };
}

OperationInfo OperatorDatabase::Check(BasicType::value first, BinaryOperator::value op, BasicType::value second) const
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
			return CheckScalarOperation(a, op, b);
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
