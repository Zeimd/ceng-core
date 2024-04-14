#include <ceng/GLSL/VariableExpression.h>

using namespace Ceng::GLSL;

VariableExpression::VariableExpression()
{

}

VariableExpression::VariableExpression(FieldExpression root)
	: chain{ root }
{

}


VariableExpression::VariableExpression(FieldExpression& root)
	: chain{root}
{

}

VariableExpression::VariableExpression(std::vector<FieldExpression>&& chain_)
	: chain(std::move(chain_))
{

}

VariableExpression::~VariableExpression()
{

}

void VariableExpression::Append(FieldExpression& access)
{
	chain.push_back(access);
}

Ceng::StringUtf8 VariableExpression::ToString() const
{
	Ceng::StringUtf8 out;

	for (auto& x : chain)
	{
		out += x.ToString();
	}

	return out;
}