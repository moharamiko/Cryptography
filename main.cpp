#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Lfsr {
private:
    static const int flips = 7;
    static const int ksize = 100;
    int key[ksize];
    int flipflops[flips];
    vector<int> feedbackTaps;

public:

    Lfsr() {

        for(int i = 0; i < flips; i++) {
            flipflops[i] = 0;
        }

        flipflops[1] = 1;
        flipflops[2] = 1;
    }


    void setInitialState(int state[], int size) {
        int minSize = (size < flips) ? size : flips;
        for(int i = 0; i < minSize; i++) {
            flipflops[i] = state[i];
        }
    }


    void setFeedbackTaps(vector<int> taps) {
        feedbackTaps = taps;
    }


    void xor_function() {
        int result = 0;
        for(int tap : feedbackTaps) {
            if(tap >= 0 && tap < flips) {
                result ^= flipflops[tap];
            }
        }
        flipflops[0] = result;
    }

    void generateKey() {
        for(int i = 0; i < ksize; i++) {

            for(int j = flips-1; j >= 1; j--) {
                flipflops[j] = flipflops[j-1];
            }

            key[i] = flipflops[flips-1];


            xor_function();
        }
    }

    void encrypt(string plain) {
        generateKey();

        cout << "Key is: ";
        for(int i = 0; i < plain.length() && i < ksize; i++) {
            cout << key[i];
        }
        cout << endl;

        string encrypted;
        for(int i = 0; i < plain.length() && i < ksize; i++) {
            if(key[i] == 1) {
                encrypted += char(plain[i] + 19);
            } else {
                encrypted += char(plain[i] + 14);
            }
        }
        cout << "Your encrypted text is: " << encrypted << endl;
    }

    void decrypt(string cipher) {
        generateKey();

        cout << "Key is: ";
        for(int i = 0; i < cipher.length() && i < ksize; i++) {
            cout << key[i];
        }
        cout << endl;

        string decrypted;
        for(int i = 0; i < cipher.length() && i < ksize; i++) {
            if(key[i] == 1) {
                decrypted += char(cipher[i] - 19);
            } else {
                decrypted += char(cipher[i] - 14);
            }
        }
        cout << "Your decrypted text is: " << decrypted << endl;
    }


    void displayState() {
        cout << "Current flipflop state: ";
        for(int i = 0; i < flips; i++) {
            cout << flipflops[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Lfsr test;

    cout << "LFSR Encryption/Decryption System: " << endl;

    // set the initial state for the flipflop
    cout<<"Enter your initial state: ";
    int initialstate[7];
    for (int i=0;i<7;i++)
    {
        cin>>initialstate[i];
    }

    test.setInitialState(initialstate, 7);

    cout << "Initial state set." << endl;
    test.displayState();

    int choice;
    cout << "Choose operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cin >> choice;

    cout<<"How many flips are included in the XOR process: ";
    int nflips;
    cin>>nflips;

    vector<int> taps;
    for(int i = 0; i < nflips; i++)
    {
        int temp;
        cout<<"Enter the index of flipflop "<<i+1<<" : ";
        cin>>temp;
        if(temp >= 0 && temp < 7) {
            taps.push_back(temp);
        }
    }

    test.setFeedbackTaps(taps);

    if(choice == 1) {
        string plain;
        cout << "Enter the plain text: ";
        cin >> plain;
        test.encrypt(plain);
    } else if(choice == 2) {
        string cipher;
        cout << "Enter the cipher text: ";
        cin >> cipher;
        test.decrypt(cipher);
    } else {
        cout << "Wrong choice!" << endl;
    }

    return 0;
}