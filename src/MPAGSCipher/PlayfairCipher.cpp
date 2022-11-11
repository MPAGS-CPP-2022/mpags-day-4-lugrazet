#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

PlayfairCipher::PlayfairCipher(const std::string& key) {
    setKey(key);
}



void PlayfairCipher::setKey(const std::string& key){
    //The playfair is based around the idea of exchanging pairs
    // of letters due to a 5x5 grid. The grid contains the key
    // with repeated letters removed and then any remaining space
    // is replaced with the alphabet (J never I)
    
    // store the original key
    // If temp_key is okay by the end, we will replace key_ with temp_key?
    key_ = key;
    std::string temp_key{key};

    //Append the alphabet    
    auto iter { std:: back_inserter( temp_key ) };
    for (auto iter2{alphabet_.begin()}; iter2!=alphabet_.end(); ++iter2)
    {
        iter = *iter2;
    }
    
    // Make sure the key is upper case
    std::transform(temp_key.begin(), temp_key.end(), temp_key.begin(), ::toupper);

    // Remove non-alpha characters
    auto iter3{ std::remove_if(temp_key.begin(), temp_key.end(), 
        [] (char c) 
        {
            return !(std::isalpha(c));
        }) };
    //actually erase
    temp_key.erase(iter3, temp_key.end());

    // Change J -> I
    std::transform(temp_key.begin(), temp_key.end(), temp_key.begin(), [] (char c) {if (c=='J') return 'I'; return c;} );
        
    // Remove duplicated letters
    std::string enc{};

    auto iter4{ std::remove_if(temp_key.begin(), temp_key.end(), 
        [&enc] (char c) 
        {
            if (enc.find(c) == std::string::npos)
            {
                enc += c;
                return false;
            }
            else
                return true;
        }
    )};
    //actually erase
    temp_key.erase(iter4, temp_key.end());

    // Store the coords of each letter
    for(std::string::size_type i = 0; i < temp_key.size(); ++i) {
        std::pair<int, int> p{i%5, i/5};
        C2PMap_[temp_key[i]] = p;
        P2CMap_[p] = temp_key[i];
    }
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