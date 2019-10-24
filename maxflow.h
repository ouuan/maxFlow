/*

MIT License

Copyright (c) 2019 ouuan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

// for further information and bug tracking,
// please visit https://github.com/ouuan/maxFlow

#ifndef MAXFLOW_BY_OUUAN
#define MAXFLOW_BY_OUUAN 1

#include <queue>
#include <vector>
#include <algorithm>

class maxFlow
{
private:
	typedef long long ll;
	std::queue<int> q;
	std::vector<int> head, cur, nxt, to, dep;
	std::vector<ll> cap; 
public:
	maxFlow(int _n = 0) { init(_n); }
	void init(int _n)
	{
		head.clear();
		head.resize(_n + 1, -1);
	}
	void init() { init(head.size() - 1); }
	void add(int u, int v, ll w)
	{
		nxt.push_back(head[u]);
		head[u] = to.size();
		to.push_back(v);
		cap.push_back(w);
	}
	void Add(int u, int v, ll w)
	{
		add(u, v, w);
		add(v, u, 0);
	}
	void del(int x) { cap[(x - 1) << 1] = cap[(x - 1) << 1 | 1] = 0; }
	bool bfs(int s, int t)
	{
		dep.clear();
		dep.resize(head.size(), -1);
		dep[s] = 0;
		q.push(s);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = head[u]; ~i; i = nxt[i])
			{
				int v = to[i];
				ll w = cap[i];
				if (w > 0 && dep[v] == -1)
				{
					dep[v] = dep[u] + 1;
					q.push(v);
				}
			}
		}
		return ~dep[t];
	}
	ll dfs(int u, ll flow, int t)
	{
		if (dep[u] == dep[t]) return u == t ? flow : 0;
		ll out = 0;
		for (int& i = cur[u]; ~i; i = nxt[i])
		{
			int v = to[i];
			ll w = cap[i];
			if (w > 0 && dep[v] == dep[u] + 1)
			{
				ll f = dfs(v, std::min(w, flow - out), t);
				cap[i] -= f;
				cap[i ^ 1] += f;
				out += f;
				if (out == flow) return out;
			}
		}
		return out;
	}
	ll maxflow(int s, int t)
	{
		ll out = 0;
		while (bfs(s, t))
		{
			cur = head;
			out += dfs(s, 0x7fffffffffffffffll, t);
		}
		return out;
	}
	ll getflow(int x) const { return cap[(x - 1) << 1 | 1]; }
};

#endif
