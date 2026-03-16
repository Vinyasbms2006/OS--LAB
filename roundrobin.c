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

    int tot_tat=0;
    int tot_wt=0;

    int n, TQ;
    int front = 0, rear = 0;
    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d AT: ", i+1);
        scanf("%d", &p[i].AT);
    }

    printf("\nEnter Burst Time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d BT: ", i+1);
        scanf("%d", &p[i].BT);
        p[i].RT = p[i].BT;
        p[i].inQueue = 0;
    }

    printf("\nEnter Time Quantum: ");
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
        tot_tat+=p[i].TAT;
        p[i].WT = p[i].TAT - p[i].BT;
        tot_wt+=p[i].WT;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1,
               p[i].AT,
               p[i].BT,
               p[i].CT,
               p[i].TAT,
               p[i].WT);
    }

    printf("average tat is : ",tot_tat/n);
    printf("\n average wt is : ",tot_wt/n);

    return 0;
}

