class Matrix {

  private:
    std::size_t nrows;
    std::size_t ncols;

  public:

    virtual void read(std::string filename) = 0;

    virtual void write(std::string filename) = 0;

    virtual double operator()(std::size_t row, std::size_t col) = 0;

    // y = A * x
    virtual void MatVec(const Vector& vecX, Vector& vecY) = 0;

    // C = A * B
    virtual void MatMat(const Matrix& matB, Matrix& matC) = 0;

    // B = A^T
    virtual void Tranpose(Matrix& matB) = 0;

};
