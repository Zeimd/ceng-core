#ifndef CENG_GLSL_AST_VARIABLE_DECLARATION_H
#define CENG_GLSL_AST_VARIABLE_DECLARATION_H

#include "IASTNode.h"

#include "InterpolationQualifierType.h"
#include "StorageQualifierType.h"
#include "PrecisionQualifierType.h"
#include "LayoutData.h"
#include "BasicType.h"

#include "AST_Datatype.h"

#include "Rvalue.h"

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
			Rvalue arraySize;

			Rvalue initializer;

		public:

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage, 
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& initializer);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray, const Rvalue& initializer);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& arraySize, bool filler);

			AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
				InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
				AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& arraySize, const Rvalue& initializer);

			~AST_VariableDeclaration() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif