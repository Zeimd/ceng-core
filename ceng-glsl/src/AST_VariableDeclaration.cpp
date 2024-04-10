#include <ceng/GLSL/AST_VariableDeclaration.h>

#include <ceng/GLSL/StorageQualifierType.h>
#include <ceng/GLSL/InterpolationQualifierType.h>
#include <ceng/GLSL/PrecisionQualifierType.h>

using namespace Ceng::GLSL;

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	DataType::value dataType, const Ceng::StringUtf8* customTypeName, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), dataType(dataType), name(name), implicitArray(false), arraySize(0)
{
	if (dataType == DataType::type_name)
	{
		this->customTypeName = *customTypeName;
	}
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	DataType::value dataType, const Ceng::StringUtf8* customTypeName, const Ceng::StringUtf8& name, bool implicitArray)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), dataType(dataType), name(name), implicitArray(true), arraySize(0)
{
	if (dataType == DataType::type_name)
	{
		this->customTypeName = *customTypeName;
	}
}

AST_VariableDeclaration::AST_VariableDeclaration(bool invariant, std::vector<LayoutData>& layout, StorageQualifierType::value storage,
	InterpolationQualifierType::value interpolation, PrecisionQualifierType::value precision,
	const Ceng::StringUtf8& typeName, const Ceng::StringUtf8* customTypeName, Ceng::UINT32 arraySize)
	: IASTNode(AST_NodeType::variable_declaration), invariant(invariant), layout(layout), storage(storage), interpolation(interpolation),
	precision(precision), dataType(dataType), name(name), implicitArray(false), arraySize(arraySize)
{
	if (dataType == DataType::type_name)
	{
		this->customTypeName = *customTypeName;
	}
}


AST_VariableDeclaration::~AST_VariableDeclaration()
{

}

Ceng::StringUtf8 AST_VariableDeclaration::ToString(Ceng::UINT32 indentLevel) const
{
	printf(__FUNCTION__);

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

	if (dataType == DataType::type_name)
	{
		out += customTypeName;
	}
	else
	{
		out += DataType::ToString(dataType);
	}

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

	out += ';';

	return out;	
}