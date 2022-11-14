//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"
// For reference, the Playfair Cipher with key playfair leads to the following grid
// P L A Y F
// J R B C D
// E G H K M
// N O Q S T
// U V W X Z

// Tests that the cipher appropriately transforms the input data before encryption.
TEST_CASE("Playfair input transforms", "[Playfair]")
{
    PlayfairCipher pfc{"playfair"};
    REQUIRE(pfc.applyCipher(pfc.applyCipher("AB", CipherMode::Encrypt),
                            CipherMode::Decrypt) == "AB");
    REQUIRE(pfc.applyCipher(pfc.applyCipher("XX", CipherMode::Encrypt),
                            CipherMode::Decrypt) == "XQXZ");
    REQUIRE(pfc.applyCipher(pfc.applyCipher("LL", CipherMode::Encrypt),
                            CipherMode::Decrypt) == "LXLZ");
    REQUIRE(pfc.applyCipher(pfc.applyCipher("AA", CipherMode::Encrypt),
                            CipherMode::Decrypt) == "AXAZ");
}

// Helloworld -> HE LX LO WO RL DZ ->e KG YV RV VQ GR MF
TEST_CASE("Playfair Cipher encryption", "[Playfair]")
{
    PlayfairCipher pfc{"playfair"};
    REQUIRE(pfc.applyCipher("HELLOWORLD", CipherMode::Encrypt) ==
            "KGYVRVVQGRMF");
}

// KGYVRVVQGRMF -> KG YV RV XV QG RM FZ ->d HE LX LO WU OH DG ZT
TEST_CASE("Playfair Cipher decryption", "[Playfair]")
{
    PlayfairCipher pfc{"playfair"};
    REQUIRE(pfc.applyCipher("KGYVRVVQGRMF", CipherMode::Decrypt) ==
            "HELXLOWUOHDGZT");
}
