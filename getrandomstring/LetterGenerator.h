#pragma once

//class LetterGenerator : public ICharacterGenerator
//{
//private:
//    static const int NumLetters = 26;
//    static const double Probabilities[NumLetters];
//    static const char Letters[NumLetters];
//
//public:
//    char GetCharacter(unsigned int randomValue)
//    {
//        char result = '\0';
//
//        double probability = ((double)randomValue / UINT_MAX) * 100;
//        double accumulator = 0.0;
//        for (size_t i = 0; i < NumLetters; i++)
//        {
//            accumulator += Probabilities[i];
//
//            if (probability <= accumulator)
//            {
//                result = Letters[i];
//                break;
//            }
//        }
//        return result;
//    }
//};
//
//
//const double LetterGenerator::Probabilities[NumLetters] = { 12.02, 9.10, 8.12, 7.68, 7.31, 6.95, 6.28, 6.02, 5.92, 4.32, 3.98, 2.88, 2.71, 2.61, 2.30, 2.11, 2.09, 2.03, 1.82, 1.49, 1.11, 0.69, 0.17, 0.11, 0.10, 0.07 };
//const char LetterGenerator::Letters[NumLetters]         = { 'e',   't',  'a',  'o',  'i',  'n',  's',  'r',  'h',  'd',  'l',  'u',  'c',  'm',  'f',  'y',  'w',  'g',  'p',  'b',  'v',  'k',  'x',  'q',  'j',  'z' };
