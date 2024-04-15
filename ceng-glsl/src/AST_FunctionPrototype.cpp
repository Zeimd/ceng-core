#include <ceng/GLSL/AST_FunctionPrototype.h>

using namespace Ceng::GLSL;

AST_FunctionPrototype::AST_FunctionPrototype(const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::function_prototype), returnType(AST_Datatype()), name(name)
{

}

AST_FunctionPrototype::AST_FunctionPrototype(AST_Datatype& returnType, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::function_prototype), returnType(returnType), name(name)
{

}

AST_FunctionPrototype::AST_FunctionPrototype(AST_Datatype& returnType, const Ceng::StringUtf8& name, std::vector<FunctionParameter>&& params)
	: IASTNode(AST_NodeType::function_prototype), returnType(returnType), name(name), params(std::move(params))
{

}

AST_FunctionPrototype::~AST_FunctionPrototype()
{

}

Ceng::StringUtf8 AST_FunctionPrototype::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += returnType.ToString();
	out += ' ';
	out += name;
	out += '(';

	for (size_t k=0; k < params.size(); k++)
	{
		out += params[k].ToString();

		if (k != params.size() - 1)
		{
			out += ", ";
		}
	}

	out += ");";
	
	return out;
}

Ceng::StringUtf8 AST_FunctionPrototype::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}