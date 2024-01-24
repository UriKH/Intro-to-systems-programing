#include <stdio.h>
#include <ctype.h>

int is_log2(double num)
{
    int power = 0;

    while (1)
    {
        if (num == 1)
            return power;
        if (num < 2)
            return -1;
        power++;
        num /= 2;
    }
}

int main()
{
    // receive the number of inputs from the user
    printf("Enter size of input:\n");

    // read line and translate the parameters into integers
    int size;
    
    scanf("%d", &size);
    if (size < 1)
    {
        printf("Invalid size\n");
        return 0;
    }

    // get user inputs - line by line
    printf("Enter numbers:\n");
    int nums[(const int)size], num;
    for (int i = 0; i < size; i++)
    {
        // read line and translate the parameters into integers
        if (!scanf("%d", &num))
        // if (scanf("%d%c", &num, &temp) != 2 || !isspace(temp))
        {
            printf("Invalid number\n");
            return 0;
        }
        nums[i] = num;
    }

    // check which numbers are in foramt and sum the powers
    int power, sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (nums[i] < 1)
            continue;
        power = is_log2(nums[i]);
        if (power != -1)
        {
            printf("The number %d is a power of 2: %d = 2^%d\n", nums[i], nums[i], power);
            sum += power;
        }
    }
    printf("Total exponent sum is %d\n", sum);
    return 0;
}