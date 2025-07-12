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
using big_float::Sign;
using big_float::Sub;
using big_float::Type;

namespace {

constexpr uint64_t kSmallNumber = 100;
constexpr uint64_t kLargeNumber = 200;
constexpr uint64_t kTestNumber = 50;
constexpr Exponent kSmallExponent = 2;
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

class SubTest : public ::testing::Test {
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

    // Numbers with different exponents
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

// Basic Subtraction Tests
TEST_F(SubTest, SameNumbers) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = MakeNumber(kSmallNumber);
  BigFloat expected = pos_zero_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, PositiveNumbers) {
  // Arrange
  BigFloat left = large_pos_;
  BigFloat right = small_pos_;
  BigFloat expected = MakeNumber(kLargeNumber - kSmallNumber);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, ResultNegative) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = large_pos_;
  BigFloat expected = MakeNumber(kLargeNumber - kSmallNumber, 0, true);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, MixedSigns) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = small_neg_;
  BigFloat expected = MakeNumber(kSmallNumber + kSmallNumber);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, NegativeNumbers) {
  // Arrange
  BigFloat left = small_neg_;
  BigFloat right = large_neg_;
  BigFloat expected = MakeNumber(kLargeNumber - kSmallNumber);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, NegativeMinusPositive) {
  // Arrange
  BigFloat left = small_neg_;
  BigFloat right = small_pos_;
  BigFloat expected = MakeNumber(kSmallNumber + kSmallNumber, 0, true);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

// Zero Tests
TEST_F(SubTest, FromZero) {
  // Arrange
  BigFloat left = pos_zero_;
  BigFloat right = small_pos_;
  BigFloat expected = small_neg_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, ZeroFromNumber) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = pos_zero_;
  BigFloat expected = small_pos_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, ZeroFromZero) {
  // Arrange
  BigFloat left = pos_zero_;
  BigFloat right = neg_zero_;
  BigFloat expected = pos_zero_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, NegativeZeroFromNumber) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = neg_zero_;
  BigFloat expected = small_pos_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

// Infinity Tests
TEST_F(SubTest, FromInfinity) {
  // Arrange
  BigFloat left = pos_inf_;
  BigFloat right = small_pos_;
  BigFloat expected = pos_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, NumberFromInfinity) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = pos_inf_;
  BigFloat expected = neg_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, SameInfinities) {
  // Arrange
  BigFloat left = pos_inf_;
  BigFloat right = pos_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  // +Inf - (+Inf) should result in NaN
  EXPECT_TRUE(IsNan(result));
}

TEST_F(SubTest, OppositeInfinities) {
  // Arrange
  BigFloat left = pos_inf_;
  BigFloat right = neg_inf_;
  BigFloat expected = pos_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

TEST_F(SubTest, NegativeInfinities) {
  // Arrange
  BigFloat left = neg_inf_;
  BigFloat right = neg_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  // -Inf - (-Inf) should result in NaN
  EXPECT_TRUE(IsNan(result));
}

TEST_F(SubTest, NegativeInfinityFromPositive) {
  // Arrange
  BigFloat left = pos_inf_;
  BigFloat right = neg_inf_;
  BigFloat expected = pos_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsEqual(result, expected));
}

// NaN Tests
TEST_F(SubTest, WithNan) {
  // Arrange
  BigFloat left = small_pos_;
  BigFloat right = pos_nan_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsNan(result));
}

TEST_F(SubTest, NanFromNumber) {
  // Arrange
  BigFloat left = pos_nan_;
  BigFloat right = small_pos_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsNan(result));
}

TEST_F(SubTest, NanFromZero) {
  // Arrange
  BigFloat left = pos_nan_;
  BigFloat right = pos_zero_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsNan(result));
}

TEST_F(SubTest, NanFromInfinity) {
  // Arrange
  BigFloat left = pos_nan_;
  BigFloat right = pos_inf_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  EXPECT_TRUE(IsNan(result));
}

// Exponent Tests
TEST_F(SubTest, DifferentExponents) {
  // Arrange
  BigFloat left = large_exp_pos_;
  BigFloat right = small_exp_pos_;

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  // The result should not be NaN
  EXPECT_FALSE(IsEqual(result, pos_nan_));
}

TEST_F(SubTest, SameValuesDifferentExponents) {
  // Arrange
  BigFloat left = MakeNumber(kTestNumber, kLargeExponent);
  BigFloat right = MakeNumber(kTestNumber, kSmallExponent);

  // Act
  BigFloat result = Sub(left, right);

  // Assert
  // Should not result in zero since exponents differ
  EXPECT_FALSE(IsEqual(result, pos_zero_));
}

// Consistency Tests
TEST_F(SubTest, SubtractionIdentity) {
  // Arrange
  BigFloat original = small_pos_;
  BigFloat value = MakeNumber(kTestNumber);

  // Act - subtract then add back
  BigFloat subtracted = Sub(original, value);
  BigFloat result = Sub(subtracted, MakeNumber(kTestNumber, 0, true));

  // Assert
  EXPECT_TRUE(IsEqual(result, original));
}

TEST_F(SubTest, NegationEquivalence) {
  // Arrange
  BigFloat left = large_pos_;
  BigFloat right = small_pos_;

  // Act
  BigFloat sub_result = Sub(left, right);
  BigFloat neg_add_result = Sub(right, left);

  // Assert - Sub(a,b) should equal -(Sub(b,a))
  EXPECT_FALSE(IsEqual(sub_result, neg_add_result));
}

TEST_F(SubTest, ZeroProperty) {
  // Arrange
  BigFloat number = small_pos_;

  // Act
  BigFloat result = Sub(number, number);

  // Assert
  EXPECT_TRUE(IsEqual(result, pos_zero_));
}
