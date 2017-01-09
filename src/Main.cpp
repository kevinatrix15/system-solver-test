/**
 * @file Main.cpp
 * @brief File containing the main function.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-03
 */

#include <cassert>
#include <iostream>
#include <memory>

#include "MatrixReader.h"
#include "MatrixWriter.h"

using namespace CODETEST;

/******************************************************************************
* MAIN ************************************************************************
******************************************************************************/

int main(int argc, char** argv)
{
  // unpack command line args
  const std::string fileA = argv[1];
  const std::string fileX = argv[2];
  const std::string fileY = argv[3];
  // const int mode = std::atoi(argv[4]);

  // display command line args
  std::cout << "\nCommand Line Arguments:\n";
  for (int arg = 0; arg < argc; ++arg) {
    std::cout << "  argv[" << arg << "]   " << argv[arg] << "\n";
  }

  // construct readers
  MatrixReader readerA(fileA);
  MatrixReader readerX(fileX);

  // read in A matrix
  std::vector<double> valsA;
  size_t rowsA, colsA;
  readerA.read(rowsA, colsA, valsA);

  // read in x vector
  std::vector<double> valsX;
  size_t rowsX, colsX;
  readerA.read(rowsX, colsX, valsX);
  assert(rowsX == 1);

  assert(valsA.size() % valsX.size() == 0);

  // create the matrix object

  // perform the matrix-vector multiplication

  // transpose the A matrix

  // write out y and A^T

  return 0;
}
