#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, a[100111], to[100111], preright[100111], sufleft[100111], dp[100111];
bool vis[100111];
vector<vector<int>> jumps;

void dac(int lb=0, int rb=n){
	int mb=(lb+rb)/2;
	preright[mb]=a[mb];
	if(mb>lb) sufleft[mb-1]=a[mb-1];
	for (int i=mb+1; i<rb; ++i)
		preright[i]=max(preright[i-1], a[i]);
	for (int i=mb-2; i>=lb; --i)
		sufleft[i]=max(sufleft[i+1], a[i]);
	for (int j=mb; j<rb; ++j){
		int m=preright[j];
		int i=j-m+1;
		if((i<mb&&i>=lb)&&sufleft[i]<=m){
			if(to[i]>=j){
				jumps[i].push_back(j);
			}
		}
	}
	for (int i=mb-1; i>=lb; --i){
		int m=sufleft[i];
		int j=i+m-1;
		if((j>=mb&&j<rb)&&preright[j]<m){
			if(to[i]>=j){
				jumps[i].push_back(j);
			}
		}
	}
	if(rb-lb==1){
		if(a[lb]==1) jumps[lb].push_back(lb);
		return;
	}
	dac(lb, mb);
	dac(mb, rb);
}

int main(){
	cin >> n;
	jumps.resize(n);
	for (int i=0; i<n; ++i)
		cin >> a[i];
	for (int i=0, j=0; i<n; ++i){
		vis[a[i]]=1;
		j=max(j, i);
		while(j+1<n&&!vis[a[j+1]]){
			vis[a[j+1]]=1;
			j++;
		}
		to[i]=j;
		vis[a[i]]=0;
	}
	dac();
	dp[0]=1;
	for (int i=0; i<n; ++i){
		for (auto j : jumps[i]){
			if(j<n)
				dp[j+1]+=dp[i];
				//(dp[j+1]+=dp[i])%=M; - jesli chcieliby modulo
		}
	}
	cout << dp[n] << "\n";
//	cout << (dp[n]?"YES":"NO") << "\n"; - dla zadania z olimpiady
}
