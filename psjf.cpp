#include "psjf.h"
using namespace std;
int psjf::findmax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
int psjf::findmin(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
