#pragma once

template<class T>
class queue {
 private:
  T *buffer;
  size_t size_;
  size_t capacity_;
  size_t head;
  size_t tail;

  void Reallocate();

 public:
  queue();

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  void enqueue(T &&value);
  void enqueue(const T &value);

  const T &dequeue();
};

template<class T>
queue<T>::queue() {
  this->buffer = new T;
  this->size_ = 0;
  this->capacity_ = 1;
  this->head = 0;
  this->tail = 0;
}

template<class T>
void queue<T>::Reallocate() {
  T *new_buffer = new T[capacity_ *= 2];
  for (int i = 0; i < size_; ++i, ++head) {
    new_buffer[i] = buffer[head % (capacity_ / 2)];
  }
  delete[] buffer;
  this->buffer = new_buffer;
  this->head = 0;
  this->tail = size_;
}

template<class T>
bool queue<T>::empty() const {
  return head == tail;
}

template<class T>
size_t queue<T>::size() const {
  return this->size_;
}

template<class T>
void queue<T>::enqueue(T &&value) {
  buffer[tail % capacity_] = value;
  ++tail;
  ++size_;
  if (size_ == capacity_) {
    Reallocate();
  }
}

template<class T>
void queue<T>::enqueue(const T &value) {
  buffer[tail % capacity_] = value;
  ++tail;
  ++size_;
  if (size_ == capacity_) {
    Reallocate();
  }
}

template<class T>
const T &queue<T>::dequeue() {
  assert(size_ != 0);
  --size_;
  return buffer[head++];
}
