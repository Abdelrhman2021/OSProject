#include<iostream>
#include<string>
#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include"psjf.h"
using namespace std;
int main()
{
	psjf p;
	P_data ps[100];
	cout << "Enter total number of processes: ";
	cin >> p.n;
	cout << "\n";
	for (int i = 0; i < p.n; i++)
	{
		cout << "Enter Process " << i << " Arrival Time: ";
		cin >> ps[i].at;
		cout << "\n";
		ps[i].pid = i;
	}
	
	for (int i = 0; i < p.n; i++)
	{
		cout << "Enter Process " << i << " Burst Time: ";
		cin >> ps[i].bt;
		cout << "\n";
	}

	while (p.completed != p.n)
	{
		int min_index = -1;
		int minimum = INT_MAX;
		for (int i = 0; i < p.n; i++)
		{
			if (ps[i].at <= p.clk && p.is_completed[i] == 0)
			{
				if (ps[i].bt < minimum)
				{
					minimum = ps[i].bt;
					min_index = i;
				}
				
				if (ps[i].bt == minimum)
					if (ps[i].at < ps[min_index].at)
					{
						minimum = ps[i].bt;
						min_index = i;
					}
			}
		}

		if (min_index == -1)
		{
			p.clk++;
		}
		else
		{
			ps[min_index].start_time = p.clk;
			ps[min_index].ft = ps[min_index].start_time + ps[min_index].bt;
			ps[min_index].tat = ps[min_index].ft - ps[min_index].at;
			ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

			p.sum_tat += ps[min_index].tat;
			p.sum_wt += ps[min_index].wt;
			p.total_idle_time += (p.is_first_process == true) ? 0 : (ps[min_index].start_time - p.prev);

			p.completed++;
			p.is_completed[min_index] = true;
			p.clk = ps[min_index].ft;
			p.prev = p.clk;
			p.is_first_process = false;
		}
	}

	p.max_completion_time = INT_MIN;
	p.min_arrival_time = INT_MAX;
	for (int i = 0; i < p.n; i++)
	{
		p.max_completion_time = p.findmax(p.max_completion_time, ps[i].ft);
		p.min_arrival_time = p.findmin(p.min_arrival_time, ps[i].at);
	}
	p.length_cycle = p.max_completion_time - p.min_arrival_time;

	cout << "\nProcess No.\tAT\tCPU Burst Time\tFT\tTAT\tWT\n";
	for (int i = 0; i < p.n; i++)
	{
		cout << ps[i].pid << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ft << "\t" << ps[i].tat << "\t" << ps[i].wt << "\n";
	}
	
	cout << "\n";

	p.cpu_utillization = (float)(p.length_cycle - p.total_idle_time) / p.length_cycle;

	cout << "Average Turn Around Time= " << (float)p.sum_tat / p.n << endl;
	cout << "\n";
	cout << "Average Waiting Time= " << (float)p.sum_wt / p.n << endl;
	cout << "\n";
	cout << "CPU Utillization(Percentage)= " << p.cpu_utillization*100 << "%" << endl;
	cout << "\n";

	system("pause");
	return 0;
}