#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <functional>
#include <limits>

template <typename T>
class Matrix
{
private:
public:
    size_t mRows, mColumns, mSize;
    std::vector<T> mData;
    Matrix()
        : mRows(0), mColumns(0), mSize(0)
    {
    }

    Matrix(const size_t &rows, const size_t &columns)
        : mRows(rows), mColumns(columns), mSize(columns * rows)
    {
        mData.reserve(mSize);
    }

    Matrix(const size_t &rows, const size_t &columns, const std::vector<T> &Data)
        : mRows(rows), mColumns(columns), mSize(columns * rows), mData(Data)
    {
    }

    Matrix(const Matrix &m)
    {
        // *this = m;
        mRows = m.rows();
        mColumns = m.columns();
        mSize = mRows * mColumns;
        mData = m.mData;
    }

    Matrix(Matrix &&m) noexcept
        : mRows(m.rows()),
          mColumns(m.columns())
    {
        mSize = mRows * mColumns;
        mData = m.getData();
    }

    ~Matrix() noexcept
    {
        mRows = 0;
        mColumns = 0;
        mSize = 0;
        mData.clear();
        mData.shrink_to_fit();
    }

    void randomize()
    {
        std::random_device r;
        std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
        std::mt19937_64 e2(seed2);
        if (std::is_same<T, int>::value)
        {
            std::uniform_int_distribution<> dist(0, 1);
            for (int i = 0; i < mSize; i++)
            {
                mData.push_back(dist(e2));
            }
        }
        else
        {
            std::uniform_real_distribution<double> dist(0, 1);
            for (int i = 0; i < mSize; i++)
            {
                mData.push_back(dist(e2));
            }
        }
    }

    void zeros()
    {
        for (int i = 0; i < mSize; i++)
        {
            mData.push_back(0);
        }
    }

    void insert(const T &val)
    {
        mData.push_back(val);
    }

    void resize(const size_t &s)
    {
        mData.resize(s);
    }

    void add(const T &val)
    {
        for (auto &x : mData)
        {
            x += val;
        }
    }

    void add(const Matrix &m)
    {
        transform(mData.begin(), mData.end(), m.mData.begin(), mData.begin(), std::plus<T>());
    }

    void subtrack(const Matrix &m)
    {
        transform(mData.begin(), mData.end(), m.mData.begin(), mData.begin(), std::minus<T>());
    }

    Matrix<T> subtrack(Matrix &a, Matrix &b)
    {
        Matrix<T> result(a.mRows, a.mColumns);
        result.resize(a.mRows * a.mColumns);
        transform(a.mData.begin(), a.mData.end(), b.mData.begin(), result.mData.begin(), std::minus<T>());
        return result;
    }
    T trace()
    {
        T tr = 0;
        if (mColumns == mRows)
        {
            for (int i = 0; i < mColumns; i++)
            {
                tr += ((*this)(i, i));
            }
            return tr;
        }
        else
        {
            return std::numeric_limits<T>::quiet_NaN();
        }
    }
    void transpose()
    {
        std::vector<T> tempv;
        for (int i = 0; i < mColumns; i++)
        {
            for (int j = 0; j < mRows; j++)
            {
                tempv.push_back((*this)(j, i));
            }
        }
        std::swap(mColumns, mRows);
        mData.clear();
        mData = tempv;
    }

    Matrix transpose(const Matrix &m)
    {
        Matrix<T> temp(m);
        temp.transpose();
        return temp;
    }

    void map(std::function<T(T &)> &f)
    {
        for (auto &data : mData)
        {
            data = f(data);
        }
    }

    Matrix map(const Matrix &m, std::function<T(T &)> &f)
    {
        Matrix<T> result(m.rows(), m.columns());
        result.resize(m.rows() * m.columns());
        result = m;
        result.map(f);
        return result;
    }

    Matrix copy()
    {
        return *this;
    }

    void copy(const Matrix &m)
    {
        mRows = m.mRows;
        mColumns = m.mColumns;
        mSize = m.mSize;
        mData.clear();
        mData = m.mData;
    }

    void multiply(const T &val)
    {
        for (auto &x : mData)
        {
            x *= val;
        }
    }

    Matrix multiply(const Matrix &a, const Matrix &b)
    {

        Matrix<T> result(a.mRows, b.mColumns);
        result.resize(a.mRows * b.mColumns);
        for (int i = 0; i < a.rows(); i++)
        {
            for (int j = 0; j < b.columns(); j++)
            {
                for (int k = 0; k < a.columns(); k++)
                {
                    result(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &b)
    {
        Matrix<T> result(this->rows(), b.columns());
        result.resize(this->rows() * b.columns());
        for (int i = 0; i < this->rows(); i++)
        {
            for (int j = 0; j < b.columns(); j++)
            {
                for (int k = 0; k < this->columns(); k++)
                {
                    result(i, j) += (*this)(i, k) * b(k, j);
                }
            }
        }
        return result;
    }

    void fromVector(const std::vector<T> &vec)
    {
        mRows = vec.size();
        mColumns = 1;
        mSize = mRows;
        mData = vec;
    }

    std::vector<T> getData() const
    {
        return mData;
    }

    void print() const
    {
        for (int i = 0; i < mRows; i++)
        {
            for (int j = 0; j < mColumns; j++)
            {
                std::cout << std::setw(11) << (*this)(i, j) << std::setw(11);
            }
            std::cout << '\n';
        }
        std::cout << "------------------------------------------------------------------------------ \n";
    }

    size_t rows() const
    {
        return mRows;
    }

    size_t columns() const
    {
        return mColumns;
    }
    size_t getSize() const
    {
        return mData.size();
    }

    T operator[](size_t i) const
    {
        return mData.at(i);
    }

    T &operator()(size_t i, size_t j)
    {
        return mData.at(j + i * mColumns);
    }

    const T &operator()(size_t i, size_t j) const
    {
        return mData.at(j + i * mColumns);
    }

    void operator=(Matrix<T> &&other)
    {
        mData = std::move(other.mData);
    }

    Matrix operator=(const Matrix &x)
    {
        if (this == &x)
        {
            return *this;
        }

        mData.resize(x.mSize);
        mData = x.mData;

        Matrix<T> result(mRows, mColumns);
        result.mData = this->mData;
        return result;
    }

    Matrix &operator+=(Matrix &x)
    {

        std::transform(mData.begin(), mData.end(), x.mData.begin(), mData.begin(), std::plus<T>());

        return *this;
    }

    Matrix &operator+(const Matrix &x)
    {
        if (mSize != x.getSize())
        {
            std::cout << "Wrong Matrix size!"
                      << '\n';
            return *this;
        }
        std::transform(mData.begin(), mData.end(), x.mData.begin(), mData.begin(), std::plus<T>());

        return Matrix<T>(mRows, mColumns, mData);
    }

    void gaussianEllimination(Matrix &mt)
    {
        int rows = mt.rows(), cols = mt.columns();
        for (int i = 0; i < rows - 1; i++)
        {
            int pivot = i;

            for (int j = i + 1; j < rows; j++)
            {
                if (fabs(mt(j, i)) > fabs(mt(pivot, i)))
                    pivot = j;
            }
            if (mt(pivot, i) == 0)
            {
                continue; //But continuing to simplify the matrix as much as possible
            }

            if (i != pivot) // Swapping the rows if new row with higher maxVals is found
            {
                std::swap(mt(pivot, 0), mt(i, 0)); // C++ swap function
                // auto temp = mt[pivot];
                // mt(pivot, 0) = mt(i, 0);
                // mt(i, 0) = temp;
            }

            for (int j = i + 1; j < rows; j++)
            {
                double scale = mt(j, i) / mt(i, i);

                for (int k = i + 1; k < cols; k++) // k doesn't start at 0, since
                {
                    mt(j, k) -= scale * mt(i, k); // values before from 0 to i
                    // are already 0
                }
                mt(j, i) = 0.0;
            }
        }
    }
};
