#include <cstdint>

#include <gtest/gtest.h>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

using big_float::Add;
using big_float::BigFloat;
using big_float::Exponent;
using big_float::GetDefaultError;
using big_float::GetNegative;
using big_float::GetPositive;
using big_float::IsEqual;
using big_float::IsNan;
using big_float::MakeBigFloat;
using big_float::MakeInf;
using big_float::MakeNan;
using big_float::MakeZero;
using big_float::Sign;
using big_float::Type;

namespace {

constexpr uint64_t kSmallNumber = 100;
constexpr uint64_t kLargeNumber = 200;
constexpr uint64_t kSumSmallLargeNumber = 300;
constexpr uint64_t kTestNumber = 50;
constexpr Exponent kSmallExponent = 2;
constexpr Exponent kLargeExponent = 5;

BigFloat
MakeNumber(uint64_t value, Exponent exp = 0, bool negative = false) {
  big_uint::BigUInt mantissa;
  mantissa.limbs = {value};

  Sign sign = negative ? GetNegative() : GetPositive();
  return MakeBigFloat(mantissa, exp, sign, Type::kDefault, GetDefaultError());
}

}  // namespace

class AddTest : public ::testing::Test {
 protected:
  void SetUp() override {
    pos_zero_ = MakeZero(GetPositive());
    neg_zero_ = MakeZero(GetNegative());
    pos_inf_ = MakeInf(GetPositive());
    neg_inf_ = MakeInf(GetNegative());
    pos_nan_ = MakeNan(GetPositive());
    neg_nan_ = MakeNan(GetNegative());

    small_pos_ = MakeNumber(kSmallNumber);
    large_pos_ = MakeNumber(kLargeNumber);
    small_neg_ = MakeNumber(kSmallNumber, 0, true);
    large_neg_ = MakeNumber(kLargeNumber, 0, true);

    small_exp_pos_ = MakeNumber(kTestNumber, kSmallExponent);
    large_exp_pos_ = MakeNumber(kTestNumber, kLargeExponent);
    small_exp_neg_ = MakeNumber(kTestNumber, kSmallExponent, true);
    large_exp_neg_ = MakeNumber(kTestNumber, kLargeExponent, true);
  }

  BigFloat pos_zero_, neg_zero_;
  BigFloat pos_inf_, neg_inf_;
  BigFloat pos_nan_, neg_nan_;
  BigFloat small_pos_, large_pos_;
  BigFloat small_neg_, large_neg_;
  BigFloat small_exp_pos_, large_exp_pos_;
  BigFloat small_exp_neg_, large_exp_neg_;
};

TEST_F(AddTest, SameExponentPositive) {
  BigFloat left = MakeNumber(kSmallNumber);
  BigFloat right = MakeNumber(kTestNumber);
  BigFloat expected = MakeNumber(kSmallNumber + kTestNumber);

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, SameExponentNegative) {
  BigFloat left = MakeNumber(kSmallNumber, 0, true);
  BigFloat right = MakeNumber(kLargeNumber, 0, true);
  BigFloat expected = MakeNumber(kSumSmallLargeNumber, 0, true);

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, DifferentExponents) {
  BigFloat left = small_exp_pos_;
  BigFloat right = large_exp_pos_;

  BigFloat result = Add(left, right);

  EXPECT_FALSE(IsEqual(result, pos_nan_));
}

TEST_F(AddTest, MixedSigns) {
  BigFloat left = small_pos_;
  BigFloat right = small_neg_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, pos_zero_));
}

TEST_F(AddTest, LargerPlusSmaller) {
  BigFloat left = large_pos_;
  BigFloat right = small_pos_;
  BigFloat expected = MakeNumber(kLargeNumber + kSmallNumber);

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, WithZero) {
  BigFloat left = small_pos_;
  BigFloat right = pos_zero_;
  BigFloat expected = small_pos_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, ZeroWithNumber) {
  BigFloat left = pos_zero_;
  BigFloat right = small_pos_;
  BigFloat expected = small_pos_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, BothZeros) {
  BigFloat left = pos_zero_;
  BigFloat right = neg_zero_;
  BigFloat expected = pos_zero_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, NegativeZeroWithNumber) {
  BigFloat left = neg_zero_;
  BigFloat right = small_pos_;
  BigFloat expected = small_pos_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, WithPositiveInfinity) {
  BigFloat left = small_pos_;
  BigFloat right = pos_inf_;
  BigFloat expected = pos_inf_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, WithNegativeInfinity) {
  BigFloat left = small_pos_;
  BigFloat right = neg_inf_;
  BigFloat expected = neg_inf_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, SameInfinities) {
  BigFloat left = pos_inf_;
  BigFloat right = pos_inf_;
  BigFloat expected = pos_inf_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, OppositeInfinities) {
  BigFloat left = pos_inf_;
  BigFloat right = neg_inf_;

  BigFloat result = Add(left, right);

  // +Inf + (-Inf) should result in NaN
  EXPECT_TRUE(IsNan(result));
}

TEST_F(AddTest, NegativeInfinities) {
  BigFloat left = neg_inf_;
  BigFloat right = neg_inf_;
  BigFloat expected = neg_inf_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(AddTest, WithNan) {
  BigFloat left = small_pos_;
  BigFloat right = pos_nan_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(AddTest, NanWithNumber) {
  BigFloat left = pos_nan_;
  BigFloat right = small_pos_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(AddTest, NanWithZero) {
  BigFloat left = pos_nan_;
  BigFloat right = pos_zero_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(AddTest, NanWithInfinity) {
  BigFloat left = pos_nan_;
  BigFloat right = pos_inf_;

  BigFloat result = Add(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(AddTest, Commutative) {
  BigFloat left = small_pos_;
  BigFloat right = MakeNumber(kTestNumber);

  BigFloat result1 = Add(left, right);
  BigFloat result2 = Add(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(AddTest, CommutativeWithNegative) {
  BigFloat left = small_pos_;
  BigFloat right = small_neg_;

  BigFloat result1 = Add(left, right);
  BigFloat result2 = Add(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(AddTest, CommutativeWithZero) {
  BigFloat left = small_pos_;
  BigFloat right = pos_zero_;

  BigFloat result1 = Add(left, right);
  BigFloat result2 = Add(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}
