#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		cols = _cols;
		rows = _rows;
		a.resize(rows, vector<double>(cols, 0));
	}
	
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			throw runtime_error("Error: Matrix dimensions don't match");
		}
		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows()) // matrix a col is 2, matrix c row is 2 as well so it should work idk why it isn't
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());
		
		for (int k = 0; k < b.getCols(); k++)
		{
			for (int i = 0; i < a.getRows(); i++)
			{
				c(i, k) = 0;
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, k) += a(i, j) * b(j, k); 
				}
			}
		}
		return c;
	}

	///Matrix comparison.  See description.
	///usage:  a == b , compare matrice a and matrice b
	bool operator==(const Matrix& a, const Matrix& b)// works?
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) > 0.001) 
				{
					return false;
				}
			}
		}
		return true;
	}

	///Matrix comparison.  See description.
	///usage:  a != b
	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			return true;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) > 0.001)
				{
					return true;
				}
			}
		}
		return false;
	}

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a) 
	{	
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
				//os << " ";
			}
			os << endl;
		}
		return os;//wip
	}
    
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }
    
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int col = 0; col < nCols; col++)
        {
            (*this)(0, col) = xShift;
            (*this)(1, col) = yShift;
        }
    }
}