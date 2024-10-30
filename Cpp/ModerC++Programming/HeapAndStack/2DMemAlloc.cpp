#include <iostream>

static void Print2DArray(int **arr, int rows, int cols)
{
    if (!arr || rows <= 0 || cols <= 0)
        return;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << arr[i][j] << " ";
            // std::cout << std::flush;
        }
        std::cout << "\n";
    }
}

int main()
{
    int rows = 8;
    constexpr int COLS = 32;

    // First method
    std::cout << "### First 2D array allocation ###\n";
    int **arrayA = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        arrayA[i] = new int[COLS];
        std::cout << "\tAddress of arraya[" << i << "]: " << std::showbase << std::hex << arrayA[i] << "\n";
        for (int j = 0; j < COLS; ++j)
        {
            arrayA[i][j] = (i + 1) * (j + 1);
        }
    }

    Print2DArray(arrayA, rows, COLS);

    for (int i = 0; i < rows; ++i)
    {
        delete[] arrayA[i];
        arrayA[i] = nullptr;
    }
    delete[] arrayA;
    arrayA = nullptr;

    // Second method
    std::cout << "\n\n### Second 2D array allocation ###\n";
    auto arrayB = new int[rows][COLS];
    for (int i = 0; i < rows; ++i)
    {
        std::cout << "\tAddress of arrayB[" << i << "]: " << std::showbase << std::hex << arrayB[i] << "\n";
        for (int j = 0; j < COLS; ++j)
        {
            arrayB[i][j] = i * COLS + j;
        }
    }

    // Print2DArray((int **)arrayB, rows, COLS);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            std::cout << arrayB[i][j] << " ";
        }
        std::cout << "\n";
    }

    delete[] arrayB;

    return EXIT_SUCCESS;
}

/*
 * Call to Print2DArray at line59 will cause SegmentationFault:
 * Print2DArray receives the array as an `int **` pointer, it first dereferences
 * the `int **`(with offset, row) to get an `int *` pointer, then again derefrences
 * the `int *`(with offset, col) to get the value stored. This works perfectly
 * for `ArrayA` since each row member is a pointer denamically allocated. However,
 * `ArrayB`'s row members are not pointers but `int [COLS]`, namely to access the
 * stored values you only need to dereference the `ArrayB` once with both row and
 * col offset.
 * For `ArrayA`:
 * 1. Dereference `ArrayA[i]` to get `int *`, each `++i` increases offset of
 * `sizeof(int *)`(pointer size)
 * 2. Dereference `ArrayA[i][j]` to get the value.
 * For `ArrayB`:
 * 1. Get the pinter to the start of an `int[COLS]` via `ArrayB[i]`, each `++i`
 * increases offset of `sizeof(int[COLS])`(sizeof int * COLS)
 * 2. Use the pointer from 1 and add the corresponding offset, namely
 * `sizeof(int) * j`, and dereference the result pointer.
 * 3. The calculation is like(for `ArrayB[i][j]`):
 * - char* arr = (char *)arrayB;
 * - char* value = arr + sizeof(int) * COLS * i;
 * - value = value + sizeof(int) * j;
 * - int result = *((int *)value);
 */
