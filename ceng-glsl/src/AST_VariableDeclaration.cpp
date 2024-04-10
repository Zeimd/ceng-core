#include <ceng/GLSL/AST_VariableDeclaration.h>

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
	return "";
}