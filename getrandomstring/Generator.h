#pragma once

template<class T>
class Generator
{
public:
    void Initialise(const std::vector<T>& values)
    {
        m_values = values;

        InitialiseProbabilities();
        InitialiseAccumulators();
    }

    void Initialise(const std::vector<T>& values, const std::vector<double>& probabilities)
    {
        m_values = values;
        m_probabilities = probabilities;

        InitialiseAccumulators();
    }

    T GetNext(unsigned int randomValue)
    {
        T result = m_values.back();

        double probability = ((double)randomValue / UINT_MAX) * 100;
        for (size_t i = 0; i < m_probabilities.size(); i++)
        {
            if (probability <= m_accumulators[i])
            {
                result = m_values[i];
                break;
            }
        }
        return result;
    }

private:
    std::vector<T>      m_values;
    std::vector<double> m_probabilities;
    std::vector<double> m_accumulators;

    void InitialiseProbabilities()
    {
        m_probabilities.resize(m_values.size());

        size_t nelem = m_values.size();
        double probability = 100.00 / nelem;
        for (size_t i = 0; i < nelem; i++)
        {
            m_probabilities[i] = probability;
        }
    }

    void InitialiseAccumulators()
    {
        m_accumulators.resize(m_values.size());

        size_t nelem = m_probabilities.size();
        double accumulator = 0.0;
        for (size_t i = 0; i < nelem; i++)
        {
            accumulator += m_probabilities[i];
            m_accumulators[i] = accumulator;
        }
        // Make sure last entry is always 100 percent
        m_accumulators.back() = 100.00;
    }
};
