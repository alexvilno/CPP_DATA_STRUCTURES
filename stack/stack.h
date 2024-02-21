#pragma once

#include <cstddef>
#include <stdexcept>

class BadAccess : public std::runtime_error {
 public:
  BadAccess() : std::runtime_error("Bad access") {
  }
};

template<class T>
class stack {
 private:
  T *buffer;
  size_t size_ = 0;
  size_t capacity_ = 0;
  long top_index_ = -1;

  void ReallocateBuffer();
 public:
  stack();
  stack(size_t capacity); //NOLINT

  void push(T &&value);
  void push(const T &value);
  void pop();
  const T &top() const;
  bool empty() const;
  size_t size() const;
};

template<class T>
void stack<T>::ReallocateBuffer() {
  T *reallocated = new T[capacity_ *= 2];
  memcpy(reallocated, buffer, sizeof(T) * size_);
  delete buffer;
  this->buffer = reallocated;
}

template<class T>
stack<T>::stack() {
  this->capacity_ = 1;
  this->buffer = new T[1];
}

template<class T>
stack<T>::stack(size_t capacity) { //NOLINT
  this->capacity_ = capacity;
}

template<class T>
void stack<T>::push(T &&value) {
  if (this->size_ == this->capacity_) {
    this->ReallocateBuffer();
  }
  this->buffer[this->size_++] = std::move(value);
  ++this->top_index_;
}

template<class T>
void stack<T>::push(const T &value) {
  if (this->size_ == this->capacity_) {
    this->ReallocateBuffer();
  }
  this->buffer[this->size_++] = std::move(value);
  ++this->top_index_;
}

template<class T>
void stack<T>::pop() {
  if (this->size_) {
    --this->top_index_;
    --this->size_;
  }
}

template<class T>
const T &stack<T>::top() const {
  if (top_index_ < 0) throw BadAccess();
  return this->buffer[this->top_index_];
}

template<class T>
bool stack<T>::empty() const {
  return !this->size_;
}

template<class T>
size_t stack<T>::size() const {
  return this->size_;
}
