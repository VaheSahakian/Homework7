#include <stdio.h>

struct Process {
    int pid, at, bt, wt, tat, rt;
};

void swap(struct Process *a, struct Process *b){
       struct Process t=*a; *a=*b; *b=t; 
}
void sort_by_arrival(struct Process p[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(p[j].at > p[j+1].at || (p[j].at == p[j+1].at && p[j].pid > p[j+1].pid)){
                swap(&p[j], &p[j+1]);
	    }
	}
    }
}

void fcfs(struct Process p[], int n) {
    sort_by_arrival(p, n);

    int time = 0;
    printf("\n=== First Come First Served (FCFS) ===\n");
    printf("Gantt Chart: ");
    for (int i =0; i < n; i++) {
        if (time < p[i].at) {
		time = p[i].at;
	}
        p[i].wt = time - p[i].at;
        p[i].rt = p[i].wt;
        p[i].tat =p[i].wt + p[i].bt;
        time += p[i].bt;
        printf("| P%d ", p[i].pid);
    }
    printf("|\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    float awt =0, atat =0, art =0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].rt);
        awt += p[i].wt; atat += p[i].tat; art += p[i].rt;
    }
    printf("\nAverage Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n", atat / n);
    printf("Average Response Time: %.2f\n", art / n);
}

void sjf(struct Process p[], int n) {
    int done[n];
    for(int i=0;i<n;i++){
	    done[i]=0;
    }
    struct Process out[n];

    sort_by_arrival(p,n);

    int time = p[0].at;
    for (int i=1;i<n;i++){
	    if(p[i].at < time){
		   time= p[i].at;
	    }
    }

    int completed = 0;
    printf("\n=== Shortest Job First (SJF) ===\n");
    printf("Gantt Chart: ");

    while (completed<n) {
        int idx = -1;
        for (int i = 0; i <n; i++) {
            if (done[i] || p[i].at > time){ 
		   continue;
	    }
            if (idx == -1){
		   idx = i;
	    }
            else {
                if (p[i].bt < p[idx].bt){
			idx = i;
		}
                else if (p[i].bt ==p[idx].bt) {
                    if (p[i].at < p[idx].at){
			    idx = i;
		    }
                    else if (p[i].at==p[idx].at && p[i].pid < p[idx].pid){
			    idx = i;
		    }
                }
            }
        }
        if (idx == -1) {
	       	time++; continue; 
	} 

        out[completed] = p[idx];
        out[completed].wt  = time -p[idx].at;
        out[completed].rt  = out[completed].wt;
        out[completed].tat = out[completed].wt + p[idx].bt;

        time += p[idx].bt;
        done[idx] =1;
        printf("| P%d ", p[idx].pid);
        completed++;
    }
    printf("|\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    float awt = 0, atat = 0, art = 0;
    for (int i = 0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               out[i].pid, out[i].at, out[i].bt,out[i].wt, out[i].tat, out[i].rt);
        awt += out[i].wt; atat += out[i].tat; art +=out[i].rt;
    }
    printf("\nAverage Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n", atat / n);
    printf("Average Response Time: %.2f\n", art / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d",&p[i].at, &p[i].bt);
    }
    fcfs(p,n);
    sjf(p,n);
    return 0;
}

