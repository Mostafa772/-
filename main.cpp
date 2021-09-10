#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>

void find_quadratic_roots(int a, int b, int c, double *x1, double *x2) {

    int Discriminant = (b * b) - 4 * a * c;

    if (Discriminant == 0) {

        printf("There is a double root for the quadratic equation\n");
        *x2 = 0;
        *x1 = -c * 1.0 / b;
        printf("the root x: %lf\n", *x1);

    } else if (Discriminant > 0) {

        printf("There are two real roots\n");
        *x1 = (-b - sqrt(Discriminant)) / 2 * a;
        *x2 = (-b + sqrt(Discriminant)) / 2 * a;

        printf("the first root x1: %lf\nthe second root x2: %lf", *x1, *x2);


    } else if (Discriminant < 0) {

        printf("There are two imaginary roots\n");
        double x1_real_part = -b / 2.0 * a;
        double x1_imaginary_part = sqrt(abs(Discriminant)) / 2.0 * a;
        printf("x1 = %lf + i %lf\n", x1_real_part, x1_imaginary_part);

        double x2_real_part = -b / 2.0 * a;
        double x2_imaginary_part = sqrt(abs(Discriminant)) / 2.0 * a;
        printf("x2 = %lf - i %lf\n", x2_real_part, x2_imaginary_part);

    }
}

void solve_quadratic_function(int a, int b, int c, double *x1, double *x2){

    printf("a: %d, b: %d, c: %d\n", a, b, c);

    if (a == 0 && b == 0 && c == 0) {
        printf("There is an infinite number of solutions\n");
        return ;
    }

    if (a == 0 && b == 0) {
        printf("There are no solutions\n");
        return ;
    }

    if (a != 0) {

        find_quadratic_roots(a, b, c, x1, x2);

    } else if (a == 0) {
        printf("There is only one root\n");
        *x1 = -c * 1.0 / b;

        if (b == 1) {
            printf("The root of the equation x + (%d) = 0 is x = %lf", c, *x1);
        }

        printf("The root of the equation %dx + (%d) = 0 is x = %lf", b, c, *x1);
    }
}

void equation_input(int *a, int *b, int *c){

    char input[8];
    bool a_has_input = false, b_has_input = false, c_has_input = false;

    while (int(a_has_input) + int(c_has_input) + int(b_has_input) < 3) {


        if (fgets(input, sizeof input, stdin)) {

            char *check;
            int tmp = (int) strtol(input, &check, 10);

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

    int a, b, c;

    /// the solutions of the equation
    double x1, x2;

    equation_input(&a, &b, &c);

    solve_quadratic_function(a, b, c, &x1, &x2);
}