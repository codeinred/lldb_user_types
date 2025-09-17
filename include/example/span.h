#pragma once


#include <cstddef>
#include <stdexcept>

namespace example {
template <class T>
struct span {
  private:
    T*     data_;
    size_t count_;

  public:
    template <class Range>
    span(Range&& range_) noexcept
      : data_(range_.data())
      , count_(range_.size()) {}

    template <size_t N>
    span(T (&arr)[N]) noexcept : data_(arr)
                               , count_(N) {}

    auto begin() const noexcept -> T* { return data_; }
    auto end() const noexcept -> T* { return data_ + count_; }
    auto size() const noexcept -> size_t { return count_; }

    T& operator[](size_t i) const noexcept { return data_[i]; }

    T& at(size_t i) const noexcept {
        if (i < count_) {
            return data_[i];
        }
        throw std::out_of_range("span<T>: input out of range");
    }
};
}; // namespace example
