#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxn=100050;

int n, k, s[mxn], queries[mxn], id[mxn], dep[mxn], ans[mxn], suma[mxn], ssuma, licz[mxn], llicz;
bool marked[mxn], r[mxn];
vector<pair<int, int>> zamki;
vector<pair<int, int>> adj[mxn];

bool cmp(pair<int, int> x, pair<int, int> y){
	return id[x.first]<id[y.first];
}

void dfs(int u=0, int p=-1){
	s[u]=1;
	for (auto v : adj[u]){
		if(v.first==p||r[v.first]) continue;
		dfs(v.first, u);
		s[u]+=s[v.first];
	}
}

void dfs2(int u, int p, int king, int l){
	if(marked[u]) zamki.push_back({u, king});
	dep[u]=l;
	for (auto v : adj[u]){
		if(v.first==p||r[v.first]) continue;
		dfs2(v.first, u, king, l+v.second);
	}
}

int get(int u, int ms, int p){
	for (auto v : adj[u]){
		if(v.first==p||r[v.first]||s[v.first]*2<=ms)
			continue;
		return get(v.first, ms, u);
	}
	return u;
}

void crt(int u=0){
	llicz=0, ssuma=0;
	dfs(u);
	int c=get(u, s[u], -1);
	dep[c]=0;
	suma[c]=0, licz[c]=0;
	for (auto v : adj[c]){
		if(r[v.first]) continue;
		suma[v.first]=0, licz[v.first]=0;
		dfs2(v.first, c, v.first, v.second);
	}
	if(marked[c]) zamki.push_back({c, c});
	sort(zamki.begin(), zamki.end(), cmp);
	for (auto [u, king] : zamki){
		ans[id[u]]+=((dep[u]*(llicz-licz[king]))+(ssuma-suma[king]))*2;
		suma[king]+=dep[u];
		ssuma+=dep[u];
		llicz++;
		licz[king]++;
	}
	zamki.clear();
	r[c]=1;
	for (auto v : adj[c]){
		if(r[v.first]) continue;
		crt(v.first);
	}
}

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for (int i=1; i<n; ++i){
		int u, v, w;
		cin >> u >> v >> w, --u, --v;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	queries[0]=0, id[0]=0, marked[0]=1;
	for (int i=1; i<=k; ++i){
		cin >> queries[i], --queries[i];
		id[queries[i]]=i;
		marked[queries[i]]=1;
	}
	crt();
	int sumka=0;
	for (int i=1; i<=k; ++i){
		sumka+=ans[i];
		cout << sumka << "\n";
	}
}
