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

typedef pair<int, int> coordinator;
typedef pair<coordinator, coordinator> edge;

vector<edge> mazeGenerator(int seed, int width, int height, bool withSeed) {
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }

    vector<edge> edges;
    if (withSeed) {
        srand(time(0) + seed);
    } else {
        srand(time(0));
    }

    bool keepHunting = true;
    bool keepKilling = true;

    coordinator startingCell;
    startingCell.first = rand() % height;
    startingCell.second = rand() % width;
    visitedArray[startingCell.first][startingCell.second] = true;
    bool starting = true;

    while (keepHunting) {
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[j][i]) {
                    keepKilling = true;
                    break;
                } else {
                    keepKilling = false;
                }
            }
        }
        while (keepKilling) {
            vector<coordinator> neighbours;
            neighbours.clear();

            if (startingCell.first - 1 > -1) {
                coordinator topCell;
                topCell.first = startingCell.first - 1;
                topCell.second = startingCell.second;
                neighbours.push_back(topCell);
            }

            if (startingCell.second + 1 < width) {
                coordinator rightCell;
                rightCell.first = startingCell.first;
                rightCell.second = startingCell.second + 1;
                neighbours.push_back(rightCell);
            }

            if (startingCell.first + 1 < height) {
                coordinator bottomCell;
                bottomCell.first = startingCell.first + 1;
                bottomCell.second = startingCell.second;
                neighbours.push_back(bottomCell);
            }

            if (startingCell.second - 1 > -1) {
                coordinator leftCell;
                leftCell.first = startingCell.first;
                leftCell.second = startingCell.second - 1;
                neighbours.push_back(leftCell);
            }

            vector<int> randomizedNeighbours;
            randomizedNeighbours.clear();
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom = rand() % neighbours.size();
                bool addingRandom = true;
                for (int i = 0; i < randomizedNeighbours.size(); ++i) {
                    if (randomizedNeighbours[i] == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                if (addingRandom) {
                    randomizedNeighbours.push_back(currentRandom);
                    coordinator neighbour = neighbours[currentRandom];
                    if (!visitedArray[neighbour.first][neighbour.second]) {
                        keepSeeking = false;
                        visitedArray[neighbour.first][neighbour.second] = true;
                        edge edge1;
                        edge1.first = startingCell;
                        edge1.second = neighbour;
                        edges.push_back(edge1);
                        startingCell.first = neighbour.first;
                        startingCell.second = neighbour.second;
//                        cout << "Killed";
                    }
                } else {
                    if (randomizedNeighbours.size() == neighbours.size()) {
                        keepSeeking = false;
                        keepKilling = false;
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
                    vector<coordinator> neighbours;
                    neighbours.clear();
                    if (startingCell.first - 1 > -1) {
                        coordinator topCell;
                        topCell.first = startingCell.first - 1;
                        topCell.second = startingCell.second;
                        neighbours.push_back(topCell);
                    }

                    if (startingCell.second + 1 < width) {
                        coordinator rightCell;
                        rightCell.first = startingCell.first;
                        rightCell.second = startingCell.second + 1;
                        neighbours.push_back(rightCell);
                    }

                    if (startingCell.first + 1 < height) {
                        coordinator bottomCell;
                        bottomCell.first = startingCell.first + 1;
                        bottomCell.second = startingCell.second;
                        neighbours.push_back(bottomCell);
                    }

                    if (startingCell.second - 1 > -1) {
                        coordinator leftCell;
                        leftCell.first = startingCell.first;
                        leftCell.second = startingCell.second - 1;
                        neighbours.push_back(leftCell);
                    }
                    for (int j = 0; j < neighbours.size(); ++j) {
                        coordinator neighbour = neighbours[j];
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
                                coordinator neighbour = neighbours[currentRandom];
                                if (visitedArray[neighbour.first][neighbour.second]) {
                                    keepSeeking = false;
                                    visitedArray[startingCell.first][startingCell.second] = true;
                                    edge edge1;
                                    edge1.first = startingCell;
                                    edge1.second = neighbour;
                                    edges.push_back(edge1);
//                                    cout << "Hunted";
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
                    keepHunting = true;
                    break;
                } else {
                    keepHunting = false;
                }
            }
        }
    }

    return edges;
}


int whereIsYourEdge(int seed, int width, int height, bool withSeed) {
    vector<pair<pair<int, int>, pair<int, int>>> mazeVector = mazeGenerator(seed, width, width, true);
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

    return 0;

}

int main() {

    whereIsYourEdge(123456, 10, 10, true);

    return 0;
}