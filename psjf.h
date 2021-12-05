#pragma once
using namespace std;
struct P_data
{
    float pid;
    float at;
    float bt;
    float ft;
    float wt;
    float tat;
    float start_time;
};

class psjf
{
public:
    int n;
    bool is_completed[100] = { false }, is_first_process = true;
    int clk = 0;
    int completed = 0;
    int sum_tat = 0, sum_wt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utillization;
    int max_completion_time, min_arrival_time;

public:
    int findmax(int a, int b);
    int findmin(int a, int b);
};

