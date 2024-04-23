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

		struct OperationInfo
		{
			OperationValidity status;
		};

		template<class T1, class T2, class T3>
		struct TupleHash
		{			
			size_t operator() (const std::tuple<T1,T2,T3>& x) const
			{
				std::hash<T1> a;
				std::hash<T2> b;
				std::hash<T3> c;

				return a(std::get<0>(x)) ^ b(std::get<1>(x)) ^ c(std::get<2>(x));
			}
		};

		class OperatorDatabase
		{
		public:

			using keytype = std::tuple<int, int, int>;

			std::unordered_map<keytype, OperationInfo, TupleHash<int,int,int>> database;

			std::unordered_map<keytype, OperationInfo, TupleHash<int, int, int>> unaryOperations;

		public:

			OperatorDatabase(std::unordered_map<keytype, OperationInfo, TupleHash<int, int, int>> database,
				std::unordered_map<keytype, OperationInfo, TupleHash<int, int, int>> unaryOperations);


			OperationInfo Find(BasicType::value first, BinaryOperator::value op, BasicType::value second);
		};

		extern const OperatorDatabase operatorDatabase;
	}
}

#endif