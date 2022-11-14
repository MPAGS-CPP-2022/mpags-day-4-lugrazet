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
    std::string outputText{inputText};

    // Change J → I
    std::transform(outputText.begin(), outputText.end(), outputText.begin(),
                   [](char c) {
                       if (c == 'J')
                           return 'I';
                       return c;
                   });

    // If repeated chars in a digraph add an X or add Q if the digraph is XX
    for (size_t i{0}; i < outputText.size() - 1; i += 2) {
        if (outputText[i] == outputText[i + 1]) {
            if (outputText[i] == 'X') {
                std::string Q_str{"Q"};
                outputText.insert(i + 1, Q_str);
            } else {
                std::string X_str{"X"};
                outputText.insert(i + 1, X_str);
            }
        }
    }

    // if the size of input is odd, add a trailing Z
    if ((outputText.size() % 2) == 1) {
        outputText += 'Z';
    }

    // Loop over the input in Digraphs
    for (std::string::size_type i{0}; i < outputText.size() - 1; i += 2) {
        // - Find the coords in the grid for each digraph

        std::pair<int, int> p0{(*C2PMap_.find(outputText[i])).second};
        std::pair<int, int> p1{(*C2PMap_.find(outputText[i + 1])).second};

        std::pair<int, int> p0_new{p0.first, p0.second};
        std::pair<int, int> p1_new{p1.first, p1.second};

        // - Apply the rules to these coords to get 'new' coords
        int flagMode{0};
        switch (cipherMode) {
            case CipherMode::Encrypt:
                flagMode = 1;
                break;
            case CipherMode::Decrypt:
                flagMode = -1;
                break;
            default:
                break;
        }
        // Do the "in-line" pairs first.
        // Modulo to wrap around
        if ((p0.first - p1.first) == 0) {
            p0_new.second = (p0.second + flagMode + 5) % 5;
            p1_new.second = (p1.second + flagMode + 5) % 5;

        } else if ((p0.second - p1.second) == 0) {
            p0_new.first = (p0.first + flagMode + 5) % 5;
            p1_new.first = (p1.first + flagMode + 5) % 5;
        }
        // Rectangle next
        else {
            p0_new.first = p1.first;
            p1_new.first = p0.first;
        };

        // - Find the letter associated with the new coords
        outputText[i] = (*P2CMap_.find(p0_new)).second;
        outputText[i + 1] = (*P2CMap_.find(p1_new)).second;
    }
    // return the text
    return outputText;
}