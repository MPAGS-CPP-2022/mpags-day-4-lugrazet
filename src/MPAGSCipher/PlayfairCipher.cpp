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
    key_ = key;

    //Append the alphabet
    auto iter{std::back_inserter(key_)};
    for (auto iter2{alphabet_.begin()}; iter2!=alphabet_.end(); ++iter2)
    {
        iter = *iter2;
    }
    
    // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);

    // Remove non-alpha characters
    auto iter3{std::remove_if(key_.begin(), key_.end(),
                              [](char c) { return !(std::isalpha(c)); })};
    //actually erase
    key_.erase(iter3, key_.end());

    // Change J -> I
    std::transform(key_.begin(), key_.end(), key_.begin(), [](char c) {
        if (c == 'J')
            return 'I';
        return c;
    });

    // Remove duplicated letters
    std::string enc{};

    auto iter4{std::remove_if(key_.begin(), key_.end(), [&enc](char c) {
        if (enc.find(c) == std::string::npos) {
            enc += c;
            return false;
        } else
            return true;
    })};
    //actually erase
    key_.erase(iter4, key_.end());

    // Store the coords of each letter
    for (std::string::size_type i = 0; i < key_.size(); ++i) {
        std::pair<int, int> p{i%5, i/5};
        C2PMap_[key_[i]] = p;
        P2CMap_[p] = key_[i];
    }
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