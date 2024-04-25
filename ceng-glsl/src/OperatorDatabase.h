#ifndef CENG_GLSL_OPERATOR_DATABASE_H
#define CENG_GLSL_OPERATOR_DATABASE_H

#include <unordered_map>
#include <optional>

#include <ceng/GLSL/AST_BinaryOperator.h>
#include <ceng/GLSL/AST_UnaryOperator.h>
#include <ceng/GLSL/BasicType.h>

namespace Ceng
{
	namespace GLSL
	{
		enum class OperationValidity
		{
			// Not allowed
			invalid,

			// Allowed without special steps
			valid,

			// Implicit promotion of second operand to first type
			left_promotion,

			// Implicit promotion of first operand to second type
			right_promotion,
		};

		enum class ConversionResult
		{
			yes,
			no,
			not_needed,
		};

		struct OperationInfo
		{
			OperationValidity status;
		};

		template<class T1, class T2>
		struct TupleHash2
		{
			size_t operator() (const std::tuple<T1, T2>& x) const
			{
				std::hash<T1> a;
				std::hash<T2> b;
	
				return a(std::get<0>(x)) ^ b(std::get<1>(x));
			}
		};

		template<class T1, class T2, class T3>
		struct TupleHash3
		{			
			size_t operator() (const std::tuple<T1,T2,T3>& x) const
			{
				std::hash<T1> a;
				std::hash<T2> b;
				std::hash<T3> c;

				return a(std::get<0>(x)) ^ b(std::get<1>(x)) ^ c(std::get<2>(x));
			}
		};

		class ConversionTable
		{
		public:

			using keytype = std::tuple<int, int>;

			std::unordered_map<keytype, bool, TupleHash2<int, int>> table;

			ConversionTable(std::unordered_map<keytype, bool,TupleHash2<int, int>> table_)
				: table(table_)
			{

			}

			bool CheckPromotion(BasicType::value source, BasicType::value dest) const
			{
				auto item = table.find({ source,dest });

				return item != table.end();
			}
		};

		extern const ConversionTable implicitConversions;

		class OperatorDatabase
		{
		public:

			using keytype = std::tuple<int, int>;

			std::unordered_map<keytype, bool, TupleHash2<int,int>> binaryOperations;

		public:

			OperationValidity CheckScalarValidity(BasicType::value a, BasicType::value b) const;

			OperatorDatabase(std::unordered_map<keytype, bool, TupleHash2<int, int>> binaryOperations);

			OperationInfo CheckAssignment(BasicType::value dest, BasicType::value source) const;

			OperationInfo CheckScalarOperation(BasicTypeInfo& a, BinaryOperator::value op, BasicTypeInfo& b) const;

			OperationInfo Check(BasicType::value first, BinaryOperator::value op, BasicType::value second) const;

		private:

			ConversionResult CheckImplicitConversion(BasicType::value source, BasicType::value dest) const;
		};

		extern const OperatorDatabase operatorDatabase;
	}
}

#endif