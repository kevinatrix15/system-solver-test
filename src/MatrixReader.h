/**
 * @file MatrixReader.h
 * @brief Class for reading in CSV matrices.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, 3DSIM LLC
 * @version 1
 * @date 2017-01-03
 */

#pragma once

#include <vector>

namespace CODETEST
{
class MatrixReader
{
  public:
    /**
     * @brief Create a new matrix reader with the given filename.
     *
     * @param filename The file name of the csv matrix file to be read.
     */
  MatrixReader(const std::string& filename);

  virtual ~MatrixReader();

  /**
   * @brief Read in the entire dense representation of the matrix, row by row.
   *
   * @param valsRef All values of the matrix (including zeros).
   */
  void read(size_t& numRowsRef, size_t& numColsRef, std::vector<double>& valsRef);

  size_t getNumRows();

  private:

  std::string m_filename;
  size_t m_numRows;
};
} // namespace CODETEST
