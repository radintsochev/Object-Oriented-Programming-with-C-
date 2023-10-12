#include <iostream>
using std::cout, std::cin, std::endl;

void fillMatrix (int** matrix, int rows, int cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            cout << "matrix[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
        
    }
    
}

void printMatrix (int** matrix, int rows, int cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            cout << matrix[i][j] << "   ";
        }
        cout << endl;
    }
    
}

int** transponedMatrix (int** matrix, int rows, int cols)
{
    int** matrixT = new int*[rows];
    for (size_t i = 0; i < cols; i++)
    {
        matrixT[i] = new int[cols];
    }
    for (size_t i = 0; i < cols; i++)
    {
        for (size_t j = 0; j < rows; j++)
        {
            matrixT[i][j] = matrix[j][i];
        }
        
    }
    return matrixT;
}

int main()
{
    int rows, cols;
    cout << "Rows: ";
    cin >> rows;
    cout << "Columns: ";
    cin >> cols;
    int** matrix = new int*[cols];
    for (size_t i = 0; i < cols; i++)
    {
        matrix[i] = new int[rows];
    }
    fillMatrix(matrix, rows, cols);
    printMatrix(matrix, rows, cols);
    printMatrix(transponedMatrix(matrix, rows, cols), cols, rows);
    for (size_t i = 0; i < cols; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix
    
}