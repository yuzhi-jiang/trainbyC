#include<iostream>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	int res=1;
	for(int i=0;i<n;++i){
		res*=2;
	}
	cout<<"2^"<<n<<" = "<<endl;



	return 0;
}
