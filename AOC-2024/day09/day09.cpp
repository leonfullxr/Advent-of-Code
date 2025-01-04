#include <bits/stdc++.h>
using namespace std;

string parse_input(const string &filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open file '" << filename << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string diskMap;
    fin >> diskMap;
    fin.close();
    return diskMap;
}

vector<int> parseDiskMapToBlocks(const string &diskMap) {
    vector<pair<int,bool>> segments;
    for (int i = 0; i < (int)diskMap.size(); i++) {
        int length = diskMap[i] - '0';
        bool isFile = (i % 2 == 0);
        segments.push_back({length, isFile});
    }
    vector<int> blocks;
    int currentFileID = 0;
    for (auto &seg : segments) {
        if (seg.first == 0) continue;
        if (seg.second) {
            for (int i = 0; i < seg.first; i++) blocks.push_back(currentFileID);
            currentFileID++;
        } else {
            for (int i = 0; i < seg.first; i++) blocks.push_back(-1);
        }
    }
    return blocks;
}

void compactDisk(vector<int> &blocks) {
    while (true) {
        int leftmostFree = -1;
        for (int i = 0; i < (int)blocks.size(); i++) {
            if (blocks[i] == -1) {
                leftmostFree = i;
                break;
            }
        }
        if (leftmostFree == -1) break;
        int rightmostOccupied = -1;
        for (int i = (int)blocks.size() - 1; i >= 0; i--) {
            if (blocks[i] != -1) {
                rightmostOccupied = i;
                break;
            }
        }
        if (rightmostOccupied == -1) break;
        if (leftmostFree < rightmostOccupied) {
            blocks[leftmostFree] = blocks[rightmostOccupied];
            blocks[rightmostOccupied] = -1;
        } else {
            break;
        }
    }
}

void compactFilesByWholeMoves(vector<int> &blocks) {
    int maxFileID = -1;
    for (int id : blocks) maxFileID = max(maxFileID, id);
    for (int fileID = maxFileID; fileID >= 0; fileID--) {
        vector<int> positions;
        for (int i = 0; i < (int)blocks.size(); i++) {
            if (blocks[i] == fileID) positions.push_back(i);
        }
        if (positions.empty()) continue;
        int fileSize = (int)positions.size();
        int leftEdge = positions.front();
        int firstFreeCandidate = -1;
        for (int i = 0; i < leftEdge; i++) {
            if (blocks[i] == -1) {
                bool enoughSpace = true;
                for (int j = i; j < i + fileSize; j++) {
                    if (j >= (int)blocks.size() || j >= leftEdge || blocks[j] != -1) {
                        enoughSpace = false;
                        break;
                    }
                }
                if (enoughSpace) {
                    firstFreeCandidate = i;
                    break;
                }
            }
        }
        if (firstFreeCandidate == -1) continue;
        for (int i : positions) blocks[i] = -1;
        for (int i = 0; i < fileSize; i++) blocks[firstFreeCandidate + i] = fileID;
    }
}

long long computeChecksum(const vector<int> &blocks) {
    long long checksum = 0;
    for (int i = 0; i < (int)blocks.size(); i++) {
        if (blocks[i] != -1) checksum += (long long)i * blocks[i];
    }
    return checksum;
}

int main() {
    string diskMap = parse_input("input.txt");
    vector<int> blocks1 = parseDiskMapToBlocks(diskMap);
    compactDisk(blocks1);
    long long checksum1 = computeChecksum(blocks1);
    cout << "Part 1 Checksum: " << checksum1 << endl;

    vector<int> blocks2 = parseDiskMapToBlocks(diskMap);
    compactFilesByWholeMoves(blocks2);
    long long checksum2 = computeChecksum(blocks2);
    cout << "Part 2 Checksum: " << checksum2 << endl;

    return 0;
}
