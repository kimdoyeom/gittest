#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    int** create_matrix(int row, int col); //배열 행렬 지정함수 
    int free_matrix(int** matrix, int row, int col); //동적할당 초기화 함수
    void print_matrix(int** matrix, int row, int col);//2차원 배열 출력 함수
    int fill_data(int **matrix, int row, int col);//0 ~19 사이의 랜덤 값 분배 함수
    int transpose_matrix(int **matrix, int **matrix_t, int row, int col);//전치행렬 구현 함수
    int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);//두 행렬을 합하는 함수
    int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);//두 행렬을 빼는 함수
    int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);//입력행렬과 해당 행렬의 전치행렬을 곱하는 함수


    void main(){

        int a, b;//행렬을 받는 변수
        int** array1, array2, array_sum, array_sub, array_t, array_axt;//각각 A, B행렬, 행렬합, 행렬 차, 전치행렬, 행렬곱
        int i;

        printf("[----- [kimdoyeom] [2019038066] -----]\n");

        printf("write row and col\n");
        printf("row col: ");
        scanf("%d %d", &a, &b);
        while (create_matrix(a,b)==-1){

            printf("write row and col\n");
            printf("row col: ");
            scanf("%d %d", &a, &b);
        }
        array1 = create_matrix(a, b);
        array2 = create_matrix(a, b);
        array_sum = create_matrix(a, b);
        array_sub = create_matrix(a, b);
        array_t = create_matrix(b, a);
        array_axt = create_matrix(a, a);

        fill_data(array1, a, b);
        fill_data(array2, a, b);

        addition_matrix(array1, array2, array_sum, a, b);
        print_matrix(array_sum, a, b);

        subtraction_matrix(array1, array2, array_sub, a, b);
        print_matrix(array_sub, a, b);

        transpose_matrix(array1, array_t, a, b);
        print_matrix(array_t, b, a);

        multiply_matrix(array1, array_t, array_axt, a, b);
        print_matrix(array_axt, a, a);

    
        free_matrix(array1, a, b);
        free_matrix(array2, a, b);
        free_matrix(array_sum, a, b);
        free_matrix(array_sub, a, b);
        free_matrix(array_t, b, a);
        free_matrix(array_axt, a, b);
        return 0;
    }

    int** create_matrix(int row, int col){

        if (row <= 0 || col <= 0) {
            printf("check your row & col\n");
            return -1;
        }
        else{
            int** array;
            int i;
            array = (int**)malloc(sizeof(int*) * row);

            for (i = 0; i < row; i++)
                array[i] = (int*)malloc(sizeof(int) * col);

            return array;
        }
    
    }

    int free_matrix(int** matrix, int row, int col){
    
        for (int i = 0; i < row; i++)
            free(matrix[i]);

        free(matrix);
    }

    int fill_data(int** matrix, int row, int col){

        srand(time(NULL));

        for (int i = 0; i < row; i++){   

            for (int j = 0; j < col; j++)
                matrix[i][j] = rand() % 19;
        }
    }

    int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col) {

        for (int i = 0; i < row; i++) {

            for (int j = 0; j < col; j++)
                matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

    int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col) {

        for (int i = 0; i < row; i++) {

            for (int j = 0; j < col; j++)
                matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }

    int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {

        for (int i = 0; i < row; i++) {
         
            for (int j = 0; j < col; j++)
                matrix_t[j][i] = matrix[i][j];
        }
    }

    int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col) {

        for (int i = 0; i < row; i++) {

            for (int j = 0; j < row; j++)
                matrix_axt[i][j] = 0;
        }

        for (int i = 0; i < row; i++) {

            for (int j = 0; j < row; j++) {
                for (int k = 0; k < col; k++)
                    matrix_axt[i][j] = matrix_axt[i][j] + matrix_a[i][k] * matrix_t[k][j];
            }
            
        }

    }

    void print_matrix(int** matrix, int row, int col) {
        for (int i = 0; i < row; i++) {

            for (int j = 0; j < col; j++)
                printf("%d   ", matrix[i][j]);
            printf("\n");
        } 
        printf("\n\n");
    }
