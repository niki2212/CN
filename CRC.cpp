//CRC
#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"Enter the number of bits in input data: ";
    int n; cin>>n;
    cout<<"Enter the number of bits in the polynomial generator(divisor): ";
    int m; cin>>m;
    cout<<"Enter the data: ";
    string data;
    cin>>data;
    cout<<"Enter the divisor: ";
    string divisor;
    cin>>divisor;

    for(int i=0; i<m-1; i++)
        data.push_back('0');
    
    string copydata = data;
    for(int i=0; i<n; i++)
    {
        if(data[i]=='0')
        {
            continue;
        }
        for(int j=0; j<m; j++)
        {
            if(data[i+j]==divisor[j])
                data[i+j]='0';
            else
                data[i+j]='1';
        }
    }
    for(int i=n; i<n+m; i++)
        copydata[i]=data[i];
    string crcvalue;
    for(int i=n;i<n+m; i++)
    {
        crcvalue.push_back(copydata[i]);
    }
    cout<<"CRC value: "<<crcvalue<<endl;
    cout<<"Transmitted data:"<<copydata<<endl;
    
    cout<<"Enter the received data: ";
    string receiver; cin>>receiver;
    
    for(int i=0; i<m-1; i++)
        receiver.push_back('0');

    for(int i=0; i<n; i++)
    {
        if(receiver[i]=='0')
        {
            continue;
        }
        for(int j=0; j<m; j++)
        {
            if(receiver[i+j]==divisor[j])
                receiver[i+j]='0';
            else
                receiver[i+j]='1';
        }
    }
    int flag=0;
    for(int i=n; i<n+m; i++)
    {
        if(receiver[i]=='1')
        {
            flag=1; 
        }
    }
    if(flag==1)
        cout<<"Errors detected"<<endl;
    else
        cout<<"No errors detected"<<endl;
}