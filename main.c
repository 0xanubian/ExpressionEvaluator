#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PROMPT ">>> "

double parseExpression(const char** exp);
double parseTerm(const char** exp);
double parseFactor(const char** exp);
double parseNumber(const char** exp);

void neglectSpace(const char** exp) {
    while (**exp) {
        if (isspace(**exp)) {
            (*exp)++; //skips the whitespace
        }
        else return;
    }
}

//evaluates + and - and calls for evaluating * and /
double parseExpression(const char** exp) {
    double result = parseTerm(exp);

    while (**exp) {
        neglectSpace(exp);
        if (**exp == '+') {
            (*exp)++; //skips the + sign
            result += parseTerm(exp);
        }
        else if (**exp == '-') {
            (*exp)++; //skips the - sign
            result -= parseTerm(exp);
        }
        else break; 
    }
    return result;
}

//evaluates * and / and calls for evaluating parenthesis
double parseTerm(const char** exp) {
    double result = parseFactor(exp);

    while (**exp) {
        neglectSpace(exp);
        if (**exp == '*') {
            (*exp)++; //skips the * sign
            result *= parseFactor(exp);
        }
        else if (**exp == '/') {
            (*exp)++; //skips the / sign
            result /= parseFactor(exp);
        }
        else break;
    }
    return result;
}

//parses expression inside parenthesis and calls for parsing numbers
double parseFactor(const char** exp) {
    neglectSpace(exp);

    if (**exp == '(') {
        (*exp)++; //skips the opening parenthesis
        double result = parseExpression(exp);
    
        neglectSpace(exp);
        if (**exp == ')') {
            (*exp)++; //skips the closing parenthesis
        }
        else fprintf(stderr, "Mismatching parenthesis\n"); 

        return result;
    }
    else return parseNumber(exp);
}

double parseNumber(const char** exp) {
    char* endptr;

    double number = strtod(*exp, &endptr);

    //error checking for strtod()
    if (*exp == endptr) fprintf(stderr, "Invalid number entered\n");

    //strtod() returns the rest of string that is cann't be converted
    //to decimal in endptr. here we change the expression to endptr
    //for parsing it further
    *exp = endptr;

    return number;
}

int main(void) {
    while(1) {
        char input_string[256];
        double result;

        printf("%s", PROMPT);
        if (fgets(input_string, sizeof(input_string), stdin) == NULL) {
            fprintf(stderr, "Couldn't get the input\n");
            return 1;
        }

        //remove the trailing newline
        input_string[strcspn(input_string, "\n")] = 0;

        const char* expression = input_string;

        result = parseExpression(&expression);

        printf("%lf\n", result);
    }
    return EXIT_SUCCESS;
}
