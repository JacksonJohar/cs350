/*
 * JacksonJohar350Final.c
 *
 *  Created on: Apr 20, 2019
 *      Author: Jackson Johar A20393623
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *theFile; 		//creating file

//Creating the struct for hex numbers
struct nums{
	char numHex[7];  //number in hex
	char action[25]; //the instruction name (add, sub, etc)
};

int main()
{
	//create file
	FILE *theFile;
	theFile = fopen("data.txt", "r");

	//check if file exists
	if (theFile == NULL) {
		exit(0);
	}


	struct nums hexNums[60];      //struct array for storing the hex inputs
	int lines = 0;
	int i = 0;
	int j = 0;
	int eofCheck = 3;
	int endOfFile = 0;
	unsigned int startLoc; //will eventually be the location of the first input (line 1)
	struct nums *ptr = hexNums;
	struct nums *start;

	//scanning from the file and storing into struct arrray
	printf("Scanning File... \n\n");
	while (endOfFile == 0) {
		lines++;
		fscanf(theFile, "%s", &hexNums[i].numHex);
		//printf("Scanned value: %s\n", hexNums[i].numHex);
		fflush(stdout);
		eofCheck = strcmp(hexNums[i].numHex, "00000000");
		if (eofCheck == 0) {
			endOfFile = 1;
		}
		i++;
	}

	//print the number of lines
	printf("Lines Scanned: %d\n\n", lines);
	fflush(stdout);

	//prompting the user for the starting storage location
	printf("Please enter a starting storage location in hex: ");
	fflush(stdout);
	scanf("%X", &startLoc);
	printf("\nStarting Location: %X\n\n", startLoc);
	fflush(stdout);

	//I couldn't figure out how to set the address of the array to the user input


	char *first6;   //opcode
	char *last6;
	char *rs; //7-11
	char *rt; //12-16
	char *rd; //17-21
	char *imm; //immediate
	char *targ;
	//temp arrays used for finding rs, rd, rt, immediate, and target
	char temp[31];
	char temp2[31];
	char temp3[31];
	char temp4[31];
	char temp5[31];
	char temp6[31];
	char temp7[31];
	char temp8[31];
	int rsDec;
	int rtDec;
	int rdDec;
	int immDec;
	int targDec;
	struct nums *point;

//Hex to Binary
	for (i = 0; i < lines; i++){
		for (j = 0; j < 8; j++) {
			switch (hexNums[i].numHex[j]) {
			        case '0':
			            temp[(j*4)] = '0';
			            temp[(j*4)+1] = '0';
			            temp[(j*4)+2] = '0';
			            temp[(j*4)+3] = '0';
			            break;
			        case '1':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '1';
			            break;
			        case '2':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '0';
			            break;
			        case '3':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '1';
			            break;
			        case '4':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '0';
			            break;
			        case '5':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '1';
			            break;
			        case '6':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '0';
			            break;
			        case '7':
			        	temp[(j*4)] = '0';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '1';
			        	break;
			        case '8':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '0';
			        	break;
			        case '9':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '1';
			        	break;
			        case 'A':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '0';
			        	break;
			        case 'B':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '0';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '1';
			        	break;
			        case 'C':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '0';
			        	break;
			        case 'D':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '0';
			        	temp[(j*4)+3] = '1';
			        	break;
			        case 'E':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '0';
			        	break;
			        case 'F':
			        	temp[(j*4)] = '1';
			        	temp[(j*4)+1] = '1';
			        	temp[(j*4)+2] = '1';
			        	temp[(j*4)+3] = '1';
			        	break;
			        default:
			        	temp[(j*4)] = 'x', temp[(j*4)+1] = 'x', temp[(j*4)+2] = 'x', temp[(j*4)+3] = 'x';
			        }

		}

		// making copies of the binary and using them to get instructions

		//OPCODE
		memcpy(temp2, temp, 10);
		first6 = temp2;
		first6[6] = '\0';


		//Getting RS
		memcpy(temp3, temp, 11);
		rs = temp3;
		rs = rs + 6;
		rs[5] = '\0';
		rsDec = binToDec(rs);

		//Switch cases used for giving registers correct value
		switch(rsDec){
		case 0:
			rs = "$zero";
			break;
		case 1:
			rs = "$at";
			break;
		case 2:
			rs = "$v0";
			break;
		case 3:
			rs = "$v1";
			break;
		case 4:
			rs = "$a0";
			break;
		case 5:
			rs = "$a1";
			break;
		case 6:
			rs = "$a2";
			break;
		case 7:
			rs = "$a3";
			break;
		case 8:
			rs = "$t0";
			break;
		case 9:
			rs = "$t1";
			break;
		case 10:
			rs = "$t2";
			break;
		case 11:
			rs = "$t3";
			break;
		case 12:
			rs = "$t4";
			break;
		case 13:
			rs = "$t5";
			break;
		case 14:
			rs = "$t6";
			break;
		case 15:
			rs = "$t7";
			break;
		case 16:
			rs = "$s0";
			break;
		case 17:
			rs = "$s1";
			break;
		case 18:
			rs = "$s2";
			break;
		case 19:
			rs = "$s3";
			break;
		case 20:
			rs = "$s4";
			break;
		case 21:
			rs = "$s5";
			break;
		case 22:
			rs = "$s6";
			break;
		case 23:
			rs = "$s7";
			break;
		case 24:
			rs = "$t8";
			break;
		case 25:
			rs = "$t9";
			break;
		case 26:
			rs = "$k0";
			break;
		case 27:
			rs = "$k1";
			break;
		case 28:
			rs = "$gp";
			break;
		case 29:
			rs = "$sp";
			break;
		case 30:
			rs = "$fp";
			break;
		case 31:
			rs = "$ra";
			break;
		default:
			rs = "N/A";
			break;
		}

		//Getting RT
		memcpy(temp4, temp, 16);
		rt = temp4;
		rt = rt+11;
		rt[5] = '\0';
		rtDec = binToDec(rt);

		switch(rtDec){
		case 0:
			rt = "$zero";
			break;
		case 1:
			rt = "$at";
			break;
		case 2:
			rt = "$v0";
			break;
		case 3:
			rt = "$v1";
			break;
		case 4:
			rt = "$a0";
			break;
		case 5:
			rt = "$a1";
			break;
		case 6:
			rt = "$a2";
			break;
		case 7:
			rt = "$a3";
			break;
		case 8:
			rt = "$t0";
			break;
		case 9:
			rt = "$t1";
			break;
		case 10:
			rt = "$t2";
			break;
		case 11:
			rt = "$t3";
			break;
		case 12:
			rt = "$t4";
			break;
		case 13:
			rt = "$t5";
			break;
		case 14:
			rt = "$t6";
			break;
		case 15:
			rt = "$t7";
			break;
		case 16:
			rt = "$s0";
			break;
		case 17:
			rt = "$s1";
			break;
		case 18:
			rt = "$s2";
			break;
		case 19:
			rt = "$s3";
			break;
		case 20:
			rt = "$s4";
			break;
		case 21:
			rt = "$s5";
			break;
		case 22:
			rt = "$s6";
			break;
		case 23:
			rt = "$s7";
			break;
		case 24:
			rt = "$t8";
			break;
		case 25:
			rt = "$t9";
			break;
		case 26:
			rt = "$k0";
			break;
		case 27:
			rt = "$k1";
			break;
		case 28:
			rt = "$gp";
			break;
		case 29:
			rt = "$sp";
			break;
		case 30:
			rt = "$fp";
			break;
		case 31:
			rt = "$ra";
			break;
		default:
			rt = "N/A";
			break;
		}

		//Getting RD
		memcpy(temp5, temp, 21);
		rd = temp5;
		rd = rd + 16;
		rd[5] = '\0';
		rdDec = binToDec(rd);

		switch(rdDec){
		case 0:
			rd = "$zero";
			break;
		case 1:
			rd = "$at";
			break;
		case 2:
			rd = "$v0";
			break;
		case 3:
			rd = "$v1";
			break;
		case 4:
			rd = "$a0";
			break;
		case 5:
			rd = "$a1";
			break;
		case 6:
			rd = "$a2";
			break;
		case 7:
			rd = "$a3";
			break;
		case 8:
			rd = "$t0";
			break;
		case 9:
			rd = "$t1";
			break;
		case 10:
			rd = "$t2";
			break;
		case 11:
			rd = "$t3";
			break;
		case 12:
			rd = "$t4";
			break;
		case 13:
			rd = "$t5";
			break;
		case 14:
			rd = "$t6";
			break;
		case 15:
			rd = "$t7";
			break;
		case 16:
			rd = "$s0";
			break;
		case 17:
			rd = "$s1";
			break;
		case 18:
			rd = "$s2";
			break;
		case 19:
			rd = "$s3";
			break;
		case 20:
			rd = "$s4";
			break;
		case 21:
			rd = "$s5";
			break;
		case 22:
			rd = "$s6";
			break;
		case 23:
			rd = "$s7";
			break;
		case 24:
			rd = "$t8";
			break;
		case 25:
			rd = "$t9";
			break;
		case 26:
			rd = "$k0";
			break;
		case 27:
			rd = "$k1";
			break;
		case 28:
			rd = "$gp";
			break;
		case 29:
			rd = "$sp";
			break;
		case 30:
			rd = "$fp";
			break;
		case 31:
			rd = "$ra";
			break;
		default:
			rd = "N/A";
			break;
		}

		//Getting Special
		memcpy(temp6, temp, 32);
		last6 = temp6;
		last6 = last6 + 26;
		last6[6] = '\0';

		//Getting immediate
		memcpy(temp7, temp, 32);
		imm = temp7;
		imm= imm + 16;
		imm[16] = '\0';
		immDec = binToDec(imm);


		memcpy(temp8, temp, 32);
		targ = temp8;
		targ = targ + 6;
		targ[26] = '\0';
		targDec = binToDec(targ);

		point = &hexNums[i];




		//Using the values calculated above to create an output
									if (strcmp(first6,"000000") == 0) { //Optcode if
									if (strcmp(last6, "100000") == 0) { //Special if
										strcpy(hexNums[i].action, "ADD");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rs, rd, rt);

									}
									else if (strcmp(last6,"100100") == 0) {
										strcpy(hexNums[i].action, "AND");
											printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
									else if (strcmp(last6, "011010") == 0) {
										strcpy(hexNums[i].action, "DIV");
										printf("Address: x%X  :  Instruction: %s   %s    %s\n",point, hexNums[i].action, rs, rt);

									}
									else if (strcmp(last6, "001000") == 0) {
										strcpy(hexNums[i].action, "JR");
										printf("Address: x%X  :  Instruction: %s   %s\n",point, hexNums[i].action, rs);

									}
									else if (strcmp(last6,"011000") == 0) {
										strcpy(hexNums[i].action, "MULT");
										printf("Address: x%X  :  Instruction: %s   %s    %s\n",point, hexNums[i].action, rs, rt);

									}
									else if (strcmp(last6,"000000") == 0) {
										strcpy(hexNums[i].action, "NOOP");
										printf("Address: x%X  :  Instruction: %s\n", point, hexNums[i].action);
									}
									else if (strcmp(last6,"100101") == 0) {
										strcpy(hexNums[i].action, "OR");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
									else if (strcmp(last6, "100111") == 0) {
										strcpy(hexNums[i].action, "NOR");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
									else if (strcmp(last6,"101010") == 0) {
										strcpy(hexNums[i].action, "SLT");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
									else if (strcmp(last6,"100010") == 0) {
										strcpy(hexNums[i].action, "SUB");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
									else  {
										strcpy(hexNums[i].action, "XOR");
										printf("Address: x%X  :  Instruction: %s   %s    %s   %s\n",point, hexNums[i].action, rd, rs, rt);

									}
							}
							else if  (strcmp(first6,"001000") == 0) {
								strcpy(hexNums[i].action, "ADDI");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "001100") == 0){
								strcpy(hexNums[i].action, "ANDI");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "000100") == 0){
								strcpy(hexNums[i].action, "BEQ");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "000101") == 0){
								strcpy(hexNums[i].action, "BNE");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "000010") == 0){
								strcpy(hexNums[i].action, "J");
								printf("Address: x%X  :  Instruction: %s   x%X\n",point, hexNums[i].action, targDec);
							}
							else if  (strcmp(first6, "000011") == 0){
								strcpy(hexNums[i].action, "JAL");
								printf("Address: x%X  :  Instruction: %s   x%X\n",point, hexNums[i].action, targDec);
							}
							else if  (strcmp(first6, "001111") == 0){
								strcpy(hexNums[i].action, "LUI");
								printf("Address: x%X  :  Instruction: %s   %s , x%X : Dec: %d\n",point, hexNums[i].action, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "100011") == 0){
								strcpy(hexNums[i].action, "LW");
								printf("Address: x%X  :  Instruction: %s   %s , x%X : Dec: %d\n",point, hexNums[i].action, rt, immDec, immDec);
							}
							else if  (strcmp(first6, "001101") == 0){
								strcpy(hexNums[i].action, "ORI");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "001010") == 0){
								strcpy(hexNums[i].action, "SLTI");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else if  (strcmp(first6, "101011") == 0){
								strcpy(hexNums[i].action, "SW");
								printf("Address: x%X  :  Instruction: %s   %s , x%X : Dec: %d\n",point, hexNums[i].action, rt, immDec, immDec);
							}
							else if  (strcmp(first6, "001110") == 0){
								strcpy(hexNums[i].action, "XORI");
								printf("Address: x%X  :  Instruction: %s   %s , %s , x%X : Dec: %d\n",point, hexNums[i].action, rs, rt, immDec, immDec);

							}
							else {
								strcpy(hexNums[i].action, "CANT FIND");
							}
						printf("\n");
	}

	printf("End Of Program");
}

//Binary to Decimal function
int binToDec(const char * str) {
    int decimal = 0;
    for (int i = strlen(str) - 1, j = 0; i >= 0; i--, j++) {
        int k = str[i] - '0';
        k <<= j;
        decimal += k;
    }
    return decimal;
}


