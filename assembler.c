/*
 * assembler.c
 *
 *  Created on: Oct 3, 2011
 *      Author: nayef
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_parser.h"
#include "hash_table.h"

int search(char *instruction);

// Array that holds the supported instructions
char *instructions[] = {
		// R-Type
	    "add",
	    "sub",
	    "xor",
	    "jr",
	    "addu",
	    "subu",
	    "or",
	    "and",
	    "slt",
	    "sll",
	    "srl",
	    "nor",
	    "sra",
	    "sltu",
	    "sllv",
	    "srlv",
	    "srav",
	    "mult",
	    "multu",
	    "div",
	    "divu",
	    "mthi",
	    "mtlo",
	    "mfhi",
	    "mflo",
	    "jalr",
	    "break",
	    "syscall",
	    "eret",
	    "mfc0",
	    "mtc0",
	    // I-Type
	    "lui",
	    "lw",
	    "sw",
	    "ori",
	    "andi",
	    "addi",
	    "beq",
	    "slti",
	    "xori",
	    "lb",
	    "lh",
	    "lbu",
	    "lhu",
	    "sb",
	    "sh",
	    "addiu",
	    "bne",
	    "sltiu",
	    "bgez",
	    "bgtz",
	    "blez",
	    "bltz",
	    "bgezal",
	    "bltzal",
	    // J-Type
	    "j",
    	"jal"
	};

// Size of array
size_t inst_len = sizeof(instructions)/sizeof(char *);

int search(char *instruction) {

	int found = 0;

	for (int i = 0; i < inst_len; i++) {

		if (strcmp(instruction, instructions[i]) == 0) {
			found = 1;
			return i;
		}
	}

	if (found == 0)
		return -1;
}

// Quick Sort String Comparison Function
int string_comp(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}

int main (int argc, char *argv[]) {

	// Make sure correct number of arguments input
	if (argc != 8) {
		printf("Incorrect number of arguments");
	}

	else {

		// Open I/O files
		// Check that files opened properly
		FILE *In;
		In = fopen(argv[1], "r");
		if (In == NULL) {
			printf("Input file could not be opened.");
			exit(1);
		}

		FILE *Out;
		Out = fopen(argv[2], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}

		FILE *src;
		src = fopen(argv[3], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}
		
		FILE *data1;
		data1 = fopen(argv[4], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}
		FILE *data2;
		data2 = fopen(argv[5], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}
		FILE *data3;
		data3 = fopen(argv[6], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}
		FILE *data4;
		data4 = fopen(argv[7], "w");
		if (Out == NULL) {
			printf("Output file could not opened.");
			exit(1);
		}

		// Sort the array using qsort for faster search
		qsort(instructions, inst_len, sizeof(char *), string_comp);

		// Create a hash table of size 127
		hash_table_t *hash_table = create_hash_table(127);

		// Parse in passes

		int passNumber = 1;
		parse_file(In, passNumber, instructions, inst_len, hash_table, Out, src);

		// Rewind input file & start pass 2
		rewind(In);
		passNumber = 2;
		parse_file(In, passNumber, instructions, inst_len, hash_table, Out, src);
		

		// Close files
		fclose(In);
		fclose(Out);
		fclose(src);
		FILE *fp = fopen("data.coe", "r");
		int c;
		int i=0;
		while((c = fgetc(fp))!=EOF) {
			if(i<8) {
				fputc(c,data1);
				i++;
			}
			else if(i>=8 && i <16) {
				fputc(c,data2);
				i++;
			}
			else if(i>=16 && i <24) {
				fputc(c,data3);
				i++;
			}
			else if(i>=24 && i <32) {
				fputc(c,data4);
				i++;
				if(i==32){
					i=0;
					continue;
				}
			}
		}
		return 0;
	}
}
