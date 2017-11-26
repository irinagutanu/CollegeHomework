// FIND K NUMBERS IN A VECTOR THAT HAVE A GIVEN SUM S 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//naive method to find 2 numbers that have the sum s. we use cnt to make sure the repetitive cycles stop and ct to find out how many
//such sums we can find
void sum2vI(vector<int> v, int nr, int s){
    int cnt = 1, ct=0;
    for( int i=0; i < nr && cnt == 1; i++){
        for(int j=0; j< nr && cnt == 1; j++){
            if( v[i] + v[j] == s){
                cout << v[i] << "-" << v[j] << endl;
                cnt = 0;
                ct++;
            }
        }
    }
    if( ct == 0){
        cout << "Not found" << endl;
    }
}

//here we sort the vector and use two variables i and j, one starting left and another right
//to find out which numbers could give us the wanted sum 
void sum2vII(vector<int> v, int nr, int s){
    sort(v.begin(), v.end());
    int cnt = 1;
    for( int i=0; i<nr && cnt == 1; ){
        for( int j=nr-1; j>=0 && cnt == 1; ){
            if(v[i] + v[j] == s){
                cout << v[i] <<"-" << v[j] << endl;
                cnt = 0;
            }
            else if(v[i] + v[j] > s){
                j--;
            }
            else if(v[i] + v[j] < s){
                i++;
            }
            if( i >= j){
                cout << "Not found "<<endl;
                cnt = 0;
            }
        }
    }
}

//use the unordered_map library because the search is in O(1)
void sum2vIII(vector<int> v, int nr, int s){
    unordered_map<int, int> Map;
    for( int i=0; i<nr; i++){
        pair<int, int> elem(i, v[i]);
        Map.insert(elem);
    }
    int x=0;
    unordered_map<int, int>::iterator it=Map.begin();
    for(int i=0; i<nr; i++){
        if( Map.find(s - v[i]) != Map.end()){
            cout << v[i] <<"-" << s-v[i] <<endl;
            x++;
        }
    }
    if(x == 0){
        cout << "Not found"<<endl;
    }
}

//here we take 3 numbers and find out naively if they add to S
void sum3vI(vector<int> v, int nr, int s){
    sort(v.begin(), v.end());
    int cnt = 1;
    for( int i=0; i < nr && cnt == 1; i++){
        for( int j=i+1; j < nr && cnt == 1; ){
            for( int k = nr-1; k >= 0 && cnt == 1; ){
                if( v[i] + v[j] + v[k] == s){
                    cout << v[i] <<"-" << v[j] <<"-" <<v[k]<<endl;
                    cnt = 0;
                }
                else if( v[i] + v[j] + v[k] < s){
                    j++;
                }
                else if( v[i] + v[j] + v[k] > s){
                    k--;
                }
                if( k < j){
                    cnt = 2;
                }
            }
        }
    }
    if( cnt != 0){
        cout << "Not found" << endl;
    }
}

//we use unordered_map again for the 3 numbers
void sum3vII(vector<int> v, int nr, int s){
    unordered_map<int, int> Map;
    for( int i=0; i<nr; i++){
        pair<int, int> elem(i, v[i]);
        Map.insert(elem);
    }
    int x=0, bol = 1;
    unordered_map<int, int>::iterator it=Map.begin();
    for(int i=0; i<nr && bol == 1; i++){
        for( int j=i+1; j<nr && bol == 1; j++){
            it = Map.find( s-v[i]-v[j]);
            if( it != Map.end() && it->first != 0){
                cout << v[i] <<"-"<< v[j] << "-"<< s-v[i]-v[j] <<endl;
                x++;
                bol = 0;
            }
        }
    }
    if(x == 0){
        cout << "Not found"<<endl;
    }
}



int main()
{
    ifstream in;
    in.open("nr.in");
    int s, nr, x;
    vector<int> v;
    in >> nr;
    in >> s;
    for( int i=0; i < nr; i++){
        in >> x;
        v.push_back(x);
    }
    sum3vII(v, nr, s);
    return 0;
}
