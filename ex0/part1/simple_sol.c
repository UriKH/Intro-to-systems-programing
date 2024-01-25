#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ------- declerations -------

/** checks if a log2 of a number is a natural number
 * @param number: number to check
 * @returns returns the exponent else, -1
*/
int isPowerOf2(double);

/** reads an integer from stdin
 * @param message: input request message
 * @returns the number given by the user
*/
int readSize(const char*);

/** reads a specified amount of integers from stdin
 * @param size: amount of integers to read
 * @param message: input request message
 * @param errorMessage: error message (if user input not valid)
 * @returns numbers given by the user 
*/
int* readNumbers(int, const char*, const char*);

/** sum all exponents of numbers fulfilling: log2(number) = natural number
 * @param size: amount of numbers to check
 * @param numbers: numbers to check
 * @param print: print a message if a number fulfils the condition
 * @returns the sum of exponents
*/
int sumExponentsOf2Powers(int, int*, bool);

// ------- defenitions -------

int isPowerOf2(double number){
    int power = 0;

    while (true){
        if (number == 1){
            return power;
        }
        if (number < 2){
            return -1;
        }
        power++;
        number /= 2;
    }
}

int readSize(const char* msg){
    int size;
    printf(msg);
    scanf("%d", &size);
    return size;
}

int* readNumbers(int size, const char* message, const char* errorMessage){
    int* numbers = (int*)malloc(size * sizeof(size));
    if (numbers == NULL){
        return NULL;
    }

    printf(message);

    int num;
    for (int i = 0; i < size; i++){
        if (!scanf("%d", &num)){
            printf(errorMessage);
            free(numbers);
            return NULL;
        }
        numbers[i] = num;
    }
    return numbers;
}

int sumExponentsOf2Powers(int size, int* numbers, bool print){
    int power, sum = 0;

    for (int i = 0; i < size; i++){
        // if (numbers[i] < 1){
        //     continue;
        // }

        power = isPowerOf2(numbers[i]);
        if (power != -1){
            if (print){
                printf("The number %d is a power of 2: %d = 2^%d\n", numbers[i], numbers[i], power);
            }
            sum += power;
        }
    }
    return sum;
}

/** check if numbers given by the user are in form: log2(number) = natural number
 * and sums the exponents */
int main(){
    int size = readSize("Enter size of input:\n");
    if (size < 1){
        printf("Invalid size\n");
        return 0;
    }

    int* numbers = readNumbers(size, "Enter numbers:\n", "Invalid number\n");
    if (numbers == NULL){
        return 0;
    }

    int sum = sumExponentsOf2Powers(size, numbers, true);
    printf("Total exponent sum is %d\n", sum);
    free(numbers);
    return 0;
}