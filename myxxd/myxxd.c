#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

void byteToHex(unsigned char data) {
	int digit1 = data/16;
	if (digit1 < 0) {
		printf("data %c, %d, produced output less than zero, digit 1 was %d", data, data, digit1);
		exit (0);
	}
	char chardigit1;
	if (digit1 > 9) {
		chardigit1 = digit1 + 87;
		printf("%c", chardigit1);
	} else {
		printf("%d", digit1);
	}
	int remainder = data%16;
	int digit2 = 0;
	char digit2char;
	if (remainder > 9) {
		digit2char = remainder + 87;
		printf("%c", digit2char);
	} else {
		digit2 = remainder;
		printf("%d", digit2);
	}


}
/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
	//printf("TODO 1: printDataAsHex (2)");
	//printf("size is %ld", size);
	int counter = 0;
	int blocks = 0;
	for (counter; counter < size; counter++) {
		if (counter%2 == 0) {
			printf(" ");
			blocks++;
		}
		byteToHex(data[counter]);
	}
	if (size < 16) {
		int remainder = 16-size;
		for (int i = 0; i < remainder; i++){
			printf("  ");
		}
		for (blocks; blocks < 8; blocks++){
			printf(" ");
		}
	}
	return;
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
	//printf("TODO 2: printDataAsChars (3)");
	for (int i = 0; i < size; i ++) {
		if (data[i] < 32 || data[i] > 126) {
			printf(".");
		} else {
			printf("%c", data[i]);
		}

	}

	return;
}

void readAndPrintInputAsHex(FILE *input) {
	unsigned char data[16];
	int numBytesRead = fread(data, 1, 16, input);
	unsigned int offset = 0;
	while (numBytesRead != 0) {
		printf("%08x:", offset);
		offset += numBytesRead;
		printDataAsHex(data, numBytesRead);
		printf("  ");
		printDataAsChars(data, numBytesRead);
		printf("\n");
		numBytesRead = fread(data, 1, 16, input);
	}
}

void printCharAsBits(unsigned char data){
	char binary[8];
	int tracker = 7;
	for (int i = 0; i < 8; i++){
		if (data % 2 == 1) {
			binary[tracker] = 1;
		} else if (data % 2 == 0){
			binary[tracker] = 0;
		} else {
			printf("\n excuse me what \n");
			exit(0);
		}
		data = data/2;
		tracker--;
	}
	for (int i = 0; i < 8; i++) {
		printf("%d", binary[i]);
	}
	return;
}

void printDataAsBits(unsigned char* data, size_t size) {
	int counter = 0;
	int blocks = 0;
	for (counter; counter < size; counter++) {
		printf(" ");
		printCharAsBits(data[counter]);
		blocks++;
	}
	if (size < 6) {
		int remainder = 6-size;
		for (int i = 0; i < remainder; i++){
			printf("        ");
		}
		for (blocks; blocks < 6; blocks++){
			printf(" ");
		}
	}
	return;
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
 	//printf("TODO 3: readAndPrintInputAsBits\n");
	unsigned char data[8];
	int numBytesRead = fread(data, 1, 6, input);
	unsigned int offset = 0;
	while (numBytesRead != 0) {
		printf("%08x:", offset);
		offset += numBytesRead;
		printDataAsBits(data, numBytesRead);
		printf("  ");
		printDataAsChars(data, numBytesRead);
		printf("\n");
		numBytesRead = fread(data, 1, 6, input);
	}
}

int main(int argc, char **argv) {
	int bits = FALSE;
	FILE *input = parseCommandLine(argc, argv, &bits);

	if (bits == FALSE) {
		readAndPrintInputAsHex(input);
	} else {
		readAndPrintInputAsBits(input);
	}
	return 0;
}
