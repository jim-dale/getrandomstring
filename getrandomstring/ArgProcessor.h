#pragma once

class ArgProcessor
{
private:
    enum ParserState
    {
        ExpectOption,
        ExpectExclusions,
        ExpectLength
    };

public:
    static Options Parse(int argc, char *argv[])
    {
        Options result{};

        ParserState state = ParserState::ExpectOption;

        result.length = 20;
        result.showHelp = (argc == 1);

        for (int i = 1; i < argc; i++)
        {
            const char* arg = argv[i];
            size_t argLength = strlen(arg);
            switch (state)
            {
            case ParserState::ExpectOption:
                if (argLength > 1)
                {
                    if (arg[0] == '-' || arg[0] == '/')
                    {
                        char option = (char)tolower(arg[1]);

                        switch (option)
                        {
                        case '?':
                            result.showHelp = true;
                            break;
                        case 'x':
                            state = ParserState::ExpectExclusions;
                            break;
                        case 'f':
                            result.useLetterFrequency = true;
                            break;
                        case 'l':
                            state = ParserState::ExpectLength;
                            break;
                        default:
                            result.showHelp = true;
                            break;
                        }
                    }
                }
                break;
            case ParserState::ExpectExclusions:
                ProcessExclusions(arg, result);
                state = ParserState::ExpectOption;
                break;
            case ParserState::ExpectLength:
                result.length = atoi(arg);
                state = ParserState::ExpectOption;
                break;
            default:
                break;
            }
        }
        return result;
    }
    static void ShowHelp()
    {
        printf("Generates a string of random characters.\n\n");
        printf("Usage: %s [-?] [-x slun] [-f] [-l length]\n\n", "getrandomstring");

        printf("  -?         Display this help information.\n");
        printf("  -x slun    Exclude specified character types.\n");
        printf("               s Exclude special characters.\n");
        printf("               l Exclude special characters.\n");
        printf("               u Exclude special characters.\n");
        printf("               n Exclude special characters.\n");
        printf("  -f         Generate alphabetic characters based on probabilities of letters appearing in English sentences.\n");
        printf("             This option produces slightly more readable letter sequences.\n");
        printf("  -l length  Length of string to generate. Default is 20 characters.\n\n");
    }

private:
    static void ProcessExclusions(char const*const list, Options& options)
    {
        for (const char* ptr = list; *ptr != '\0'; ptr++)
        {
            char ch = (char)tolower(*ptr);
            switch (ch)
            {
            case 'n':
                options.excludeNumbers = true;
                break;
            case 'l':
                options.excludeLowercase = true;
                break;
            case 'u':
                options.excludeUppercase = true;
                break;
            case 's':
                options.excludeSpecial = true;
                break;
            default:
                break;
            }
        }
    }
};
