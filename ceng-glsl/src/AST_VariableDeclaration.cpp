#include <ceng/GLSL/AST_VariableDeclaration.h>

#include <ceng/GLSL/StorageQualifierType.h>
#include <ceng/GLSL/InterpolationQualifierType.h>
#include <ceng/GLSL/PrecisionQualifierType.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

/*
AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize()
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& initializer)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(), initializer(initializer)
{

}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(true), arraySize()
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray, const Rvalue& initializer)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(true), arraySize(), initializer(initializer)
{

}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& arraySize, bool filler)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(arraySize)
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, const Rvalue& arraySize, const Rvalue& initializer)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(arraySize), initializer(initializer)
{

}



AST_VariableDeclaration::~AST_VariableDeclaration()
{

}

Ceng::StringUtf8 AST_VariableDeclaration::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	if (invariant)
	{
		out += "invariant ";
	}

	if (layout.size() > 0)
	{
		out += "layout(";

		for (int k = 0; k < layout.size(); k++)
		{
			out += layout[k].name;

			if (layout[k].hasValue)
			{
				out += '=';
				out += layout[k].value;
			}

			if (k < layout.size() - 1)
			{
				out += ", ";
			}
		}

		out += ") ";
	}

	out += GLSL::InterpolationQualifierType::ToString(interpolation);
	if (interpolation != InterpolationQualifierType::unused)
	{
		out += ' ';
	}

	out += GLSL::StorageQualifierType::ToString(storage);
	if (storage != StorageQualifierType::unused)
	{
		out += ' ';
	}

	out += GLSL::PrecisionQualifierType::ToString(precision);
	if (precision != GLSL::PrecisionQualifierType::unassigned)
	{
		out += ' ';
	}

	out += datatype.ToString();

	out += ' ';

	out += name;

	if (arraySize.valueType != RvalueType::unused)
	{
		out += '[';
		out += arraySize.ToString(indentLevel);
		out += ']';
	}
	else if (implicitArray)
	{
		out += "[]";
	}

	if (initializer.valueType != RvalueType::unused)
	{
		out += " = ";
		out += initializer.ToString(indentLevel);
	}
	
	out += ";\n";

	return out;	
}

Ceng::StringUtf8 AST_VariableDeclaration::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}
*/