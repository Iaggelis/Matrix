#include <vector>
#include <iterator>
#include <iostream>
#include <random>
#include <algorithm>

template <typename T>
class Matrix
{
  public:
    Matrix(size_t rows, size_t columns)
        : mRows(rows), mColumns(columns), mSize(columns * rows)
    {
        mData.reserve(mSize);
    }
    Matrix(const Matrix &m)
        : mRows{m.rows}, mColumns{m.columns}, mSize{m.getSize()}, mData{m.getData()}
    {
    }

    void add(const T val)
    {
        mData.push_back(val);
    }

    T operator[](size_t i)
    {
        return mData.at(i);
    }

    T operator()(int i, int j)
    {
        // return mData[i*mRows + j];
        return mData.at(j + i * mColumns);
    }

    void randomize()
    {
        std::random_device r;
        std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
        std::mt19937 e2(seed2);
        std::normal_distribution<> normal_dist(0, 1);
        for (int i = 0; i < mSize; i++)
        {
            mData.push_back(normal_dist(e2));
            // x = normal_dist(e2);
        }
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
        mData += m.mData;
    }

    void multiply(const T &val)
    {
        for (auto &x : mData)
        {
            x *= val;
        }
    }

    std::vector<T> getData()
    {
        return mData;
    }

    // Matrix operator+(const T val){
    // 	this->add(val)
    // 	return this;
    // }

    void print() const
    {
        for (int i = 0; i < mRows; i++)
        {
            for (int j = 0; j < mColumns; j++)
            {
                std::cout << (*this)(i, j) << "\t";
            }
            std::cout << "\n";
        }
    }

    T row(size_t i) const
    {
        return mData.at(i);
    }

    int getSize() const
    {
        return mSize;
    }

  private:
    size_t mRows, mColumns, mSize;
    std::vector<T> mData;
};