#include <stdio.h>
#include <stdbool.h>

int grid[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

bool not_in_rc(int row, int col, int num)
{
    // Annahme: Die Zahl ist nicht in der Reihe
    for (int i = 0; i < 9; i++)
    {
        if (grid[row][i] == num || grid[i][col] == num)
        {
            return false;
        }

    }
    return true;
}
bool not_in_subgrid(int row, int col, int num)
{
    // Definition der Bereiche für das 3x3-Subquadrat
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);

    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (grid[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}
bool grid_is_valid(int row, int col, int num)
{
    if (not_in_rc(row, col, num) && not_in_subgrid(row, col, num))
    {
        return true;
    }
    return false;
}

void print_grid(int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
bool empty(int* row, int* col) //Pointer auf die Variablen row, col der Solve Funktion
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            //cell is empty
            if (grid[i][j] == 0)
            {
                *row = i;   //Setzen der Variablen für die Solve Funktion
                *col = j;
                return true;
            }
        }
    }
    return false;
}
bool solve()
{
    int row, col;
    if (!empty(&row, &col)) // Übergeben der Adressen der Variablen row, col
    {
        return true;
    }


    for (int num = 1; num <= 9; num++)
    {
        if (grid_is_valid(row, col, num))
        {
            grid[row][col] = num; // Setze die Zahl ein
            if (solve())
            {
                return true; // Rekursiv lösen (Backtrack)
            }

            grid[row][col] = 0;
        }
    }
    return false;
}

int main()
{
    if (solve())
    {
        printf("Solution:\n");
        print_grid(grid);
    }
    else
    {
        printf("No solution exists.\n");
    }

    return 0;
}