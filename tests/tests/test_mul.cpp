#include <cstdint>

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
using big_float::IsNan;
using big_float::MakeBigFloat;
using big_float::MakeInf;
using big_float::MakeNan;
using big_float::MakeZero;
using big_float::Mul;
using big_float::Sign;
using big_float::Type;

namespace {

constexpr uint64_t kSmallNumber = 5;
constexpr uint64_t kLargeNumber = 10;
constexpr uint64_t kProductSmallLarge = 50;
constexpr uint64_t kTestNumber = 3;
constexpr uint64_t kOne = 1;
constexpr Exponent kSmallExponent = 2;
constexpr Exponent kLargeExponent = 4;

BigFloat
MakeNumber(uint64_t value, Exponent exp = 0, bool negative = false) {
  big_uint::BigUInt mantissa;
  mantissa.limbs = {value};

  Sign sign = negative ? GetNegative() : GetPositive();
  return MakeBigFloat(mantissa, exp, sign, Type::kDefault, GetDefaultError());
}

}  // namespace

class MulTest : public ::testing::Test {
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
    one_pos_ = MakeNumber(kOne);
    one_neg_ = MakeNumber(kOne, 0, true);

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
  BigFloat one_pos_, one_neg_;
  BigFloat small_exp_pos_, large_exp_pos_;
  BigFloat small_exp_neg_, large_exp_neg_;
};

TEST_F(MulTest, BasicPositiveMultiplication) {
  BigFloat left = small_pos_;
  BigFloat right = large_pos_;
  BigFloat expected = MakeNumber(kProductSmallLarge);

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, BasicNegativeMultiplication) {
  BigFloat left = small_neg_;
  BigFloat right = large_neg_;
  BigFloat expected = MakeNumber(kProductSmallLarge);

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MixedSignsMultiplication) {
  BigFloat left = small_pos_;
  BigFloat right = large_neg_;
  BigFloat expected = MakeNumber(kProductSmallLarge, 0, true);

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationWithExponents) {
  BigFloat left = MakeNumber(kSmallNumber, kSmallExponent);
  BigFloat right = MakeNumber(kLargeNumber, kLargeExponent);
  BigFloat expected =
      MakeNumber(kProductSmallLarge, kSmallExponent + kLargeExponent);

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationByOne) {
  BigFloat left = small_pos_;
  BigFloat right = one_pos_;
  BigFloat expected = small_pos_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationByNegativeOne) {
  BigFloat left = small_pos_;
  BigFloat right = one_neg_;
  BigFloat expected = small_neg_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationByZero) {
  BigFloat left = small_pos_;
  BigFloat right = pos_zero_;
  BigFloat expected = pos_zero_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationByNegativeZero) {
  BigFloat left = small_pos_;
  BigFloat right = neg_zero_;
  BigFloat expected = neg_zero_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, NegativeMultiplicationByZero) {
  BigFloat left = small_neg_;
  BigFloat right = pos_zero_;
  BigFloat expected = neg_zero_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationWithPositiveInfinity) {
  BigFloat left = small_pos_;
  BigFloat right = pos_inf_;
  BigFloat expected = pos_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, MultiplicationWithNegativeInfinity) {
  BigFloat left = small_pos_;
  BigFloat right = neg_inf_;
  BigFloat expected = neg_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, NegativeMultiplicationWithPositiveInfinity) {
  BigFloat left = small_neg_;
  BigFloat right = pos_inf_;
  BigFloat expected = neg_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, InfinityMultiplication) {
  BigFloat left = pos_inf_;
  BigFloat right = neg_inf_;
  BigFloat expected = neg_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, SameInfinityMultiplication) {
  BigFloat left = pos_inf_;
  BigFloat right = pos_inf_;
  BigFloat expected = pos_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(MulTest, ZeroTimesInfinityIsNan) {
  BigFloat left = pos_zero_;
  BigFloat right = pos_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(MulTest, InfinityTimesZeroIsNan) {
  BigFloat left = pos_inf_;
  BigFloat right = pos_zero_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(MulTest, NegativeZeroTimesInfinityIsNan) {
  BigFloat left = neg_zero_;
  BigFloat right = pos_inf_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(MulTest, MultiplicationWithNan) {
  BigFloat left = small_pos_;
  BigFloat right = pos_nan_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(MulTest, NanMultiplication) {
  BigFloat left = pos_nan_;
  BigFloat right = neg_nan_;

  BigFloat result = Mul(left, right);

  EXPECT_TRUE(IsNan(result));
}

TEST_F(MulTest, CommutativeProperty) {
  BigFloat left = small_pos_;
  BigFloat right = large_pos_;

  BigFloat result1 = Mul(left, right);
  BigFloat result2 = Mul(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(MulTest, CommutativeWithNegative) {
  BigFloat left = small_pos_;
  BigFloat right = large_neg_;

  BigFloat result1 = Mul(left, right);
  BigFloat result2 = Mul(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(MulTest, CommutativeWithExponents) {
  BigFloat left = small_exp_pos_;
  BigFloat right = large_exp_pos_;

  BigFloat result1 = Mul(left, right);
  BigFloat result2 = Mul(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(MulTest, CommutativeWithZero) {
  BigFloat left = small_pos_;
  BigFloat right = pos_zero_;

  BigFloat result1 = Mul(left, right);
  BigFloat result2 = Mul(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}

TEST_F(MulTest, CommutativeWithInfinity) {
  BigFloat left = small_pos_;
  BigFloat right = pos_inf_;

  BigFloat result1 = Mul(left, right);
  BigFloat result2 = Mul(right, left);

  EXPECT_TRUE(IsEqual(result1, result2));
}
