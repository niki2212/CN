#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int MAX_NumFrames = 50;
const int MAX_SECONDS = 3;

struct Frame {
    int num;
    string data;
    bool ack;
};

bool sendFrame(Frame frame) {
    int waiting_time = rand() % 4;
    cout << "         " << waiting_time << ", ";

    usleep(1000000);
    usleep(1000000);

    bool ack = rand() % 2;

    if (ack) {
        cout << "\t        Yes                 No" << endl;
    } else {
        cout << "\t        No                  Resend" << endl;
    }

    return ack;
}

int main() {
    srand(time(NULL)); 

    int n;
    cout << "Enter the number of frames to be transmitted: ";
    cin >> n;

    int w;
    cout << "Enter the window size: ";
    cin >> w;

    Frame frames[MAX_NumFrames];

    for (int i = 0; i < n; i++) {
        frames[i].num = i + 1;
        frames[i].data = to_string(rand() % 100);
        frames[i].ack = false;
    }

    cout<< "Frame_No        Data       Waiting_Time (Sec)       Acknowledgement        Resend"<<endl;

    int base = 0, count = 0;
    while (base < n) {
        for (int i = base; i < min(base + w, n); i++) {
            if (!frames[i].ack) {
                cout << "\n" << frames[i].num << "               " << frames[i].data << "         ";

                bool ack = sendFrame(frames[i]);

                if (ack) {
                    frames[i].ack = true;
                }
                count++;
            }
        }
        while (base < n && frames[base].ack) {
            base++;
        }
    }

    return 0;
}