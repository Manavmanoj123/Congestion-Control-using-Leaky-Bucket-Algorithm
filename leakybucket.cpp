#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// LeakyBucket class encapsulates all functionalities
class LeakyBucket {
private:
    int bucketSize;
    int outputRate;
    int buffer;
    int currentTime;
    vector<int> incomingPackets;

public:
    // Constructor
    LeakyBucket(int bSize, int oRate, vector<int> packets)
        : bucketSize(bSize), outputRate(oRate), buffer(0), currentTime(0), incomingPackets(packets) {}

    // Displays initial information
    void displayInitialInfo() {
        cout << "\n[INFO] Bucket Size     : " << bucketSize << " KB" << endl;
        cout << "[INFO] Output Rate     : " << outputRate << " KB/s" << endl;
        cout << "[INFO] Total Packets   : " << incomingPackets.size() << endl;
        cout << "------------------------------------------------------------\n";
    }

    // Main simulation logic
    void simulateTraffic() {
        cout << left << setw(8) << "Time" 
             << setw(15) << "Packet Size" 
             << setw(15) << "Buffer Size" 
             << setw(15) << "Action" << endl;

        cout << "------------------------------------------------------------\n";

        for (int i = 0; i < incomingPackets.size(); ++i) {
            currentTime++;
            int pkt = incomingPackets[i];

            cout << left << setw(8) << currentTime 
                 << setw(15) << (to_string(pkt) + " KB");

            if (pkt + buffer <= bucketSize) {
                buffer += pkt;
                cout << setw(15) << (to_string(buffer) + " KB") 
                     << "Accepted" << endl;
            } else {
                cout << setw(15) << (to_string(buffer) + " KB") 
                     << "Dropped" << endl;
            }

            // Simulate transmission
            transmit();
        }

        // Drain remaining buffer
        while (buffer > 0) {
            currentTime++;
            cout << left << setw(8) << currentTime 
                 << setw(15) << "0 KB"
                 << setw(15) << (to_string(buffer) + " KB") 
                 << "Sent" << endl;
            transmit();
        }
    }

private:
    // Simulate data transmission from buffer
    void transmit() {
        if (buffer > outputRate)
            buffer -= outputRate;
        else
            buffer = 0;
    }
};

// Function to generate random packet sizes
vector<int> generatePackets(int n) {
    vector<int> packets;
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        packets.push_back(rand() % 100 + 1); // Packet size between 1–100 KB
    }
    return packets;
}

// Main function
int main() {
    int bucketSize, outputRate, numPackets;

    cout << "=== Leaky Bucket Algorithm (OOP Simulation) ===\n";
    cout << "Enter Bucket Size (KB): ";
    cin >> bucketSize;

    cout << "Enter Output Rate (KB/s): ";
    cin >> outputRate;

    cout << "Enter Number of Packets: ";
    cin >> numPackets;

    // Generate random packets
    vector<int> packets = generatePackets(numPackets);

    // Create object and run simulation
    LeakyBucket lb(bucketSize, outputRate, packets);
    lb.displayInitialInfo();
    lb.simulateTraffic();

    return 0;
}