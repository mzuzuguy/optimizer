#include <iostream>
#include <queue>
#include <string> 
#include <vector>


using namespace std;

enum class Priority {
    BE = 0, //Web browsing
    AF = 1, //business-critical data like remote access or live feeds
    EF = 2  //VOIP and video time sensitive data
};

//structure representing a single network data packet
struct Packet {
    string packetId;
    long long timestamp;
    string serviceType;
    int priority;
    string payload;
};



  template<typename T>
int main(){

    Packet p1;
    
    //create min heap
    priority_queue<T,vector<T>, greater<T>> pq;



}


