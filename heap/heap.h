#pragma once

#include <cstdlib>

template<class T>
class heap {
 private:
  T *buffer_;
  size_t size_;
  size_t capacity_;

  void Reallocate();
  void BuildHeap();

 public:
  heap();
  heap(T* arr, size_t n);

  void sift_up(size_t i);
  void sift_down(size_t i);

  [[nodiscard]] size_t size() const;
  [[nodiscard]] bool empty() const;
};

template<class T>
void heap<T>::Reallocate() {
  T* newBuffer = new T[capacity_ * 2];
  std::copy(buffer_, buffer_ + size_, newBuffer);
  delete[] buffer_;
  buffer_ = newBuffer;
  capacity_ *= 2;
}

template<class T>
heap<T>::heap(T *arr, size_t n) {
  this->buffer_ = arr;
  this->size_ = n;
  this->capacity_ = n;
  BuildHeap();
}

template<class T>
size_t heap<T>::size() const {
  return size_;
}

template<class T>
bool heap<T>::empty() const {
  return size_ == 0;
}

template<class T>
void heap<T>::sift_up(size_t i) {
  while (i > 0) {
    if (buffer_[(i - 1) / 2] >= buffer_[i]) {
      return;
    }
    std::swap(buffer_[(i - 1) / 2], buffer_[i]);
    i = (i - 1) / 2;
  }
}

template<class T>
void heap<T>::sift_down(size_t i) {
  size_t largest = i;
  if ((2 * i + 1) < size_ && buffer_[2 * i + 1] > buffer_[largest]) {
    largest = 2 * i + 1;
  }
  if ((2 * i + 2) < size_ && buffer_[2 * i + 2] > buffer_[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(buffer_[largest], buffer_[i]);
    sift_down(largest);
  }
}

template<class T>
void heap<T>::BuildHeap() {
  for (int i = size_ / 2 - 1; i >= 0; --i) {
    sift_down(i);
  }
}
