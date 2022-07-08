#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, q, a[200111];
ll pre[200111], ans[200111];

void dac(vector<vector<int>> &events){
	int mb=events.size()/2;
	vector<vector<int>> left=vector<vector<int>>(events.begin(), events.begin()+mb),
	right=vector<vector<int>>(events.begin()+mb, events.end());
	vector<vector<int>> event;
	for (auto it : left)
		if(it.size()==2)
			event.push_back(it);
	for (auto it : right)
		if(it.size()==3)
			event.push_back(it);
	sort(event.begin(), event.end());
	ll sum=0, speed=0, lind=0;
	for (auto e : event){
		sum+=(e[0]-lind)*speed;
		if(e.size()==2){
			speed+=e[1];
			sum+=e[1];
		} else{
			int index=e[2];
			if(e[1]==(ll)2e9)
				ans[index]-=sum;
			else
				ans[index]+=sum;
		}
		lind=e[0];
	}
	if(events.size()==1)
		return;
	dac(left);
	dac(right);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for (int i=1; i<=n; ++i)
		cin >> a[i], pre[i]=pre[i-1]+a[i];
	vector<vector<int>> events;
	int count=0;
	while(q--){
		int a;
		cin >> a;
		if(a==1){
			int x, y, val;
			cin >> x >> y >> val;
			events.push_back({x, val});
			events.push_back({y+1, -val});
		} else{
			int x, y;
			cin >> x >> y;
			events.push_back({x-1, (ll)2e9, count});
			events.push_back({y, (ll)2e9+1, count});
			ans[count]+=pre[y]-pre[x-1];
			count++;
		}
	}
	dac(events);
	for (int i=0; i<count; ++i)
		cout << ans[i] << "\n";
}
