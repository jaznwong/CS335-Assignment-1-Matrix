//Jasmine Wong
//February 15, 2018
//matrix.h file
//This is the linear_algebra_project namespace
//which includes the of the Matrix class delcaration and implementation

#ifndef TEACH_CSCI335_MATRIX_H_
#define TEACH_CSCI335_MATRIX_H_

#include <iostream>
#include <vector>

// Make it a habit to use namespaces for your code.
namespace linear_algebra_project {

template <typename Object>
  class Matrix {
    public:
      // default constructor
      Matrix(): num_columns_{0}, num_rows_{0} {}

      // destructor
      ~Matrix() {
        for (size_t i = 0; i < num_rows_; ++i) {
          delete[] array_[i]; // deallocates reference to each row in matrix
        }
        delete[] array_; // deallocates reference to whole matrix
      }

      // copy constructor
      // called if existing object is a lvalue
      Matrix(const Matrix &rhs): num_columns_{rhs.num_columns_}, num_rows_{rhs.num_rows_} {
        array_ = new Object*[num_rows_];

        for (size_t m = 0; m < num_rows_; ++m){  //matrix created using row and
          array_[m] = new Object[num_columns_];  //column size of existing matrix
        }
        for (size_t i = 0; i < num_rows_; ++i){
          for (size_t j = 0; j < num_columns_; ++j){
            array_[i][j] = rhs.array_[i][j];  //each matrix value in rhs.array_ is placed in newly allocated array
          }
        }
      }

      // copy assignment
      // creates a copy using copy constructor and then swaps with existing object
      // @returns reference to matrix
      Matrix& operator=(const Matrix &rhs) {
        if (this != &rhs) {  //checks if matrices are not already the same
          num_rows_ = rhs.num_rows_;
          num_columns_ = rhs.num_columns_;
        }
        for (size_t i = 0; i < num_rows_; ++i) {
          for (size_t j = 0; j < num_columns_; ++j) {
            array_[i][j] = rhs.array_[i][j];
          }
        }
        return *this;
      }

      // move constructor
      // called if existed object is a rvalue
      Matrix(Matrix &&rhs): num_columns_{rhs.num_columns_}, num_rows_{rhs.num_rows_} {
        rhs.num_rows_ = 0;
        rhs.num_columns_ = 0;

        array_ = rhs.array_;

        rhs.array_ = nullptr;
      }

      // move assignment
      // swap member by member
      // @returns reference to Matrix
      Matrix& operator=(Matrix &&rhs) {
        std::swap(array_, rhs.array_);
        std::swap(num_rows_, rhs.num_rows_);
        std::swap(num_columns_, rhs.num_columns_);

        return *this;
      }

      // reads user provided number of rows, number of columns, and matrix vlues
      // and then constructs the corresponding matrix with those values
      void ReadMatrix() {
        std::cin >> num_rows_ >> num_columns_; // first two values read are number of row and columns of matrix

        array_ = new Object*[num_rows_];  // 2d array created based on user input of row and columns
        for (size_t m = 0; m < num_rows_; ++m) {
          array_[m] = new Object[num_columns_];
        }
        for (size_t i = 0; i < num_rows_; ++i) {
          for (size_t j = 0; j < num_columns_; ++j) {
            std::cin >> array_[i][j]; // remaining values read are the matrices values
          }
        }
      }

      // @row: an index to a row of the matrix.
      // @returns the row as a vector of items.
      // const version.
      std::vector<Object> operator[](int row) const {
        std::vector<Object> temp_vector;

        for (size_t i = 0; i < num_columns_; ++i) {
          temp_vector.push_back(array_[row-1][i]); // each value in row of matrix is added to the vector
        }
        return temp_vector;
      }

      // @b_matrix: matrix to be added to this
      // only adds two matrices if their siezs are the same
      // @returns the temp_matrix with each element of this is added to each corresponding element in b_matrix
      Matrix operator+(const Matrix &b_matrix) {
        if (b_matrix.num_rows_ != num_rows_ || b_matrix.num_columns_ != num_columns_) {  // will abort if size of matrices are not the same
          std::cout << "Not possible to add. Matrices are not the same size." << std::endl;
          abort();

        } else {
          Matrix temp_matrix = *this; // temp_matrix created to store added matrix
          for (size_t i = 0; i < num_rows_; ++i){
            for (size_t j = 0; j < num_columns_; ++j){
              temp_matrix.array_[i][j] += b_matrix.array_[i][j]; //every element of b_matrix is added to that of temp_matrix
            }
          }
          return temp_matrix;
        }
      }

      // @an_object: value to be added to each element of this
      // @returns the temp_matrix with the added value
      Matrix operator+(const Object &an_object) {
        Matrix temp_matrix = *this; // temp_matrix created to store added matrix
        for (size_t i = 0; i < num_rows_; ++i) {
          for (size_t j = 0; j < num_columns_; ++j) {
            temp_matrix.array_[i][j] += an_object; //an_object is added to every element of temp_matrix
          }
        }
        return temp_matrix;
      }

      // @returns number of rows.
      size_t NumRows() const {
        return num_rows_;
      }

      // @returns number of columns.
      size_t NumCols() const {
        return num_columns_;
      }

      // Overloading the << operator.
      // @returns a matrix in [] form correctly placed in its corresponding row
      //and column
      friend std::ostream &operator<<(std::ostream &out, const Matrix &a_matrix) {
        out << "[";
        for (size_t i = 0; i < a_matrix.num_rows_; ++i) {
          for (size_t j = 0; j < a_matrix.num_columns_; ++j) {
            out << a_matrix.array_[i][j];

            if (j != a_matrix.num_columns_-1) { // the following lines are to print out matrices in [] form
              out << " ";
            }
          }
          if (i == a_matrix.num_rows_-1) { // ']' is printed to signify end of matrix
            out << "]";
          } else {
            out << std::endl<< " ";
          }
        }
        out << std::endl<< " "; // once elements in each row are printed, the next row will be printed on the following line
        return out;
      }

    private:
      size_t num_columns_;
      size_t num_rows_;
      Object **array_;
  };

}  // namespace linear_algebra_project

#endif  // TEACH_CSCI335_MATRIX_H
