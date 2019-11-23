#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include "file_parser.h"
#include "tokenizer.h"
#include <errno.h>
extern int search(char *instruction);
/*
 * The structs below map a character to an integer.
 * They are used in order to map a specific instruciton/register to its binary format in ASCII
 */

struct {
    const char* bin;
    const char hex;
} bin2hex[] = {
    { "0000", '0'},
    { "0001", '1'},
    { "0010", '2'},
    { "0011", '3'},
    { "0100", '4'},
    { "0101", '5'},
    { "0110", '6'},
    { "0111", '7'},
    { "1000", '8'},
    { "1001", '9'},
    { "1010", 'A'},
    { "1011", 'B'},
    { "1100", 'C'},
    { "1101", 'D'},
    { "1110", 'E'},
    { "1111", 'F'}
};

// Struct that stores registers and their respective binary reference
struct {
    const char *name;
    char *address;
} registerMap[] = {
    { "zero", "00000" }, 
    { "at", "00001" },	
    { "v0", "00010" }, 
    { "v1", "00011" },
    { "a0", "00100" },
    { "a1", "00101" },
    { "a2", "00110" },
    { "a3", "00111" },
    { "t0", "01000" },
    { "t1", "01001" },
    { "t2", "01010" },
    { "t3", "01011" },
    { "t4", "01100" },
    { "t5", "01101" },
    { "t6", "01110" },
    { "t7", "01111" },
    { "s0", "10000" },
    { "s1", "10001" },
    { "s2", "10010" },
    { "s3", "10011" },
    { "s4", "10100" },
    { "s5", "10101" },
    { "s6", "10110" },
    { "s7", "10111" },
    { "t8", "11000" },
    { "t9", "11001" },
    { "k0", "11010" },
    { "k1", "11011" },
    { "gp", "11100" },
    { "sp", "11101" },
    { "fp", "11110" },
    { "ra", "11111" },
    { "status","01100"},
    { "cause", "01101"},
    { "epc", "01110"},
    { NULL, 0 }
};

// Struct for R-Type instructions mapping for the 'function' field in the instruction
struct {
    const char *name;
    char *function;
} rMap[] = {
    { "add", "100000" },
    { "sub", "100010" },
    { "and", "100100" },
    { "or",  "100101" },
    { "sll", "000000" },
    { "slt", "101010" },
    { "srl", "000010" },
    { "jr",  "001000" },
    { "xor", "100110" },
    { "addu", "100001" },
    { "subu", "100011" },
    { "nor",  "100111" },
    { "sra",  "000011"},
    { "sltu", "101011"},
    { "sllv", "000100"},
    { "srlv", "000110"},
    { "srav", "000111"},
    { "mult", "011000"},
    { "multu", "011001"},
    { "div",  "011010"},
    { "divu", "011011"},
    { "mfhi", "010000"},
    { "mflo", "010010"},
    { "mthi", "010001"},
    { "mtlo", "010011"},
    { "jalr", "001001"},
    { "break", "001101"},
    { "syscall", "001100"},
    { "eret", "011000"},
    { "mfc0", "000000"},
    { "mtc0", "000000"},

    { NULL, 0 }
};

// Struct for I-Type instructions
struct {
    const char *name;
    char *address;
} iMap[] = {
    { "lw",   "100011" },
    { "sw",   "101011" },
    { "andi", "001100" },
    { "ori",  "001101" },
    { "lui",  "001111" },
    { "beq",  "000100" },
    { "slti", "001010" },
    { "addi", "001000" },
    { "xori", "001110" },
    { "lb",   "100000" },
    { "lbu",  "100100" },
    { "lh",   "100001" },
    { "lhu",  "100101" },
    { "sb",   "101000" },
    { "sh",   "101001" },
    { "bne",   "000101" },
    { "sltiu", "001011" },
    { "bgez",  "000001" },
    { "bgtz",  "000111" },
    { "blez",  "000110" },
    { "bltz",  "000001" },
    { "bgezal", "000001" },
    { "bltzal", "000001" },
    { "addiu", "001001" },


    { NULL, 0 }
};

// Struct for J-Type instructions
struct {
    const char *name;
    char *address;
} jMap[] = {
    { "j", "000010" },
    { "jal", "000011" },
    { NULL, 0 }
};

///---------------------------------------------------------------------------------------------///

void parse_file(FILE *fptr, int pass, char *instructions[], size_t inst_len, hash_table_t *hash_table, FILE *Out) {

	char line[MAX_LINE_LENGTH + 1];
	char *tok_ptr, *ret, *token = NULL;
	int32_t line_num = 1;
	int data_reached = 0;

	while (1) {
		if ((ret = fgets(line, MAX_LINE_LENGTH, fptr)) == NULL)
			break;
		line[MAX_LINE_LENGTH] = 0;

		tok_ptr = line;
		if (strlen(line) == MAX_LINE_LENGTH) {
			fprintf(Out,
					"line %d: line is too long. ignoring line ...\n", line_num);
			line_num++;
			continue;
		}

		/* parse the tokens within a line */
		while (1) {
			token = parse_token(tok_ptr, " \n\t$,", &tok_ptr, NULL);

			/* blank line or comment begins here. go to the next line */
			if (token == NULL || *token == '#') {
				line_num++;
				free(token);
				break;
			}
			printf("token: %s\n", token);

			int x = search(token);
			if (x >= 0) {
				if (strcmp(token, "la") == 0)
					instruction_count = instruction_count + 8;
				else
					instruction_count = instruction_count + 4;
			}
			else if (strcmp(token, ".data") == 0) {
				data_reached = 1;
			}




		}
	}
}

// Binary Search the Array
int binarySearch(char *instructions[], int low, int high, char *string) {

	int mid = low + (high - low) / 2;
	int comp = strcmp(instructions[mid], string);\

	if (comp == 0)
		return mid;

	// Not found
	if (high <= low)
		return -1;

	// If instructions[mid] is less than string
	else if (comp > 0)
		return binarySearch(instructions, low, mid - 1, string);

	// If instructions[mid] is larger than string
	else if (comp < 0)
		return binarySearch(instructions, mid + 1, high, string);

	// Return position
	else
		return mid;

	// Error
	return -2;
}

// Determine Instruction Type
char instruction_type(char *instruction) {

	if (strcmp(instruction, "add") == 0 || strcmp(instruction, "addu") == 0
			|| strcmp(instruction, "sub") == 0 || strcmp(instruction, "subu") == 0 
			|| strcmp(instruction, "and") == 0 || strcmp(instruction, "mult") == 0 
			|| strcmp(instruction, "multu") == 0 || strcmp(instruction, "div") == 0
            || strcmp(instruction, "divu") == 0 || strcmp(instruction, "mfhi") == 0
            || strcmp(instruction, "mflo") == 0 || strcmp(instruction, "mthi") == 0
            || strcmp(instruction, "mtlo") == 0 || strcmp(instruction, "mfc0") == 0
            || strcmp(instruction, "mtc0") == 0 || strcmp(instruction, "or") == 0
            || strcmp(instruction, "xor") == 0 || strcmp(instruction, "nor") == 0
            || strcmp(instruction, "slt") == 0 || strcmp(instruction, "sltu") == 0
            || strcmp(instruction, "sll") == 0 || strcmp(instruction, "srl") == 0
            || strcmp(instruction, "sra") == 0 || strcmp(instruction, "sllv") == 0
            || strcmp(instruction, "srlv") == 0 || strcmp(instruction, "srav") == 0
            || strcmp(instruction, "jr") == 0 || strcmp(instruction, "jalr") == 0
            || strcmp(instruction, "eret") == 0
			) {

		return 'r';
	}

	else if (strcmp(instruction, "addi") == 0 || strcmp(instruction, "addiu") == 0
				|| strcmp(instruction, "andi") == 0 || strcmp(instruction, "ori") == 0
				|| strcmp(instruction, "xori") == 0 || strcmp(instruction, "lui") == 0
				|| strcmp(instruction, "lb") == 0 || strcmp(instruction, "lbu") == 0
				|| strcmp(instruction, "lh") == 0 || strcmp(instruction, "lhu") == 0
				|| strcmp(instruction, "sb") == 0 || strcmp(instruction, "sh") == 0
				|| strcmp(instruction, "lw") == 0 || strcmp(instruction, "sw") == 0
				|| strcmp(instruction, "beq") == 0 || strcmp(instruction, "bne") == 0
				|| strcmp(instruction, "bgez") == 0 || strcmp(instruction, "bgtz") == 0
				|| strcmp(instruction, "blez") == 0 || strcmp(instruction, "bltz") == 0
				|| strcmp(instruction, "bgezal") == 0 || strcmp(instruction, "bltzal") == 0
				|| strcmp(instruction, "slti") == 0 || strcmp(instruction, "sltiu") == 0
		) {

		return 'i';
	}

	else if (strcmp(instruction, "j") == 0 || strcmp(instruction, "jal") == 0) {
		
		return 'j';
	}

	// Failsafe return statement
	return 0;
}

// Return the binary representation of the register
char *register_address(char *registerName) {

	size_t i;
	for (i = 0; registerMap[i].name != NULL; i++) {
		if (strcmp(registerName, registerMap[i].name) == 0) {
			return registerMap[i].address;
		}
	}

	return NULL;
}

// Write out the R-Type instruction
void rtype_instruction(char *instruction, char *rs, char *rt, char *rd, int shamt, FILE *Out) {

	// Set the instruction bits
	char *opcode = "000000";

	char *rdBin = "00000";
	if (strcmp(rd, "00000") != 0)
		rdBin = register_address(rd);

	char *rsBin = "00000";
	if (strcmp(rs, "00000") != 0)
		rsBin = register_address(rs);

	char *rtBin = "00000";
	if (strcmp(rt, "00000") != 0)
		rtBin = register_address(rt);

	char *func = NULL;
	char shamtBin[6];

	// Convert shamt to binary and put in shamtBin as a char*
	getBin(shamt, shamtBin, 5);

	size_t i;
	for (i = 0; rMap[i].name != NULL; i++) {
		if (strcmp(instruction, rMap[i].name) == 0) {
			func = rMap[i].function;
		}
	}

	// Print out the instruction to the file
	fprintf(Out, "%s%s%s%s%s%s\n", opcode, rsBin, rtBin, rdBin, shamtBin, func);
}

// Write out the I-Type instruction
void itype_instruction(char *instruction, char *rs, char *rt, int immediateNum, FILE *Out) {

	// Set the instruction bits
	char *rsBin = "00000";
	if (strcmp(rs, "00000") != 0)
		rsBin = register_address(rs);

	char *rtBin = "00000";
		if (strcmp(rt, "00000") != 0)
			rtBin = register_address(rt);

	char *opcode = NULL;
	char immediate[17];

	size_t i;
	for (i = 0; iMap[i].name != NULL; i++) {
		if (strcmp(instruction, iMap[i].name) == 0) {
			opcode = iMap[i].address;
		}
	}

	// Convert immediate to binary
	getBin(immediateNum, immediate, 16);

	// Print out the instruction to the file
	fprintf(Out, "%s%s%s%s\n", opcode, rsBin, rtBin, immediate);
}

// Write out the J-Type instruction
void jtype_instruction(char *instruction, int immediate, FILE *Out) {

	// Set the instruction bits
	char *opcode = NULL;

	// Get opcode bits
	size_t i;
	for (i = 0; jMap[i].name != NULL; i++) {
		if (strcmp(instruction, jMap[i].name) == 0) {
			opcode = jMap[i].address;
		}
	}

	// Convert immediate to binary
	char immediateStr[27];
	getBin(immediate, immediateStr, 26);

	// Print out instruction to file
	fprintf(Out, "%s%s\n", opcode, immediateStr);
}

// Write out the variable in binary
void word_rep(int binary_rep, FILE *Out) {

	for (int k = 31; k >= 0; k--) {
		fprintf(Out, "%c", (binary_rep & (1 << k)) ? '1' : '0');
	}

	fprintf(Out, "\n");
}

// Write out the ascii string
void ascii_rep(char string[], FILE *Out) {

	// Separate the string, and put each four characters in an element of an array of strings
	size_t str_length = strlen(string);
	str_length++;
	int num_strs = str_length / 4;
	if ((str_length % 4) > 0)
		num_strs++;

	char *ptr;
	ptr = &string[0];

	// Create an array of strings which separates each 4-char string
	char **sep_str;
	sep_str = malloc(num_strs * sizeof(char*));
	if (sep_str == NULL) {
		fprintf(Out, "Out of memory\n");
		exit(1);
	}

	for (int i = 0; i < num_strs; i++) {
		sep_str[i] = malloc(4 * sizeof(char));
		if (sep_str[i] == NULL) {
			fprintf(Out, "Out of memory\n");
			exit(1);
		}
	}

	int count = 0;
	for (int i = 0; i < str_length; i++) {
		sep_str[i / 4][i % 4] = *ptr;
		ptr++;
		count++;
	}

	// Reverse each element in the array
	char temp;

	for (int i = 0; i < num_strs; i++) {

		for (int j = 0, k = 3; j < k; j++, k--) {

			temp = sep_str[i][j];
			sep_str[i][j] = sep_str[i][k];
			sep_str[i][k] = temp;
		}
	}

	// Convert into binary
	for (int i = 0; i < num_strs; i++) {

		for (int j = 0; j < 4; j++) {
			char c = sep_str[i][j];
			for (int k = 7; k >= 0; k--) {
				fprintf(Out, "%c", (c & (1 << k)) ? '1' : '0');
			}
		}

		fprintf(Out, "\n");
	}

	// Deallocate sep_str
	for (int i = 0; i < num_strs; i++) {
		free(sep_str[i]);
	}
	free(sep_str);
	sep_str = NULL;
}

void getBin(int num, char *str, int padding) {

	*(str + padding) = '\0';

	long pos;
	if (padding == 5)
		pos = 0x10;
	else if (padding == 16)
		pos = 0x8000;
	else if (padding == 26)
		pos = 0x2000000;
	else if (padding == 32)
		pos = 0x80000000;

	long mask = pos << 1;
	while (mask >>= 1)
		*str++ = !!(mask & num) + '0';
}

// Convert a binary string to a decimal value
int getDec(char *bin) {

	int  b, k, m, n;
	int  len, sum = 0;

	// Length - 1 to accomodate for null terminator
	len = strlen(bin) - 1;

	// Iterate the string
	for(k = 0; k <= len; k++) {

		// Convert char to numeric value
		n = (bin[k] - '0');

		// Check the character is binary
		if ((n > 1) || (n < 0))  {
			return 0;
		}

		for(b = 1, m = len; m > k; m--)
			b *= 2;

		// sum it up
		sum = sum + n * b;
	}

	return sum;
}

// convert bin to hex
char getHex(char *bin){
    int i = 0;
    while(i < 16) {
        if(strncmp(bin2hex[i].bin, bin, 4) == 0) break;
        i++;
    }
    return bin2hex[i].hex;
}

