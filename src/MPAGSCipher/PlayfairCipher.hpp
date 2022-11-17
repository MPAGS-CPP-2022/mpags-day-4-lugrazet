#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"
#include <map>
#include <cstddef>
#include <string>
#include <vector>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
  public:
    /**
     * \brief Creates a new PlayfairCipher, converting the given string into the key via the setKey function
     *
     * \param key the key to be transformed for use in the cipher
     */
    PlayfairCipher(const std::string& key);

    /** 
     * \brief Function for converting a string into the appropriate grid map for the cipher.
     *
     * \param key the string to convert into the "effective" key to be used in the cipher
     */
    void setKey(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param PlayfairMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText,
                            const CipherMode cipherMode) const;

  private:
    /// The alphabet - used to determine the cipher character given the plain character and the key
    const std::vector<char> alphabet_{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /// The size of the alphabet
    const std::size_t alphabetSize_{alphabet_.size()};

    // The key Maps, transforming Characters to Pairs of coordinates or vice-versa.
    std::map<char, std::pair<int, int>> C2PMap_;
    std::map<std::pair<int,int>, char> P2CMap_;
    // The key fed into the Playfair cipher, transformed for use in creating the Map.
    std::string key_{""};
};
#endif