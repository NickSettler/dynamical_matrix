#include <stdio.h>
#include <malloc.h>
#include <string.h>

// create a type with matrix, rows and columns
typedef struct {
    int rows;
    int columns;
    char **matrix;
} matrix_t;

matrix_t *init_matrix(int rows, int columns, const char initial_value) {
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->matrix = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        matrix->matrix[i] = malloc(columns * sizeof(char));
        for(int j = 0; j < columns; j++) {
            matrix->matrix[i][j] = initial_value;
        }
    }
    return matrix;
}

// create a function to copy matrix
matrix_t *copy_matrix(matrix_t *matrix) {
    matrix_t *copy = init_matrix(matrix->rows, matrix->columns, ' ');
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            copy->matrix[i][j] = matrix->matrix[i][j];
        }
    }
    return copy;
}

// create a function to copy matrix values
void copy_matrix_values(matrix_t *matrix, matrix_t *copy) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            copy->matrix[i][j] = matrix->matrix[i][j];
        }
    }
}

void resize_matrix(matrix_t *matrix, int rows, int columns) {
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->matrix = realloc(matrix->matrix, rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        matrix->matrix[i] = realloc(matrix->matrix[i], columns * sizeof(char));
    }
}

// create a function to resize matrix and fill new cells with initial value
void resize_matrix_fill(matrix_t *matrix, int new_rows, int new_columns, const char initial_value) {
    // init new matrix
    matrix_t *new_matrix = init_matrix(new_rows, new_columns, initial_value);

    // copy old matrix
    copy_matrix_values(matrix, new_matrix);

    // free old matrix
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    // set new matrix to old matrix
    matrix->matrix = new_matrix->matrix;
    matrix->rows = new_matrix->rows;
    matrix->columns = new_matrix->columns;
    // free new matrix
    free(new_matrix);
}

// create a function to add rows with value to matrix
void add_row(matrix_t *matrix, int row_index, char *value) {
    // check if row index is valid
    if (row_index < 0 || row_index >= matrix->rows) {
        printf("Invalid row index\n");
        return;
    }
    // check if matrix is full
    if (matrix->columns == matrix->rows) {
        resize_matrix(matrix, matrix->rows + 1, matrix->columns);
    }
    // add row to the matrix
    for (int i = matrix->rows - 1; i > row_index; i--) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->matrix[i][j] = matrix->matrix[i - 1][j];
        }
    }

    // compare value length with matrix columns and extend matrix if necessary
    if (strlen(value) > matrix->columns) {
        resize_matrix_fill(matrix, matrix->rows, strlen(value), ' ');
    }

    matrix->matrix[row_index] = value;
}

// create a function to print matrix
void print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%c", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

// create a function to get size of the matrix in memory
int get_size(matrix_t *matrix) {
    return matrix->rows * matrix->columns * sizeof(char);
}

int main() {
    matrix_t matrix = *init_matrix(3, 3, '0');
    add_row(&matrix, 1, "asdwd");
    add_row(&matrix, 1, "asdasfdasdwd");
    print_matrix(&matrix);

    free_matrix(&matrix);

    return 0;
}
