//Ahmed Waleed Shawky 20200060.
//Omar Ayman Saeid    20200343.

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function that prints the 2d matrix.
void print_2d(int **matrix,int row,int col)
{
    for (int i = 0; i <row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {

    
    //Intializing the program
    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int matrix_1_row,matrix_1_col; int** matrix_1;
    int matrix_2_row,matrix_2_col; int** matrix_2;
    int matrix_3_row,matrix_3_col; int** matrix_3;
   

     if (rank == 0) {

        //taking input type from user. 
        printf("Welcome to vector Matrix multiplication program!\n");
        printf("(1) To read dimensions and values from file\n(2) To read dimensions and values from console \n\n");
        int choice; scanf("%d",&choice);
        
        if(choice==1)//if we take input from file.
        {

            FILE *file;
            file = fopen("input.txt", "r"); //make sure you have a file that the program can read from.

            fscanf(file, "%d %d", &matrix_1_row,&matrix_1_col);

            matrix_1 = (int**)malloc(matrix_1_row * sizeof(int*));
            for (int i = 0; i < matrix_1_row; i++)
            matrix_1[i] = (int*)malloc(matrix_1_col * sizeof(int));

            for (int i = 0; i < matrix_1_row; i++)
            {
                for (int j = 0; j < matrix_1_col; j++)
                {
                    fscanf(file,"%d",&matrix_1[i][j]);
                }
            }

            fscanf(file,"%d %d",&matrix_2_row,&matrix_2_col);

            matrix_2 = (int**)malloc(matrix_2_row * sizeof(int*));
            for (int i = 0; i < matrix_2_row; i++)
            matrix_2[i] = (int*)malloc(matrix_2_col * sizeof(int));

            printf("Enter the elements of the second matrix:- \n");
            fflush(stdout);
        
            for (int i = 0; i < matrix_2_row; i++)
            {
                for (int j = 0; j < matrix_2_col; j++)
                {
                    fscanf(file,"%d",&matrix_2[i][j]);
                }
            }

            matrix_3_row=matrix_1_row; matrix_3_col=matrix_2_col;
            matrix_3 = (int**)malloc(matrix_3_row * sizeof(int*));
            for (int i = 0; i < matrix_3_row; i++)
            matrix_3[i] = (int*)malloc(matrix_3_col * sizeof(int));
        
            for (int i = 0; i < matrix_3_row; i++) {
                for (int j = 0; j < matrix_3_col; j++) {
                    matrix_3[i][j]=0;
                }
            }

            fclose(file);
            printf("input has been taken from file \"input.txt\" \n\n");
            
        }
        else    //if we take input from user.
        {
            printf("Enter the dimentions of the first matrix: ");
            fflush(stdout);
            scanf("%d %d",&matrix_1_row,&matrix_1_col);

            matrix_1 = (int**)malloc(matrix_1_row * sizeof(int*));
            for (int i = 0; i < matrix_1_row; i++)
            matrix_1[i] = (int*)malloc(matrix_1_col * sizeof(int));

            printf("Enter the elements of the first matrix:- \n");
            fflush(stdout);
        
            for (int i = 0; i < matrix_1_row; i++)
            {
                for (int j = 0; j < matrix_1_col; j++)
                {
                    scanf("%d",&matrix_1[i][j]);
                }
            }


            printf("Enter the dimentions of the second matrix: ");
            fflush(stdout);
            scanf("%d %d",&matrix_2_row,&matrix_2_col);

            matrix_2 = (int**)malloc(matrix_2_row * sizeof(int*));
            for (int i = 0; i < matrix_2_row; i++)
            matrix_2[i] = (int*)malloc(matrix_2_col * sizeof(int));

            printf("Enter the elements of the second matrix:- \n");
            fflush(stdout);
        
            for (int i = 0; i < matrix_2_row; i++)
            {
                for (int j = 0; j < matrix_2_col; j++)
                {
                    scanf("%d",&matrix_2[i][j]);
                }
            }


            matrix_3_row=matrix_1_row; matrix_3_col=matrix_2_col;
            matrix_3 = (int**)malloc(matrix_3_row * sizeof(int*));
            for (int i = 0; i < matrix_3_row; i++)
            matrix_3[i] = (int*)malloc(matrix_3_col * sizeof(int));
        
            for (int i = 0; i < matrix_3_row; i++) {
                for (int j = 0; j < matrix_3_col; j++) {
                    matrix_3[i][j]=0;
                }
            }
        }
        
        //if the matrices are not dividable.
        if(matrix_1_col!=matrix_2_row)
        {
            printf("\nInvalid matrices.\n");
            MPI_Finalize();
            return 0;
        }


        // distribute matrices and their dimentions to each other process.
        for (int i = 1; i < size; i++) {
            MPI_Send(&matrix_1_row, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_1_col, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_2_row, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_2_col, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_3_row, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&matrix_3_col, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            //sending matrix1 value.
            for (size_t j = 0; j <matrix_1_row; j++)
            {
                MPI_Send(matrix_1[j], matrix_1_col, MPI_INT, i, 0, MPI_COMM_WORLD);
            }

            
            //sending matrix2 value.
            for (size_t j = 0; j <matrix_2_row; j++)
            {
                MPI_Send(matrix_2[j], matrix_2_col, MPI_INT, i, 0, MPI_COMM_WORLD);
            }

            //sending matrix3 value.
            for (size_t j = 0; j <matrix_3_row; j++)
            {
                MPI_Send(matrix_3[j], matrix_3_col, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

     }
    else 
    {
        
        // receive matrices from master process.
        MPI_Recv(&matrix_1_row, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix_1_col, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix_2_row, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix_2_col, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix_3_row, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&matrix_3_col, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //building each matrix again.
        matrix_1 = (int**)malloc(matrix_1_row * sizeof(int*));
        for (int i = 0; i < matrix_1_row; i++)
        matrix_1[i] = (int*)malloc(matrix_1_col * sizeof(int));
        
        matrix_2= (int**)malloc(matrix_2_row * sizeof(int*));
        for (int i = 0; i < matrix_2_row; i++)
        matrix_2[i] = (int*)malloc(matrix_2_col * sizeof(int));

        matrix_3 = (int**)malloc(matrix_3_row * sizeof(int*));
        for (int i = 0; i < matrix_3_row; i++)
        matrix_3[i] = (int*)malloc(matrix_3_col * sizeof(int));


        //receiving each matrix values.
        for (size_t j = 0; j <matrix_1_row; j++)
        {
            MPI_Recv(matrix_1[j], matrix_1_col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (size_t j = 0; j <matrix_2_row; j++)
        {
            MPI_Recv(matrix_2[j], matrix_2_col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for (size_t j = 0; j <matrix_3_row; j++)
        {
            MPI_Recv(matrix_3[j], matrix_3_col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

    }

    //intializing values that will help in computing the matrices values.
    int rows_per_process = matrix_1_row / size;
    int leftover_rows = matrix_1_row % size;
    int start_row = rank * rows_per_process;
    int end_row = start_row + rows_per_process;
    if (rank == size - 1) {
        end_row += leftover_rows;
    }


    // multiplying matrices in every proccess.

    if(rows_per_process==0) //if number of rows is less than the number of processes, where the rows can't be divided on all processes.
    {   
        if(rank+1==size)
        {
            for (int i = start_row; i <end_row; i++) {
                for (int j = 0; j < matrix_2_col; j++) {
                    for (int k = 0; k < matrix_1_col; k++) {
                        matrix_3[i][j] += matrix_1[i][k] * matrix_2[k][j];
                    }
                }
            }

            printf("Result Matrix is (%dx%d): \n",matrix_3_row,matrix_3_col);
            print_2d(matrix_3,matrix_3_row,matrix_3_col);
            MPI_Finalize();
            return 0;
        }
    }
    else{   //if number of rows can be divided on the processes.

        for (int i = start_row; i <end_row; i++) {
            for (int j = 0; j < matrix_2_col; j++) {
                for (int k = 0; k < matrix_1_col; k++) {
                    matrix_3[i][j] += matrix_1[i][k] * matrix_2[k][j];
                }
            }
        } 
    }
    
    
    


    if (rank == 0) {    //receiving each computed value from other processes to master process.

        for (int i = 1; i < size; i++) {

            int start;
            int end;
            MPI_Recv(&start, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&end, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //printf("at process %d start=%d end=%d \n",i,start,end);
            for (size_t j = start; j < end; j++)
            {
                MPI_Recv(matrix_3[j], matrix_3_col, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            //print_2d(matrix_3,matrix_3_row,matrix_3_col);
        }

    } else {    //sending each computed value from processes to master.
        
        //sending starting row and col of each process.
        MPI_Send(&start_row, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Send(&end_row, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

        //sending the computed rows.
        for (int i =start_row; i <end_row; i++)
        {
            MPI_Send(matrix_3[i], matrix_3_col, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
        
        
    }

    // printing the resulting matrix.
    if (rank == 0) {
        printf("Result Matrix is (%dx%d): \n",matrix_3_row,matrix_3_col);
        print_2d(matrix_3,matrix_3_row,matrix_3_col);
    }
    
    MPI_Finalize();
    return 0;
}
