#include <priority.enum.h>
#include <packet.h>

#include <iostream>
#include <queue>
#include <string> 
#include <vector>



using namespace std;

struct PacketComparator {
    // compare packets
    bool operator()(const packet& a, const packet& b) const {
        return a.priority < b.priority;
    }
};

int main()
{
    // Create a priority queue to hold packets
    priority_queue<packet, vector<packet>, PacketComparator> packetQueue;

    // Create some packets and add them to the queue
    packet p1 = {"packet1", 1622547800, "serviceA", 2, "payload1"};
    packet p2 = {"packet2", 1622547810, "serviceB", 1, "payload2"};
    packet p3 = {"packet3", 1622547820, "serviceC", 3, "payload3"};

    packetQueue.push(p1);
    packetQueue.push(p2);
    packetQueue.push(p3);

    // Process packets in order of priority
    while (!packetQueue.empty()) {
        packet currentPacket = packetQueue.top();
        cout << "Processing " << currentPacket.packetId << " with priority " << currentPacket.priority << endl;
        packetQueue.pop();
    }

    return 0;
}

