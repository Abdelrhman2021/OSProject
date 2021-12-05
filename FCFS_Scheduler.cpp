#include <iostream>
using namespace std;

struct process_struct
{
	float pid, at, bt, ct, wt, tat, start_time;
}ps[100];

int find_max(int a, int b)
{
	return a > b ? a : b;
}

int comparatorAT(const void* a, const void* b)
{
	int x = ((struct process_struct*)a)->at;
	int y = ((struct process_struct*)b)->at;
	if (x < y)
		return -1;
	else if (x >= y)
		return 1;
}

int comparatorPID(const void* a, const void* b)
{
	int x = ((struct process_struct*)a)->pid;
	int y = ((struct process_struct*)b)->pid;
	if (x < y)
		return -1;
	else if (x >= y)
		return 1;
}

int main()
{
	int n;
	cout<<"Enter total number of process: "<<endl;
	cin >> n;
	float sum_tat = 0, sum_wt = 0;
	int length_cycle, total_idle_time=0;

	// take arrival time form user
	for (int i = 0; i < n; i++)
	{
		cout<<"Enter process arrival time: "<<i<<endl;
		cin>>ps[i].at;
		ps[i].pid = i;
    }
	 // take burst time form user 
	for (int i=0;i<n;i++)
	{
		cout<<"\nEnter process Burst Time: "<<i << endl;
		cin>>ps[i].bt;
	}
	// for sorting 

	qsort((void*)ps, n, sizeof(struct process_struct), comparatorAT);
	
	//calculations

	for (int i = 0; i < n; i++)
	{
		ps[i].start_time = (i == 0) ? ps[i].at : find_max(ps[i].at, ps[i - 1].ct);
		ps[i].ct = ps[i].start_time + ps[i].bt;
		ps[i].tat = ps[i].ct - ps[i].at;
		ps[i].wt = ps[i].tat - ps[i].bt;

		sum_tat += ps[i].tat;
		sum_wt += ps[i].wt;
		total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i].ct);
	}

	length_cycle = ps[n - 1].ct - ps[0].start_time;

	qsort((void*)ps, n, sizeof(struct process_struct), comparatorPID);
	 
	//output
	cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\t\n";
	for (int i = 0; i < n; i++)
		cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t"<< endl;
	cout << endl;
		
	
	
	cout<< "Average TAT = "<<sum_tat / n<<endl;
	cout << "Average TAT = " << sum_wt / n << endl;

}
