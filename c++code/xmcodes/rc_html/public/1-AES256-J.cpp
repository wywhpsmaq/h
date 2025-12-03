#include <codecvt>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#define byte uint8_t
using namespace std;
struct Word {
	byte bytes[4];
};
struct State {
	byte bytes[4][4];
};
Word roundKeys[60];
const byte rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
const byte sbox[256] = {
	// 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, // 0
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, // 1
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, // 2
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, // 3
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, // 4
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF, // 5
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, // 6
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, // 7
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, // 8
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, // 9
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, // A
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08, // B
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, // C
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, // D
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, // E
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16	// F
};
const byte invSbox[256] = {
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
	0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
	0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
	0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F, 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
	0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D};
namespace aes_1 {
Word g (Word input, int roundIndex) {
	Word result = input;
	byte temp = result.bytes[0];
	result.bytes[0] = result.bytes[1];
	result.bytes[1] = result.bytes[2];
	result.bytes[2] = result.bytes[3];
	result.bytes[3] = temp;
	for (int i = 0; i < 4; i++) { result.bytes[i] = sbox[result.bytes[i]]; }
	result.bytes[0] ^= rcon[roundIndex];
	return result;
}
Word h (Word input) {
	Word result = input;
	for (int i = 0; i < 4; i++) { result.bytes[i] = sbox[result.bytes[i]]; }
	return result;
}
}
namespace aes_2 {
void addRoundKey (State &state, const Word roundKey[4]) {
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) { state.bytes[row][col] ^= roundKey[col].bytes[row]; }
	}
}
void subBytes (State &state) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) { state.bytes[row][col] = sbox[state.bytes[row][col]]; }
	}
}
void invSubBytes (State &state) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) { state.bytes[row][col] = invSbox[state.bytes[row][col]]; }
	}
}
void shiftRows (State &state) {
	byte temp = state.bytes[1][0];
	state.bytes[1][0] = state.bytes[1][1];
	state.bytes[1][1] = state.bytes[1][2];
	state.bytes[1][2] = state.bytes[1][3];
	state.bytes[1][3] = temp;
	std::swap (state.bytes[2][0], state.bytes[2][2]);
	std::swap (state.bytes[2][1], state.bytes[2][3]);
	temp = state.bytes[3][3];
	state.bytes[3][3] = state.bytes[3][2];
	state.bytes[3][2] = state.bytes[3][1];
	state.bytes[3][1] = state.bytes[3][0];
	state.bytes[3][0] = temp;
}
void invShiftRows (State &state) {
	byte temp = state.bytes[1][3];
	state.bytes[1][3] = state.bytes[1][2];
	state.bytes[1][2] = state.bytes[1][1];
	state.bytes[1][1] = state.bytes[1][0];
	state.bytes[1][0] = temp;
	std::swap (state.bytes[2][0], state.bytes[2][2]);
	std::swap (state.bytes[2][1], state.bytes[2][3]);
	temp = state.bytes[3][0];
	state.bytes[3][0] = state.bytes[3][1];
	state.bytes[3][1] = state.bytes[3][2];
	state.bytes[3][2] = state.bytes[3][3];
	state.bytes[3][3] = temp;
}
byte gfMultiply (byte a, byte b) {
	byte result = 0;
	byte highBit;
	for (int i = 0; i < 8; i++) {
		if (b & 1) { result ^= a; }
		highBit = a & 0x80;
		a <<= 1;
		if (highBit) { a ^= 0x1B; }
		b >>= 1;
	}
	return result;
}
void mixColumns (State &state) {
	byte temp[4];
	for (int col = 0; col < 4; col++) {
		temp[0] = state.bytes[0][col];
		temp[1] = state.bytes[1][col];
		temp[2] = state.bytes[2][col];
		temp[3] = state.bytes[3][col];
		state.bytes[0][col] = gfMultiply (0x02, temp[0]) ^ gfMultiply (0x03, temp[1]) ^ temp[2] ^ temp[3];
		state.bytes[1][col] = temp[0] ^ gfMultiply (0x02, temp[1]) ^ gfMultiply (0x03, temp[2]) ^ temp[3];
		state.bytes[2][col] = temp[0] ^ temp[1] ^ gfMultiply (0x02, temp[2]) ^ gfMultiply (0x03, temp[3]);
		state.bytes[3][col] = gfMultiply (0x03, temp[0]) ^ temp[1] ^ temp[2] ^ gfMultiply (0x02, temp[3]);
	}
}
void invMixColumns (State &state) {
	byte temp[4];
	for (int col = 0; col < 4; col++) {
		temp[0] = state.bytes[0][col];
		temp[1] = state.bytes[1][col];
		temp[2] = state.bytes[2][col];
		temp[3] = state.bytes[3][col];

		state.bytes[0][col] = gfMultiply (0x0E, temp[0]) ^ gfMultiply (0x0B, temp[1]) ^ gfMultiply (0x0D, temp[2]) ^ gfMultiply (0x09, temp[3]);
		state.bytes[1][col] = gfMultiply (0x09, temp[0]) ^ gfMultiply (0x0E, temp[1]) ^ gfMultiply (0x0B, temp[2]) ^ gfMultiply (0x0D, temp[3]);
		state.bytes[2][col] = gfMultiply (0x0D, temp[0]) ^ gfMultiply (0x09, temp[1]) ^ gfMultiply (0x0E, temp[2]) ^ gfMultiply (0x0B, temp[3]);
		state.bytes[3][col] = gfMultiply (0x0B, temp[0]) ^ gfMultiply (0x0D, temp[1]) ^ gfMultiply (0x09, temp[2]) ^ gfMultiply (0x0E, temp[3]);
	}
}
void hexStringToState (const string &hexStr, State &state) {
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			string byteStr = hexStr.substr (col * 8 + row * 2, 2);
			state.bytes[row][col] = static_cast<byte> (std::stoul (byteStr, nullptr, 16));
		}
	}
}
string stateToHexString (const State &state) {
	string result;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			char buf[3];
			snprintf (buf, sizeof (buf), "%02x", state.bytes[row][col]);
			result += buf;
		}
	}
	return result;
}
} // namespace aes_2
string stringToHex (const string &input) {
	stringstream ss;
	for (unsigned char c : input) { ss << hex << setw (2) << setfill ('0') << static_cast<int> (c); }
	return ss.str ();
}
string hexToString (const string &hex) {
	string result;
	for (size_t i = 0; i < hex.length (); i += 2) {
		string byteString = hex.substr (i, 2);
		char byte = static_cast<char> (strtol (byteString.c_str (), nullptr, 16));
		result.push_back (byte);
	}
	return result;
}
string processKey (const string &key) {
	string processedKey = key;
	if (processedKey.length () < 32) {
		uint8_t padValue = 32 - processedKey.length ();
		processedKey.append (padValue, static_cast<char> (padValue));
	} else if (processedKey.length () > 32) {
		processedKey = processedKey.substr (0, 32);
	}
	return processedKey;
}
string pkcs7Unpad (const string &text) {
	if (text.empty ()) return text;
	uint8_t padValue = static_cast<uint8_t> (text[text.length () - 1]);
	if (padValue > text.length ()) return text;
	for (size_t i = text.length () - padValue; i < text.length (); i++) {
		if (static_cast<uint8_t> (text[i]) != padValue) { return text; }
	}
	return text.substr (0, text.length () - padValue);
}
string aes256DecryptBlock (const string &keyHex, const string &ciphertextHex) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			string byteStr = keyHex.substr (i * 8 + j * 2, 2);
			roundKeys[i].bytes[j] = static_cast<byte> (std::stoul (byteStr, nullptr, 16));
		}
	}
	for (int i = 8; i < 60; i++) {
		if (i % 8 == 0) {
			Word temp = aes_1::g (roundKeys[i - 1], i / 8 - 1);
			for (int j = 0; j < 4; j++) { roundKeys[i].bytes[j] = roundKeys[i - 8].bytes[j] ^ temp.bytes[j]; }
		} else if (i % 8 == 4) {
			Word temp = aes_1::h (roundKeys[i - 1]);
			for (int j = 0; j < 4; j++) { roundKeys[i].bytes[j] = roundKeys[i - 8].bytes[j] ^ temp.bytes[j]; }
		} else {
			for (int j = 0; j < 4; j++) { roundKeys[i].bytes[j] = roundKeys[i - 8].bytes[j] ^ roundKeys[i - 1].bytes[j]; }
		}
	}
	State state;
	aes_2::hexStringToState (ciphertextHex, state);
	aes_2::addRoundKey (state, &roundKeys[14 * 4]);
	for (int round = 13; round >= 1; round--) {
		aes_2::invShiftRows (state);
		aes_2::invSubBytes (state);
		aes_2::addRoundKey (state, &roundKeys[round * 4]);
		aes_2::invMixColumns (state);
	}
	aes_2::invShiftRows (state);
	aes_2::invSubBytes (state);
	aes_2::addRoundKey (state, roundKeys);
	return aes_2::stateToHexString (state);
}
string aes256Decrypt (const string &key, const string &ciphertext) {
	string processedKey = processKey (key);
	string hexKey = stringToHex (processedKey);
	vector<string> blocks;
	for (size_t i = 0; i < ciphertext.length (); i += 32) {
		string block = ciphertext.substr (i, 32);
		if (block.length () < 32) { block.append (32 - block.length (), '0'); }
		blocks.push_back (block);
	}
	string plaintext;
	for (const string &block : blocks) {
		string hexPlaintext = aes256DecryptBlock (hexKey, block);
		plaintext += hexToString (hexPlaintext);
	}
	return pkcs7Unpad (plaintext);
}
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	string key, ciphertext;
	freopen ("AES256-p.txt", "r", stdin);
	freopen ("AES256-p1.txt", "w", stdout);
	getline (cin, key);
	getline (cin, ciphertext);
	string plaintext = aes256Decrypt (key, ciphertext);
	cout << plaintext << endl;
	return 0;
}