import java.util.*;
import java.util.Map.Entry;

class MetroMap {
    Map<String, List<Pair>> adj = new HashMap<>();

    public void addNode(String stationName) {
        adj.put(stationName, new ArrayList<>());
    }

    public void addEdge(String station1, String station2, int distance) {
        adj.get(station1).add(new Pair(station2, distance));
        adj.get(station2).add(new Pair(station1, distance));
    }

    public void displayStations() {
        System.out.println("Stations in the metro map:");
        int count = 1;
        for (String station : adj.keySet()) {
            System.out.println(count + ". " + station);
            count++;
        }
    }

    public void displayMetroMap() {
        System.out.println("Metro Map:");
        for (Entry<String, List<Pair>> entry : adj.entrySet()) {
            System.out.print(entry.getKey() + " -> ");
            for (Pair connection : entry.getValue()) {
                System.out.print(connection.station + " (" + connection.distance + " KM) ");
            }
            System.out.println();
        }
    }

    class Pair {
        String station;
        int distance;

        public Pair(String station, int distance) {
            this.station = station;
            this.distance = distance;
        }
    }
}

class DijkstraAlgo {
    public Map<String, Integer> dijkstra(Map<String, List<MetroMap.Pair>> adj, String source) {
        Map<String, Integer> dist = new HashMap<>();
        for (String station : adj.keySet()) {
            dist.put(station, Integer.MAX_VALUE);
        }
        dist.put(source, 0);

        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(p -> p.distance));
        pq.add(new Pair(0, source));

        while (!pq.isEmpty()) {
            Pair top = pq.poll();
            int dis = top.distance;
            String node = top.station;

            for (MetroMap.Pair it : adj.get(node)) {
                String adjNode = it.station;
                int edgeWeight = it.distance;

                if (dis + edgeWeight < dist.get(adjNode)) {
                    dist.put(adjNode, dis + edgeWeight);
                    pq.add(new Pair(dist.get(adjNode), adjNode));
                }
            }
        }

        return dist;
    }

    class Pair {
        int distance;
        String station;

        public Pair(int distance, String station) {
            this.distance = distance;
            this.station = station;
        }
    }
}

class AntColonyOptimization {
    public Map<String, Integer> aco(Map<String, List<MetroMap.Pair>> adj, String source) {
        int numAnts = 10;
        double alpha = 1.0; // Pheromone influence
        double beta = 2.0;  // Distance influence
        double evaporationRate = 0.1;
        double initialPheromone = 1.0;

        Map<String, Map<String, Double>> pheromones = new HashMap<>();
        for (String station : adj.keySet()) {
            pheromones.put(station, new HashMap<>());
            for (MetroMap.Pair connection : adj.get(station)) {
                pheromones.get(station).put(connection.station, initialPheromone);
                pheromones.get(connection.station).put(station, initialPheromone);
            }
        }

        Map<String, Integer> bestPathDistance = new HashMap<>();
        for (String station : adj.keySet()) {
            bestPathDistance.put(station, Integer.MAX_VALUE);
        }

        Random rand = new Random(System.currentTimeMillis());

        for (int iteration = 0; iteration < 100; iteration++) {
            List<Map<String, Integer>> antPaths = new ArrayList<>();
            for (int ant = 0; ant < numAnts; ant++) {
                String currentStation = source;
                List<Integer> path = new ArrayList<>();
                path.add(distanceFromSource(adj, source));

                List<String> unvisitedStations = new ArrayList<>(adj.keySet());
                unvisitedStations.remove(source);

                while (!unvisitedStations.isEmpty()) {
                    String nextStation = selectNextStation(currentStation, unvisitedStations, pheromones, adj, alpha, beta);
                    int distance = distanceFromSource(adj, nextStation);
                    path.add(distance);
                    updatePheromoneLevels(pheromones, currentStation, nextStation, distance, evaporationRate);
                    currentStation = nextStation;
                    unvisitedStations.remove(nextStation);
                }

                if (path.get(path.size() - 1) < bestPathDistance.get(currentStation)) {
                    bestPathDistance.put(currentStation, path.get(path.size() - 1));
                }
            }
        }

        return bestPathDistance;
    }

    private int distanceFromSource(Map<String, List<MetroMap.Pair>> adj, String station) {
        if (adj.containsKey(station)) {
            int totalDistance = 0;
            for (MetroMap.Pair connection : adj.get(station)) {
                totalDistance += connection.distance;
            }
            return totalDistance;
        }
        return Integer.MAX_VALUE;
    }

    private String selectNextStation(String currentStation, List<String> unvisitedStations, Map<String, Map<String, Double>> pheromones,
                                     Map<String, List<MetroMap.Pair>> adj, double alpha, double beta) {
        // Implement ant selection logic to choose the next station based on pheromones and distances.
        // This can be done using the pheromone and distance information, and a probability distribution.

        // Here's a simplified version that chooses a random unvisited station.
        int randomIndex = new Random().nextInt(unvisitedStations.size());
        return unvisitedStations.get(randomIndex);
    }

    private void updatePheromoneLevels(Map<String, Map<String, Double>> pheromones, String station1, String station2,
                                     int distance, double evaporationRate) {
        // Implement pheromone update logic, including evaporation and pheromone deposit.
        // The details of this logic depend on the ACO algorithm parameters and strategy.
        // This is a simplified version.
        pheromones.get(station1).put(station2, (1 - evaporationRate) * pheromones.get(station1).get(station2) + (1.0 / distance));
        pheromones.get(station2).put(station1, pheromones.get(station1).get(station2));
    }
}

public class Main {
    public static void main(String[] args) {
        MetroMap metroMap = new MetroMap();
        DijkstraAlgo dijkstraAlgo = new DijkstraAlgo();
        AntColonyOptimization acoAlgo = new AntColonyOptimization();

        metroMap.addNode("Noida Sector 62~B");
        metroMap.addNode("Noida City Center~B");
        metroMap.addNode("Sector 15~B");
        metroMap.addEdge("Noida Sector 62~B", "Noida City Center~B", 6);
        metroMap.addEdge("Noida Sector 62~B", "Sector 15~B", 4);

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nChoose an option:");
            System.out.println("1. Shortest path by Dijkstra's algorithm");
            System.out.println("2. Shortest path by Ant Colony Optimization (ACO)");
            System.out.println("3. Display stations");
            System.out.println("4. Display metro map");
            System.out.println("5. Add Station");
            System.out.println("6. Add Connection");
            System.out.println("7. Exit");

            int choice = scanner.nextInt();

            if (choice == 7) {
                break;
            }

            switch (choice) {
                case 1: {
                    String source;
                    scanner.nextLine(); // Consume newline character
                    System.out.print("Enter the source station: ");
                    source = scanner.nextLine();
                    Map<String, Integer> distances = dijkstraAlgo.dijkstra(metroMap.adj, source);
                    int i = 0;
                    for (String station : metroMap.adj.keySet()) {
                        System.out.println("Shortest distance from " + source + " to " + station + " is " + distances.get(station) + " KM");
                        i++;
                    }
                    break;
                }
                case 2: {
                    String source;
                    scanner.nextLine(); // Consume newline character
                    System.out.print("Enter the source station: ");
                    source = scanner.nextLine();
                    Map<String, Integer> distances = acoAlgo.aco(metroMap.adj, source);
                    int i = 0;
                    for (String station : metroMap.adj.keySet()) {
                        System.out.println("Shortest distance from " + source + " to " + station + " is " + distances.get(station) + " KM");
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
                    String stationName;
                    scanner.nextLine(); // Consume newline character
                    System.out.print("Enter the name of the station to add: ");
                    stationName = scanner.nextLine();
                    metroMap.addNode(stationName);
                    System.out.println("Station '" + stationName + "' added to the metro map.");
                    break;
                }
                case 6: {
                    String station1, station2;
                    int distance;
                    scanner.nextLine(); // Consume newline character
                    System.out.print("Enter the names of the two stations to connect: ");
                    station1 = scanner.nextLine();
                    station2 = scanner.nextLine();
                    System.out.print("Enter the distance between " + station1 + " and " + station2 + ": ");
                    distance = scanner.nextInt();
                    metroMap.addEdge(station1, station2, distance);
                    System.out.println("Connection added between " + station1 + " and " + station2 + " with a distance of " + distance + " KM.");
                    break;
                }
                default: {
                    System.out.println("Invalid choice. Please select a valid option.");
                    break;
                }
            }
        }
    }
}