#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], request[n][m], available[m];
    int finish[n];

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    // Initialize finish array
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int changed = 1;

    while (changed)
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int possible = 1;

                for (j = 0; j < m; j++)
                {
                    if (request[i][j] > available[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {
                    for (k = 0; k < m; k++)
                    {
                        available[k] += allocation[i][k];
                    }

                    finish[i] = 1;
                    changed = 1;

                    printf("Process P%d can complete\n", i);
                }
            }
        }
    }

    int deadlock = 0;

    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            deadlock = 1;
            printf("Process P%d is deadlocked\n", i);
        }
    }

    if (!deadlock)
    {
        printf("No Deadlock Detected\n");
    }

    return 0;
}
