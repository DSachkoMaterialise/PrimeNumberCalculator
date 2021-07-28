#include <PrimeNumber.Core/PrimeNumberCalculator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>

using namespace std;

auto foo = []()
	{
	return vector<string>();
	};

#define TUPLE_VECTORS(NAME, ...) static const tuple<vector<size_t>, vector<int>, vector<double>, vector<string>, vector<wstring>> NAME = {	\
		{ __VA_ARGS__},							\
		{ __VA_ARGS__},							\
		{ __VA_ARGS__},							\
		[]()												\
		{														\
			vector<string> res;				\
			vector<size_t> toTransform{__VA_ARGS__};\
			transform(begin(toTransform), end(toTransform), back_inserter(res), [](size_t trans){return to_string(trans);});\
			return res;\
		}(),\
		[]()												\
		{														\
			vector<wstring> res;				\
			vector<size_t> toTransform{__VA_ARGS__};\
			transform(begin(toTransform), end(toTransform), back_inserter(res), [](size_t trans){return to_wstring(trans);});\
			return res;\
		}()\
}		//ILLE

TUPLE_VECTORS(tuple_primes,	
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,	// https://oeis.org/A000040
	61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
	131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
	193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
	263, 269, 271
);


template <typename T>
class ResultTester : public ::testing::Test
	{
	public:
		ResultTester() : PRIMES(get<vector<T>>(tuple_primes))
			{}
		PrimeNumberCalculator calc;
		const vector<T> PRIMES;
		vector<T> getAnswer(T bound) const
			{
			return vector(begin(PRIMES), upper_bound(begin(PRIMES), end(PRIMES), bound, [](T l, T r)
				{
				return convertToSize_T(l) < convertToSize_T(r);
				}));
			}
	};

TYPED_TEST_SUITE_P(ResultTester);

TYPED_TEST_P(ResultTester, checkAlgorithm)
	{
	for (size_t i = 0; i <= convertToSize_T(PRIMES.back()); i++)
		{
		auto res = this->calc.GetPrimeNumbers(convertFromSize_T<TypeParam>(i));
		ASSERT_EQ(getAnswer(convertFromSize_T<TypeParam>(i)), res);
		}

	}

REGISTER_TYPED_TEST_SUITE_P(ResultTester, checkAlgorithm);

using Types = ::testing::Types<size_t, int, double, string, wstring>;

INSTANTIATE_TYPED_TEST_SUITE_P(TestPrefix, ResultTester, Types);

