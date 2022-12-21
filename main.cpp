#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int calculateRedundant(int m){
    int r=0;
    while (pow(2, r)<=m+r){
        r++;
    }
    return r;
}

void printVector(vector<int>& vect)
{
    for(auto var: vect){
        cout<<var;
    }
}

void reservingParity(vector<int>& data_bits, vector<int>& hamming){
    int j =0, k=0;
    for (int i = 0; i < hamming.size() ; ++i) {
        if (pow(2,j)-1==i){
            hamming[i]= -1;
            j++;
        }
        else{
            hamming[i]=data_bits[k];
            k++;
        }
    }
}

void findHamming(vector<int>& hamming){
    for (int i = 0; i < (hamming.size()); i++) {
        if (hamming[i] != -1) // if it's not a redundant bit, skips the for
            continue;
        int x = log2(i + 1);
        int one_count = 0; //count for parity
        for (int j = i + 2; j <= (hamming.size()); ++j) {//counter that tells the machine for which bit to check
            if (j & (1 << x)) { //checks that the xh-bit is set and that the j has the bit as 1, it multiplies them
                if (hamming[j - 1] == 1) {
                    one_count++;
                }
            }
        }

        if (one_count % 2 == 0) {
            hamming[i] = 0;
        }
        else {
            hamming[i] = 1;
        }
    }
}

void AcceptBits(int n, vector<int>& input_bits){
    cout << "Write the bits\n";
    for (int i = 0; i < n; ++i) {
        cin >>input_bits[i];
    }
}

void EncodeHamming(){
    int m, r;
    cout<<"Write the number of bits\n";
    cin>>m;
    r = calculateRedundant(m);
    vector<int> input_bits(m), hamming(m+r);
    AcceptBits(m, input_bits);
    reservingParity(input_bits, hamming);
    findHamming(hamming);
    printVector(hamming);
}

vector<int> findParity(vector<int>& vect){
    int k=0;
    vector<int> data_bits;
    for(int i=0; i<vect.size(); i++ ){
        if(i==pow(2, k)-1) {
            k++;
            continue;
        }
        data_bits.push_back(vect[i]);
    }
    return data_bits;
}

void findErrorBit(vector<int> v1, vector<int> v2){
    for(int i=0; i<v1.size();++i){
        if(v1[i]!=v2[i])
            cout<<"error in bit: "<<i+1<<endl;
    }
}

void FindError(){
    int n;
    cout<<"Write the number of bits\n";
    cin>>n;
    vector<int> data, hamming(n), corrected(n);
    AcceptBits(n, hamming);
    data= findParity(hamming);
    reservingParity(data,corrected);
    findHamming(corrected);
    findErrorBit(corrected, hamming);
}

int main(){
    int n;
    cout<< "What do you wish to do?\n";
    cout<<"1. Encode data bits\n" << "2. Find error in encoded message\n";
    cin>>n;
    switch (n) {
        case(1):
            EncodeHamming();
            break;
        case(2):
            FindError();
            break;
        default:
            cout<< "Not a valid option";
            break;
    }
};