class MatrixDense : public Matrix {
  
  private:
    std::vector<double> data;

  public:

    void read(std::string filename) override
    {
      std::fstream inFile(filename, std::fstream::in);
      if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + m_filename);
      }

      // read in the header for matrix dimensions
      inFile >> nrows >> ncols;
      assert(nrows > 0);
      assert(ncols > 0);

      data.resize(nrows * ncols);

      // read until the end of the file is reached
      std::string entry;
      int i = 0;
      while (inFile >> entry) {
        data[i++] = std::stod(entry);
      }

      assert(i == nrows * ncols);
       
    }

    void write(std::string filename) override
    {

      std::fstream outFile(m_filename, std::fstream::out | std::fstream::trunc);
      if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + m_filename);
      }

      // write out the header of matrix dimensions
      outFile << nrows << " " << ncols << std::endl;

      for (size_t row=0; row < nrows; ++row) {
        for (size_t col=0; col < ncols; ++col) {
          const size_t idx = col + row*ncols;
          outFile << data[idx] << " ";
        }
        outFile << std::endl;
      }
    }

    void MatVec(const Vector& vecX, Vector& vecY)
    {
      assert(getNumCols() == vecX.getNumRows());

      vecY.clear();
      vecY.resize(getNumRows());

      for (std::size_t row = 0; row < getNumRows(); ++row)
      {
        for (std::size_t col = 0; col < getNumCols(); ++col)
        {
          vecY[row] += data(row,col) * vecX[row]; 
        }
      }

    }

};
