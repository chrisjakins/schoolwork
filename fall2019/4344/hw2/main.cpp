/****
 * Chris Jakins
 * 1000802309
 * lab 2
 * 11/8/2019
 */
#include <string>
#include <iostream>
#include <fstream>

// for testing
#include <chrono>

#define STABLE 0
#define ITERATIVE 1

class NodeList {
public:
    NodeList(int len)
        : len_(len)
    { }

    int getLength() const {
        return len_;
    }

    void setLength(int newLength) {
        len_ = newLength;
    }

    void set(int i, int j, int val) {
        nodes_[i].dist_[j] = val;
    }

    const static int MAX_NODES = 6;
    const static int INF = 99;

private:
    struct node {
        int dist_[NodeList::MAX_NODES];
    };

    struct node nodes_[NodeList::MAX_NODES];
    int len_;
    
public:
    struct node at(int index) const {
        return nodes_[index];
    }

};


// This function simply performs the max operation on two integers
//
// @param x
// @param y
// @return the greater of x and y
int max(int x, int y) {
    return x > y ? x : y;
}


// This method prints each router in our list
//
// @param currRouters
// @param prevRouters
// @param init
//
void printNodes(const NodeList &currRouters
                , const NodeList *prevRouters
                , int init)
{
    for(int i = 0; i < currRouters.getLength(); ++i) {
        std::cout << "\n\n================" << std::endl;
        std::cout << "=== Router " << i + 1 << " ===" << std::endl;
        std::cout << "================" << std::endl;

        for(int j = 0; j < currRouters.getLength(); ++j) {
            for(int k = 0; k < currRouters.getLength(); ++k) {
                if ((!prevRouters && !init) || j == i) {
                    std::cout << currRouters.at(j).dist_[k] << "  ";
                }
                else {
                    if (init) {
                        std::cout << NodeList::INF << " ";
                    }
                    else {
                        std::cout << prevRouters->at(j).dist_[k] << "  ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}


// This function implements the Bellman Ford Algorithm
// as discussed in the slides
//
// @param currRouters 
// @param prevRouters
// @param distanceTable
// @return true if anything changed in current iteration
//
bool bellmanFordIteration(NodeList *currRouters
                          , NodeList *prevRouters
                          , int distanceTable[NodeList::MAX_NODES][NodeList::MAX_NODES])
{
    bool changed = false;

    //copy NodeList to one another, needed for proper printing
    memcpy(prevRouters, currRouters, sizeof(NodeList));

    for(int i = 0; i < currRouters->getLength(); ++i ) {
        for(int j = 0; j < currRouters->getLength(); ++j ) {
            for(int k = 0; k < currRouters->getLength(); ++k ) {
                if(currRouters->at(i).dist_[j] > distanceTable[i][k] + currRouters->at(k).dist_[j] ) {
                    int val = currRouters->at(i).dist_[k] + currRouters->at(k).dist_[j];
                    currRouters->set(i, j, val);
                    changed = true;
                }
            }
        }
    }

    return changed;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "\nUsage: ./a.out filename.txt\n" << std::endl;
        return 1;
    }

    int i = 0, j = 0;
    int dist = 0;
    int stepChoice = 0;
    int num_iterations = 0;
    bool hasChanged = true;

    int distanceTable[NodeList::MAX_NODES][NodeList::MAX_NODES];

    std::string line;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double, std::micro> duration;

    NodeList currRouters(0);
    NodeList prevRouters(0);

    // initialize distance table
    for (int i = 0; i < NodeList::MAX_NODES; ++i) {
        for (int j = 0; j < NodeList::MAX_NODES; ++j) {
            distanceTable[i][j] = i == j ? 0 : NodeList::INF;
        }
    }
     
    // file i/o for distance table population
    std::ifstream file;
    file.open(argv[1]);

    while (file >> i >> j >> dist) {
        distanceTable[i - 1][j - 1] = dist;
        distanceTable[j - 1][i - 1] = dist;
        currRouters.setLength(max(i, currRouters.getLength()));
        currRouters.setLength(max(j, currRouters.getLength()));
    }

    std::cout << "\nCost matrix:" << std::endl;
    for (int i = 0; i < currRouters.getLength(); ++i) {
        for (int j = 0; j < currRouters.getLength(); ++j) {
            printf("%2u ", distanceTable[i][j]);
        }
        std::cout << "\n";
    }

    //set router values to link distance 
    for(i = 0; i < currRouters.getLength(); ++i) {
        for(j = 0; j < currRouters.getLength(); ++j) {
            currRouters.set(i, j, distanceTable[i][j]);
        }
    }
    std::cout << "\n";

    // main loop
    // display menu
    std::cout << "0: Run till stable and time algorithm\n1: Step through\nEnter: ";
    std::cin >> stepChoice;
    while (stepChoice != STABLE && stepChoice != ITERATIVE) {
        std::cout << "0: Run till stable and time algorithm\n1: Step through\nEnter: ";
        std::cin >> stepChoice;
    }

    if (stepChoice == ITERATIVE) {
        std::cout << "===============================" << std::endl;
        std::cout << "===== INITIAL COST MATRIX =====" << std::endl;
        std::cout << "===============================" << std::endl;
        printNodes(currRouters, nullptr, 1);
    }
    else {
        start = std::chrono::high_resolution_clock::now();
    }

    while (hasChanged) {
        ++num_iterations;
        char c = 0;

        // step through loop
        if (stepChoice && num_iterations > 1) {
            std::cout << "==== c <enter> to continue to next iteration, l <enter> to change the value of a link ====" << std::endl;
            std::cin >> c;

            // user has chosen to change link cost
            if (c == 'l') {
                std::cout << "Enter first router number" << std::endl;
                std::cin >> i;
                std::cout << "Enter second router number" << std::endl;
                std::cin >> j;
                std::cout << "Enter new cost value or 99 for infinite/offline" << std::endl;
                std::cin >> dist;
                // convert num to index
                --i;
                --j;

                // update distance table and routers
                distanceTable[i][j] = dist;
                distanceTable[j][i] = dist;
                currRouters.set(i, j, dist);
                currRouters.set(j, i, dist);
                prevRouters.set(i, j, dist);
                prevRouters.set(j, i, dist);

                std::cout << "==== Tables with updated link values";
                printNodes(currRouters, &prevRouters, 0);

                --num_iterations;
                continue;
            }
        }

        hasChanged = bellmanFordIteration(&currRouters, &prevRouters, distanceTable);

        if (hasChanged && stepChoice) {
            std::cout << "\n|||||||||| ITERATION  " << num_iterations << " ||||||||||" << std::endl;
            printNodes(currRouters, &prevRouters, 0);
        }
    }

    if (stepChoice == STABLE) {
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "\nFINAL TIME = " << duration.count() << " microseconds."<< std::endl;
    }

    std::cout << "\n|||||||||| ITERATION  " << num_iterations << " ||||||||||" << std::endl;
    printNodes(currRouters, NULL, 0);

    return 0;
}
