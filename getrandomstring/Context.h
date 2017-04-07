#pragma once

struct Context
{
    int result;
    size_t length;
    std::vector<CharacterType> characterTypes;

    RandomNumberGenerator random;
    Generator<CharacterType> typeGenerator;
    Generator<char> letterGenerator;
    Generator<char> numberGenerator;
    Generator<char> special;

    std::vector<unsigned int> randomTypeValues;
    std::vector<unsigned int> randomCharValues;

    std::string randomString;
};
