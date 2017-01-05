/**
 * @file MatrixReaderTest.cpp
 * @brief Unit tests for the MatrixReader class.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-04
 */

#include "gtest/gtest.h"

#include "MatrixReader.h"
#include "MatrixWriter.h"

using namespace CODETEST;

/******************************************************************************
* CONSTANTS *******************************************************************
******************************************************************************/
namespace
{
std::string FILENAME("testMat.txt");

const size_t NUM_ROWS(4);
const size_t NUM_COLS(5);

const std::vector<double> MAT_VALS{
  0.0, 2.1, 1.0, 0.0, 9.0,
  8.7, 0.0, 0.0, 4.0, 0.0,
  3.0, 0.0, 0.0, 5.0, 7.0,
  6.2, 0.0, 3.0, 0.0, 0.0};
}

/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

TEST(MatrixReaderTest, ReadTest)
{
  // arrange
  MatrixWriter writer(FILENAME);
  writer.write(NUM_ROWS, NUM_COLS, MAT_VALS);

  MatrixReader reader(FILENAME);

  // act
  std::vector<double> readVals;
  size_t numRows, numCols;
  reader.read(numRows, numCols, readVals);

  // assert
  EXPECT_EQ(numRows, NUM_ROWS);
  EXPECT_EQ(numCols, NUM_COLS);
  for (size_t row = 0; row < NUM_ROWS; ++row) {
    for (size_t col = 0; col < NUM_COLS; ++col) {
      const size_t idx = col + (row * NUM_COLS);
      EXPECT_DOUBLE_EQ(readVals[idx], MAT_VALS[idx]);
    }
  }
}
