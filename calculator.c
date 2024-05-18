#include <stdio.h>
#include <math.h>

// Function to add two numbers
int add(int x, int y) {
    return x + y;
}

// Function to multiply two numbers
int multiply(int x, int y) {
    return x * y;
}

// Function to find the square of a number
int square(int x) {
    return x * x;
}

// Function to find the square root of a number
double squareRoot(int x) {
    if (x < 0) {
        printf("Cannot compute square root of a negative number!\n");
        return -1.0;
    }
    return sqrt(x);
}

// Function to display the menu
void printMenu() {
    printf("Calculator:\n");
    printf("1. Add Two Numbers\n");
    printf("2. Multiply Two Numbers\n");
    printf("3. Square a Number\n");
    printf("4. Square Root of a Number\n");
    printf("0. Exit\n");
}

// Function to get the user's choice
int getChoice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to get a number from the user
int getNumber() {
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    return num;
}

// Main function
int main() {
    int x, y, result;
    double dResult;
    int choice;

    while (1) {
        printMenu();
        choice = getChoice();

        if (choice == 0) break;

        if (choice == 3 || choice == 4) {
            x = getNumber();
        } else {
            printf("Enter two numbers:\n");
            x = getNumber();
            y = getNumber();
        }

        switch (choice) {
            case 1:
                result = add(x, y);
                printf("Result: %d\n", result);
                break;
            case 2:
                result = multiply(x, y);
                printf("Result: %d\n", result);
                break;
            case 3:
                result = square(x);
                printf("Result: %d\n", result);
                break;
            case 4:
                dResult = squareRoot(x);
                if (dResult != -1.0) printf("Result: %.2f\n", dResult);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
