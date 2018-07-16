#include <iostream>
#include <stdlib.h>
/*
  Function prototype, initialised to be used later on.
*/
void readArray(int, int, double **);

int main(int argc, char *argv[])
{
    /*
      Initialising the rows and columns to be the second and third argument passed in.
      Including the command to run the program, which is the first argument.
    */
    int rows    = atoi(argv[1]);
    int columns = atoi(argv[2]);
    int zeroes = 0;
    int totalZeroes = 0;
    int totalNonZeroes = 0;

    /*
      We are only taking in matrices with the dimensions of n * n.
      Therefore, if the dimensions of the matrix are not the same, an error is output.
    */
    if (rows != columns)
    {
        std::cerr<< "Matrix dimensions mismatch; exiting.\n";
        exit(-1);
    }
    /*
      Revserving space for the array.
    */
    double **A = new double*[rows];
    /*
      Each element points to a row of A.
    */
        for(int w = 0; w < rows; w++)
        /*
          A row of 'column' floats.
        */
            A[w] = new double[columns];

    readArray(rows, columns, A);
    /*
      The number of rows, n, is output.
    */
    std::cout << rows << std::endl;

    for(int x = 0; x < rows; x++)
    {
        /*
          Reading through the rows, counting how many zeroes are present.
        */
        for(int y = 0; y < columns; y++)
            if(A[x][y] == 0)
                zeroes++;
        /*
          Constantly adding to the totalZeroes count.
        */
        totalZeroes += zeroes;
        /*
          Printing out the amount of nonZeroes in the row.
        */
        std::cout << columns - zeroes;

        /*
          Prints out the column location and the corresponding nonZero value.
          Ignores the zeroes when printing, and spacing the values to get the desired input.
        */
        for(int z = 0; z < columns; z++)
            if(!(A[x][z] == 0))
                std::cout << " " << (z + 1) << " " << A[x][z];
        /*
          Starts a new line to begin on the next row.
        */
        std::cout << std::endl;
        /*
          Aount of zeroes on the row is reset for to begin again on the next row.
        */
        zeroes = 0;
    }

    /*
      Get the total count of totalZeroes by getting the number
      of all the elements in the matrix and subtracting the zeroes that are present.
    */
    totalNonZeroes = (rows * columns) - totalZeroes;

    /*
      Finally, print out the final count of the totalZeroes in the matrix.
    */
    std::cout << totalNonZeroes << std::endl;

    return 0;
}

/*
  Method reading from Keyboard into this array, row by row.
  Total of rowLength * columnLength entries.
  Space for array allocated from line 21 - 23
  Note: Could this be input into main to get rid of a function call?
*/
void readArray(int rowLength, int columnLength, double** arr)
{
    for(int u = 0; u < rowLength; u++)
        for(int v = 0; v < columnLength; v++)
            std::cin>> arr[u][v];
}
