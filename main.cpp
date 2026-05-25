#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

// Structure representing a single network data packet
struct Packet {
    std::string packetId;
    long long timestamp;
    std::string serviceType;
    int priority;
    std::string payload;
};

// Function to parse the CSV-style log file
std::vector<Packet> loadNetworkLogs(const std::string& filename) {
    std::vector<Packet> packets;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return packets;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines if any
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string pId, timeStr, service, priorityStr, payloadData;

        // Extract each comma-separated field
        std::getline(ss, pId, ',');
        std::getline(ss, timeStr, ',');
        std::getline(ss, service, ',');
        std::getline(ss, priorityStr, ',');
        std::getline(ss, payloadData, ',');

        // Safely convert strings to numeric types
        long long timestamp = std::stoll(timeStr);
        int priority = std::stoi(priorityStr);

        // Add the parsed packet to our vector using std::move to avoid deep copying strings
        packets.push_back(Packet{pId, timestamp, service, priority, std::move(payloadData)});
    }

    file.close();
    return packets;
}

int main() {
    std::string filename = "network_logs.txt";

    std::cout << "=== TNM Network Traffic Simulator (Phase 1) ===" << std::endl;
    std::cout << "Loading packets from " << filename << "..." << std::endl;

    // Measure the time it takes to parse the file
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Packet> loadedPackets = loadNetworkLogs(filename);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    if (loadedPackets.empty()) {
        std::cerr << "Failed to load packets. Please check if network_logs.txt exists." << std::endl;
        return 1;
    }

    // Print out verification results
    std::cout << "Successfully loaded " << loadedPackets.size() << " packets." << std::endl;
    std::cout << "Parsing Execution Time: " << duration << " microseconds." << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    
    // Display the first packet to confirm correct data parsing
    std::cout << "First Loaded Packet Sample:" << std::endl;
    std::cout << "ID: " << loadedPackets[0].packetId << std::endl;
    std::cout << "Service: " << loadedPackets[0].serviceType << " (Priority: " << loadedPackets[0].priority << ")" << std::endl;
    std::cout << "Payload: " << loadedPackets[0].payload << std::endl;

    return 0;
}
