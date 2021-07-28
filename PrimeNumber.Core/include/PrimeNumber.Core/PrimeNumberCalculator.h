#pragma once

#include <PrimeNumber.Core/PrimeNumber.Core.API.h>

#include <vector>
#include <sstream>
#include <algorithm>

template<typename T>
inline size_t convertToSize_T(T toConv)
	{
	return static_cast<size_t>(toConv);
	}

template<>
inline size_t convertToSize_T(std::string toConv)
	{
	size_t ret;
	std::istringstream(toConv) >> ret;
	return ret;
	}

template<>
inline size_t convertToSize_T(std::wstring toConv)
	{
	size_t ret;
	std::wistringstream(toConv) >> ret;
	return ret;
	}

template<typename T>
inline T convertFromSize_T(size_t toConv)
	{
	return static_cast<T>(toConv);
	}

template<>
inline std::string convertFromSize_T(size_t toConv)
	{
	return std::to_string(toConv);
	}

template<>
inline std::wstring convertFromSize_T(size_t toConv)
	{
	return std::to_wstring(toConv);
	}

class PRIMENUMBERCORE_API PrimeNumberCalculator
  {
  public:
    PrimeNumberCalculator();

		template<typename T>
		std::vector<T> GetPrimeNumbers(T i_till_value)
			{
			vector<T> res;
			static vector<size_t> primes = {2};
			for (size_t i = primes.back() + 1, n = convertToSize_T(i_till_value); i <= n; i++)
				{
				bool is_prime = 1;
				for (size_t prime : primes)
					{
					if (i % prime == 0)
						{
						is_prime = 0;
						break;
						}
					}
				if (is_prime)
					primes.push_back(i);
				}

			transform(
				begin(primes), 
				upper_bound(begin(primes), end(primes), convertToSize_T(i_till_value)), 
				back_inserter(res), 
				convertFromSize_T<T>
			);
			return res;

			}
  };

