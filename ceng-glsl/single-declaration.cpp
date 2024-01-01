#include <ceng/single-declaration.h>

using namespace Ceng;

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name)
	: fullType(fullType), name(name)
{

}