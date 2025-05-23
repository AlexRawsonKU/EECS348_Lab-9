#include "matrix.hpp"

#include <fstream>
#include <iostream>
#include <string>

template <typename T>
Matrix<T> read_square_matrix(size_t size, std::ifstream &file)
{
    Matrix<T> matrix(size);

    for (size_t row = 0; row < size; row++)
    {
        for (size_t col = 0; col < size; col++)
        {
            T value = {};
            file >> value;
            matrix.set_value(row, col, value);
        }
    }

    return matrix;
}

template <typename T>
void process(Matrix<T> m1, Matrix<T> m2)
{

    std::cout << "Matrix A:\n";
    m1.print_matrix();
    std::cout << "Matrix B:\n";
    m2.print_matrix();
    std::cout << std::endl;

    // 2. Add two matrices and display the result:
    std::cout << "Sum of A+B:\n";
    (m1 + m2).print_matrix();
    std::cout << std::endl;

    // 3. Multiply two matrices and display the result:
    std::cout << "Product of A×B:\n";
    (m1 * m2).print_matrix();
    std::cout << std::endl;

    // 4. Get the sum of matrix diagonal elements:
    std::cout << "Matrix Diagonal Elements:\n";
    std::cout << "Matrix A:\n\tMajor: " << m1.sum_diagonal_major()
              << "\n\tMinor: " << m1.sum_diagonal_minor() << "\n";
    std::cout << "Matrix B:\n\tMajor: " << m2.sum_diagonal_major()
              << "\n\tMinor: " << m2.sum_diagonal_minor() << "\n";
    std::cout << std::endl;

    // 5. Swap matrix rows and display the result:
    size_t swap_row1;
    std::cout << "Notice: Swapped rows are permanent from this point on.\n";
    std::cout << "Pick a row to swap (0-indexed, enter out-of-bound value to skip): ";
    std::cin >> swap_row1;
    if (swap_row1 < m1.height())
    {
        size_t swap_row2 = -1;
        while (swap_row2 >= m1.height())
        {
            std::cout << "Pick a row to swap it with (no longer skippable): ";
            std::cin >> swap_row2;
        }
        m1.swap_rows(swap_row1, swap_row2);
        m2.swap_rows(swap_row1, swap_row2);

        std::cout << "\nSwapped Matrix A:\n";
        m1.print_matrix();
        std::cout << "Swapped Matrix B:\n";
        m2.print_matrix();
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Skipping row swaps!" << std::endl;
    }

    // 6. Swap matrix columns and display the result:
    size_t swap_col1;
    std::cout << "Pick a column to swap (0-indexed, enter out-of-bound value to skip): ";
    std::cin >> swap_col1;
    if (swap_col1 < m1.width())
    {
        size_t swap_col2 = -1;
        while (swap_col2 >= m1.width())
        {
            std::cout << "Pick a column to swap it with (no longer skippable): ";
            std::cin >> swap_col2;
        }
        m1.swap_cols(swap_col1, swap_col2);
        m2.swap_cols(swap_col1, swap_col2);

        std::cout << "\nSwapped Matrix A:\n";
        m1.print_matrix();
        std::cout << "Swapped Matrix B:\n";
        m2.print_matrix();
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Skipping column swaps!" << std::endl;
    }

    // 7. Update matrix rows and display the result:
    size_t new_value_row = -1;
    std::cout << "Enter the index of a row for the value to modify on Matrix A (0-based, enter out-of-bound value to skip): ";
    std::cin >> new_value_row;
    if (new_value_row <= m1.height())
    {
        size_t new_value_col = -1;
        while (new_value_col >= m1.width())
        {
            std::cout << "Pick the index of a column to swap it with (no longer skippable): ";
            std::cin >> new_value_col;
        }

        std::cout << "Enter the new value: ";
        int new_value;
        std::cin >> new_value;

        m1.set_value(new_value_row, new_value_col, new_value);

        std::cout << "\nModified Matrix A:\n";
        m1.print_matrix();
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Skipping value modifications!" << std::endl;
    }
}

int main()
{
    // read a filename
    std::string filename;
    std::cout << "Enter a filename: ";
    std::cin >> filename;

    // 1. Read values from a file into the matrix
    std::ifstream input_file(filename);
    if (!input_file.is_open())
    {
        std::cerr << "failed to open " << filename << std::endl;
        return 1;
    }
    size_t n = -1;
    input_file >> n;
    size_t format = -1; // 0 = int, 1 = double
    input_file >> format;

    if (format == 0)
    {
        Matrix<int> m1 = read_square_matrix<int>(n, input_file);
        Matrix<int> m2 = read_square_matrix<int>(n, input_file);
        process(m1, m2);
    }
    else if (format == 1)
    {
        Matrix<double> m1 = read_square_matrix<double>(n, input_file);
        Matrix<double> m2 = read_square_matrix<double>(n, input_file);
        process(m1, m2);
    }
    else
    {
        std::cerr << "unknown format number" << n << std::endl;
        return 1;
    }

    return 0;
}
