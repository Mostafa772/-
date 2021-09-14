#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <assert.h>


const double epsilon = 1e-10;

bool If_Double_Equal_Zero (double a) {
    return (fabs(a) <= epsilon);
}

enum SolutionType {
    REAL_ROOTS_WITH_DIFFERENT_VALUES = 1,
    REAL_ROOTS_WITH_SAME_VALUES,
    IMAGINARY_ROOTS,
    LINEAR_EQUATION,
    NO_ROOTS,
    INFINITE_NUMBER_OF_ROOTS
};

struct Solution {
    enum SolutionType type;
    double first_root;
    double second_root;
    double real_part;
    double imaginary_part;
    double one_root;
};

enum SolutionType find_root_type(double discriminant, double a, double b, double c) {

    if (discriminant > 0) {

        return REAL_ROOTS_WITH_DIFFERENT_VALUES;

    } else if (If_Double_Equal_Zero(discriminant) == 0) {

        return REAL_ROOTS_WITH_SAME_VALUES;

    } else if (If_Double_Equal_Zero(a) && If_Double_Equal_Zero(b) && If_Double_Equal_Zero(c)) {

        return INFINITE_NUMBER_OF_ROOTS;

    } else if (If_Double_Equal_Zero(a) && If_Double_Equal_Zero(b) && !If_Double_Equal_Zero(c)) {

        return NO_ROOTS;

    } else if (If_Double_Equal_Zero(a)){

        return LINEAR_EQUATION;

    } else {

        return IMAGINARY_ROOTS;
    }
}


void print_solution(struct Solution solution) {

    switch (solution.type) {

        case REAL_ROOTS_WITH_DIFFERENT_VALUES:
            printf("Roots are real and different: \n");
            printf("First root: %lf\n", solution.first_root);
            printf("Second root: %lf\n", solution.second_root);
            break;

        case REAL_ROOTS_WITH_SAME_VALUES:
            printf("Roots are real and same: \n");
            printf("Root: %lf\n", solution.first_root);
            break;

        case IMAGINARY_ROOTS:
            printf("Roots are complex and different \n");
            printf("First root: %lf + %lfi\n", solution.real_part, solution.imaginary_part);
            printf("Second root: %lf - %lfi\n", solution.real_part, solution.imaginary_part);
            break;

        case LINEAR_EQUATION:
            printf("The equation is linear and has one root: \n");
            printf("Root: %lf\n", solution.one_root);
            break;

        case INFINITE_NUMBER_OF_ROOTS:
            printf("There is an infinite number of roots \n");
            break;

        case NO_ROOTS:
            printf("The equation has no roots \n");
            break;

        default:
            break;
    }
}

struct Solution solve_quadratic_equation(double a, double b, double c) {

    double discriminant = (b * b) - 4 * a * c;

    struct Solution solution;

    solution.type = find_root_type(discriminant, a, b, c);

    switch (solution.type) {

        case REAL_ROOTS_WITH_DIFFERENT_VALUES:
            solution.first_root = (-b + sqrt(fabs(discriminant))) / (2 * a);
            solution.second_root = (-b - sqrt(fabs(discriminant))) / (2 * a);
            break;

        case REAL_ROOTS_WITH_SAME_VALUES:
            solution.first_root = solution.second_root = -b / (2 * a);
            break;

        case IMAGINARY_ROOTS:
            solution.real_part = -b / (2 * a);
            solution.imaginary_part = sqrt(fabs(discriminant)) / (2 * a);
            break;

        case LINEAR_EQUATION:
            solution.one_root = -c / (2 * a);

        default:
            break;
    }
    return solution;
}

void equation_input(double *a, double *b, double *c){

    char input[8] = "";
    bool a_has_input = false, b_has_input = false, c_has_input = false;

    while (double(a_has_input) + double(c_has_input) + double(b_has_input) < 3) {


        if (fgets(input, sizeof input, stdin)) {

            char *check = nullptr;
            double tmp = (double) strtol(input, &check, 10);

            if (!isspace(*check) && *check != 0) {
                printf("%s is not a valid integer: try again\n", input);
            }

            else if (!a_has_input){

                *a = tmp;
                a_has_input = true;
            }

            else if(!b_has_input) {
                *b = tmp;
                b_has_input = true;
            }

            else if(!c_has_input) {
                *c = tmp;
                c_has_input = true;
            }

        }
        else {
            printf("Read error on standard input\n");
            break;
        }
    }
}

int main() {

    double a = 0, b = 0, c = 0;

    /// the solutions of the equation

    equation_input(&a, &b, &c);
    struct Solution solution = solve_quadratic_equation(a, b, c);
    print_solution(solution);
}
