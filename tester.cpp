//
// Created by mostafa on 16.09.2021.
//

#include "../untitled/main.cpp"


void Testing () {
    /// we will have six test cases
    /// each testing one of the enum values

    struct Solution solution;
    double a = 0, b = 0, c = 0;

    /// tests that will produce each of the cases SolutionType has

    int test_cases[3][6] = {{1, 1, 1, 0, 0, 0},
                            {5, 2, 1, 1, 0, 0},
                            {4, 1, 3, -1, 3, 0}};

    int solutions[6] = {1, 2, 3, 4, 5, 6};



    for (int i = 0; i < 6; ++i) {

        bool case1 = false;
        bool case2 = false;

        if (i == 0){

            solution = SolveQuadraticEquation(test_cases[0][i], test_cases[1][i], test_cases[2][i]);
            case1 = (solution.first_root == -4 && solution.second_root == -1);
            case2 = (solution.first_root == -1 && solution.second_root == -4);

        } else if (i == 1) {

            solution = SolveQuadraticEquation(test_cases[0][i], test_cases[1][i], test_cases[2][i]);
            case1 = (solution.first_root == -1);

        } else if (i == 2) {

            solution = SolveQuadraticEquation(test_cases[0][i], test_cases[1][i], test_cases[2][i]);
            case1 = (AreSame(solution.real_part,-0.5) && AreSame(solution.imaginary_part, 1.6583123951777) );
            /// printf("real part:%lf, imaginary_part:%lf\n", solution.real_part, solution.imaginary_part);
        }

        else if (i == 3) {


            solution = SolveQuadraticEquation(test_cases[0][i], test_cases[1][i], test_cases[2][i]);
            case1 = AreSame(solution.one_root, 1);
            ///printf("one_root: %lf",solution.one_root);
        }

        else if (i == 4 || i == 5) {

            solution = SolveQuadraticEquation(test_cases[0][i], test_cases[1][i], test_cases[2][i]);
            case1 = true;
        }

        if ((solution.type == solutions[i]) && (case1 || case2)) {

                printf("Test%d passed\n", solutions[i]);

        } else {

            printf("TEST%d FAILED!!!\n", solutions[i]);

        }
    }
}

int main(){
    Testing();
}
