#ifndef ARRAY_HPP
#define ARRAY_HPP

template < typename Array >
struct array_iterator
{
    using reference = Array &;
    reference a;
    size_t  index;

    array_iterator ( Array & a, size_t N ) : a( a ), index(N) {}
    typename Array::reference operator * () { return a[index] ; }
    array_iterator &operator +=(size_t size) {
        index += size;
        return *this;
    }
    array_iterator &operator +(size_t size) const{
        return array_iterator(*this, index + size);
    }
    array_iterator &operator -(size_t size) const {
        return array_iterator(*this, index - size);
    }
    array_iterator &operator -=(size_t size) {
        index -= size;
        return *this;
    }
    array_iterator &operator ++() {
        index++;
        return *this;
    }
    array_iterator operator ++(int x ) {
        (void)x;
        array_iterator copy = (*this);
        ++*this;
        return copy;
    }
    bool operator !=(array_iterator &ref) {
        return this->index != ref.index;
    }
    bool operator ==(array_iterator &ref) {
        return this->index == ref.index;
    }
    bool operator <(array_iterator &ref) {
        return this->index < ref.index;
    }
    bool operator >(array_iterator &ref) {
        return this->index > ref.index;
    }
    bool operator <=(array_iterator &ref) {
        return this->index <= ref.index;
    }
    typename Array::reference operator [](size_t n) {
        return a[index + n];
    }
};

template <typename T, std::size_t N>
class Array
{
private:
    T storage[N];
public:
    using iterator = array_iterator<Array>;
    using reference = T &;

    T   &operator[](std::size_t i) {
        return storage[i];
    }
    const T   &operator[](std::size_t i) const {
        return storage[i];
    }
    std::size_t size() const { return N; }
    iterator    begin() { return iterator(*this, 0); }
    iterator    end() { return iterator(*this, N ); }
};

#endif