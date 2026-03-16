#include <stdio.h>

#define MAX 100

int main() {
    int n;
    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], Start[MAX];

    int SystemQueue[MAX], UserQueue[MAX];
    int sysCount = 0, userCount = 0;

    int order[MAX];
    int orderCount = 0;

    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter PID, Arrival Time, Burst Time, Type (0=System,1=User)\n");

    for(int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &PID[i], &AT[i], &BT[i], &TYPE[i]);
    }

    for(int i = 0; i < n; i++) {
        if(TYPE[i] == 0)
            SystemQueue[sysCount++] = i;
        else
            UserQueue[userCount++] = i;
    }

    for(int i = 0; i < sysCount-1; i++) {
        for(int j = i+1; j < sysCount; j++) {
            if(AT[SystemQueue[i]] > AT[SystemQueue[j]]) {
                int temp = SystemQueue[i];
                SystemQueue[i] = SystemQueue[j];
                SystemQueue[j] = temp;
            }
        }
    }

    for(int i = 0; i < userCount-1; i++) {
        for(int j = i+1; j < userCount; j++) {
            if(AT[UserQueue[i]] > AT[UserQueue[j]]) {
                int temp = UserQueue[i];
                UserQueue[i] = UserQueue[j];
                UserQueue[j] = temp;
            }
        }
    }

    for(int i = 0; i < sysCount; i++) {

        int p = SystemQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;

        order[orderCount++] = p;

        time += BT[p];

        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    for(int i = 0; i < userCount; i++) {

        int p = UserQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;

        order[orderCount++] = p;

        time += BT[p];

        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], TYPE[i],
               CT[i], TAT[i], WT[i]);
    }


    printf("\nGantt Chart:\n");

    printf("|");
    for(int i = 0; i < orderCount; i++) {
        printf(" P%d |", PID[order[i]]);
    }

    printf("\n");

    printf("%d", Start[order[0]]);
    for(int i = 0; i < orderCount; i++) {
        printf("    %d", CT[order[i]]);
    }

    printf("\n");

    return 0;
}
