#ifndef CENG_GLSL_AST_VARIABLE_DECLARATION_H
#define CENG_GLSL_AST_VARIABLE_DECLARATION_H

#include "IASTNode.h"

#include "InterpolationQualifierType.h"
#include "StorageQualifierType.h"
#include "PrecisionQualifierType.h"
#include "LayoutData.h"
#include "BasicType.h"

#include "AST_Datatype.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_VariableDeclaration : public IASTNode
		{
		public:
			bool invariant;

			std::vector<LayoutData> layout;

			StorageQualifierType::value storage;
			InterpolationQualifierType::value interpolation;
			PrecisionQualifierType::value precision;

			AST_Datatype datatype;

			Ceng::StringUtf8 name;			

			bool implicitArray;
			Ceng::UINT32 arraySize;

			// TODO: initializer

		public:

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage, 
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, Ceng::UINT32 arraySize);

			~AST_VariableDeclaration() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif