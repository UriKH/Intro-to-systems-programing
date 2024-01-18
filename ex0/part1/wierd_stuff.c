#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* mtm_tot() detects numbers of the form: num = 2^n when n is
 * a natural number, and then prints the sum of all powers of
 * the aforementioned format.
 */
void mtm_tot();

/* check if an input given by the user is a whole number.
 * @param input: pointer to where to save the number
 * @param msg: the error message
 * @return true if the input given by user is a whole number else false
 */
bool validate_input(double*, const char *);

int main()
{
    mtm_tot();
    return 0;
}

int count_digits(int number)
{
    int digits = 0;
    if (number < 0)
        number *= -1;

    while (number != 0)
    {
        number /= 10;
        digits++;
    }
    return digits;
}

bool validate_input(double *input, const char *msg)
{
    char *buffer = (char *)calloc(1, sizeof(char));

    int ind = 0;
    while (true)
    {
        buffer[ind] = getchar();
        if (buffer[ind] == '\n')
        {
            buffer[ind] = '\0';
            if (strlen(buffer) == 0)
                continue;
            break;
        }

        buffer = (char *)realloc(buffer, ind + 2);
        buffer[ind + 1] = '\0';
        ind++;
    }

    int number = atoi(buffer);
    if ((number == 0 && buffer[0] != '0') ||
        (number > 0 && (strlen(buffer) != count_digits(number))) ||
        (number < 0 && (strlen(buffer) - 1 != count_digits(number))))
    {
        printf("%s\n", msg);
        return false;
    }
    *input = number;
    return true;
}

void mtm_tot(){
    // utility type - a power of two
    typedef struct {
        int number;
        int power;
    } pow_of_2;

    double *inputs = (double *)malloc(sizeof(double)); // number of inputs
    
    printf("Enter size of input:\n");
    if (!validate_input(inputs, "Invalid size\n")){
        free(inputs);
        return;
    }

    if (*inputs <= 0) // number of inputs must be positive 
    {
        printf("Invalid size\n");
        free(inputs);
        return;
    }

    double *curr_num = (double *)malloc(sizeof(double));
    double log2_num;
    int sum = 0, cnt = 0;
    pow_of_2 powers_of_2[(const int)*inputs]; // array for saving numbers of the form: num = 2^n

    printf("Enter numbers:\n");

    for (int i = 0; i < *inputs; i++){
        // get numbers from the user and validate them
        if(!validate_input(curr_num, "Invalid number\n")){
            free(curr_num);
            free(inputs);
            return;
        }
        
        // check if the number is in format
        log2_num = log2(*curr_num);
        if (log2_num == floor(log2_num) && log2_num >= 0)
        {
            powers_of_2[cnt].number = (int)*curr_num;
            powers_of_2[cnt].power = (int)log2_num;
            cnt++;
        }
    }

    // print results
    for (int i = 0; i < cnt; i++){
        printf("The number %d is a power of 2: %d = 2^%d\n",
               powers_of_2[i].number, powers_of_2[i].number, powers_of_2[i].power);
        sum += powers_of_2[i].power;
    }

    printf("Total exponent sum is %d\n", sum);
    free(curr_num);
    free(inputs);
    return;
}