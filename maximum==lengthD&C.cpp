#include <bits/stdc++.h>
using namespace std;

int n, a[200111], preright[200111], sufleft[200111], ans;

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
			++ans;
		}
	}
	for (int i=mb-1; i>=lb; --i){
		int m=sufleft[i];
		int j=i+m-1;
		if((j>=mb&&j<rb)&&preright[j]<m){
			++ans;
		}
	}
	if(rb-lb==1){
		if(a[lb]==1) ++ans;
		return;
	}
	dac(lb, mb);
	dac(mb, rb);
}

int main() {
	cin >> n;
	for (int i=0; i<n; ++i)
		cin >> a[i];
	dac();
	cout << ans << "\n";
}
