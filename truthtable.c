#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    char name[20];
    int value;
    char type[20];
} node; 

typedef struct{
    char operation[20];
    char left[20];
    char right[20];
    char output[20];
    node* selector; 
    node* inputs;
    int sel;
} logicGate;

int size = 0; 
int logicSize = 0;

int power(int x){
    int total = 1; 
    for(int i = 0; i < x; i++){
        total*=2;
    }
    return total;
}

void printDict(node* array){
    for(int i = 0; i < size; i++){
        printf("%s %d\n", array[i].name, array[i].value);
        
    }
}

void printGate(logicGate* array){
    for(int i = 0; i < logicSize; i++){
        printf("Operation: %s\nleft: %s\nright: %s\noutput: %s\n", array[i].operation, array[i].left, array[i].right, array[i].output);
        printf("Inputs: ");
        int x = power(array[i].sel);
        for(int j = 0; j < array[i].sel; j++){
            printf("%s ", array[i].inputs[j].name);
        }
        printf("\n");
        printf("Selectors: ");
        for(int j = 0; j < x; j++){
            printf("%s ", array[i].selector[j].name);
        }
        printf("\n");
    }
}

int** mallocArray(int rows, int cols){
    int **matrix = (int**)malloc(rows*sizeof(int*));
    for(int i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(cols*sizeof(int));
    }
    return matrix;
}

void printArray(int** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeArray(int** array, int rows){
    for (int i = 0; i < rows; i++){
        free(array[i]);
    }
    free(array);
}

int find(node *array, char *x){
    for(int i = 0; i < size; i++){
        int res = strcmp(array[i].name, x);
        if (res == 0){
            return i;
        }
    }
    return -1;
}

void insertDict(node* array, char* in){
    strcpy(array[size].name, in);
    strcpy(array[size].type, "TEMP");
    size+=1; 
}

void and(node* dict, char* left, char* right, char* out){
    int findIndexLeft = find(dict, left);
    if(findIndexLeft == -1){
        insertDict(dict, left);
        dict[size-1].value = atoi(left);
        findIndexLeft = size-1;
    }
    int findIndexRight = find(dict, right);
    if(findIndexRight == -1){
        insertDict(dict, right);
        dict[size-1].value = atoi(right);
        findIndexRight = size-1;
    }
    int findIndexOut = find(dict, out);
    if(findIndexOut == -1){
        insertDict(dict, out);
        findIndexOut = size-1;
    }

    //edgecase
    if(findIndexLeft == -1 || findIndexRight == -1){
        printf("The node you were looking for does not exist.");
        return;
    }

    if(dict[findIndexLeft].value == 1 && dict[findIndexRight].value == 1){
        dict[findIndexOut].value = 1;
    }
    else{
        dict[findIndexOut].value = 0;
    }
}

void or(node* dict, char* left, char* right, char* out){
    int findIndexLeft = find(dict, left);
    if(findIndexLeft == -1){
        insertDict(dict, left);
        dict[size-1].value = atoi(left);
        findIndexLeft = size-1;
    }
    int findIndexRight = find(dict, right);
    if(findIndexRight == -1){
        insertDict(dict, right);
        dict[size-1].value = atoi(right);
        findIndexRight = size-1;
    }
    int findIndexOut = find(dict, out);
    if(findIndexOut == -1){
        insertDict(dict, out);
        findIndexOut = size-1;
    }
    
    //edgecase
    if(findIndexLeft == -1 || findIndexRight == -1){
        printf("The node you were looking for does not exist.");
        return;
    }

    if(dict[findIndexLeft].value == 1 || dict[findIndexRight].value == 1){
        dict[findIndexOut].value = 1;
    }
    else{
        dict[findIndexOut].value = 0;
    }
}

void xor(node* dict, char* left, char* right, char* out){
    int findIndexLeft = find(dict, left);
    if(findIndexLeft == -1){
        insertDict(dict, left);
        dict[size-1].value = atoi(left);
        findIndexLeft = size-1;
    }
    int findIndexRight = find(dict, right);
    if(findIndexRight == -1){
        insertDict(dict, right);
        dict[size-1].value = atoi(right);
        findIndexRight = size-1;
    }
    int findIndexOut = find(dict, out);
    if(findIndexOut == -1){
        insertDict(dict, out);
        findIndexOut = size-1;
    }
    
    //edgecase
    if(findIndexLeft == -1 || findIndexRight == -1){
        printf("The node you were looking for does not exist.");
        return;
    }

    if(dict[findIndexLeft].value == 1 && dict[findIndexRight].value == 1){
        dict[findIndexOut].value = 0;
    }
    else if(dict[findIndexLeft].value == 1 || dict[findIndexRight].value == 1){
        dict[findIndexOut].value = 1;
    }
    else{
        dict[findIndexOut].value = 0;
    }
}

void nand(node* dict, char* left, char* right, char* out){
    int findIndexLeft = find(dict, left);
    if(findIndexLeft == -1){
        insertDict(dict, left);
        dict[size-1].value = atoi(left);
        findIndexLeft = size-1;
    }
    int findIndexRight = find(dict, right);
    if(findIndexRight == -1){
        insertDict(dict, right);
        dict[size-1].value = atoi(right);
        findIndexRight = size-1;
    }
    int findIndexOut = find(dict, out);
    if(findIndexOut == -1){
        insertDict(dict, out);
        findIndexOut = size-1;
    }

    //edgecase
    if(findIndexLeft == -1 || findIndexRight == -1){
        printf("The node you were looking for does not exist.");
        return;
    }

    if(dict[findIndexLeft].value == 1 && dict[findIndexRight].value == 1){
        dict[findIndexOut].value = 0;
    }
    else{
        dict[findIndexOut].value = 1;
    }
}



void not(node* dict, char* left, char* out){
    int findIndexLeft = find(dict, left);
    if(findIndexLeft == -1){
        insertDict(dict, left);
        dict[size-1].value = atoi(left);
        findIndexLeft = size-1;
    }
    int findIndexOut = find(dict, out);
    if(findIndexOut == -1){
        insertDict(dict, out);
        findIndexOut = size-1;
    }

    //edgecase
    if(findIndexLeft == -1){
        printf("The node you were looking for does not exist.");
        return;
    }

    if(dict[findIndexLeft].value == 1){
        dict[findIndexOut].value = 0;
    }
    else{
        dict[findIndexOut].value = 1;
    }
}

void combination(int** table, int rows, int cols){
    int x = rows; 
    int y = 1; 
    int j = 0; 

    for(int a = 0; a < cols; a++){ //runs 5 times 
        x = x/2;
        for(int m = 0; m < y; m++){
            for(int n = 0; n < x; n++){
                table[j][a] = 0;
                j++;
            }
            for(int n = 0; n < x; n++){
                table[j][a] = 1;
                j++;
            }
        }
        j = 0; 
        y = y*2;
    }
}

int notM(int x){
    if(x == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int andM(int x, int y){
    if(x == 1 && y == 1){
         return 1;
    }
    else{
        return 0;
    }
}

int orM(int x, int y){
    if(x == 0 && y == 0){
         return 0;
    }
    else{
        return 1;
    }
}

int multiplexer(node* dict, node* D, node* S, int** array, int rows, int cols){
    combination(array, rows, cols);
    //printArray(array, rows, cols);
    int lastOutput; 
    int currentOutput;
    for(int i = 0; i < rows; i++){
        if(strcmp(D[i].name, "0") == 0 || strcmp(D[i].name, "1") == 0){
            currentOutput = atoi(D[i].name);
        }
        else{
            int x = find(dict, D[i].name);
            currentOutput = dict[x].value;
        }
        for(int j = 0; j < cols; j++){
            int x = find(dict, S[j].name);
            int select = dict[x].value;
            if(array[i][j] == 0){
                select = notM(select);
            } 
            currentOutput = andM(currentOutput, select);
        }
        
        if(i == 0){
            lastOutput = currentOutput;
        }
        else{
            lastOutput = orM(lastOutput, currentOutput);
        }
    }
    return lastOutput;
}

void decoder(node* dict, node* inp, node* outp, int** array, int rows, int cols){
    combination(array, rows, cols);

    int x; 
    int currentOutput;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(j == 0){
                x = find(dict, inp[j].name);
                if(array[i][j] == 0){
                    currentOutput = notM(dict[x].value);
                }else{
                    currentOutput = dict[x].value;
                }
            }else{
                x = find(dict, inp[j].name);
                int cmp = dict[x].value;
                if(array[i][j] == 0){
                    cmp = notM(cmp);
                }
                currentOutput = andM(currentOutput, cmp);
            }
        }
        x = find(dict, outp[i].name);
        if(x == -1){
            insertDict(dict, outp[i].name);
            x = size-1;
        }
        dict[x].value = currentOutput;

    }
}


logicGate* mallocGate(){
    logicGate* gate = (logicGate*)malloc(50 * sizeof(logicGate));
    for(int i = 0; i < 50; i++){
        gate[i].inputs = (node*)malloc(50 * sizeof(node));
        gate[i].selector = (node*)malloc(50 * sizeof(node));
    }
    return gate;
}

void freeGate(logicGate* gate){
    for(int i = 0; i < 50; i++){
        free(gate[i].inputs);
        free(gate[i].selector); 
    }
    free(gate);
}



//void decoder(node* dict, node* input, node selector){}

int main(int argc, char** argv){
    
    node* dictionary = (node*)malloc(50 * sizeof(node));
    logicGate* gate = mallocGate();
    //(logicGate*)malloc(50 * sizeof(logicGate)); 
    
    //open file
    FILE *file = fopen(argv[1], "r");
    if(file == NULL ){
        exit(EXIT_FAILURE);
    }

    //gets first line: INPUT
    char str[16];
    fscanf(file, "%s", str);
    int numOfIn; 
    fscanf(file, "%d", &numOfIn);
    char in[16];
    for(int i = 0; i < numOfIn; i++){
        fscanf(file, "%s", in);
        strcpy(dictionary[i].name, in);
        strcpy(dictionary[i].type, "INPUT");
        size++;
    }

    //gets second line: OUTPUT
    fscanf(file, "%s", str);
    int numOfOut; 
    fscanf(file, "%d", &numOfOut);
    char out[16];
    int s = size;
    for(int i = s; i < numOfOut + s; i++){
        fscanf(file, "%s", out);
        strcpy(dictionary[i].name, out);
        strcpy(dictionary[i].type, "OUTPUT");
        size++;
    }
    
    //create logicGate structure 
    while (fscanf(file, "%s", str) != EOF) {
        if(strcmp(str, "AND") == 0 || strcmp(str, "NAND") == 0 || strcmp(str, "OR") == 0 || strcmp(str, "XOR") == 0 || strcmp(str, "NOR") == 0){
            strcpy(gate[logicSize].operation, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].right, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].output, str);
            logicSize+=1;
        }
        if(strcmp(str, "NOT") == 0 || strcmp(str, "PASS") == 0){
            strcpy(gate[logicSize].operation, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].output, str);
            logicSize+=1;
        }
        if(strcmp(str, "MULTIPLEXER") == 0){
            strcpy(gate[logicSize].left, "null");
            strcpy(gate[logicSize].right, "null");
            //printf("operation: %s \n", str);
            strcpy(gate[logicSize].operation, str);
            int numOfSelector = 0; 
            fscanf(file, "%d", &numOfSelector);
            //printf("numofSelector: %d \n", numOfSelector);
            gate[logicSize].sel = numOfSelector;
            int y = power(numOfSelector);
            char word[20];
            //printf("Inputs: ");
            for(int i = 0; i < y; i++){
                fscanf(file, "%s", word);
                //printf("%s ", word);
                strcpy(gate[logicSize].inputs[i].name, word);
            }
            //printf("\nselectors: ");
            for(int i = 0; i < numOfSelector; i++){
                fscanf(file, "%s", word);
                //printf("%s ", word);
                strcpy(gate[logicSize].selector[i].name, word);
            }
            //printf("\noutputs: ");
            fscanf(file, "%s", str);
            //printf("%s \n", str);
            strcpy(gate[logicSize].output, str);
            logicSize+=1;
        }
        if(strcmp(str, "DECODER") == 0){
            strcpy(gate[logicSize].left, "null");
            strcpy(gate[logicSize].right, "null");
            strcpy(gate[logicSize].output, "null");
            strcpy(gate[logicSize].operation, str);
            int numOfSelector = 0; 
            fscanf(file, "%d", &numOfSelector);
            gate[logicSize].sel = numOfSelector;
            char word[20];
            for(int i = 0; i < numOfSelector; i++){
                fscanf(file, "%s", word);
                strcpy(gate[logicSize].inputs[i].name, word);
            }
            int y = power(numOfSelector);
            for(int i = 0; i < y; i++){
                fscanf(file, "%s", word);
                strcpy(gate[logicSize].selector[i].name, word);
            }
            logicSize+=1;
        }
        if(strcmp(str, "PASS") == 0){
            strcpy(gate[logicSize].operation, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].left, str);
            fscanf(file, "%s", str);
            strcpy(gate[logicSize].output, str);


        }
    }
    
    int rows = power(numOfIn);
    int cols = numOfIn; 
    int** table = mallocArray(rows, cols);
    combination(table, rows, cols);

    for(int i = 0; i < rows; i++){ //runs each row
        for(int j = 0; j < cols; j++){ //inserts value from table into dictionary 
            dictionary[j].value = table[i][j];
            printf("%d ", table[i][j]);
        }
        printf("|");
        for(int j = 0; j < logicSize; j++){ //runs one operation from logic gate 
            if(strcmp(gate[j].operation, "AND") == 0){
                and(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if(strcmp(gate[j].operation, "NAND") == 0){
                nand(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if(strcmp(gate[j].operation, "OR") == 0){
                or(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if(strcmp(gate[j].operation, "XOR") == 0){
                xor(dictionary, gate[j].left, gate[j].right, gate[j].output);
            }
            if(strcmp(gate[j].operation, "NOT") == 0){
                not(dictionary, gate[j].left, gate[j].output);
            }
            if(strcmp(gate[j].operation, "NOR") == 0){
                or(dictionary, gate[j].left, gate[j].right, gate[j].output);
                not(dictionary, gate[j].left, gate[j].output);
            }
            if(strcmp(gate[j].operation, "MULTIPLEXER") == 0){
                int c = gate[j].sel;
                int r = power(c);
                int** arr = mallocArray(r, c);
                int i = multiplexer(dictionary, gate[j].inputs, gate[j].selector, arr, r, c);
                int dicti = find(dictionary, gate[j].output);
                if(dicti == -1){
                    insertDict(dictionary, gate[j].output);
                    dicti = size-1;
                }
                dictionary[dicti].value = i;
                //printf("The value of %s is %d\n", dictionary[dicti].name, dictionary[dicti].value);
                freeArray(arr, r);
            }
            if(strcmp(gate[j].operation, "DECODER") == 0){
                int c = gate[j].sel;
                int r = power(c);
                int** arr = mallocArray(r, c);
                decoder(dictionary, gate[j].inputs, gate[j].selector, arr, r, c);
                //printf("The value of %s is %d\n", dictionary[dicti].name, dictionary[dicti].value);
                freeArray(arr, r);
            }
            if(strcmp(gate[j].operation, "PASS") == 0){
                int xIn = find(dictionary, gate[j].left);
                if(xIn == -1){
                    insertDict(dictionary, gate[j].left);
                    xIn = size-1;
                }
                int xOut = find(dictionary, gate[j].output);
                if(xOut == -1){
                    insertDict(dictionary, gate[j].output);
                    xOut = size-1;
                }
                dictionary[xOut].value = dictionary[xIn].value;


            }
            

        }

        for(int i = 0; i < size; i++){
            if(strcmp(dictionary[i].type, "OUTPUT") == 0){
                printf(" %d", dictionary[i].value);
            }
        }

        printf("\n");

    }

    freeArray(table, rows);
    free(dictionary);
    freeGate(gate);
    fclose(file);
    
    
}