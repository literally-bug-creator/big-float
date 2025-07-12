#include <gtest/gtest.h>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

using big_float::BigFloat;
using big_float::Exponent;
using big_float::GetDefaultError;
using big_float::GetNegative;
using big_float::GetPositive;
using big_float::IsEqual;
using big_float::IsGreater;
using big_float::IsLower;
using big_float::MakeBigFloat;
using big_float::MakeInf;
using big_float::MakeNan;
using big_float::MakeZero;
using big_float::Sign;
using big_float::Type;

namespace {

constexpr uint64_t kSmallNumber = 123;
constexpr uint64_t kLargeNumber = 456;
constexpr uint64_t kTestNumber = 999;
constexpr Exponent kSmallExponent = 3;
constexpr Exponent kLargeExponent = 5;

// Helper function to create BigFloat directly
BigFloat
MakeNumber(uint64_t value, Exponent exp = 0, bool negative = false) {
  big_uint::BigUInt mantissa;
  mantissa.limbs = {value};

  Sign sign = negative ? GetNegative() : GetPositive();
  return MakeBigFloat(mantissa, exp, sign, Type::kDefault, GetDefaultError());
}

}  // namespace

class ComparisonTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Special values
    pos_zero_ = MakeZero(GetPositive());
    neg_zero_ = MakeZero(GetNegative());
    pos_inf_ = MakeInf(GetPositive());
    neg_inf_ = MakeInf(GetNegative());
    pos_nan_ = MakeNan(GetPositive());
    neg_nan_ = MakeNan(GetNegative());

    // Normal numbers
    small_pos_ = MakeNumber(kSmallNumber);
    large_pos_ = MakeNumber(kLargeNumber);
    small_neg_ = MakeNumber(kSmallNumber, 0, true);
    large_neg_ = MakeNumber(kLargeNumber, 0, true);
  }

  BigFloat pos_zero_, neg_zero_;
  BigFloat pos_inf_, neg_inf_;
  BigFloat pos_nan_, neg_nan_;
  BigFloat small_pos_, large_pos_;
  BigFloat small_neg_, large_neg_;
};

TEST_F(ComparisonTest, EqualSameNumbers) {
  BigFloat left = MakeNumber(kSmallNumber);
  BigFloat right = MakeNumber(kSmallNumber);
  bool expected = true;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualDifferentNumbers) {
  BigFloat left = small_pos_;
  BigFloat right = large_pos_;
  bool expected = false;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualBothZeros) {
  BigFloat left = pos_zero_;
  BigFloat right = neg_zero_;
  bool expected = true;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualSameInfinities) {
  BigFloat left = pos_inf_;
  BigFloat right = MakeInf(GetPositive());
  bool expected = true;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualDifferentInfinities) {
  BigFloat left = pos_inf_;
  BigFloat right = neg_inf_;
  bool expected = false;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualNanWithNumber) {
  BigFloat left = pos_nan_;
  BigFloat right = small_pos_;
  bool expected = false;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualNanWithNan) {
  BigFloat left = pos_nan_;
  BigFloat right = neg_nan_;
  bool expected = false;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualDifferentExponents) {
  BigFloat left = MakeNumber(kSmallNumber, kLargeExponent);
  BigFloat right = MakeNumber(kSmallNumber, kSmallExponent);
  bool expected = false;

  bool result = IsEqual(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterPositiveVsNegative) {
  BigFloat left = small_pos_;
  BigFloat right = small_neg_;
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterLargerVsSmaller) {
  BigFloat left = large_pos_;
  BigFloat right = small_pos_;
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterNegativeNumbers) {
  BigFloat left = small_neg_;
  BigFloat right = large_neg_;
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterInfinityVsNumber) {
  BigFloat left = pos_inf_;
  BigFloat right = large_pos_;
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterNumberVsNegInfinity) {
  BigFloat left = small_neg_;
  BigFloat right = neg_inf_;
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterZeroVsZero) {
  BigFloat left = pos_zero_;
  BigFloat right = neg_zero_;
  bool expected = false;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterNanVsAny) {
  BigFloat left = pos_nan_;
  BigFloat right = pos_inf_;
  bool expected = false;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterAnyVsNan) {
  BigFloat left = pos_inf_;
  BigFloat right = pos_nan_;
  bool expected = false;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterEqualValues) {
  BigFloat left = small_pos_;
  BigFloat right = MakeNumber(kSmallNumber);
  bool expected = false;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, GreaterLargerExponent) {
  BigFloat left = MakeNumber(kSmallNumber, kLargeExponent);
  BigFloat right = MakeNumber(kSmallNumber, kSmallExponent);
  bool expected = true;

  bool result = IsGreater(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerNegativeVsPositive) {
  BigFloat left = small_neg_;
  BigFloat right = small_pos_;
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerSmallerVsLarger) {
  BigFloat left = small_pos_;
  BigFloat right = large_pos_;
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerNegativeNumbers) {
  BigFloat left = large_neg_;
  BigFloat right = small_neg_;
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerNegInfinityVsNumber) {
  BigFloat left = neg_inf_;
  BigFloat right = large_neg_;
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerNumberVsInfinity) {
  BigFloat left = large_pos_;
  BigFloat right = pos_inf_;
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerZeroVsZero) {
  BigFloat left = neg_zero_;
  BigFloat right = pos_zero_;
  bool expected = false;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerNanVsAny) {
  BigFloat left = neg_nan_;
  BigFloat right = neg_inf_;
  bool expected = false;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerAnyVsNan) {
  BigFloat left = neg_inf_;
  BigFloat right = neg_nan_;
  bool expected = false;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerEqualValues) {
  BigFloat left = large_pos_;
  BigFloat right = MakeNumber(kLargeNumber);
  bool expected = false;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, LowerSmallerExponent) {
  BigFloat left = MakeNumber(kSmallNumber, kSmallExponent);
  BigFloat right = MakeNumber(kSmallNumber, kLargeExponent);
  bool expected = true;

  bool result = IsLower(left, right);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, NegativeLargerMagnitudeIsLower) {
  BigFloat neg_small = MakeNumber(kSmallNumber, 0, true);  // -123
  BigFloat neg_large = MakeNumber(kLargeNumber, 0, true);  // -456
  bool expected = true;

  bool result = IsLower(neg_large, neg_small);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, NegativeSmallerMagnitudeIsGreater) {
  BigFloat neg_small = MakeNumber(kSmallNumber, 0, true);  // -123
  BigFloat neg_large = MakeNumber(kLargeNumber, 0, true);  // -456
  bool expected = true;

  bool result = IsGreater(neg_small, neg_large);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, NegativeIsLowerThanZero) {
  BigFloat neg_num = MakeNumber(kSmallNumber, 0, true);
  BigFloat zero = MakeZero(GetPositive());
  bool expected = true;

  bool result = IsLower(neg_num, zero);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, NegativeIsLowerThanPositive) {
  BigFloat neg_num = MakeNumber(kSmallNumber, 0, true);
  BigFloat pos_num = MakeNumber(kSmallNumber, 0, false);
  bool expected = true;

  bool result = IsLower(neg_num, pos_num);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, EqualNegativeNumbers) {
  BigFloat neg1 = MakeNumber(kSmallNumber, 0, true);
  BigFloat neg2 = MakeNumber(kSmallNumber, 0, true);
  bool expected = true;

  bool result = IsEqual(neg1, neg2);

  EXPECT_EQ(result, expected);
}

TEST_F(ComparisonTest, NegativeLargerExponentIsLower) {
  BigFloat neg_small_exp = MakeNumber(kSmallNumber, kSmallExponent, true);
  BigFloat neg_large_exp = MakeNumber(kSmallNumber, kLargeExponent, true);
  bool expected = true;

  bool result = IsLower(neg_large_exp, neg_small_exp);

  EXPECT_EQ(result, expected);
}
