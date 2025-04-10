#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>

// all of your function definitions should be in this file now

template <typename T>
class Matrix
{
public:
    Matrix(std::size_t N) : Matrix(N, N) {}

    Matrix(std::size_t width, std::size_t height)
    {
        // initialize the member variables
        _height = height;
        _width = width;
        _buffer = std::vector<T>(_width * _height);

        // zero-initialize the buffer
        for (size_t i = 0; i < _width * _height; i++)
            _buffer[i] = 0;
    }

    Matrix(std::vector<std::vector<T>> nums)
    {
        // get the heights of the member variables
        _height = nums.size();
        _width = _height > 0 ? nums[0].size() : 0; // default to a height of zero for sanity sake

        // initialize the buffer
        _buffer = std::vector<T>(_width * _height);

        // fill in the buffer
        for (size_t row = 0; row < _height; row++)
        {
            for (size_t col = 0; col < _width; col++)
            {
                // fill in the value using the bounds-checked array accessor (in case of user error)
                _buffer[idx(col, row)] = nums.at(row).at(col);
            }
        }
    }

    ~Matrix() {}

    Matrix<T> operator+(const Matrix<T> &rhs) const
    {
        // verify prerequisite for matrix addition
        if (this->_width != rhs._width || this->_height != rhs._height)
        {
            throw std::range_error("cannot add matrices of different sizes");
        }
        // initialize the result of the addition
        Matrix result(_width, _height);
        // add each position
        for (size_t i = 0; i < _buffer.size(); i++)
        {
            result._buffer[i] = _buffer[i] + rhs._buffer[i];
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T> &rhs) const
    {
        // verify prerequisite for matrix multiplication
        if (this->_width != rhs._height)
        {
            throw std::range_error("cannot multiply matrix due to sizes");
        }
        // initialize the result of the addition
        Matrix result(this->_height, rhs._width);
        // add each position
        for (size_t row = 0; row < result._height; row++)
        {
            for (size_t col = 0; col < result._width; col++)
            {
                for (size_t i = 0; i < _width; i++)
                {
                    result._buffer[result.idx(col, row)] += get_value(row, i) * rhs.get_value(i, col);
                }
            }
        }
        return result;
    }

    void set_value(std::size_t row, std::size_t col, T n)
    {
        _buffer.at(idx(col, row)) = n;
    }

    T get_value(std::size_t row, std::size_t col) const
    {
        return _buffer.at(idx(col, row));
    }

    T sum_diagonal_major() const
    {
        T sum = {};
        for (size_t i = 0; i < std::min(_width, _height); i++)
        {
            sum += get_value(i, i);
        }
        return sum;
    }

    T sum_diagonal_minor() const
    {
        // check the precondition
        if (_width != _height)
        {
            throw std::range_error("cannot calculate minor diagonal of non-square matrix");
        }
        // do the calculation
        T sum = {};
        for (size_t i = 0; i < _width; i++)
        {
            sum += get_value(_width - 1 - i, i);
        }
        return sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2)
    {
        if (std::max(r1, r2) >= _height)
        {
            throw std::out_of_range("swapped row is out of range");
        }
        for (size_t col = 0; col < _width; col++)
        {
            std::swap(_buffer[idx(col, r1)], _buffer[idx(col, r2)]);
        }
    }

    void swap_cols(std::size_t c1, std::size_t c2)
    {
        if (std::max(c1, c2) >= _width)
        {
            throw std::out_of_range("swapped column is out of range");
        }
        for (size_t row = 0; row < _height; row++)
        {
            std::swap(_buffer[idx(c1, row)], _buffer[idx(c2, row)]);
        }
    }

    void print_matrix() const
    {
        for (size_t y = 0; y < _height; y++)
        {
            for (size_t x = 0; x < _width; x++)
            {
                std::cout << _buffer[idx(x, y)] << "\t";
            }
            std::cout << std::endl;
        }
    }

    size_t width() const { return _width; }
    size_t height() const { return _height; }

private:
    size_t _width, _height;
    /*
    the backing buffer for the matrix, an array of size _width * _height

    this buffer is laid out as follows (by index):
    ```
    0 1 2
    3 4 5
    ```
    */
    std::vector<T> _buffer;

    inline size_t idx(size_t col, size_t row) const { return col + row * _width; }
};

#endif // __MATRIX_HPP__
