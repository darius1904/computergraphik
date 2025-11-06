#include "MatrixInt.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>


MatrixInt::MatrixInt() : m_raw_data(nullptr), m_row_cnt(0), m_column_cnt(0) {
}

///////
// TODO
// Implement the constructor
// Make sure to check the hpp file for the desired behaviour.
MatrixInt::MatrixInt(unsigned int row_cnt, unsigned int column_cnt)
    : m_raw_data(nullptr), m_row_cnt(row_cnt), m_column_cnt(column_cnt)
{
    if (row_cnt == 0 || column_cnt == 0) {
        m_raw_data = nullptr;
    } else {
        m_raw_data = new int[row_cnt * column_cnt](); // initialize to 0
    }
}

MatrixInt::~MatrixInt() {
    ///////
    // TODO
    // Implement the destructor
    delete[] m_raw_data;
    m_raw_data = nullptr;

}

MatrixInt::MatrixInt(MatrixInt const& other)
    : m_raw_data(nullptr), m_row_cnt(other.m_row_cnt), m_column_cnt(other.m_column_cnt)
{
    if (other.m_raw_data != nullptr) {
        m_raw_data = new int[m_row_cnt*m_column_cnt];
        std::memcpy(m_raw_data, other.m_raw_data, m_row_cnt*m_column_cnt * sizeof(int));
    }
}

MatrixInt::MatrixInt(MatrixInt&& other) : MatrixInt() {
    std::swap(m_raw_data, other.m_raw_data);
    std::swap(m_row_cnt, other.m_row_cnt);
    std::swap(m_column_cnt, other.m_column_cnt);
}

MatrixInt& MatrixInt::operator=(MatrixInt const& rhs) {
    if (this != &rhs) {
        MatrixInt tmp(rhs);
        std::swap(m_raw_data, tmp.m_raw_data);
        std::swap(m_row_cnt, tmp.m_row_cnt);
        std::swap(m_column_cnt, tmp.m_column_cnt);
    }

    return *this;
}

MatrixInt& MatrixInt::operator=(MatrixInt&& rhs) {
    if (this != &rhs) {
        std::swap(m_raw_data, rhs.m_raw_data);
        std::swap(m_row_cnt, rhs.m_row_cnt);
        std::swap(m_column_cnt, rhs.m_column_cnt);
    }

    return *this;
}

MatrixInt MatrixInt::operator*(MatrixInt const& rhs)
{
    // matrix A size
    unsigned int rows1 = this->getRowCount();
    unsigned int columns1 = this->getColumnCount();

    // matrix B size
    unsigned int rows2 = rhs.getRowCount();
    unsigned int columns2 = rhs.getColumnCount();

    if (columns1 != rows2) {
        std::cerr << "Matrix multiplication size mismatch." << std::endl;
        return MatrixInt();
    }

    MatrixInt resultMatrix(rows1, columns2);

    ///////
    // TODO
    // Implement matrix multiplication (A * B).
    // Hint: Values of matrix A are accessed using the "this" pointer,
    // values of matrix B are accessed from function input parameter "rhs".
    // Hint: The matrizes are stored in row-major order. Be careful to use
    // the correct offsets when accessing values of row- and column-vectors
    // of A and B respectively.
    
    for (unsigned int i = 0; i < rows1; ++i)
        {
            for (unsigned int j = 0; j < columns2; ++j)
            {
                int sum = 0;
                for (unsigned int k = 0; k < columns1; ++k)
                {
                    sum += this->m_raw_data[i * columns1 + k] * rhs.m_raw_data[k * columns2 + j];
                }
                resultMatrix.m_raw_data[i * columns2 + j] = sum;
            }
        }

    return resultMatrix;
}
