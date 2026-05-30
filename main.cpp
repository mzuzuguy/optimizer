#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>


using namespace std;

// Structure representing a single network data packet
struct Packet {
    string packetId;
    long long timestamp;
    string serviceType;
    int priority;
    string payload;
};

// Function to parse the CSV-style log file
std::vector<Packet> loadNetworkLogs(const string& filename) {
    vector<Packet> packets;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return packets;
    }

    std::string line;
    while (getline(file, line)) {
        // Skip empty lines if any
        if (line.empty()) continue;

        stringstream ss(line);
        string pId, timeStr, service, priorityStr, payloadData;

        // Extract each comma-separated field
        getline(ss, pId, ',');
        getline(ss, timeStr, ',');
        getline(ss, service, ',');
        getline(ss, priorityStr, ',');
        getline(ss, payloadData, ',');

        // Safely convert strings to numeric types
        long long timestamp = stoll(timeStr);
        int priority = stoi(priorityStr);

        // Add the parsed packet to our vector using std::move to avoid deep copying strings
        packets.push_back(Packet{pId, timestamp, service, priority, move(payloadData)});
    }

    file.close();
    return packets;
}

int main() {
    string filename = "network_logs.txt";

    cout << "=== TNM Network Traffic Simulator (Phase 1) ===" << endl;
    cout << "Loading packets from " << filename << "..." << endl;

    // Measure the time it takes to parse the file
    auto start = chrono::high_resolution_clock::now();
    vector<Packet> loadedPackets = loadNetworkLogs(filename);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    if (loadedPackets.empty()) {
        cerr << "Failed to load packets. Please check if network_logs.txt exists." << std::endl;
        return 1;
    }

    // Print out verification results
    cout << "Successfully loaded " << loadedPackets.size() << " packets." << endl;
    cout << "Parsing Execution Time: " << duration << " microseconds." << endl;
    cout << "-----------------------------------------------" << endl;
    
    // Display the first packet to confirm correct data parsing
    cout << "First Loaded Packet Sample:" << endl;
    cout << "ID: " << loadedPackets[0].packetId << endl;
    cout << "Service: " << loadedPackets[0].serviceType << " (Priority: " << loadedPackets[0].priority << ")" << std::endl;
    cout << "Payload: " << loadedPackets[0].payload << endl;

    return 0;
}
