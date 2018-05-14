#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <functional>

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
        // mData.resize(mSize);
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
        std::uniform_real_distribution<double> dist(0, 2);
        for (int i = 0; i < mSize; i++)
        {
            mData.push_back(dist(e2));
            // x = normal_dist(e2);
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
        std::transform(mData.begin(), mData.end(), m.mData.begin(), mData.begin(), std::plus<T>());
        // mData += m.getData();
    }

    void subtrack(const Matrix &m)
    {
        std::transform(mData.begin(), mData.end(), m.mData.begin(), mData.begin(), std::minus<T>());
    }

    void transpose()
    {
        // Matrix<T> temp(mColumns, mRows);
        std::vector<T> tempv;
        for (int i = 0; i < mColumns; i++)
        {
            for (int j = 0; j < mRows; j++)
            {
                // temp.insert((*this)(j, i));
                tempv.push_back((*this)(j, i));
            }
        }
        // *this = temp;
        std::swap(mColumns, mRows);
        mData.clear();
        mData = tempv;
    }

    void map(std::function<T(T &)> &f)
    {
        for (auto &data : mData)
        {
            data = f(data);
        }
    }

    Matrix addMatrix(Matrix &m)
    {
        return Matrix(4, 4, (mData));
    }

    Matrix copy()
    {
        return *this;
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

    Matrix multiply(Matrix b)
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

    std::vector<T> getData()
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
            std::cout << "\n";
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
        // return mSize;
        return mData.size();
    }

    T operator[](size_t i) const
    {
        return mData.at(i);
    }

    T &operator()(size_t i, size_t j)
    {
        // return mData[i*mRows + j];
        return mData.at(j + i * mColumns);
    }

    const T &operator()(size_t i, size_t j) const
    {
        // return mData[i*mRows + j];
        return mData.at(j + i * mColumns);
    }

    void operator=(Matrix<T> &&other)
    {
        mData = std::move(other.mData);
    }

    Matrix &operator=(const Matrix &x)
    {
        if (this == &x)
        {
            return *this;
        }
        // if (mSize != x.getSize())
        // {
        //     return *this;
        // }
        // mData.clear();
        mData.resize(x.mSize);
        mData = x.mData;
        // std::cout << mData.size() << "\n";

        // std::swap(mData, x.mData);
        return *this;
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
                      << "\n";
            return *this;
        }
        // std::vector<T> new_vec = this->mData + x.getData();
        std::transform(mData.begin(), mData.end(), x.mData.begin(), mData.begin(), std::plus<T>());

        return Matrix<T>(mRows, mColumns, mData);
    }
};