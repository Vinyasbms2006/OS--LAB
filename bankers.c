#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], safeSeq[n], work[m];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n) {
        printf("\nSystem is in SAFE state\n");
        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
    }
    else {
        printf("\nSystem is NOT in safe state\n");
    }

    return 0;
}
