#include<bits/stdc++.h>
using namespace std;

int main(){
    int i,j,k;
    // cout<<DBL_MAX<<endl;
    double a[] = {1.1,5.2,7.3,8.4,4.2,3,2.2,1};
    int size = sizeof(a)/sizeof(a[0]);

    for(i=0; i<size; i++){
        cout<<a[i]<<" ";
    }
    sort(a+0, a+size);
    cout<<endl;
    for(i=0; i<size; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}