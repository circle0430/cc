
 
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
inline int read()
{
	char ch=getchar();int i=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){i=(i<<3)+(i<<1)+ch-'0';ch=getchar();}
	return i*f;
}
const int N = 200010;
struct eg{ int to,before; }edge[N];
int n,m,tot,ecnt;
int last[N],pos[N],idx[N],fa[N],sdom[N],idom[N];
int father[N],val[N];
vector<int> pre[N],bkt[N];
int findf(int p)
{
	if(father[p]==p) return p;
	int r=findf(father[p]);
	if(sdom[val[father[p]]]<sdom[val[p]]) val[p] = val[father[p]];
	return father[p] = r;
}
inline int eval(int p)
{
	findf(p);
	return val[p];
}
void dfs(int p)
{
	idx[pos[p]=++tot]=p,sdom[p]=pos[p];
	for(int pt=last[p];pt;pt=edge[pt].before) if(!pos[edge[pt].to])
	dfs(edge[pt].to),fa[edge[pt].to]=p;
}
void work()
{
	int i,p;
	dfs(1);
	for(i=tot;i>=2;i--)
	{
		p=idx[i];
		for(int k:pre[p])
			if(pos[k])sdom[p]=min(sdom[p],sdom[eval(k)]);
		bkt[idx[sdom[p]]].push_back(p);
		int fp=fa[p];father[p]=fa[p];
		for(int v:bkt[fp])
		{
			int u = eval(v);
			idom[v] = sdom[u]==sdom[v]?fp:u;
		}
		bkt[fp].clear();
	}
	for(i=2;i<=tot;i++) p=idx[i],idom[p]=(idom[p]==idx[sdom[p]])?idom[p]:idom[idom[p]];
	for(i=2;i<=tot;i++) p=idx[i],sdom[p]=idx[sdom[p]];
}
inline void link(int a,int b)
{
	edge[++ecnt].to=b,edge[ecnt].before=last[a],last[a]=ecnt;
	pre[b].push_back(a);
}
int main()
{
	int i;
	n=read(),m=read();
	tot=ecnt=0;
	for(i=1;i<=n;i++)last[i]=pos[i]=0,father[i]=val[i]=i,pre[i].clear(),bkt[i].clear();
	for(i=1;i<=m;i++)
	{
		int a=read(); 
		link(a,read()); 
	}
	work();
	return 0;
}
