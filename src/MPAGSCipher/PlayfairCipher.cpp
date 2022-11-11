#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>

PlayfairCipher::PlayfairCipher(const std::string& key) {
    setKey(key);
}



void PlayfairCipher::setKey(const std::string& key){
    //The playfair is based around the idea of exchanging pairs
    // of letters due to a 5x5 grid. The grid contains the key
    // with repeated letters removed and then any remaining space
    // is replaced with the alphabet (J never I)
    
    // store the original key
    key_ = key;

    //Append the alphabet    
    
    std::string temp_key{key};
    auto iter { std:: back_inserter( temp_key ) };
    for (auto iter2{alphabet_.begin()}; iter2!=alphabet_.end(); ++iter2)
    {
        iter = *iter2;
    }
    
    // Make sure the key is upper case
    std::transform(temp_key.begin(), temp_key.end(), temp_key.begin(), ::toupper);

    // Remove non-alpha characters
    // Change J -> I
    // Remove duplicated letters
    // Store the coords of each letter
    // Store the playfair cihper key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
                                      const CipherMode cipherMode) const
{
    // Change J → I
    // If repeated chars in a digraph add an X or Q if XX
    // if the size of input is odd, add a trailing Z
    // Loop over the input in Digraphs
    // - Find the coords in the grid for each digraph
    // - Apply the rules to these coords to get 'new' coords
    // - Find the letter associated with the new coords
    // return the text
    switch(cipherMode) {
        case CipherMode::Encrypt:
            // code block
            break;
        case CipherMode::Decrypt:
            // code block
            break;
        default:
            break;
        }
    return inputText;
}