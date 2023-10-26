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
        // adj[station2].emplace_back(station1, distance);
    }
    void displayStations() {
        cout<< "-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "Stations in the metro map:" << endl;
        int count = 1;
        for (const auto& pair : adj) {
            cout << count << ". " << pair.first << endl;
            count++;
        }
        cout<< "-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    }
    void displayMetroMap() {
        cout<< "-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "Metro Map:" << endl;
        for (const auto& pair : adj) {
            cout << pair.first << " -> ";
            for (const auto& connection : pair.second) {
                cout << connection.first << " (" << connection.second << " KM) ";
            }
            cout << endl;
        }
        cout<< "-----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
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
};

class AntColonyOptimization {
public:
    vector<int> aco(map<string, vector<pair<string, int>> > adj, const string& source) {
        // Initialize parameters
        const int numAnts = 10;
        const double alpha = 1.0; // Pheromone influence
        const double beta = 2.0;  // Distance influence
        const double evaporationRate = 0.1;
        const double initialPheromone = 1.0;
        // Initialize pheromone levels
        map<string, map<string, double>> pheromones;
        for (const auto& pair : adj) {
            for (const auto& connection : pair.second) {
                pheromones[pair.first][connection.first] = initialPheromone;
                pheromones[connection.first][pair.first] = initialPheromone;
            }
        }
        vector<int> bestPathDistance;
        bestPathDistance.resize(adj.size(), INT_MAX);
        srand(static_cast<unsigned>(time(nullptr)));
        for (int iteration = 0; iteration < 100; iteration++) {
            vector<vector<int>> antPaths(numAnts);
            for (int ant = 0; ant < numAnts; ant++) {
                string currentStation = source;
                antPaths[ant].push_back(distanceFromSource(adj, source));
                vector<string> unvisitedStations;
                for (const auto& pair : adj) {
                    if (pair.first != source) {
                        unvisitedStations.push_back(pair.first);
                    }
                }
                while (!unvisitedStations.empty()) {
                    string nextStation = selectNextStation(currentStation, unvisitedStations, pheromones, adj, alpha, beta);
                    int distance = distanceFromSource(adj, nextStation);
                    antPaths[ant].push_back(distance);
                    updatePheromoneLevels(pheromones, currentStation, nextStation, antPaths[ant].back(), evaporationRate);
                    currentStation = nextStation;
                    // Using remove_if to erase based on a condition
                    unvisitedStations.erase(
                        remove_if(
                            unvisitedStations.begin(), unvisitedStations.end(),
                            [&](const string& station) { return station == nextStation; }),
                        unvisitedStations.end()
                    );
                }
                // Update best path distance
                if (antPaths[ant].back() < bestPathDistance.back()) {
                    bestPathDistance = antPaths[ant];
                }
            }
        }
        return bestPathDistance;
    }
    int distanceFromSource(const map<string, vector<pair<string, int>> >& adj, const string& station) {
        if (adj.find(station) != adj.end()) {
            int totalDistance = 0;
            for (const auto& connection : adj.at(station)) {
                totalDistance += connection.second;
            }
            return totalDistance;
        }
        return INT_MAX;
    }
    string selectNextStation(const string& currentStation, const vector<string>& unvisitedStations,const map<string, map<string, double>>& pheromones,const map<string, vector<pair<string, int>> >& adj,double alpha, double beta) {
        // Implement ant selection logic to choose the next station based on pheromones and distances.
        // This can be done using the pheromone and distance information, and a probability distribution.
        // Here's a simplified version that chooses a random unvisited station.
        int randomIndex = rand() % unvisitedStations.size();
        return unvisitedStations[randomIndex];
    }
    void updatePheromoneLevels(map<string, map<string, double>>& pheromones, const string& station1,const string& station2, int distance, double evaporationRate) {
        // Implement pheromone update logic, including evaporation and pheromone deposit.
        // The details of this logic depend on the ACO algorithm parameters and strategy.
        // This is a simplified version.
        pheromones[station1][station2] = (1 - evaporationRate) * pheromones[station1][station2] + (1.0 / distance);
        pheromones[station2][station1] = pheromones[station1][station2];
    }
};

int main() {
    MetroMap metroMap;
    DijkstraAlgo dijkstraAlgo;
    AntColonyOptimization acoAlgo;
    metroMap.addNode("zero");
    metroMap.addNode("one");
    metroMap.addNode("two");
    metroMap.addNode("three");
    metroMap.addNode("four");
    metroMap.addEdge("zero", "one", 3);
    metroMap.addEdge("zero", "three", 7);
    metroMap.addEdge("zero", "four", 8);
    metroMap.addEdge("one", "zero", 3);
    metroMap.addEdge("one", "two", 1);
    metroMap.addEdge("one", "three", 4);
    metroMap.addEdge("two", "one", 1);
    metroMap.addEdge("two", "three", 2);
    metroMap.addEdge("three", "two", 2);
    metroMap.addEdge("three", "one", 4);
    metroMap.addEdge("three", "zero", 7);
    metroMap.addEdge("three", "four", 3);
    metroMap.addEdge("four", "zero", 8);
    metroMap.addEdge("four", "three", 3);
    while (true) {
        cout << endl;
        cout << "\n\t\t\t***WELCOME TO THE METRO APP***" << std::endl;
        cout << "\t\t\t       ~LIST OF ACTIONS~\n\n";
        cout << "1. Shortest path by Dijkstra's algorithm" << endl;
        cout << "2. Shortest path by Ant Colony Optimization (ACO)" << endl;
        cout << "3. Display stations" << endl;
        cout << "4. Display metro map" << endl;
        cout << "5. Add Station" << endl;
        cout << "6. Add Connection" << endl;
        cout << "7. Exit" << endl;
        int choice;
        cout << "Enter Your Choice form (1 <--> 7): ";
        cin >> choice;
        if (choice == 7) {
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
                    cout << "Shortest distance from " << source << " to " << pair.first << " is " << distances[i] << " KM" << endl;
                    i++;
                }
                break;
            }
            case 2: {
                string source;
                cout << "Enter the source station: ";
                cin.ignore();
                getline(cin, source);
                vector<int> distances = acoAlgo.aco(metroMap.adj, source);
                int i = 0;
                for (const auto& pair : metroMap.adj) {
                    cout << "Shortest distance from " << source << " to " << pair.first << " is " << distances[i] << " KM" << endl;
                    i++;
                }
                break;
            }
            case 3: {
                metroMap.displayStations();
                break;
            }
            case 4: {
                metroMap.displayMetroMap();
                break;
            }
            case 5: {
                string stationName;
                cout << "Enter the name of the station to add: ";
                cin.ignore();
                getline(cin, stationName);
                metroMap.addNode(stationName);
                cout << "Station '" << stationName << "' added to the metro map." << endl;
                break;
            }
            case 6: {
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