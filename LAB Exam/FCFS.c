#include<stdio.h>

int main(){

    int at[10], bt[10], ct[10], tat[10], wt[10];
    int no_process;
    printf("Enter the no. of processes = ");
    scanf("%d",&no_process);

    for(int i = 0;i<no_process;i++){
        printf("Enter no. of Arrival time for process %d = ",i+1);
        scanf("%d",&at[i]);
        printf("Enter no. of Burst time for process %d = ",i+1);
        scanf("%d",&bt[i]);
        printf("\n");
    }
    int sum =at[0];
    for(int i = 0;i<no_process;i++){
        sum = sum+bt[i];
        ct[i] = sum;
    }
    int totalTAT;
    for(int i = 0;i<no_process;i++){
        tat[i] = ct[i]-at[i];
        totalTAT = totalTAT+tat[i];
    }
    int totalWT;
    for(int i = 0;i<no_process;i++){
        wt[i] = tat[i]-bt[i];
        totalWT = totalWT+wt[i];
    }

    printf("PID AT BT CT TAT WT\n");
    for(int i = 0;i<no_process;i++){
        printf("%d   %d  %d  %d  %d  %d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}