#include "Utils.h"
#include "SCCResult.h"
#include "StrongConnectedComponents.h"
#include "ElementaryCyclesSearch.h"

int main(void)
{
    const int N = 16;
    vector<string> nodes(N);
    vector < vector<bool> > adjMatrix(N, vector<bool>(N));

    // initialization
    for (int i = 0; i < N; i++)
    {
        nodes[i] = "Node " + std::to_string(i);
    }

    string SR = "1 5 4\n2 6 5 4 8\n3 7 6 10 9 13 12\n6 10 9\n7 11 15 14 13\n8 4 5 6 2\n9 10 6\n11 15 14\n12 8 9 10 11 7 3\n13 9 10 6 7\n14 10 11";
    // "1 2 3\n2 3 1\n3 1 2\n3 2";
    // "1 2\n3 2\n3 4 5 6 7\n4 5 6 7 3\n5 6 3\n6 3\n6 7 3";
    // "1 5 4\n2 6 5 4 8\n3 7 6 10 9 13 12\n6 10 9\n7 11 15 14 13\n8 4 5 6 2\n9 10 6\n11 15 14\n12 8 9 10 11 7 3\n13 9 10 6 7\n14 10 11";
    // "1 5 4\n2 6 5 4 8\n3 7 6 10 9 13 12\n4 0 1\n6 10 9\n7 11 15 14 13\n8 4 5 6 2\n9 10 6\n11 15 14\n12 8 9 10 11 7 3\n13 9 10 6 7\n14 10 11";

    vector<string> lines = split(SR, '\n');

    // Creating an Adjacency Matrix
    for (int i = 0; i < lines.size(); i++)
    {
        vector<string> components = split(lines[i], ' ');

        for (int i = 0; i < components.size() - 1; i++)
        {
            int x = atoi(components[i].c_str());
            int y = atoi(components[i + 1].c_str());
            adjMatrix[x][y] = true;
        }
    }

    // Run algorithm
    ElementaryCyclesSearch ecs = ElementaryCyclesSearch(adjMatrix, nodes);
    vector<vector<string> > cycles = ecs.getElementaryCycles();

    // Print result
    for (int i = 0; i < cycles.size(); i++)
    {
        vector<string> cycle = cycles[i];
        for (int j = 0; j < cycle.size(); j++)
        {
            string node = cycle[j];
            if (j < cycle.size() - 1)
            {
                cout << node << " -> ";
            }
            else
            {
                cout << node;
            }
        }
        cout << endl;
    }
    return 0;
}
