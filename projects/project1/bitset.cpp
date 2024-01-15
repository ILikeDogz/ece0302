#include "bitset.hpp"
#include <cstring>
#include <cmath>
#define size_of_element 8
//1 uint8_t = 8 bits, int ((N-1)/8 + 1)
//the bitset array is similar to a 2d array, with one axis being the byte position, and the other axis being the bit position
Bitset::Bitset() {
    valid_bitset = true; //size is greater than 0, therefore valid
    size_bitset = 8; //default size is 8
    intmax_t element_count = ((size_bitset - 1)/size_of_element) + 1; //bit to byte
    
    //allocate dynamic memory
    array_bitset = new uint8_t[element_count]; 

    memset(array_bitset, 0, sizeof(array_bitset[0])* element_count); //from the cstring library, fills array with 0;
}

Bitset::Bitset(intmax_t size) {
    if (size <= 0){
        valid_bitset = false; //N <=0 is invalid, if invalid don't bother with bitset
    } else {
        valid_bitset = true;
        size_bitset = size;
        intmax_t element_count = ((size_bitset - 1)/size_of_element) + 1; //bit to byte
    
        //allocate dynamic memory
        array_bitset = new uint8_t[element_count]; 

 	    memset(array_bitset, 0, sizeof(array_bitset[0])* element_count); //from the cstring library, fills array with 0;
    }
}

Bitset::Bitset(const std::string & value) {
    
    //set valid initially
    valid_bitset = true;
    size_bitset = value.length();
    intmax_t element_count = ((size_bitset - 1)/size_of_element) + 1; //bit to byte

    //allocate dynamic memory
    array_bitset = new uint8_t[element_count]; 

    memset(array_bitset, 0, sizeof(array_bitset[0]) * element_count); //from the cstring library, fills array with 0;
	int byte_position = 0; //position of the array, the array is an array of bytes (8 bits)
    for (int bit_position = 0; bit_position < size_bitset; bit_position++){
        byte_position = bit_position/size_of_element; //calculate the position relative to the bit position

		int zero_or_one = (value[bit_position] - '0'); //convert from string char to int
        if (zero_or_one != 0 && zero_or_one != 1){
            valid_bitset = false;
            continue; //skips it, leaving it at zero
        }
		array_bitset[byte_position] |= (zero_or_one << (bit_position % size_of_element));  
        // Set the bit at the correct byte and bit position using shift and bitwise or
	}
}

Bitset::~Bitset() {
    //deletes dynamically stored memory
    delete[] array_bitset; 
}

// method to get the size
intmax_t Bitset::size() const {
    return size_bitset;
}

// method to confirm is valid or invalid
bool Bitset::good() const{
    return valid_bitset;
}

//set value to 1 at index
void Bitset::set(intmax_t index){
	intmax_t element_count = ((size() - 1)/size_of_element) + 1; //converts length from bits to bytes
	if (index > size()-1 || index < 0){
		valid_bitset = false;
	}
	int bit_position = index;
	int byte_position = bit_position/size_of_element; //bit to byte
	array_bitset[byte_position] |= (1 << (bit_position % size_of_element));        
    // Set the bit at the correct byte and bit position using shift and bitwise or
}

//set value to 0 at index
void Bitset::reset(intmax_t index){
    intmax_t element_count = ((size() - 1)/size_of_element) + 1; //converts length from bits to bytes
	if (index > size()-1 || index < 0){
		valid_bitset = false;
	}
	int bit_position = index;
	int byte_position = bit_position/size_of_element; //bit to byte
	array_bitset[byte_position] &= ~(1 << (bit_position % size_of_element));
    //invert and to insert a 0 at the correct position
}

//toggle the bit
void Bitset::toggle(intmax_t index){
    intmax_t element_count = ((size() - 1)/size_of_element) + 1; //converts length from bits to bytes
	if (index > size()-1 || index < 0){
		valid_bitset = false;
	}
	int bit_position = index;
	int byte_position = bit_position/size_of_element; //bit to byte
	array_bitset[byte_position] ^= (1 << (bit_position % size_of_element));        
    // Using xor to toggle
}

//checking if 1 is present at index
bool Bitset::test(int index){
    //assume that its valid
    if (index > size()-1 || index < 0){
        valid_bitset = false;
		return false;
	}
    int bit_position = index;
    int byte_position = bit_position/size_of_element; //bit to byte
    return (array_bitset[byte_position] & (1 << (bit_position % size_of_element)) ) / pow(2, bit_position % size_of_element);
    // Using and to single out the bit position at said byte, and using comparison to confirm a number existed or is 0, 
    // ie checking position 1, with bitset set to 111, 111 & 010 = 010, number is returned as an int, so using most significant bit
}

std::string Bitset::asString() const{
    //assume this is valid
    std::string my_string;
    for (int i = 0; i < size(); i++){
        if((array_bitset[i/size_of_element] & (1 << (i % size_of_element)) ) / pow(2, i % size_of_element)){ //using same function to check if 0 or 1
            my_string += '1';
        } else{
            my_string += '0';
        }
    }
    return my_string;
}



