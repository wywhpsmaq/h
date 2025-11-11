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
string pkcs7Unpad (const string &text) {
	if (text.empty ()) return text;

	uint8_t padValue = static_cast<uint8_t> (text[text.length () - 1]);
	if (padValue > text.length ()) return text;

	for (size_t i = text.length () - padValue; i < text.length (); i++) {
		if (static_cast<uint8_t> (text[i]) != padValue) { return text; }
	}
	return text.substr (0, text.length () - padValue);
}
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	freopen ("AES256-p.txt", "r", stdin);
	freopen ("AES256-p1.txt", "w", stdout);
	string key, ciphertext;
	getline (cin, key);
	getline (cin, ciphertext);
	string processedKey = processKey (key);
	string hexKey = stringToHex (processedKey);
	ofstream keyFile ("my-in.txt");
	if (!keyFile) { return 1; }
	keyFile << hexKey;
	keyFile.close ();
	vector<string> blocks;
	for (size_t i = 0; i < ciphertext.length (); i += 32) {
		string block = ciphertext.substr (i, 32);
		if (block.length () < 32) { block.append (32 - block.length (), '0'); }
		blocks.push_back (block);
	}
	string plaintext;
	for (size_t i = 0; i < blocks.size (); i++) {
		ofstream ciphertextFile ("jm-in.txt");
		if (!ciphertextFile) { return 1; }
		ciphertextFile << blocks[i];
		ciphertextFile.close ();
		int result = system ("AES256-J.exe");
		if (result != 0) { return 1; }
		ifstream plaintextFile ("jm-out.txt");
		if (!plaintextFile) { return 1; }
		string hexPlaintext;
		plaintextFile >> hexPlaintext;
		plaintextFile.close ();

		plaintext += hexToString (hexPlaintext);
	}
	string ans = pkcs7Unpad (plaintext);
	cout << ans;
	return 0;
}