#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	namespace DeclarationType
	{
		enum value
		{
			function_prototype,
			init_list,
			precision,
			global_interface_block,
			scoped_interface_block,
			scoped_interface_block_array,
			type_qualifier,
		};
	}

	class InitDeclaratorList;
	class FunctionPrototype;
	class PrecisionQualifier;
	class TypeSpecifierNoPrec;
	class StructDeclarationList;
	class TypeQualifier;
	class Expression;

	class Declaration : public INonTerminal
	{
	public:

		DeclarationType::value declarationType;

		std::shared_ptr<FunctionPrototype> prototype;

		std::shared_ptr<InitDeclaratorList> declList;

		std::shared_ptr<PrecisionQualifier> precision;
		std::shared_ptr<TypeSpecifierNoPrec> spec;

		std::shared_ptr<TypeQualifier> typeQ;

		Ceng::StringUtf8 interfaceName;

		std::shared_ptr<StructDeclarationList> list;

		Ceng::StringUtf8 variableName;

		bool implicitArray;

		std::shared_ptr<Expression> arraySize;

	public:

		~Declaration() override;

		void Release() override;

		Declaration(std::shared_ptr<FunctionPrototype>& prototype);

		Declaration(std::shared_ptr<InitDeclaratorList>& declList);

		Declaration(std::shared_ptr<PrecisionQualifier>& precision, std::shared_ptr<TypeSpecifierNoPrec>& spec);

		Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list);

		Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
			const Ceng::StringUtf8& variableName);

		Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
			const Ceng::StringUtf8& variableName, bool implicitArray);

		Declaration(std::shared_ptr<TypeQualifier>& typeQ, const Ceng::StringUtf8& interfaceName, std::shared_ptr<StructDeclarationList>& list,
			const Ceng::StringUtf8& variableName, std::shared_ptr<Expression>& arraySize);

		// Used for geometry shader input in the form "layout(layout_type) in;"
		Declaration(std::shared_ptr<TypeQualifier>& typeQ);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

		size_t NumSymbols() const;

		const Ceng::StringUtf8* GetSymbolName(size_t n) const;

		bool IsConst() const;
		bool IsInteger() const;

	};
}

#endif