#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int j=1;

int binaryToInt(const char *binaryString) {
    int result = 0;
    int length = strlen(binaryString);

    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            result = (result << 1) | 1;
        } else if (binaryString[i] == '0') {
            result = result << 1;
        } else {
            printf("Invalid character in binary string: %c\n", binaryString[i]);
            return -1; 
        }
    }

    return result;
}
char* hexCharToBinary(char hexChar) {
    switch(hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A':
        case 'a': return "1010";
        case 'B':
        case 'b': return "1011";
        case 'C':
        case 'c': return "1100";
        case 'D':
        case 'd': return "1101";
        case 'E':
        case 'e': return "1110";
        case 'F':
        case 'f': return "1111";
        default:
            return NULL; 
    }
}

char* hexToBinary(const char* hex) {
    if (hex == NULL) {
        return NULL;
    }

    int hexLength = strlen(hex);
    int binaryLength = hexLength * 4; 
    char* binary = (char*)malloc(binaryLength + 1);

    if (binary == NULL) {
        return NULL; 
    }

    binary[binaryLength] = '\0';

    for (int i = 0; i < hexLength; i++) {
        char* binaryDigit = hexCharToBinary(hex[i]);
        if (binaryDigit == NULL) {
            free(binary);
            return NULL; 
        }
        strcat(binary, binaryDigit); 
    }

    return binary;
}
void R(char* binaryValue) {
    char funct7[8], rs2[6], rs1[6], funct3[4], rd[6], opcode[8];
    
        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
        
        strncpy(funct7, binaryValue, 7);
        funct7[7] = '\0';

        strncpy(rs2, binaryValue + 7, 5);
        rs2[5] = '\0';

        strncpy(rs1, binaryValue + 12, 5);
        rs1[5] = '\0';

        strncpy(funct3, binaryValue + 17, 3);
        funct3[3] = '\0';

        strncpy(rd, binaryValue + 20, 5);
        rd[5] = '\0';
    
    char* ins = NULL;

    if (strcmp(funct3, "000") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "add";
        else if (strcmp(funct7, "0100000") == 0) ins = "sub";
    }
    else if (strcmp(funct3, "001") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "sll";
    }
    else if (strcmp(funct3, "100") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "xor";
    }
    else if (strcmp(funct3, "101") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "srl";
        else if (strcmp(funct7, "0100000") == 0) ins = "sra";
    }
    else if (strcmp(funct3, "110") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "or";
    }
    else if (strcmp(funct3, "111") == 0) {
        if (strcmp(funct7, "0000000") == 0) ins = "and";
    }

    if (ins != NULL) {
        printf("%s x%d, x%d, x%d\n", ins, binaryToInt(rd), binaryToInt(rs1), binaryToInt(rs2));
    }
}

void I(char* binaryValue) {
    char opcode[8];
    char rd[6];
    char funct3[4];
    char rs1[6];
    char imm[13];

        strncpy(imm, binaryValue , 12);
        imm[12] = '\0';
        
        strncpy(rs1, binaryValue+12, 5);
        rs1[5] = '\0';

        strncpy(funct3, binaryValue + 17, 3);
        funct3[3] = '\0';

        strncpy(rd, binaryValue + 20, 5);
        rd[5] = '\0';

        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';


    char* ins = NULL;
    if (strcmp(opcode, "0010011") == 0){
    if (strcmp(funct3, "000") == 0) ins = "addi";
    else if (strcmp(funct3, "100") == 0) ins = "xori";
    else if (strcmp(funct3, "110") == 0) ins = "ori";
    else if (strcmp(funct3, "111") == 0) ins = "andi";
    else if (strcmp(funct3, "001") == 0) ins = "slli";
    else if (strcmp(funct3, "001") == 0) {
        if (imm[0] == '1') ins = "srai";
        else ins = "srli";
    }}
    else if(strcmp(opcode, "0000011") == 0){
    if (strcmp(funct3, "000") == 0) ins = "lb";
    else if (strcmp(funct3, "001") == 0) ins = "lh";
    else if (strcmp(funct3, "010") == 0) ins = "lw";
    else if (strcmp(funct3, "011") == 0) ins = "ld";
    else if (strcmp(funct3, "100") == 0) ins = "lbu";
    else if (strcmp(funct3, "110") == 0) ins = "lhu";
    else if (strcmp(funct3, "111") == 0) ins = "lwu";
}else if(strcmp(opcode, "1100111") == 0){
  ins = "jalr";
}
    if (ins != NULL) {
        printf("%s x%d, x%d, %d\n", ins, binaryToInt(rd), binaryToInt(rs1), binaryToInt(imm));
    }
}


void S(char* binaryValue) {
    char imm[13], rs2[6], rs1[6], funct3[4], opcode[8];
    
        strncpy(imm, binaryValue , 7);
        strncpy(imm+7,binaryValue+20, 5);
        imm[12] = '\0';
        
        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
        
        strncpy(rs2, binaryValue + 7, 5);
        rs2[5] = '\0';

        strncpy(rs1, binaryValue + 12, 5);
        rs1[5] = '\0';

        strncpy(funct3, binaryValue + 17, 3);
        funct3[3] = '\0';

    char* ins = NULL;

    if (strcmp(funct3, "000") == 0) ins = "sb";
    else if (strcmp(funct3, "001") == 0) ins = "sh";
    else if (strcmp(funct3, "010") == 0) ins = "sw";
    else if (strcmp(funct3, "011") == 0) ins = "sd";
    if (ins != NULL) {
        printf("%s x%d, %d(x%d)\n", ins, binaryToInt(rs2), binaryToInt(imm), binaryToInt(rs1));
    }
}


int B(char* binaryValue, int pc) {
    char imm[14], rs2[6], rs1[6], funct3[4], opcode[8];
    
        strncpy(imm, binaryValue , 1);
        strncpy(imm+1, binaryValue+24 ,1);
        strncpy(imm+2,binaryValue+1, 6);
        strncpy(imm+8,binaryValue+20, 4);
        imm[12]='0';
        imm[13] = '\0';
        
        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
        
        strncpy(rs2, binaryValue + 7, 5);
        rs2[5] = '\0';

        strncpy(rs1, binaryValue + 12, 5);
        rs1[5] = '\0';

        strncpy(funct3, binaryValue + 17, 3);
        funct3[3] = '\0';

    char* ins = NULL;

    if (strcmp(funct3, "000") == 0) ins = "beq";
    else if (strcmp(funct3, "001") == 0) ins = "bne";
    else if (strcmp(funct3, "100") == 0) ins = "blt";
    else if (strcmp(funct3, "101") == 0) ins = "bge";
    else if (strcmp(funct3, "110") == 0) ins = "bltu";
    else if (strcmp(funct3, "111") == 0) ins = "bgeu";

    if (ins != NULL) {
        printf("%s x%d, x%d, L%d\n", ins, binaryToInt(rs1), binaryToInt(rs2),  j);
    }
    return pc+binaryToInt(imm);
}


void J(char* binaryValue, int pc) {
    char opcode[8];
    char rd[6];
    char imm[21];
        strncpy(imm, binaryValue , 1);
        strncpy(imm+1, binaryValue + 12, 8);
        strncpy(imm+9, binaryValue + 11, 1);
        strncpy(imm+10, binaryValue +1, 10);
        imm[20] = '\0';
        
        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
        
        strncpy(rd, binaryValue + 20, 5);
        rd[5] = '\0';

    char* ins = NULL;

    if (strcmp(opcode, "1101111") == 0) ins = "jal";
    

    if (ins != NULL) {
        printf("%s x%d, L%d\n", ins, binaryToInt(rd), j);
    }
}

void U(char* hexValue){
   char* binaryValue = hexToBinary(hexValue);
   char* ins = NULL;
    char opcode[8];
    char rd[6];
    char imm[7];
        strncpy(imm, hexValue , 5);  
        imm[6] = '\0';
        
        strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
        
        strncpy(rd, binaryValue + 20, 5);
        rd[5] = '\0';   
   if (strcmp(opcode, "0110111") == 0) ins = "lui";
     
       if (ins != NULL) {
        printf("%s x%d ,0x%s  \n", ins, binaryToInt(rd),imm);
    }
}


int main() {
   char hexValues[][9] = {
    "007201b3","00720863","00c0006f","00533623","100004b7",  "00c50493"
    };
    
    int pc = 0;
    int level =-1;
    char* binaryValue;
    for (int i = 0; i < 6; i++) {
        binaryValue = hexToBinary(hexValues[i]);
        char opcode[8];
        
       strncpy(opcode, binaryValue + 25, 7);
        opcode[7] = '\0';
       if(pc == level){
       printf("L1: ");
       j++;}
         if (strcmp(opcode, "0110011") == 0) {
            R(binaryValue);
        }else if (strcmp(opcode, "0010011") == 0 || strcmp(opcode, "0000011") == 0 || strcmp(opcode, "1100111") == 0) {
            I(binaryValue);
        }else if (strcmp(opcode, "0100011") == 0) {
            S(binaryValue);
        }
        else if (strcmp(opcode, "1100011") == 0) {
           level= B(binaryValue, pc);
        }
        else if (strcmp(opcode, "1101111") == 0 ) {
           J(binaryValue, pc);
        }else if (strcmp(opcode, "0110111") == 0) {
           U(hexValues[i]);
        }
        else {
            printf("Unknown instruction\n");
        }

       pc += 4;
    }
    

    return 0;



        free(binaryValue);
}