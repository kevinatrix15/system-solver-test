/**
 * @file MatrixWriter.h
 * @brief Class for writing out CSV matrices.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-03
 */

#pragma once

#include <vector>

namespace CODETEST
{
class MatrixWriter
{
  public:
  MatrixWriter(const std::string& filename);

  void write(const size_t numRows,
    const size_t numCols,
    const std::vector<double>& vals);

  private:
  std::string m_filename;
};
} // namespace CODETEST

