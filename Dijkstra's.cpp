#include <bits/stdc++.h>
using namespace std;

class MetroMap {
public:
    map<string, vector<pair<string, int>> > adj;
    void addNode(const string& stationName) {
        adj[stationName] = {};
    }

    void addEdge(const string& station1, const string& station2, int distance) {
        adj[station1].emplace_back(station2, distance);
        adj[station2].emplace_back(station1, distance);
    }

    void displayStations() {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Stations in the metro map:" << endl;
        int count = 1;
        for (const auto& pair : adj) {
            cout << count << ". " << pair.first << endl;
            count++;
        }
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void displayMetroMap() {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Metro Map:" << endl;
        for (const auto& pair : adj) {
            cout << pair.first << " -> ";
            for (const auto& connection : pair.second) {
                cout << connection.first << " (" << connection.second << " KM) ";
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};

class DijkstraAlgo {
public:
    vector<int> dijkstra(map<string, vector<pair<string, int>> > adj, const string& source) {
        map<string, int> dist;
        for (const auto& pair : adj) {
            dist[pair.first] = INT_MAX;
        }
        dist[source] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, source});
        while (!pq.empty()) {
            int dis = pq.top().first;
            string node = pq.top().second;
            pq.pop();
            for (const auto& it : adj[node]) {
                string adjNode = it.first;
                int edgeWeight = it.second;
                if (dis + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = dis + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        vector<int> distances;
        for (const auto& pair : dist) {
            distances.push_back(pair.second);
        }
        return distances;
    }
}

int main() {
    MetroMap metroMap;
    metroMap.addNode("CLOCK TOWER");
    metroMap.addNode("DILARAM CHOWK");
    metroMap.addNode("BB");
    metroMap.addNode("CENTERIO MALL");
    metroMap.addNode("KRISHAN NAGAR CHOWK");
    metroMap.addNode("RAJ BHAWAN");
    metroMap.addNode("ISBT");
    metroMap.addNode("BALLUPUR CHOWK");
    metroMap.addNode("ONGC");
    metroMap.addNode("VASANT VIHAR");
    metroMap.addNode("PANDITWADI");
    metroMap.addNode("IMA");
    metroMap.addNode("MB");
    metroMap.addNode("PREM NAGER");
    metroMap.addNode("PHULSANI");
    metroMap.addNode("NANDA KI CHOWKI");
    metroMap.addNode("PONDHA");
    metroMap.addNode("KANDOLI");
    metroMap.addNode("UPES");
    metroMap.addEdge("CLOCK TOWER", "BB", 10);  // Multiply by 10
    metroMap.addEdge("CLOCK TOWER", "DILARAM CHOWK", 19);  // Multiply by 10
    metroMap.addEdge("BB", "KRISHAN NAGAR CHOWK", 13);  // Multiply by 10
    metroMap.addEdge("KRISHAN NAGAR CHOWK", "BALLUPUR CHOWK", 19);  // Multiply by 10
    metroMap.addEdge("BALLUPUR CHOWK", "ISBT", 75);  // Multiply by 10
    metroMap.addEdge("BALLUPUR CHOWK", "VASANT VIHAR", 25);  // Multiply by 10
    metroMap.addEdge("VASANT VIHAR", "PANDITWADI", 22);  // Multiply by 10
    metroMap.addEdge("PANDITWADI", "IMA", 18);  // Multiply by 10
    metroMap.addEdge("IMA", "MB", 10);  // Multiply by 10
    metroMap.addEdge("MB", "PREM NAGER", 5);  // Multiply by 10
    metroMap.addEdge("IMA", "PREM NAGER", 23);  // Multiply by 10
    metroMap.addEdge("PREM NAGER", "NANDA KI CHOWKI", 24);  // Multiply by 10
    metroMap.addEdge("NANDA KI CHOWKI", "PHULSANI", 50);  // Multiply by 10
    metroMap.addEdge("DILARAM CHOWK", "CENTERIO MALL", 28);  // Multiply by 10
    metroMap.addEdge("CENTERIO MALL", "RAJ BHAWAN", 13);  // Multiply by 10
    metroMap.addEdge("RAJ BHAWAN", "ONGC", 42);  // Multiply by 10
    metroMap.addEdge("ONGC", "BALLUPUR CHOWK", 25);  // Multiply by 10
    metroMap.addEdge("ONGC", "PHULSANI", 40);  // Multiply by 10
    metroMap.addEdge("PHULSANI", "PONDHA", 20);  // Multiply by 10
    metroMap.addEdge("NANDA KI CHOWKI", "PONDHA", 36);  // Multiply by 10
    metroMap.addEdge("PONDHA", "KANDOLI", 30);  // Multiply by 10
    metroMap.addEdge("KANDOLI", "UPES", 30);  // Multiply by 10
    while (true) {
        cout << endl;
        cout << "\n\t\t\t***WELCOME TO THE METRO APP***" << std::endl;
        cout << "\t\t\t       ~LIST OF ACTIONS~\n\n";
        cout << "1. Shortest path by Dijkstra's algorithm" << endl;
        cout << "2. Display stations" << endl;
        cout << "3. Display metro map" << endl;
        cout << "4. Add Station" << endl;
        cout << "5. Add Connection" << endl;
        cout << "6. Exit" << endl;
        int choice;
        cout << "Enter Your Choice form (1 <--> 6): ";
        cin >> choice;
        if (choice == 6) {
            break;
        }
        switch (choice) {
            case 1: {
                string source;
                cout << "Enter the source station: ";
                cin.ignore();
                getline(cin, source);
                vector<int> distances = dijkstraAlgo.dijkstra(metroMap.adj, source);
                int i = 0;
                for (const auto& pair : metroMap.adj) {
                    cout << "Shortest distance from " << source << " to " << pair.first << " is " << float(distances[i])/10.0 << " KM" << endl;
                    i++;
                }
                break;
            }
            case 2: {
                metroMap.displayStations();
                break;
            }
            case 3: {
                metroMap.displayMetroMap();
                break;
            }
            case 4: {
                string stationName;
                cout << "Enter the name of the station to add: ";
                cin.ignore();
                getline(cin, stationName);
                metroMap.addNode(stationName);
                cout << "Station '" << stationName << "' added to the metro map." << endl;
                break;
            }
            case 5: {
                string station1, station2;
                int distance;
                cout << "Enter the names of the two stations to connect: ";
                cin.ignore();
                getline(cin, station1);
                getline(cin, station2);
                cout << "Enter the distance between " << station1 << " and " << station2 << ": ";
                cin >> distance;
                metroMap.addEdge(station1, station2, distance);
                cout << "Connection added between " << station1 << " and " << station2 << " with a distance of " << distance << " KM." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }
        }
    }
    return 0;
}