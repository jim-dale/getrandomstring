#pragma once

class RandomNumberGenerator
{
public:
    std::vector<unsigned int> VectorGenerator(size_t numberOfValues)
    {
        std::vector<unsigned int> result;

        for (size_t i = 0; i < numberOfValues; i++)
        {
            unsigned int randomValue;
            errno_t error = rand_s(&randomValue);
            if (error == 0)
            {
                result.push_back(randomValue);
            }
        }
        return result;
    }
};
