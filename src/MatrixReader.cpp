/**
 * @file MatrixReader.cpp
 * @brief Implementation of the MatrixReader class.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-03
 */

#include <cassert>
#include <fstream>
#include <string>

#include "MatrixReader.h"

namespace CODETEST
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTORS **************************************************
******************************************************************************/

MatrixReader::MatrixReader(const std::string& filename)
  : m_filename(filename),
  m_numRows(0)
{
  assert(!m_filename.empty());

  // do nothing
}

MatrixReader::~MatrixReader()
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void MatrixReader::read(size_t& numRowsRef,
    size_t& numColsRef,
    std::vector<double>& valsRef)
{
  valsRef.clear();

  std::fstream inFile(m_filename, std::fstream::in);
  if (!inFile.is_open()) {
    throw std::runtime_error("Failed to open file: " + m_filename);
  }

  // read in the header for matrix dimensions
  inFile >> numRowsRef >> numColsRef;
  assert(numRowsRef > 0);
  assert(numColsRef > 0);

  // read until the end of the file is reached
  std::string entry;
  while (inFile >> entry) {
    valsRef.emplace_back(std::stod(entry));
  }

  assert(valsRef.size() == numRowsRef * numColsRef);
}

size_t MatrixReader::getNumRows()
{
  // TODO: ensure read has been called
  return m_numRows;
}
} // namespace CODETEST
