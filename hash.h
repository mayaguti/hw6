#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string k_ = k;
        unsigned long long w[5]{0, 0, 0, 0, 0};

        for (int i = 4; i >= 0; i--){
			for(int j = k_.size()-1; j >= 0; j--){
				if(j < 6){
					w[i] += pow(36, j)*letterDigitToNumber(k_[abs(j - k_.size()+1)]);
                }
			}
			for(int j = 0; j < 6; j++){
				if (k_.size() != 0){
					k_.pop_back(); 
				}
		    }
		}

		HASH_INDEX_T hashed { 0 };
		for(int i = 0; i < 5; i++){
			hashed += rValues[i] * w[i];
		}
		return hashed;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter <= 'Z' && letter >= 'A'){
            letter = std::tolower(letter);
        }
        if(letter <= '9' && letter >= '0'){
            return letter - '0' + 26;
        }
        else if(letter <= 'z' && letter >= 'a'){
            return letter - 'a';
        }
        else return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif