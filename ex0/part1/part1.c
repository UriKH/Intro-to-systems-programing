#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
} bool;

/**
 * Free a char type double pointer
 * @param dptr: double pointer to free
 * @param len: len of array the double pointer represents 
*/
void free_char_dptr(char **, size_t);

/**
 * Calculate the power (n) of a number that is in the format: num = 2^n
 * @param num: the number to calculate its log2
 * @returns -1 for non positive numbers or numbers not in format else n
 */
int is_log2(double);

/**
 * Check if the line contains only space like characters
 * @param line: the given string to check
 * @returns 1 if true else 0
*/
bool is_empty_line(char *);

/**
 * Read a line (until the \n character) from stdin
 * @returns the line
*/
char *readLine();

/**
 * Splits a given string by the spaces in it
 * @param line: the give string to split
 * @param num_pieces: pointer to the number of strings in the output 
 * (the pointer will be asigned a value in the function)
 * @returns a list of pointers of len 'num_strings' with all the pieces of the split
*/
char **split_spaces(char *, int *);

/**
 * Convert a series of strings to integers
 * @param strings: the list of strings to convert
 * @param num_pieces: the length of the list
 * @return the list of integers if successful, else NULL
 */
int *strings_to_nums(char **, int);



void free_char_dptr(char **dptr, size_t len){
    for (size_t i = 0; i < len; i++)
        free(dptr[i]);
    free(dptr);
}

int is_log2(double num)
{
    static int power = 0;

    if (num == 1){
        int temp = power;
        power = 0;
        return temp;
    }
    if (num < 2){
        power = 0;
        return -1;
    }
    power++;
    return is_log2(num / 2);
}

bool is_empty_line(char *line){
    for (int i = 0; i < strlen(line); i++){
        if (!isspace(line[i]))
            return FALSE;
    }
    return TRUE;
}

char *readLine(){
    int size = 1;
    char *line = (char *)malloc(size * sizeof(char));
    char curr_ch;
    int last_ch = 0;
    int first_ch = 0;

    while (TRUE){
        scanf("%c", &curr_ch);

        if (curr_ch == '\n') 
            break;
        
        line[size - 1] = curr_ch;
        if (!isspace(curr_ch)) // find index of last non space like char in the string
            last_ch = size - 1;
        
        size++;
        line = (char *)realloc(line, size * sizeof(char));
    }

    while (isspace(line[first_ch])) // find index of first non space like char in the string
        first_ch++;

    memcpy(line, line + first_ch, (last_ch - first_ch + 2) * sizeof(char)); // copy only the 
    line[last_ch - first_ch + 1] = '\0';
    return line;
}

char** split_spaces(char *line, int *num_pieces){
    *num_pieces = 1;
    int curr_str_size = 1;
    char **pieces = (char **)malloc(*num_pieces * sizeof(char*));
    pieces[*num_pieces - 1] = (char *)malloc(curr_str_size * sizeof(char));
    bool single_space = TRUE; // flag if only one space between inputs have been used

    for (int i = 0; i < strlen(line); i++)
    {
        if (isspace(line[i]))
        {
            if (single_space)
            { // prepare for the creation of a new piece
                pieces[*num_pieces - 1][curr_str_size - 1] = '\0';
                curr_str_size = 1;
                pieces = (char **)realloc(pieces, ++(*num_pieces) * sizeof(char*));
                pieces[*num_pieces - 1] = (char *)malloc(curr_str_size * sizeof(char));
            }
            single_space = FALSE;
            continue;
        }
        // add a character to the piece
        single_space = TRUE;
        pieces[*num_pieces - 1][curr_str_size - 1] = line[i];
        pieces[*num_pieces - 1] = (char *)realloc(pieces[*num_pieces - 1], ++curr_str_size * sizeof(char));
    }
    pieces[*num_pieces - 1][curr_str_size - 1] = '\0';
    return pieces;
}

int *strings_to_nums(char **strings, int num_pieces){
    int *nums = (int *)malloc(num_pieces * sizeof(int));

    for (int i = 0, j; i < num_pieces; i++){
        j = 0;
        while (strings[i][j] != '\0'){
            if (!isdigit(strings[i][j]) && !(strings[i][j] == '-' && j == 0)){
                free(nums);
                return NULL;
            }
            j++;
        }
        
        nums[i] = atoi(strings[i]);
    }
    return nums;
}

int main(){
    int line_param_cnt = 0;
    char *line, **pieces;    
    
    int *dec_pieces;
    bool error_found = FALSE;

    // receive the number of inputs from the user
    printf("Enter size of input:\n");

    // read line and translate the parameters into integers
    do {
        line = readLine();
        pieces = split_spaces(line, &line_param_cnt);
        dec_pieces = strings_to_nums(pieces, line_param_cnt);
    } while (is_empty_line(line));

    free(line);
    free_char_dptr(pieces, line_param_cnt);

    // if a non positive number received -> error
    if (dec_pieces == NULL || dec_pieces[0] < 1)
    {
        if (dec_pieces != NULL)
            free(dec_pieces);
        printf("Invalid size\n");
        return 0;
    }

    // get user inputs - line by line
    printf("Enter numbers:\n");

    int inputs_requiered = dec_pieces[0]; 
    int nums[(const int)inputs_requiered];
    free(dec_pieces);

    int i = 0;
    while (i < inputs_requiered)
    {
        // read line and translate the parameters into integers
        line = readLine();
        if (is_empty_line(line)){
            free(line);
            continue;
        }
        pieces = split_spaces(line, &line_param_cnt);
        dec_pieces = strings_to_nums(pieces, line_param_cnt);
        free(line);
        free_char_dptr(pieces, line_param_cnt);

        if (dec_pieces == NULL){
            error_found = TRUE;
            break;
        }

        if (i += line_param_cnt >= inputs_requiered) // make sure excess params are being ignored
            line_param_cnt = inputs_requiered - i;

        // move the decimal parameters from the line to the numbers list
        for (int j = 0; j < line_param_cnt; j++)
            nums[i + j] = dec_pieces[j];
        i += line_param_cnt;
        free(dec_pieces);
    }

    // exit if one of the inputs was not a number
    if (error_found){
        printf("Invalid number\n");
        return 0;
    }

    // check which numbers are in foramt and sum the powers
    int power, sum = 0;
    for (int i = 0; i < inputs_requiered; i++)
    {
        if (nums[i] < 1)
            continue;
        power = is_log2(nums[i]);
        if (power != -1){
            printf("The number %d is a power of 2: %d = 2^%d\n", nums[i], nums[i], power);
            sum += power;
        }
    }
    printf("Total exponent sum is %d\n", sum);
    return 0;
}