#include <cstdio>
#include <iostream>
#include "maxflow.h"

using namespace std;

int main()
{
	int n, m, s, t;
	
	cin >> n >> m >> s >> t;
	
	maxFlow flow(n);
	
	while (m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		flow.Add(u, v, w);
	}
	
	cout << flow.maxflow(s, t);
	
	return 0;
}
