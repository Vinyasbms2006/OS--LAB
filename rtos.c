#include <stdio.h>

#define MAX_TASKS 10
#define MAX_TIME 20

typedef struct {
    int id;
    int C;
    int P;
    int next_arrival;
    int remaining_time;
} Task;

void sort_by_period(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[MAX_TASKS];

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].C, &tasks[i].P);

        tasks[i].next_arrival = 0;
        tasks[i].remaining_time = 0;
    }


    sort_by_period(tasks, n);

    printf("\nScheduling Order (lower period = higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Task T%d (P=%d, C=%d)\n", tasks[i].id, tasks[i].P, tasks[i].C);
    }

    int time = 0;
    int gantt[MAX_TIME];


    printf("\nExecution Timeline:\n");

    while (time < MAX_TIME) {

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }


        int current = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current = i;
                break;
            }
        }

        if (current != -1) {
            printf("Time %2d: Running T%d\n", time, tasks[current].id);
            gantt[time] = tasks[current].id;
            tasks[current].remaining_time--;
        } else {
            printf("Time %2d: CPU Idle\n", time);
            gantt[time] = 0;
        }

        time++;
    }


    printf("\nGantt Chart:\n");

    printf("Time:  ");
    for (int i = 0; i < MAX_TIME; i++) {
        printf("%2d ", i);
    }

    printf("\n      ");
    for (int i = 0; i < MAX_TIME; i++) {
        if (gantt[i] == 0)
            printf("ID ");
        else
            printf("T%d ", gantt[i]);
    }

    printf("\n");

    return 0;
}
