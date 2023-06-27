#include <iostream>
#include <cstdlib>
#include<thread>
#include<chrono>
#include <time.h>
using namespace std;

int main(){
    int n;
    cout<<"Enter the number of frames to be transmitted: "; 
    cin>>n;
    cout<< "Frame_No        Data       Waiting_Time (Sec)       Acknowledgement        Resend"<<endl;

    srand(time(0));
    int frame = 1, data, count;

    while(n--){
        data = rand()%100;
        Here:
        count = rand()%4;

        cout<<frame<<"                "<<data<<"           ";

        for(int i=0; i<5; i++){
            if(i <= count){
                cout<<i<<",";
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            else
            cout<<"    ";
        }

        if(count>2){
            cout<<"No             Resend"<<endl;;
            goto Here;
        }
        else 
            cout<<"Yes             No"<<endl;
        frame++;
    }
}