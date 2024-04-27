
// Debug information
#ifdef _MSC_VER

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>

#endif // _DEBUG

#endif // _MSC_VER

#include <stdio.h>
#include <fstream>
#include <sstream>

#include <ceng/GLSL/Tokenizer.h>
#include <ceng/GLSL/ceng_GLSL.h>

int main()
{
#ifdef _MSC_VER

#ifdef _DEBUG
	// Detect memory leaks after main-function ends
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif // _DEBUG

#endif // _MSC_VER

	/*
	
	int x = 0;
	int y = 0;

	x = 1;

	y = x++ + 1 + (x = 3) + (x = 4);

	printf("x = %i, y = %i\n", x, y);

	x = 1;

	y = x + 1 << 2*2;

	printf("x = %i, y = %i\n", x, y);

	return 0;
	*/
	
	
	

	std::ifstream fileReader;

	const char* shaderFile = "forward.vs";

	fileReader.open(shaderFile, std::ios::in);
	if (!fileReader.good())
	{
		printf("Failed to open file: %s\n", shaderFile);
		return 0;
	}

	std::stringstream builder;

	std::string line;

	while (!fileReader.eof())
	{
		std::getline(fileReader, line);
		if (!fileReader.good())
		{
			if (fileReader.bad())
			{
				return 0;
			}
		}

		builder << line << '\n';
	}

	printf("Source file:\n");
	printf("%s\n", builder.str().c_str());

	Ceng::Tokenizer tokenizer;

	/*
	std::vector<Ceng::Token> tokens;

	tokens.push_back(Ceng::Token("foo", 0, 0, false, false, false, false, Ceng::TokenType::keyword_in));
	tokens.push_back(Ceng::Token("foo", 0, 0, false, false, false, false, Ceng::TokenType::type_vec4));
	tokens.push_back(Ceng::Token("foo", 0, 0, false, false, false, false, Ceng::TokenType::identifier,"position"));
	tokens.push_back(Ceng::Token("foo", 0, 0, false, false, false, true, Ceng::TokenType::semicolon));
	*/

	Ceng::StringUtf8 text = builder.str();

	std::vector<Ceng::Token> tokens;

	Ceng::CRESULT cresult = tokenizer.Tokenize("forward.vs",text, tokens);

	printf("**********************************************************\n");	

	cresult = tokenizer.RemoveComments(tokens, tokens);

	printf("Tokenized output:\n");
	printf("--------------------------------------\n");
	printf("Clean:\n");
	for (auto& x : tokens)
	{
		printf("%s ", x.ToString().ToCString());
		if (x.endLine)
		{
			printf("\n");
		}
	}
	
	printf("--------------------------------------\n");
	printf("Diagnostic:\n");
	for (auto& x : tokens)
	{
		
		printf("%s ", x.ToDiagnosticString().ToCString());
		if (x.endLine)
		{
			printf("\n");
		}
	}

	printf("**********************************************************\n");
	printf("Parser output:\n");

	Ceng::GLSL::IParser* parser;

	cresult = Ceng::GLSL::GetParser(&parser);

	if (cresult != Ceng::CE_OK)
	{
		printf("Failed to get parser: %i\n", cresult);
		return 0;
	}

	
	Ceng::GLSL::AbstractSyntaxTree programTree;

	cresult = parser->Parse(Ceng::GLSL::ShaderType::geometry,tokens, programTree);

	auto log = parser->GetLog();

	printf("%s\n", log.ToString().ToCString());
	

	parser->Release();

	return 0;
}