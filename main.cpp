// Copied on: 2025/03/19 09:40:42
// Extra comment: 38252821.37
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;

const int BFS_KILL_MAX=50;
const int BFS_KILLL_MAX=100;
const double DB=1.7;
const double GAP=0.65;
const double CUT=0.7;
const double NODE_PRO=0.4;
const double MAX_EN=1.9e8;
const double EDGE_LIMIT=300.0/2e5;
const double NODE_LIMIT=150.0/2e5;
const int KILL_NODE_LIMIT=6;

int n,now_round;

vector<int>root,kill_node;

int alive[MAXN];
int alive_cnt;

int alive_node,alive_edge;

bool set_root,first_set_root=0;
int del_edge,add_node;

class Node
{
public:
	vector<int>out,in;
	int value,id;
}node[MAXN];
bitset<MAXN>dead;
bitset<MAXN>is_root;
bitset<MAXN>vis;
bitset<MAXN>vis_;
int que[MAXN];
int que_[MAXN];

inline void Insert(vector<int> &e,const int u)
{
	e.insert(upper_bound(e.begin(),e.end(),u),u);
}
inline void Delete(vector<int> &e,const int u)
{
	e.erase(lower_bound(e.begin(),e.end(),u));
}
inline void AddEdgeF(const int u,const int v)
{
	alive_edge++;
	Insert(node[u].out,v);
	Insert(node[v].in,u);
}
inline void KillNode(const int now);
inline void BFSKill(const int now)
{
	if(!first_set_root||dead[now]||is_root[now])
	{
		return;
	}
	int head=0,tail=1,s=node[que[head]].in.size();
	if(s>BFS_KILL_MAX)
	{
		return;
	}
	que[tail]=now;
	vis[now]=1;
	while(++head<=tail)
	{
		for(int v:node[que[head]].in)
		{
			if(!vis[v])
			{
				s+=node[v].in.size();
				if(s>BFS_KILL_MAX||is_root[v])
				{
					for(int i=1;i<=tail;++i)
					{
						vis[que[i]]=0;
					}
					return;
				}
				vis[v]=1;
				que[++tail]=v;
			}
		}
	}
	vector<int>del(tail);
	for(int i=1;i<=tail;++i)
	{
		vis[que[i]]=0;
		del[i-1]=que[i];
	}
	for(int u:del)
	{
		KillNode(u);
	}
}
inline void BFSKilll(const int now)
{
	if(!first_set_root||dead[now]||is_root[now])
	{
		return;
	}
	int head=0,tail=1,s=node[que[head]].in.size();
	if(s>BFS_KILLL_MAX)
	{
		return;
	}
	que[tail]=now;
	vis[now]=1;
	while(++head<=tail)
	{
		for(int v:node[que[head]].in)
		{
			if(!vis[v])
			{
				s+=node[v].in.size();
				if(s>BFS_KILLL_MAX||is_root[v])
				{
					for(int i=1;i<=tail;++i)
					{
						vis[que[i]]=0;
					}
					return;
				}
				vis[v]=1;
				que[++tail]=v;
			}
		}
	}
	vector<int>del(tail);
	for(int i=1;i<=tail;++i)
	{
		vis[que[i]]=0;
		del[i-1]=que[i];
	}
	for(int u:del)
	{
		KillNode(u);
	}
}
inline void DeleteEdgeF(const int u,const int v)
{
	--alive_edge;
	++del_edge;
	Delete(node[u].out,v);
	Delete(node[v].in,u);
	BFSKill(v);
}
inline void KillNode(const int now)
{
	if(!first_set_root||dead[now]||is_root[now])
	{
		return;
	}
	dead[now]=1;
	alive[node[now].id]=0;
	alive_node--;
	alive_edge-=node[now].out.size();
	del_edge+=node[now].out.size();
	kill_node.push_back(now);
	for(int v:node[now].out)
	{
		Delete(node[v].in,now);
		if(node[v].in.size()==0)
		{
			KillNode(v);
		}
	}
	for(int v:node[now].out)
	{
		BFSKill(v);
	}
}
inline void KillNode_(const int now)
{
	dead[now]=1;
	alive_node--;
	alive_edge-=node[now].out.size()+node[now].in.size();
	kill_node.push_back(now);
	for(int v:node[now].out)
	{
		Delete(node[v].in,now);
	}
	for(int v:node[now].in)
	{
		Delete(node[v].out,now);
	}
}
inline void SetRoot()
{
	first_set_root=set_root=1;
	for(int u:root)
	{
		vis_[u]=0;
		is_root[u]=0;
	}
	int m;
	cin>>m;
	vector<int>root_last=root;
	root.resize(m);
	for(int i(0);i<m;++i)
	{
		cin>>root[i];
		vis_[root[i]]=1;
		que_[i+1]=root[i];
		is_root[root[i]]=1;
		int v=alive[i+1];
		if(v!=root[i])
		{
			alive[i+1]=root[i];
			alive[node[root[i]].id]=v;
			node[v].id=node[root[i]].id;
			node[root[i]].id=i+1;
		}
	}
	for(int u:root_last)
	{
		if(node[u].in.size()==0)
		{
			KillNode(u);
		}
		else
		{
			BFSKilll(u);
		}
	}
}
inline void AddEdge()
{
	int x,y;
	cin>>x>>y;
	AddEdgeF(x,y);
}
inline void DeleteEdge()
{
	int x,y;
	cin>>x>>y;
	DeleteEdgeF(x,y);
}
inline void AddNode()
{
	int x;
	char type;
	cin>>x>>type;
	++add_node;
	++alive_node;
	alive[++alive_cnt]=x;
	node[x].id=alive_cnt;
	dead[x]=0;
	cin>>node[x].value;
	int m,y;
	cin>>m;
	node[x].in.resize(m);
	alive_edge+=m;
	for(int i=0;i<m;++i)
	{
		cin>>y;
		Insert(node[y].out,x);
		node[x].in[i]=y;
	}
	sort(node[x].in.begin(),node[x].in.end());
	cin>>m;
	alive_edge+=m;
	node[x].out.resize(m);
	for(int i=0;i<m;++i)
	{
		cin>>y;
		Insert(node[y].in,x);
		node[x].out[i]=y;
	}
	sort(node[x].out.begin(),node[x].out.end());
}
inline int BFS()
{
	int head=0,tail=root.size();
	while(++head<=tail)
	{
		for(int v:node[que_[head]].out)
		{
			if(!vis_[v])
			{
				vis_[v]=1;
				que_[++tail]=v;
			}
		}
	}
	int alive_cnt_=root.size(),u;
	for(int i=root.size()+1;i<=alive_cnt;++i)
	{
		if(!(u=alive[i]))
		{
			continue;
		}
		if(!vis_[u])
		{
			KillNode_(u);
		}
		else
		{
			vis_[alive[node[u].id=++alive_cnt_]=u]=0;
		}
	}
	int result=alive_cnt-alive_cnt_;
	alive_cnt=alive_cnt_;
	return result*NODE_PRO;
}
inline double F0(const double x)
{
	return x;
}
inline double FPM(const double x)
{
	if(x>GAP)
	{
		return 1;
	}
	return 1-GAP+x;
}
inline double F1(const double x)
{
	return pow(x,DB);
}
inline double F2(const double x)
{
	return pow(x,1/DB);
}
inline double F3(const double x)
{
	if(x<CUT)
	{
		return CUT*F1(x/CUT);
	}
	else
	{
		return CUT+(1-CUT)*F2((x-CUT)/(1-CUT));
	}
}
inline double F4(const double x)
{
	if(x<CUT)
	{
		return CUT*F2(x/CUT);
	}
	else
	{
		return CUT+(1-CUT)*F1((x-CUT)/(1-CUT));
	}
}

int last_cnt=0,ask_cnt=0;
int sum_en=0;
inline void Ask()
{
	int ti;
	cin>>ti;
	if(!first_set_root)
	{
		cout<<0<<"\n"<<endl;
		return;
	}
	int need_en=alive_node+(alive_node-root.size())*NODE_PRO+alive_edge;
	double progress=1.0*now_round/n;
	int max_en=MAX_EN*F3(progress);
	int pro_max_en=MAX_EN*(FPM(progress));
	ask_cnt++;
	int edge_limit=alive_cnt*EDGE_LIMIT;
	int node_limit=alive_cnt*NODE_LIMIT;
	if(sum_en+need_en<pro_max_en&&set_root||sum_en+need_en<max_en&&(set_root||del_edge>edge_limit||add_node>node_limit||kill_node.size()>KILL_NODE_LIMIT)||n==now_round)
	{
		set_root=0;
		del_edge=0;
		add_node=0;
		sum_en+=need_en-BFS();
		last_cnt=ask_cnt;
	}
	cout<<kill_node.size()<<'\n';
	for(int u:kill_node)
	{
		cout<<u<<" ";
	}
	cout<<endl;
	kill_node.clear();
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	string opt;
	for(now_round=1;now_round<=n;++now_round)
	{
		cin>>opt;
		if(opt=="SetRoot")
		{
			SetRoot();
		}
		if(opt=="AddEdge")
		{
			AddEdge();
		}
		if(opt=="DeleteEdge")
		{
			DeleteEdge();
		}
		if(opt=="AddNode")
		{
			AddNode();
		}
		if(opt=="Ask")
		{
			Ask();
		}
	}
	return 0;
}
