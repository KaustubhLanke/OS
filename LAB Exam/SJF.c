#include<stdio.h>
int main(){

    int at[10],bt[10],tat[10],wt[10],p[10];
    float atat=0,awt=0;
    int no_process;

    printf("Enter the no. of processes = ");
    scanf("%d",&no_process);

    for(int i = 0;i<no_process;i++){
        printf("Enter process number = ");
        scanf("%d",&p[i]);
    }

    for(int i = 0;i<no_process;i++){
        printf("Enter no. of Burst time for process %d = ",i+1);
        scanf("%d",&bt[i]);
        printf("\n");
    }
printf("im here\n");
    int temp;

    for(int i = 0;i<no_process;i++){
        for(int j = 0;j<no_process-i-1;j++){
            if(bt[j] > bt[j+1]){
                temp = bt[j+1];
                bt[j+1] = bt[j];
                bt[j] = temp;

                temp = p[j+1];
                p[j+1] = p[j];
                p[j] = temp;
            }
        }
    }
    for (int i = 0;i<no_process;i++){
        wt[i] = 0;
        tat[i] = 0;
        for(int j = 0;j<i;j++){
            wt[i]=wt[i]+bt[j];
        }
        tat[i]= wt[i]+bt[i];
        awt=awt+wt[i];
        atat =  atat+tat[i];
    }

    printf("PID BT TAT WT\n");
    for(int i = 0;i<no_process;i++){
        printf("%d  %d  %d  %d\n",p[i],bt[i],tat[i],wt[i]);
    }
    return 0;
}