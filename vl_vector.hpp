//
// Created by amsel on 01/04/2024.
//
#include <algorithm>
#include <cstddef>
#include <exception>


#ifndef VL_VECTOR_VL_VECTOR_H
#define VL_VECTOR_VL_VECTOR_H

#endif //VL_VECTOR_VL_VECTOR_H
// vl_vector.hpp
using std::exception;

template<typename T, size_t capacity_static= 16UL>
class vl_vector {
protected:
    T st_data[capacity_static];// Static array to hold elements
    T * heap_data= nullptr;


    size_t _capacity= capacity_static;
    size_t _size;// Current _size of the vector

    size_t cap(int k=0) const {
        if (_size + k <= capacity_static)
        {
            return capacity_static;
        }
        if (k==0)
        {
            return _capacity;
        }
        return (3*(_size + k)) / 2;
    }

public:



    class Iterator {

    public:
        using pointer = T *;
        using reference = T &;

        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;


        Iterator(): _ptr(nullptr), vec_ref(nullptr){}
        Iterator(T* p,vl_vector * v) : _ptr(p), vec_ref(v) {}
//        //copy_constructor
        Iterator(const  Iterator &other): _ptr(other._ptr)
        ,vec_ref(other.vec_ref){}

        reference operator*() const { return *_ptr; }

        pointer operator->() { return _ptr; }

        //increment the vector
         Iterator  &operator++() {

            ++_ptr;
            return *this;
        }

        Iterator  operator++(int) {
            Iterator tmp= *this;
            ++(*this);
            return tmp ;
        }
        //decrement operator

        Iterator operator --()
        {
            --_ptr;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --_ptr;
            return tmp;
        }
        difference_type operator-(const Iterator& other) const {
            return _ptr - other._ptr;
        }
        difference_type operator+(const Iterator& other) const {
            return _ptr + other._ptr;
        }
        // Arithmetic operators
        Iterator operator+(difference_type n) const
        { return Iterator(_ptr + n, vec_ref); }
        Iterator operator-(difference_type n) const
        { return Iterator(_ptr - n,vec_ref); }

       Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                _ptr = other._ptr;
               vec_ref = other.vec_ref;
           }
            return *this;
        }



        Iterator& operator=(const Iterator& other) const
        {

             Iterator tmp(other);
             *this= tmp;

            return *this;
        }


        Iterator& operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }
        Iterator& operator-=(difference_type n) {
            _ptr-= n;
            return *this;
        }



        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            return a._ptr == b._ptr;
        };

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return a._ptr != b._ptr;
        };



        // Function to obtain the beginning Iterator
        Iterator begin() {

            return Iterator(vec_ref->data(),  vec_ref);

        }


        // Function to obtain the end Iterator
        Iterator end() {
            return Iterator(vec_ref->data()+ vec_ref->size(), vec_ref);
        }
        // Dereference with offset operator
        reference operator[](difference_type n) const {
            return *(_ptr + n);
        }
        difference_type distance(Iterator first, Iterator last) const {
            return std::distance(first._ptr, last._ptr);
        }
    private:
        pointer _ptr; // Pointer to the current element
//        const vl_vector& vec_ref;
     vl_vector * vec_ref;
    };

    // Class for const_iterator
    class ConstIterator {
    public:
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        ConstIterator() : _ptr(nullptr), _vec_ref(nullptr) {}
        ConstIterator(const T* p, const vl_vector* v) : _ptr(p), _vec_ref(v) {}
        // Copy constructor
        ConstIterator(const ConstIterator& other) : _ptr(other._ptr), _vec_ref(other._vec_ref) {}

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        ConstIterator& operator++() { // increment
            ++_ptr;
            return *this;
        }

        ConstIterator operator++(int) { //  increment
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ConstIterator& operator--() { //  decrement
            --_ptr;
            return *this;
        }

        ConstIterator operator--(int) { //  decrement
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        ConstIterator operator+(difference_type n) const {
            return ConstIterator(_ptr + n, _vec_ref);
        }

        ConstIterator operator-(difference_type n) const {
            return ConstIterator(_ptr - n, _vec_ref);
        }

        difference_type operator-(const ConstIterator& other) const {
            return _ptr - other._ptr;
        }

        bool operator==(const ConstIterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const ConstIterator& other) const {
            return *this != other;
        }

        reference operator[](difference_type n) const {
            return *(_ptr + n);
        }
        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                _ptr = other._ptr;
                _vec_ref = other._vec_ref;
            }
            return *this;
        }


    private:
        const T* _ptr;             // Pointer to the current element
        const vl_vector* _vec_ref; // Pointer to the vector container
    };
    // Typedefs as per C++ standard names
    using value_type = T;
    using reverse_iterator = std::reverse_iterator<Iterator>;
    using  const_reverse_iterator = std::reverse_iterator<ConstIterator>;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    // Constructor
    vl_vector() : _capacity(capacity_static), _size(0) {
       // heap_data = new T[_capacity];
    }

     T * data () const
    {
        if(_size > capacity_static)
        {
            return heap_data;
        }
        T* ptr = const_cast<T*>(st_data); // cast
        return ptr;
    }

    // copy_constructor
    vl_vector(const vl_vector& other) :
             _capacity(other._capacity) ,_size(other._size)
    {
        if (_size > capacity_static)
        {
            heap_data = new T[_capacity];
        }

            std::copy(other.data(), other.data() + _size, data());

    }


    //Sequence_based_constructor
    template<class ForwardIterator>
    vl_vector(const ForwardIterator& first, const ForwardIterator& last)
    {
//         calculates the number of elements between two iterators
        _size = (size_t)(std::distance(first, last));
       if (_size > capacity_static)
       {
           heap_data = new T[_capacity];
       }
           std::copy(first, last, data());

    }

    vl_vector(size_t count, const T v): _size(count)
    {
        if (count >capacity_static)
        {
            heap_data= new T[_capacity];
        }

            std::fill_n(data(), count, v);


    }
    vl_vector(std::initializer_list<T> l): _size(l.size())
    {
        if (_size > capacity_static)
        {
            heap_data= new T[_capacity];
        }
        std::copy(l.begin(), l.end(),data());

    }


    size_t capacity() const
    {
        return _capacity;
    }
    bool empty() const
    {
        return (_size == 0);
    }

    size_t size() const
    {
        return _size;
    }

    ~vl_vector()
    {
        if (_size > capacity_static) {
            delete[] heap_data;
        }
    }
    T& at(size_t index) const
    {
        if (index >= _size)
        {
            throw exception();
        }
        return data()[index];
    }
// add a value to the end of the vector.
    void push_back(T element )
    {

        if (_size == _capacity)
        {
            T * new_heap_data= new T[cap(1)];
            std::copy(data(), data()+ _capacity, new_heap_data);
            {delete[] heap_data;}
            heap_data =new_heap_data;
            _capacity= cap(1);

        }
        _size++;
        data()[_size-1]=element;



    }

Iterator insert(Iterator position, const T& v)
{
    size_t index = position.distance(position.begin(), position);
    if (_size >= capacity_static)
    {
        size_t new_capacity= cap(1);
        T* new_heap = new T[new_capacity];
        //copy the first part
        std::copy(heap_data,heap_data +index, new_heap );
        new_heap[index]= v;
        //copy the second part
        std::copy(heap_data + index, heap_data + _size, new_heap + index + 1);
        delete[] heap_data;
        heap_data = new_heap;
        _capacity = new_capacity;
        _size++;

    }
    else {

        for (size_t i = _size ; i > index; --i)
        {
            st_data[i]= st_data[i-1];

        }
        st_data[index]= v;
        _size++;
    }
//    Iterator new_position = new Iterator(position);
        return Iterator(data() + index, this);

}
    template<class ForwardIterator>
Iterator insert(Iterator position ,  const ForwardIterator &first,
                const ForwardIterator& last)
{
    //The index from which I start adding
         size_t index= std::distance(position.begin(), position);
    // Calculate the number of elements to be inserted
    size_t count = std::distance(first, last);

    if (_size + count> capacity_static)
    {
        size_t new_capacity = cap(count);
        T *new_heap_data = new T[new_capacity];
        // copy_first_part
        std::copy(data(), data() + index, new_heap_data);
        // copy_second_part
        std::copy(first, last, new_heap_data + index);

        // copy_the_rest_of_the_vector
        std::copy(data() +index , data() + _size,
                  new_heap_data+ count+index);
        delete[] heap_data;
        _capacity = new_capacity;
        heap_data = new_heap_data;
        _size+= count;
    }
    else
        {
        // shift_all_the_element_after_the_position
        for(size_t i= _size - 1; i >= index; --i)
        {
            st_data[i+ count]= st_data[i];
        }
        //data()[index+count]= data()[index];
        std::copy(first, last, data()+index);
        _size+=count;

        }
    return Iterator(data() + index, this);

}
    Iterator begin()
    {
        return Iterator(data(),this);
    }

    ConstIterator cbegin() const
    {
        return ConstIterator(data(),this);
    }

     ConstIterator begin() const
    {
        return ConstIterator(data(), this);

    }


    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(cend());

    }

    Iterator end()
    {
        return Iterator(data() + _size, this);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());

    }
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(cbegin());

    }

    ConstIterator cend() const {
        // Return a const iterator pointing just past the last element
        return ConstIterator(data() + _size, this);
    }


    ConstIterator end() const
    {
        return const_iterator (data() + _size, this);
    }

    void pop_back()
    {
         if (_size == 0)
         {
             throw exception();
         }
         if(_size == capacity_static + 1)
         {
             std::copy(heap_data, heap_data+capacity_static, st_data);
             delete[] heap_data;
             heap_data= nullptr;
             _capacity= capacity_static;


         }
         else
         {
             _size--;
         }
    }
    Iterator erase(Iterator position)
    {
         size_t index = position.distance(begin(), position);

        for (size_t i = index; i < _size ; ++i)
        {
            data()[i]= data()[i+1];
        }
        if (_size == capacity_static + 1)
        {
            std::copy(heap_data, heap_data+capacity_static, st_data);
            delete[] heap_data;
            heap_data= nullptr;
            _capacity= capacity_static;

        }
        --_size;
        return Iterator(data()+ index,this);

    }

    template<class ForwardIterator>
    Iterator erase(Iterator position ,  const ForwardIterator &first,
                   const ForwardIterator& last)
    {
        //The index from which I start delete
        size_t index= position.distance(position.begin(), position);
        // Calculate the number of elements to be delete
        size_t count = std::distance(first, last);
        for(size_t i = index+ count -1; i < _size; i++)
        {
            data()[i- count+1]= data()[i];
        }
        if (_size == capacity_static + count)
        {
            std::copy(heap_data, heap_data+capacity_static, st_data);
            delete[] heap_data;
            heap_data= nullptr;
            _capacity= capacity_static;

        }
        _size-= count - 1;
        return Iterator(data() +index, *this);

    }

    //function to remove all elment in the vector
    void clear()
    {
        _size= 0;
        _capacity=capacity_static;
        // If using dynamic memory, deallocate the heap_data
        if (data()==heap_data)
        {
            delete[] heap_data;
            heap_data = nullptr;

        }


    }

bool operator==(const vl_vector& other )
{
    if (_size != other.size())
    {
        return false;

    }
    for (size_t i=0; i < _size; i++)
    {
        if (data()[i]!=other.data()[i])
        {
            return false;
        }
    }
    return true;

}

    bool operator!=(const vl_vector& other )
    {
    if (*this==other)
    {
        return false;
    }
    return true;
    }
    T& operator[](size_t index)
    {
        return this->at(index);
    }
    const T& operator[](size_t index) const {
        return this->at(index);
    }
//    void operator=(const vl_vector& other)
//            {
//        if (other.size()> capacity_static)
//        {
//            // Allocate new heap memory if necessary
//            T *new_heap_data = new T[other._capacity];
//
//            // Copy elements from other heap_data to this vector heap_data
//            std::copy(other.heap_data, other.heap_data + other._size,
//                      new_heap_data);
//
//            // Deallocate existing heap_data if this vector was previously using heap memory
//            if (_size > capacity_static) {
//                delete[] heap_data;
//            }
//            // Update heap_data pointer and capacity
//            heap_data = new_heap_data;
//            _capacity = other._capacity;
//        }
//        else
//            {
//                // Deallocate existing heap_data if this vector was previously using heap memory
//                if (_size > capacity_static)
//                {
//                    delete[] heap_data;
//                }
//                // Copy elements from other's static array to this vector's static array
//                std::copy(other.st_data, other.st_data + other._size, st_data);
//            }
//
//            // Update _size and is_static flag
//            _size = other._size;
//            is_static = (other._size <= capacity_static);
//        }


};





