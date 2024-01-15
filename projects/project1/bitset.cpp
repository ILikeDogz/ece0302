#include "bitset.hpp"
#include <cstring>
//1 uint8_t = 8 bits, int ((N-1)/8 + 1)
//the bitset array is similar to a 2d array, with one axis being the byte position, and the other axis being the bit position
Bitset::Bitset() {
    valid_bitset = true; //size is greater than 0, therefore valid
    size_bitset = 8; //default size is 8
    array_bitset = new uint8_t[1]; //allocate dynamic memory, int ((8-1)/8 + 1 = 1)
    *array_bitset = 0;
}

Bitset::Bitset(intmax_t size) {
    if (size <= 0){
        valid_bitset = false; //N <=0 is invalid, if invalid don't bother with bitset
    } else {
        valid_bitset = true;
        size_bitset = size;
        intmax_t size_array = ((size_bitset - 1)/8) + 1; //bit to byte
        array_bitset = new uint8_t[size_array]; //allocate dynamic memory
 	    memset(array_bitset, 0, sizeof(uint8_t)* size_array); //from the cstring library, fills array with 0;
    }
}

Bitset::Bitset(const std::string & value) {
    //set valid initially
    valid_bitset = true;
    size_bitset = value.length();
    intmax_t size_array = ((size_bitset - 1)/8) + 1; //bit to byte
    array_bitset = new uint8_t[size_array]; //allocate dynamic memory
    memset(array_bitset, 0, sizeof(uint8_t) * size_array); //from the cstring library, fills array with 0;
	int byte_position = 0; //position of the array, the array is an array of bytes (8 bits)
    for (int bit_position = 0; bit_position < size_bitset; bit_position++){
        byte_position = bit_position/8; //calculate the position relative to the bit position
		int zero_or_one = (value[bit_position] - '0'); //convert from string char to int
		if (byte_position < -1 || ((zero_or_one != 1) && (zero_or_one != 0))){
                valid_bitset = false; //byte position should not be negative and also should be 1 or 0, invalid won't make it past this
        }
		array_bitset[byte_position] |= (zero_or_one << (bit_position % 8));  
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
	intmax_t size_array = ((size() - 1)/8) + 1; //converts length from bits to bytes
	if (index > size()-1 || index < 0){
		valid_bitset = false;
	}
	int bit_position = index;
    uint8_t array_bitset[size_array];
    memset(array_bitset, 0, sizeof(uint8_t)* size_array); //from the cstring library, fills array with 0;
	int byte_position = bit_position/8; //bit to byte
	array_bitset[byte_position] |= (1 << (bit_position % 8));        
    // Set the bit at the correct byte and bit position using shift and bitwise or
}


