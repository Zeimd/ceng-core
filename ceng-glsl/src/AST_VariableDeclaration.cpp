#include <ceng/GLSL/AST_VariableDeclaration.h>

#include <ceng/GLSL/StorageQualifierType.h>
#include <ceng/GLSL/InterpolationQualifierType.h>
#include <ceng/GLSL/PrecisionQualifierType.h>

using namespace Ceng::GLSL;

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(0), initializer(nullptr)
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, std::shared_ptr<IASTNode>& initializer)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(0), initializer(initializer)
{

}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(true), arraySize(0), initializer(nullptr)
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, bool implicitArray, std::shared_ptr<IASTNode>& initializer)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(true), arraySize(0), initializer(initializer)
{

}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, Ceng::UINT32 arraySize)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), datatype(datatype), name(name), implicitArray(false), arraySize(arraySize), initializer(nullptr)
{
	
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	AST_Datatype& datatype, const Ceng::StringUtf8& name, Ceng::UINT32 arraySize, std::shared_ptr<IASTNode>& initializer)
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

	if (arraySize > 0)
	{
		out += '[';
		out += arraySize;
		out += ']';
	}
	else if (implicitArray)
	{
		out += "[]";
	}

	if (initializer != nullptr)
	{
		out += initializer->RhsToString(indentLevel);
	}

	out += ";\n";

	return out;	
}

Ceng::StringUtf8 AST_VariableDeclaration::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}