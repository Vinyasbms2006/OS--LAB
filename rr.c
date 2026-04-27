#include <stdio.h>

#define MAX 100

struct Process {
    int AT, BT, RT;
    int CT, WT, TAT;
    int inQueue;
};

int main() {
    struct Process p[MAX];
    int queue[MAX];

    int n, TQ;
    int front = 0, rear = 0;

    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &p[i].AT);

    printf("Enter Burst Time:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i].BT);
        p[i].RT = p[i].BT;
        p[i].inQueue = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &TQ);

    while(completed < n) {


        for(int i = 0; i < n; i++) {
            if(p[i].AT <= time && p[i].inQueue == 0 && p[i].RT > 0) {
                queue[rear++] = i;
                p[i].inQueue = 1;
            }
        }

        if(front == rear) {
            time++;
            continue;
        }

        int cur = queue[front++];

        if(p[cur].RT > TQ) {
            time += TQ;
            p[cur].RT -= TQ;
        }
        else {
            time += p[cur].RT;
            p[cur].RT = 0;
            p[cur].CT = time;
            completed++;
        }


        for(int i = 0; i < n; i++) {
            if(p[i].AT <= time && p[i].inQueue == 0 && p[i].RT > 0) {
                queue[rear++] = i;
                p[i].inQueue = 1;
            }
        }


        if(p[cur].RT > 0) {
            queue[rear++] = cur;
        }
    }

    for(int i = 0; i < n; i++) {
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    return 0;


}


