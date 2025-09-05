//
// Created by 22905 on 2025/9/5.
//

#ifndef H_AES256_H
#define H_AES256_H

#include <cstdint>

#include <cstdint>
using uint8_t = std::uint8_t;


class aes256 {
using uint8_t = std::uint8_t;
private:
    
    static constexpr int Nb = 4;
    static constexpr int Nk = 8;
    static constexpr int Nr = 14;
    
    uint8_t RoundKey[240];
    uint8_t state[4][4];
    
    static const uint8_t sbox[256];
    static const uint8_t rsbox[256];
    
    void KeyExpansion(const uint8_t* Key);
    void AddRoundKey(int round);
    void SubBytes();
    void ShiftRows();
    void MixColumns();
    void InvSubBytes();
    void InvShiftRows();
    void InvMixColumns();

public:
    void encrypt(uint8_t* output, const uint8_t* input, const uint8_t* key);
    void decrypt(uint8_t* output, const uint8_t* input, const uint8_t* key);
};


#endif //H_AES256_H