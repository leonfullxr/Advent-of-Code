#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Define the number of locations
const int numLocations = 7; // Update this according to the number of locations

// Function to calculate the total distance for a given route
int calculateTotalDistance(const std::vector<int>& route, const std::vector<std::vector<int>>& distances) {
    int totalDistance = 0;

    for (int i = 0; i < route.size() - 1; ++i) {
        totalDistance += distances[route[i]][route[i + 1]];
    }

    return totalDistance;
}

// Function to generate next lexicographically ordered permutation
bool nextPermutation(std::vector<int>& a) {
    int i = a.size() - 2;
    while (i >= 0 && a[i] >= a[i + 1]) {
        i--;
    }

    if (i < 0) {
        return false; // No more permutations
    }

    int j = a.size() - 1;
    while (a[j] <= a[i]) {
        j--;
    }

    std::swap(a[i], a[j]);
    std::reverse(a.begin() + i + 1, a.end());

    return true;
}

// Function to find the shortest route using brute force
std::vector<int> findShortestRoute(const std::vector<std::vector<int>>& distances) {
    std::vector<int> locations(numLocations);
    for (int i = 0; i < numLocations; ++i) {
        locations[i] = i;
    }

    std::vector<int> shortestRoute = locations;
    int shortestDistance = calculateTotalDistance(locations, distances);

    while (nextPermutation(locations)) {
        int currentDistance = calculateTotalDistance(locations, distances);
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            shortestRoute = locations;
        }
    }

    return shortestRoute;
}

int main() {
    // Read distances from a file
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Define the distances between locations
    std::vector<std::vector<int>> distances(numLocations, std::vector<int>(numLocations));

    for (int i = 0; i < numLocations; ++i) {
        for (int j = 0; j < numLocations; ++j) {
            inputFile >> distances[i][j];
        }
    }

    inputFile.close();

    // Find the shortest route
    std::vector<int> shortestRoute = findShortestRoute(distances);

    // Print the result
    std::cout << "Shortest route: ";
    for (int location : shortestRoute) {
        std::cout << location << " ";
    }
    std::cout << "\nShortest distance: " << calculateTotalDistance(shortestRoute, distances) << std::endl;

    return 0;
}
