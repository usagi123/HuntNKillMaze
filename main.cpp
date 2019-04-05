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
typedef pair<coord, coord> mazePath, mazeEdges;

void feedMeInput(); //control the user input
void feedMeInputTwo(); //version 2
vector<mazePath> hnkAllDemCells(int seed, bool seedStatus, int width, int height); //Hunt and Kill algorithm
vector<mazeEdges> whereIsYourEdge(int seed, bool seedStatus, int width, int height); //Find edges between 2 cells in maze path
void drawThatSVGMazeForMe(string fileName, int seed, bool seedStatus, int width, int height); //Draw maze details into SVG files
void yourMazeDetailsInBinary(string fileName, int seed, bool seedStatus, int width, int height); //Export maze details into binary file
string readYourBinaryMazeDetails(string fileName); //and convert it from binary to string //Import maze details binary file
int rngDice(int min, int max); //Randomize function with mt19937

int main() {
    drawThatSVGMazeForMe("10x10.svg", 0, true, 10, 10);
//    yourMazeDetailsInBinary("aloha.maze", 123456, true, 10, 10);
//    cout << readYourBinaryMazeDetails("aloha.maze") << endl;

//    feedMeInput(); //TODO: WIP, still does not works properly. Only --g seed width height flag works
    return 0;
}

void feedMeInputTwo() {
    int seed = 0;
    bool seedStatus;
    int width = 0;
    int height = 0;
    string mazeSVGFileName;
    string mazeBinaryFileName;
    int choice = 0;

    cout << "Maze width: ";
    cin >> width;
    cout << "Maze height: ";
    cin >> height;
    cout << "Seed (optional, 0 to skip): ";
    cin >> seed;

    if (seed == 0) {
        seedStatus = false;
    } else {
        seedStatus = true;
    }
}

void feedMeInput() {
    string userInput;
    string stop = "stop";
    string errorInputMessage = "Wrong params \n";
    string zeroInputMessage = "Some input smaller or equal to 0 \n";
    string mazeGenCustomSeedMessage = "Running maze generator with custom seed \n";

    do {
        vector<string> userInputVector;
        bool validInput = false;

        pair<int, bool> defaultSeedFlag;
        pair<int, bool> customSeedFlag;
        pair<int, bool> loadBinaryFlag;
        pair<int, bool> loadSVGFlag;
        pair<int, bool> saveBinaryFlag;
        pair<int, bool> saveSVGFlag;

        cout << "./mazer ";
        getline(cin, userInput);

        stringstream ss;
        ss << userInput;
        copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(userInputVector));

        for (auto i = 0; i < userInputVector.size(); i++) {
            if (userInputVector[i] == "-g") {
                if (!defaultSeedFlag.second) {
                    defaultSeedFlag.first = i;
                    defaultSeedFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
            if (userInputVector[i] == "--g") {
                if (!customSeedFlag.second) {
                    customSeedFlag.first = i;
                    customSeedFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
            if (userInputVector[i] == "--lb") {
                if (!loadBinaryFlag.second) {
                    loadBinaryFlag.first = i;
                    loadBinaryFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
            if (userInputVector[i] == "--lv") {
                if (!loadSVGFlag.second) {
                    loadSVGFlag.first = i;
                    loadSVGFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
            if (userInputVector[i] == "--sb") {
                if (!saveBinaryFlag.second) {
                    saveBinaryFlag.first = i;
                    saveBinaryFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
            if (userInputVector[i] == "--sv") {
                if (!saveSVGFlag.second) {
                    saveSVGFlag.first = i;
                    saveSVGFlag.second = true;
                    validInput = true;
                } else {
                    validInput = false;
                    cout << errorInputMessage;
                    break;
                }
            }
        }

        if (validInput) {
            bool canSave = true;
            int mWidth = 0;
            int mHeight = 0;

            if (customSeedFlag.second) {
                int seed = 0;
                int width = 0;
                int height = 0;
                string fileName;

                try {
                    seed = stoi(userInputVector[customSeedFlag.first + 1]);
                    width = stoi(userInputVector[customSeedFlag.first + 2]);
                    height = stoi(userInputVector[customSeedFlag.first + 3]);
                    fileName = userInputVector[saveBinaryFlag.first + 4];

                    cout << fileName << endl;

                    if (seed > 0 && width > 0 && height > 0) {
                        canSave = true;
                        cout << mazeGenCustomSeedMessage;
                        mWidth = width;
                        mHeight = height;
                        whereIsYourEdge(seed, true, width, height);
//                        drawThatSVGMazeForMe(fileName, seed, true, width, height);
                        break;
                    } else {
                        canSave = false;
                        cout << zeroInputMessage;
                    }
                } catch (...) {
                    canSave = false;
                    cout << errorInputMessage;
                }
            }

            if (defaultSeedFlag.second) {
                int firstParam = 0;
                int secondParam = 0;

                try {
                    firstParam = stoi(userInputVector[defaultSeedFlag.first + 1]);
                    secondParam = stoi(userInputVector[defaultSeedFlag.first + 2]);

                    int thirdParam = 0;

                    try {
                        thirdParam = stoi(userInputVector[defaultSeedFlag.first + 3]);

                        if (firstParam > 0 && secondParam > 0 && thirdParam > 0) {
                            canSave = true;
                            cout << "Running maze generator with random seed \n";
                            mWidth = secondParam;
                            mHeight = thirdParam;
                            whereIsYourEdge(firstParam, true, secondParam, thirdParam);
                        } else {
                            canSave = false;
                            cout << zeroInputMessage;
                        }
                    } catch (...) {
                        if (firstParam > 0 && secondParam > 0) {
                            canSave = true;
                            cout << mazeGenCustomSeedMessage;
                            mWidth = firstParam;
                            mHeight = secondParam;
                            whereIsYourEdge(0, false, firstParam, secondParam);
                        } else {
                            canSave = false;
                            cout << zeroInputMessage;
                        }
                    }
                } catch (...) {
                    canSave = false;
                    cout << errorInputMessage;
                }
            }

            if (loadBinaryFlag.second) {
                // call load binary func here
            }

            if (loadSVGFlag.second) {
                // call load binary func here
            }

            if (customSeedFlag.second && saveBinaryFlag.second) {
                int seed = 0;
                int width = 0;
                int height = 0;
                string fileName;

                try {
                    seed = stoi(userInputVector[customSeedFlag.first + 1]);
                    width = stoi(userInputVector[customSeedFlag.first + 2]);
                    height = stoi(userInputVector[customSeedFlag.first + 3]);
//                    fileName = userInputVector[saveBinaryFlag.first + 4];

                    if (seed > 0 && width > 0 && height > 0) {
                        canSave = true;
                        cout << mazeGenCustomSeedMessage;
                        mWidth = width;
                        mHeight = height;
                        drawThatSVGMazeForMe(fileName, seed, true, width, height);
                        break;
                    } else {
                        canSave = false;
                        cout << zeroInputMessage;
                    }
                } catch (...) {
                    canSave = false;
                    cout << errorInputMessage;
                }
            }

        } else {
            if (userInputVector[0] != stop) {
                cout << errorInputMessage;
            }

            if (userInputVector[0] == stop) {
                break;
            }
        }
    } while (userInput != stop);
}

int rngDice(int min, int max) {
    int thatRandomNumber;

    random_device randomDevice; // obtain a random number from hardware
    mt19937 eng(randomDevice()); // seed the generator
    uniform_int_distribution<> distribution(min, max); // define the range

    thatRandomNumber = distribution(eng); // generate numbers

    return thatRandomNumber;
}

vector<mazePath> hnkAllDemCells(int seed, bool seedStatus, int width, int height) {
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }

    vector<mazePath> pathsList;
    //check if user does include seed or not
    if (seedStatus) { //if yes, combine user seed
        srand(clock() + seed);
        seedStatus = true;
    } else { //if no, then change seedStatus to false, proceed to use rngDice(int min, int max)
        seedStatus = false;
    }

    bool huntingStatus = true;
    bool killingStatus = true;

    //Pick starting cell coordinate randomly
    coord startingCell;
    if (seedStatus) {
        startingCell.first = rngDice(0, height);
        startingCell.second = rngDice(0, width);
    } else {
        startingCell.first = rand() % height;
        startingCell.second = rand() % width;
    }

    visitedArray[startingCell.first][startingCell.second] = true;
    bool starting = true;

    //In hunt mode to scan the whole grid
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

        //If found avaiable neighbors cell to visitedCell, then proceed to kill (move to it)
        while (killingStatus) {
            vector<coord> neighbors;
            neighbors.clear();

            //Map North/East/West/South cell's coordinator of visitedCell
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

            //Check if N/E/W/S cell found above available to move to or not
            vector<int> availableNeighbors;
            availableNeighbors.clear();
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom;
                if (seedStatus) {
                    currentRandom = rand() % neighbors.size();
                } else {
                    currentRandom = rngDice(0, neighbors.size());
                }
                bool addingRandom = true;
                for (int i = 0; i < availableNeighbors.size(); ++i) {
                    if (availableNeighbors[i] == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                if (addingRandom) {
                    //Pick one cell randomly in that vector to move
                    availableNeighbors.push_back(currentRandom);
                    coord neighbour = neighbors[currentRandom];
                    if (!visitedArray[neighbour.first][neighbour.second]) {
                        keepSeeking = false;
                        visitedArray[neighbour.first][neighbour.second] = true;
                        mazePath edge1;
                        edge1.first = startingCell;
                        edge1.second = neighbour;
                        pathsList.push_back(edge1);
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
                    for (int j = 0; j < neighbors.size(); ++j) {
                        coord neighbour = neighbors[j];
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
                            int currentRandom;
                            if (seedStatus) {
                                currentRandom = rand() % neighbors.size();
                            } else {
                                currentRandom = rngDice(0, neighbors.size());
                            }
                            bool addingRandom = true;
                            for (int m = 0; m < randomizedNeighbours.size(); ++m) {
                                if (randomizedNeighbours[m] == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                coord neighbour = neighbors[currentRandom];
                                if (visitedArray[neighbour.first][neighbour.second]) {
                                    keepSeeking = false;
                                    visitedArray[startingCell.first][startingCell.second] = true;
                                    mazePath edge1;
                                    edge1.first = startingCell;
                                    edge1.second = neighbour;
                                    pathsList.push_back(edge1);
                                }
                            } else {
                                if (randomizedNeighbours.size() == neighbors.size()) {
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
    return pathsList;
}

vector<mazeEdges> whereIsYourEdge(int seed, bool seedStatus, int width, int height) {
    //using returned maze path cell's coordinator, we can calculate the edge between 2 cells in that maze path
    vector<mazePath> mazeVector = hnkAllDemCells(seed, seedStatus, width, width);
    vector<mazeEdges> edgePathVector;

    for (auto i = 0; i < mazeVector.size(); i++) {
        //TODO: Think a way implement lambda function here for better readability
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

    return edgePathVector;
}

void drawThatSVGMazeForMe(string fileName, int seed, bool seedStatus, int width, int height) {
    float w = width;
    float h = height;
    vector<mazeEdges> edgePathVector = whereIsYourEdge(seed, seedStatus, width, height);

    //Got edges from whereIsYourEdge function above, we convert those edges coordinate into an SVG line
    vector<string> deleteSVGLineVector;

    for (vector<mazeEdges>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->first.first)/w << "' y1='" << setprecision(2) << (it->first.second)/h << "' x2='" << setprecision(2) << (it->second.first)/w << "' y2='" << setprecision(2) << (it->second.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    for (vector<mazeEdges>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->second.first)/w << "' y1='" << setprecision(2) << (it->second.second)/h << "' x2='" << setprecision(2) << (it->first.first)/w << "' y2='" << setprecision(2) << (it->first.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    //Generate a SVG grid
    stringstream ss;

    ss << "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'> \n";
    ss << "<rect width='1' height='1' style='fill: black' /> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='0' x2='1' y2='0'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='0' x2='1' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='1' x2='0' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='1' x2='0' y2='0'/> \n";

    //Draw SVG grid based on column loop
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

    //Find converted edges into SVG line that match in a SVG grid, remove that line. Which result in a maze
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
    file.open(fileName);
    file << mazeString;
    file.close();
}

void yourMazeDetailsInBinary(string fileName, int seed, bool seedStatus, int width, int height) {

    //Combine all data gathered and calculated into a mazeDetails
    pair<pair<int, int>, pair<int, vector<mazeEdges>>> mazeDetails;
    vector<mazeEdges> edges = whereIsYourEdge(seed, seedStatus, width, height);

    mazeDetails.first.first = width;
    mazeDetails.first.second = height;
    mazeDetails.second.first = edges.size();
    mazeDetails.second.second = edges;

    //Push into stringstream
    ofstream file;
    stringstream ss;
    ss << mazeDetails.first.first << "\n";
    ss << mazeDetails.first.second << "\n";
    ss << mazeDetails.second.first << "\n";
    for (auto i = 0; i < edges.size(); i++) {
        ss << edges[i].first.first << edges[i].first.second << edges[i].second.first << edges[i].second.second << "\n";
    }

    //And save it out
    file.open(fileName, ios::out | ios::binary);
    if (file.is_open()) {
        file.write((char const*) &ss, sizeof(ss));
        file.close();
    }
    else cout << "Unable to open file";
}

string readYourBinaryMazeDetails(string fileName) {

    //Read binary file, convert back to string
    ofstream file (fileName);
    string lineOfBinary;

    if (file.is_open()) {
        file.open(fileName, ios::out | ios::app);
        file.close();
    }
    else cout << "Unable to open file";

    stringstream ss(lineOfBinary);
    string output;
    while (ss.good()) {
        bitset<8> bits;
        ss >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    return output;
}