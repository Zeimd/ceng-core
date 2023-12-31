
#include <stdio.h>
#include <fstream>
#include <sstream>

#include <ceng/tokenizer.h>

int main()
{
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

	cresult = tokenizer.RemoveComments(tokens,tokens);

	printf("Tokenized output:\n");
	for (auto& x : tokens)
	{
		printf("%s ", x.ToString().ToCString());
		//printf("%s ", x.ToDiagnosticString().ToCString());
		if (x.endLine)
		{
			printf("\n");
		}
	}
	
	return 0;
}