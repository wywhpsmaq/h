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
using namespace std;
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
string pkcs7Pad (const string &text, size_t blockSize) {
	size_t padValue = blockSize - (text.length () % blockSize);
	if (padValue == 0) padValue = blockSize;

	string paddedText = text;
	paddedText.append (padValue, static_cast<char> (padValue));
	return paddedText;
}
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	string key, plaintext;
	freopen ("AES256-q.txt", "r", stdin);
	freopen ("AES256-q1.txt", "w", stdout);
	getline (cin, key);
	getline (cin, plaintext);
	string processedKey = processKey (key);
	string hexKey = stringToHex (processedKey);
	ofstream keyFile ("my-in.txt");
	if (!keyFile) {
		return 1;
	}
	keyFile << hexKey;
	keyFile.close ();
	string paddedText = pkcs7Pad (plaintext, 16);
	vector<string> blocks;
	for (size_t i = 0; i < paddedText.length (); i += 16) {
		string block = paddedText.substr (i, 16);
		blocks.push_back (stringToHex (block));
	}
	string ciphertext;
	for (size_t i = 0; i < blocks.size (); i++) {
		ofstream plaintextFile ("jm-in.txt");
		if (!plaintextFile) {
			return 1;
		}
		plaintextFile << blocks[i];
		plaintextFile.close ();
		int result = system ("AES256.exe");
		if (result != 0) {
			return 1;
		}
		ifstream ciphertextFile ("jm-out.txt");
		if (!ciphertextFile) {
			return 1;
		}
		string hexCiphertext;
		ciphertextFile >> hexCiphertext;
		ciphertextFile.close ();
		ciphertext += hexCiphertext;
	}
	cout << ciphertext << endl;
	return 0;
}