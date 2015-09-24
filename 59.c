#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "59.h"

void decrypt(unsigned char *key, size_t key_len, unsigned char *bytes, size_t len, char *output) {
	size_t i;
	for(i = 0; i < len; ++i)
		output[i] = bytes[i] ^ key[i % 3];
	output[i] = 0;
}

int summarize(char *str) {
	int sum = 0;
	while(*str) {
		sum += *str;
		++str;
	}
	return sum;
}

int main(int argc, char **argv) {
	// Break the cipher text using three lowercase characters and XOR encryption, then add the ascii values of the original text
	unsigned char key[3];
	size_t len = sizeof(cipher_text)/sizeof(cipher_text[0]);
	char original[len + 1];

	for(key[0] = 'a'; key[0] <= 'z'; ++key[0]) {
		for(key[1] = 'a'; key[1] <= 'z'; ++key[1]) {
			for(key[2] = 'a'; key[2] <= 'z'; ++key[2]) {
				decrypt(key, 3, cipher_text, len, original);
				// Locate two command english words used in sentences
				if(strstr(original, " the ") && strstr(original, " a "))
					printf("%s\n\nSum is: %d\n", original, summarize(original));
			}
		}
	}
	return 0;
}
