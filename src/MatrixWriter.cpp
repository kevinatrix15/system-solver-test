/**
 * @file MatrixWriter.cpp
 * @brief Implementation of the MatrixWriter class.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-03
 */

#include <cassert>
#include <fstream>
#include <string>

#include "MatrixWriter.h"

namespace CODETEST
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTORS **************************************************
******************************************************************************/

MatrixWriter::MatrixWriter(const std::string& filename)
  : m_filename(filename)
{
  assert(!m_filename.empty());

  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void MatrixWriter::write(const size_t numRows,
    const size_t numCols,
    const std::vector<double>& vals)
{
  std::fstream outFile(m_filename, std::fstream::out | std::fstream::trunc);
  if (!outFile.is_open()) {
    throw std::runtime_error("Failed to open file: " + m_filename);
  }

  // write out the header of matrix dimensions
  outFile << numRows << " " << numCols << std::endl;

  for (size_t row=0; row < numRows; ++row) {
    for (size_t col=0; col < numCols; ++col) {
      const size_t idx = col + row*numCols;
      outFile << vals[idx] << " ";
    }
    outFile << std::endl;
  }
}
} // namespace CODETEST

