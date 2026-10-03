#include <iostream>
#include <stdexcept>
#include <algorithm>

class Matrix {
private:
    int rows;
    int cols;
    double* data; 

public:
    Matrix(int r, int c, double initial_val = 0.0) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw std::invalid_argument("Las dimensiones deben ser mayores a cero.");
        }
        data = new double[rows * cols];
        std::fill(data, data + (rows * cols), initial_val);
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double[rows * cols];
        std::copy(other.data, other.data + (rows * cols), data);
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            double* new_data = new double[other.rows * other.cols];
            std::copy(other.data, other.data + (other.rows * other.cols), new_data);
            
            delete[] data; 
            
            data = new_data;
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    }

    ~Matrix() {
        delete[] data;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }


    double& operator()(int r, int c) {
        return data[r * cols + c];
    }

    const double& operator()(int r, int c) const {
        return data[r * cols + c];
    }


    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Dimensiones incompatibles para la suma.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Dimensiones incompatibles para la resta.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Dimensiones incompatibles para multiplicación matricial.");
        }
        Matrix result(rows, other.cols, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int k = 0; k < cols; ++k) {
                double temp = (*this)(i, k);
                for (int j = 0; j < other.cols; ++j) {
                    result(i, j) += temp * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    friend Matrix operator*(double scalar, const Matrix& mat) {
        return mat * scalar;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                os << mat(i, j) << "\t";
            }
            os << "\n";
        }
        return os;
    }
};

int main() {
    Matrix A(2, 3, 2.0); 
    Matrix B(3, 2, 3.0); 

    A(0, 0) = 5.0;
    A(1, 2) = 1.5;

    std::cout << "Matriz A (2x3):\n" << A << "\n";
    std::cout << "Matriz B (3x2):\n" << B << "\n";

    Matrix C = A * B; 
    std::cout << "Producto A * B (2x2):\n" << C << "\n";

    Matrix D = A * 2.5; 
    std::cout << "Escalar A * 2.5:\n" << D << "\n";

    Matrix E = A;      
    E = D;              

    return 0;
}
