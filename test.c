#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// bool validate_input(double *input, const char *msg)
// {
//     double temp;

//     if (scanf("%lf", &temp))
//     {
//         if (floor(temp) == temp)
//         {
//             *input = temp;
//             return true;
//         }
//     }

//     printf("%s\n", msg);
//     return false;
// }
int *validate_many(double *input, const char *msg);
int validate_input(double *input, const char *msg);
int count_digits(int number);

char *readline()
{
    char *buffer = (char *)calloc(1, sizeof(char));

    int ind = 0;
    while (true)
    {
        buffer[ind] = getchar();
        buffer = (char *)realloc(buffer, ind + 2);
        buffer[ind + 1] = '\0';
        ind++;
    }
    return buffer;
}

int count_digits(int number)
{
    int digits = 0;
    if (number < 0)
        number *= -1;
    
    while (number != 0){
        number /= 10;
        digits++;
    }
    return digits;
}

int* validate_many(double *input, const char *msg){
    char *line = readline();
    int *numbers = (int *)calloc(2, sizeof(int));
    int cnt = 0, val;
    
    int i = 0;
    int j = 0;
    while (true)
    {
        char temp_num[64] = "";
        bool found_ch = false;
        j = 0;
        while (line[i] != '\0'){
            if (line[i] != ' '){
                if (found_ch)
                    break;
                i++;
                continue;
            }

            temp_num[j] = line[i];
            j++;
            i++;
        }
        
        val = validate_input(input, msg);
        numbers[cnt + 1] = *input;
        cnt++;
        numbers = (int *)realloc(numbers, cnt + 2);

        if (val == 0)
            return NULL;
        else if (val == 1)
            break;
    }
    numbers[0] = cnt;
    return numbers;
}


int validate_input(double *input, const char *msg)
{
    char *buffer = (char *)calloc(1, sizeof(char));

    int ind = 0;
    int ret_val = 1;
    while (true)
    {
        buffer[ind] = getchar();
        if (buffer[ind] == '\n' || buffer[ind] == ' ')
        {
            buffer[ind] = '\0';
            if (buffer[ind] == ' '){
                ret_val = -1;
                break;
            }
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
        (number < 0 && (strlen(buffer) -1 != count_digits(number))))
    {
        printf("%s\n", msg);
        return 0;
    }
    *input = number;
    return ret_val;
}

int main(){
    // double* temp = (double *)malloc(sizeof(double));
    // int *numbers = validate_many(temp, "false");
    // if (numbers == NULL){
    //     printf("error");
    // }
    // for (int i = 0; i < numbers[0]; i++){
    //     printf("%d ", numbers[i + 1]);
    // }
    // printf("\n");

    int x;
    scanf("%d", &x);
    printf("%d", x);

    // int out = scanf("%lf", &temp);
    // if (out){
    //     printf("True\n");
    // }
    // else{
    //     printf("False\n");
    // }
    // printf("number: %lf\nscanf output: %d", temp, out);
}