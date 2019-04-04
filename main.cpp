#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <stack>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

typedef pair<int, int> coord;
typedef pair<coord, coord> edge;

void feedMeYourInput();
vector<edge> huntNKillAlgo(int seed, int width, int height, bool seedStatus);
void whereIsYourEdge(int seed, int width, int height, bool seedStatus);

int main() {

    whereIsYourEdge(123456, 10, 10, true);

    return 0;
}

vector<edge> huntNKillAlgo(int seed, int width, int height, bool seedStatus) {
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }

    vector<edge> edges;
    if (seedStatus) {
        srand(clock() + seed);
    } else {
        srand(clock());
    }

    bool huntingStatus = true;
    bool killingStatus = true;

    coord startingCell;
    startingCell.first = rand() % height;
    startingCell.second = rand() % width;
    visitedArray[startingCell.first][startingCell.second] = true;
    bool starting = true;

    while (huntingStatus) {
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[j][i]) {
                    killingStatus = true;
                    break;
                } else {
                    killingStatus = false;
                }
            }
        }
        while (killingStatus) {
            vector<coord> neighbors;
            neighbors.clear();

            if (startingCell.first - 1 > -1) {
                coord topCell;
                topCell.first = startingCell.first - 1;
                topCell.second = startingCell.second;
                neighbors.push_back(topCell);
            }

            if (startingCell.second + 1 < width) {
                coord rightCell;
                rightCell.first = startingCell.first;
                rightCell.second = startingCell.second + 1;
                neighbors.push_back(rightCell);
            }

            if (startingCell.first + 1 < height) {
                coord bottomCell;
                bottomCell.first = startingCell.first + 1;
                bottomCell.second = startingCell.second;
                neighbors.push_back(bottomCell);
            }

            if (startingCell.second - 1 > -1) {
                coord leftCell;
                leftCell.first = startingCell.first;
                leftCell.second = startingCell.second - 1;
                neighbors.push_back(leftCell);
            }

            vector<int> availableNeighbors;
            availableNeighbors.clear();
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom = rand() % neighbors.size();
                bool addingRandom = true;
                for (int i = 0; i < availableNeighbors.size(); ++i) {
                    if (availableNeighbors[i] == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                if (addingRandom) {
                    availableNeighbors.push_back(currentRandom);
                    coord neighbour = neighbors[currentRandom];
                    if (!visitedArray[neighbour.first][neighbour.second]) {
                        keepSeeking = false;
                        visitedArray[neighbour.first][neighbour.second] = true;
                        edge edge1;
                        edge1.first = startingCell;
                        edge1.second = neighbour;
                        edges.push_back(edge1);
                        startingCell.first = neighbour.first;
                        startingCell.second = neighbour.second;
                    }
                } else {
                    if (availableNeighbors.size() == neighbors.size()) {
                        keepSeeking = false;
                        killingStatus = false;
                    }
                }
            }
        }

        bool foundStarting = false;
        for (int k = 0; k < height; ++k) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[k][i]) {
                    startingCell.first = k;
                    startingCell.second = i;
                    vector<coord> neighbours;
                    neighbours.clear();
                    if (startingCell.first - 1 > -1) {
                        coord topCell;
                        topCell.first = startingCell.first - 1;
                        topCell.second = startingCell.second;
                        neighbours.push_back(topCell);
                    }

                    if (startingCell.second + 1 < width) {
                        coord rightCell;
                        rightCell.first = startingCell.first;
                        rightCell.second = startingCell.second + 1;
                        neighbours.push_back(rightCell);
                    }

                    if (startingCell.first + 1 < height) {
                        coord bottomCell;
                        bottomCell.first = startingCell.first + 1;
                        bottomCell.second = startingCell.second;
                        neighbours.push_back(bottomCell);
                    }

                    if (startingCell.second - 1 > -1) {
                        coord leftCell;
                        leftCell.first = startingCell.first;
                        leftCell.second = startingCell.second - 1;
                        neighbours.push_back(leftCell);
                    }
                    for (int j = 0; j < neighbours.size(); ++j) {
                        coord neighbour = neighbours[j];
                        if (visitedArray[neighbour.first][neighbour.second]) {
                            foundStarting = true;
                            break;
                        }
                    }
                    if (foundStarting) {
                        vector<int> randomizedNeighbours;
                        randomizedNeighbours.clear();
                        bool keepSeeking = true;
                        while (keepSeeking) {
                            int currentRandom = rand() % neighbours.size();
                            bool addingRandom = true;
                            for (int m = 0; m < randomizedNeighbours.size(); ++m) {
                                if (randomizedNeighbours[m] == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                coord neighbour = neighbours[currentRandom];
                                if (visitedArray[neighbour.first][neighbour.second]) {
                                    keepSeeking = false;
                                    visitedArray[startingCell.first][startingCell.second] = true;
                                    edge edge1;
                                    edge1.first = startingCell;
                                    edge1.second = neighbour;
                                    edges.push_back(edge1);
                                }
                            } else {
                                if (randomizedNeighbours.size() == neighbours.size()) {
                                    keepSeeking = false;
                                    foundStarting = false;
                                }
                            }
                        }
                    }
                    if (foundStarting) {
                        break;
                    }
                }
            }
            if (foundStarting) {
                break;
            }
        }
        for (int l = 0; l < height; ++l) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[l][i]) {
                    huntingStatus = true;
                    break;
                } else {
                    huntingStatus = false;
                }
            }
        }
    }

    return edges;
}


void whereIsYourEdge(int seed, int width, int height, bool seedStatus) {
    vector<pair<pair<int, int>, pair<int, int>>> mazeVector = huntNKillAlgo(seed, width, width, seedStatus);
    vector<pair<pair<int, int>, pair<int, int>>> edgePathVector;

    for (auto i = 0; i < mazeVector.size(); i++) {
        cout << mazeVector[i].first.first << mazeVector[i].first.second << mazeVector[i].second.first << mazeVector[i].second.second << endl;
    }

    for (auto i = 0; i < mazeVector.size(); i++) {
        if (mazeVector[i].first.first < mazeVector[i].second.first && mazeVector[i].first.second == mazeVector[i].second.second) { //x increase, y not change
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].second.first, mazeVector[i].second.second), make_pair(mazeVector[i].second.first, mazeVector[i].second.second + 1)));
        }
        if (mazeVector[i].first.first == mazeVector[i].second.first && mazeVector[i].first.second < mazeVector[i].second.second) {//x not change, y increase
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].second.first, mazeVector[i].second.second), make_pair(mazeVector[i].second.first + 1, mazeVector[i].second.second)));
        }
        if (mazeVector[i].first.first == mazeVector[i].second.first && mazeVector[i].first.second > mazeVector[i].second.second) {//x not change, y decrease
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].first.first, mazeVector[i].first.second), make_pair(mazeVector[i].first.first + 1, mazeVector[i].first.second)));
        }
        if (mazeVector[i].first.first > mazeVector[i].second.first && mazeVector[i].first.second == mazeVector[i].second.second) {//x decrease, y not change
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].first.first, mazeVector[i].first.second), make_pair(mazeVector[i].first.first, mazeVector[i].first.second + 1)));
        }
    }

    float w = width;
    float h = height;

    vector<string> deleteSVGLineVector;


    for (vector<pair<pair<int, int>, pair<int, int>>>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->first.first)/w << "' y1='" << setprecision(2) << (it->first.second)/h << "' x2='" << setprecision(2) << (it->second.first)/w << "' y2='" << setprecision(2) << (it->second.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    for (vector<pair<pair<int, int>, pair<int, int>>>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->second.first)/w << "' y1='" << setprecision(2) << (it->second.second)/h << "' x2='" << setprecision(2) << (it->first.first)/w << "' y2='" << setprecision(2) << (it->first.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    stringstream ss;

    ss << "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'> \n";
    ss << "<rect width='1' height='1' style='fill: black' /> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='0' x2='1' y2='0'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='0' x2='1' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='1' x2='0' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='1' x2='0' y2='0'/> \n";

    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;

    for (auto i = 1; i <= h; i++) {

        float x1CP = 0;
        float y1CP = 0;
        float x2CP = 0;
        float y2CP = 0;

        for (auto j = 0; j < w; j++) {
            x1 = (1/w)*i;
            y1 = y1CP;
            x2 = x1;
            y2 = y1CP + (1/w);

            x1CP = x1;
            y1CP = y1;
            x2CP = x2;
            y2CP = y2;

            ss << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << x1 << "' y1='" << setprecision(2) << y1 << "' x2='" << setprecision(2) << x2 << "' y2='" << setprecision(2) << y2 << "'/> \n";

            x1 = (1/w)*i;
            y1 = y1CP + (1/w);
            x2 = x2CP - (1/w);
            y2 = y1CP + (1/w);

            x1CP = x1;
            y1CP = y1;
            x2CP = x2;
            y2CP = y2;

            ss << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << x1 << "' y1='" << setprecision(2) << y1 << "' x2='" << setprecision(2) << x2 << "' y2='" << setprecision(2) << y2 << "'/> \n";
        }
    }
    ss << "</svg> \n";

    string mazeString = ss.str();

    for (auto k = 0; k < deleteSVGLineVector.size(); k++) {
        string target = deleteSVGLineVector[k];

        int found = -1;
        do {
            found = mazeString.find(target, found + 1);
            if (found != -1) {
                mazeString = mazeString.substr(0, found) + mazeString.substr(found + target.length());
            }
        } while (found != -1);
    }

    ofstream file;
    file.open("aloha.svg");
    file << mazeString;
    file.close();
}