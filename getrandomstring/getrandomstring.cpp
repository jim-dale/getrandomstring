
#define _CRT_RAND_S
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <memory>
#include <vector>

#include "RandomNumberGenerator.h"
#include "Generator.h"
#include "CharacterType.h"

#include "Options.h"
#include "Context.h"
#include "ArgProcessor.h"

static const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
static const char* digits = "0123456789";
static const char* specials = R"({}[]()<>!%^&*-_=+;:@#~,./?\|)";

static const char* lettersByFrequency = "etaoinsrhdlucmfywgpbvkxqjz";
static const std::vector<double> lettersProbabilities = { 12.02, 9.10, 8.12, 7.68, 7.31, 6.95, 6.28, 6.02, 5.92, 4.32, 3.98, 2.88, 2.71, 2.61, 2.30, 2.11, 2.09, 2.03, 1.82, 1.49, 1.11, 0.69, 0.17, 0.11, 0.10, 0.07 };

std::vector<char> MakeVectorFromString(char const*const str)
{
    std::vector<char> result;
    for (const char* ptr = str; *ptr != '\0'; ptr++)
    {
        result.push_back(*ptr);
    }
    return result;
}

Context CreateContext(Options options)
{
    Context result{};

    result.length = options.length;

    if (options.excludeNumbers == false)
    {
        result.characterTypes.push_back(CharacterType::Number);
    }
    if (options.excludeLowercase == false)
    {
        result.characterTypes.push_back(CharacterType::LowercaseLetter);
    }
    if (options.excludeUppercase == false)
    {
        result.characterTypes.push_back(CharacterType::UppercaseLetter);
    }
    if (options.excludeSpecial == false)
    {
        result.characterTypes.push_back(CharacterType::Special);
    }
    result.typeGenerator.Initialise(result.characterTypes);

    if (options.useLetterFrequency)
    {
        result.letterGenerator.Initialise(MakeVectorFromString(lettersByFrequency), lettersProbabilities);
    }
    else
    {
        result.letterGenerator.Initialise(MakeVectorFromString(alphabet));
    }
    result.numberGenerator.Initialise(MakeVectorFromString(digits));
    result.special.Initialise(MakeVectorFromString(specials));

    result.randomTypeValues = result.random.VectorGenerator(result.length);
    result.randomCharValues = result.random.VectorGenerator(result.length);

    return result;
}

char GenerateCharacter(Context context, unsigned int randomTypeValue, unsigned int randomCharValue)
{
    char result = '\0';

    auto type = context.typeGenerator.GetNext(randomTypeValue);
    switch (type)
    {
    case UppercaseLetter:
        result = context.letterGenerator.GetNext(randomCharValue);
        result = (char)toupper(result);
        break;
    case LowercaseLetter:
        result = context.letterGenerator.GetNext(randomCharValue);
        break;
    case Number:
        result = context.numberGenerator.GetNext(randomCharValue);
        break;
    case Special:
        result = context.special.GetNext(randomCharValue);
        break;
    default:
        break;
    }
    return result;
}

int main(int argc, char *argv[])
{
    auto options = ArgProcessor::Parse(argc, argv);
    auto context = CreateContext(options);

    if (options.showHelp)
    {
        ArgProcessor::ShowHelp();
    }
    else
    {
        for (size_t i = 0; i < context.length; i++)
        {
            auto randomTypeValue = context.randomTypeValues[i];
            auto randomCharValue = context.randomCharValues[i];

            char ch = GenerateCharacter(context, randomTypeValue, randomCharValue);
            if (ch != '\0')
            {
                context.randomString.append(1, ch);
            }
            else
            {
                context.result = 1;
                break;
            }
        }
        if (context.result == 0)
        {
            puts(context.randomString.c_str());
        }
    }
    return context.result;
}
