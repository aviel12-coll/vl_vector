//
// Created by aviel12 on 5/5/24.
//

#ifndef VL_VECTOR_VL_STRING_HPP
#define VL_VECTOR_VL_STRING_HPP

#endif //VL_VECTOR_VL_STRING_HPP
//#include "vl_vector.hpp"
#include <iostream>
#include <cstring>
template< size_t StaticCapacity= 16UL>
class vl_string: public vl_vector<char, StaticCapacity>
{

public:
    char * data () const
    {
        if(this->_size > StaticCapacity)
        {
            return this->heap_data;
        }

        char * ptr = (char *)(this->st_data); // cast
        return ptr;
    }
            vl_string()
            {
                this->_size= 0;
                this->_capacity=StaticCapacity;
                for (int i =0; i<StaticCapacity; i++)
                {
                    this->data()[i]=0;
                }


    }
    //copy_constructor

    // Copy constructor
    vl_string(const vl_string& other) : vl_vector<char, StaticCapacity>(other) {
        // If using heap memory, allocate new memory
        if (other._size > StaticCapacity)
        {
            this->heap_data = new char[other._capacity];
            std::strncpy(this->data(), other.data()  , other._size);
        }
    }


            //implicit constuctor
     vl_string(const char * str){

        size_t length_str= strlen(str);
        if (length_str>StaticCapacity)
        {
            size_t new_capacity= this->cap(length_str);
            this->heap_data= new char[new_capacity];
            this->_capacity= new_capacity;

        }
        this->_size= length_str;
        std::strncpy(data(), str,length_str);

            }



    // Append a  string to the vl_string
    void append(const char* str) {
        size_t input_len = strlen(str);
        size_t new_capacity= this->cap(input_len);
        if (input_len+ this->size()> this->_capacity)
        {
            char * nec_heap_string= new  char[new_capacity];
            //first_part
            std::strncpy(nec_heap_string, data(), this->size());
            //second part
          std::strncpy(nec_heap_string+ this->size(), str , input_len);
            delete[] this->heap_data;
            this->heap_data= nec_heap_string;

        }
        else
        {
            std::memcpy(this->data()+ this->size(), str , input_len);
        }
        this->_size+= input_len;
        this->_capacity= new_capacity;
    }



    // Overload the += operator to append a C-style string
    vl_string& operator+=(const char* str) {
        this->append(str);
        return *this;
    }
    // Overload the += operator to append a single character to vl_string
    vl_string& operator+=(const char ch) {
        this->push_back(ch);// Append the character at the end of the vl_string

        return *this;
    }


    // Overload the + operator to concatenate a vl_string and a C-style string
    friend vl_string operator+(const vl_string& lhs, const char* rhs) {
        vl_string result = lhs;
        result.append(rhs);
        return result;
    }

    // Overload the + operator to concatenate a C-style string and a vl_string
    friend vl_string operator+(const char* lhs, const vl_string& rhs) {
        vl_string result(lhs);
        result.append(rhs.data());
        return result;
    }

    // Overload the += operator to append another vl_string
    vl_string& operator+=(const vl_string& other) {
        this->insert(this->end(), other.begin(), other.end());
        return *this;
    }
    ~vl_string()= default;

     operator std::string ()const
     {
         char  new_str[this->size()];
         std::strncpy(new_str, data(), this->size());
         //new_str[this->size()]= '\0';
         return std::string (new_str);
     }
    // Conversion operator to std::string
   // operator std::string() const {
       //  Allocate a temporary buffer to store the string
     //   char* temp_buffer = new char[this->_size];
       // std::memcpy(temp_buffer, this->data(), this->_size); // Copy the characters
        // Null-terminate the C-style string
        //std::string result(temp_buffer); // Construct std::string from the buffer
        //delete[] temp_buffer; // Clean up temporary buffer
        //return result;}












    };