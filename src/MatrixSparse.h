class MatrixSparse : public Matrix {

  private:
    std::size_t nrows;
    std::size_t ncols;
    std::size_t nnz;
    std::vector<size_t> row_ptr;
    std::vector<size_t> col_idx;
    std::vector<double> data;

  public:

    // constructor ... define vector sizes
    MatrixSparse() : nrows(0), ncols(0), nnz(0), row_ptr(), col_idx(), data() {}

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

      row_ptr.resize(nrows);
      col_idx.clear();
      data.clear();

      // read until the end of the file is reached
      std::string entry;
      nnz = 0; std:size_t i = 0;
      std::size_t row = 0;
      std::size_t col = 0;
      bool row_start_set = false;
      while (inFile >> entry) {
        i++;
        double val = std::stod(entry);
        if (val != 0) {
          if (!row_start_set) {
            row_ptr.push_back(nnz);
            row_start_set = true;
          }
          col_idx.push_back(col);
          data.push_back(val);
          nnz++;
        }
        col++;
        if (col == ncols) {
          col = 0;
          row++;
          row_start_set = false;
        }
      }
      row_ptr.push_back(nnz);
    
      col_idx.resize(nnz);
      data.resize(nnz);

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
        for (std::size_t n = row_ptr[row]; n < row_ptr[row+1]; ++n)
        {
          vecY[row] += data[n] * vecX[col_idx[n]];
        }
      }

    }

    void MatMat(const Matrix& matB, Matrix& matC)
    {
      assert(getNumCols() == matB.getNumRows());

      // make sure C is allocated to correct size

      // C(i,k) = A(i,j)*B(j,k)
      std::size_t Cnnz = 0;
      vector<std::size_t> :: Crow_ptr;
      vector<std::size_t> :: Ccol_idx;
      vector<double> :: Cdata;

      for (std::size_t row = 0; row < getNumRows(); ++row)
      {
        bool row_start_set = false;
        for (std::size_t col = 0; col < matB.getNumCols(); ++col)
        {
          double sum = 0.;
          for (std::size_t n = row_ptr[row]; n < row_ptr[row+1]; ++n)
          {
             sum += data[n] * matB(col_idx[n],col) // assume matB()
          }
          if (sum != 0) {
            if (!row_start_set) {
              Crow_ptr.push_back(Cnnz);
              row_start_set = true;
            }
            Ccol_idx.push_back(col);
            Cdata.push_back(sum);
            Cnnz++;
          }
        }
      }
      
    }

};

