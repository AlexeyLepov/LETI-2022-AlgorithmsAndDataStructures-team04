#ifndef STRONGCONNECTEDCOMPONENTS_H
#define STRONGCONNECTEDCOMPONENTS_H

#include <math.h>

class StrongConnectedComponents
{
public:

    StrongConnectedComponents()
    {
    }

    StrongConnectedComponents(const StrongConnectedComponents& orig)
    {
    }

    virtual ~StrongConnectedComponents()
    {
    }

    /**
     * Конструктор
     *
     * @param adjList-список смежности графа
     */
    StrongConnectedComponents(vector<vector<int> > adjList)
    {
        adjListOriginal = adjList;
    }

    /**
     * Этот метод возвращает структуру смежности компонента сильной связности
     * с наименьшей вершиной в подграфе исходного графа, порожденного узлами
     * {s, s + 1, ..., n}, где s - заданный узел
     *
     * (Функция не будет возвращать один узел)
     *
     * @param node node s
     * @return HFILE_STRONGCONNECTEDCOMPONENTSRESULT_H with adjacency-structure of the strong connected
     * component; null, if no such component exists
     */
    SCCResult* getAdjacencyList(int node)
    {
        visited.clear();
        lowlink.clear();
        number.clear();
        stack.clear();
        currentSCCs.clear();
        if(visited.size()==0)visited.resize(adjListOriginal.size());
        if(lowlink.size()==0)lowlink.resize(adjListOriginal.size());
        if(number.size()==0)number.resize(adjListOriginal.size());

        makeAdjListSubgraph(node);

        for (int i = node; i < adjListOriginal.size(); i++)
        {
            if (!visited[i])
            {
                getStrongConnectedComponents(i);
                vector<int> nodes = getLowestIdComponent();
                if (nodes.size() > 0 && std::find(nodes.begin(), nodes.end(), node) == nodes.end() && std::find(nodes.begin(), nodes.end(), node + 1) == nodes.end())
                {
                    return getAdjacencyList(node + 1);
                }
                else
                {
                    vector<vector<int> > adjacencyList = getAdjList(nodes);
                    if (adjacencyList.size() > 0)
                    {
                        for (int j = 0; j < adjListOriginal.size(); j++)
                        {
                            if (adjacencyList[j].size() > 0)
                            {
                                return new SCCResult(adjacencyList, j);
                            }
                        }
                    }
                }
            }
        }
        return NULL;
    }

private:

    /**
     * Строит список смежности для подграфа, содержащего только узлы >= заданного индекса
     *
     * @param node Узел с наименьшим индексом в подграфе
     */
    void makeAdjListSubgraph(int node)
    {
        adjList.clear();
        if(adjList.size()==0)adjList.resize(adjListOriginal.size());

        for (int i = node; i < adjList.size(); i++)
        {
            vector<int> successors;
            for (int j = 0; j < adjListOriginal[i].size(); j++)
            {
                if (adjListOriginal[i][j] >= node)
                {
                    successors.push_back(adjListOriginal[i][j]);
                }
            }
            if (successors.size() > 0)
            {
                adjList[i].clear();
                if(adjList[i].size()==0) adjList[i].resize(successors.size());
                for (int j = 0; j < successors.size(); j++)
                {
                    int succ = successors[j];
                    adjList[i][j] = succ;
                }
            }
        }
    }

    /**
     * Вычисляет компонент сильной связности из набора scc, который содержит узел с наименьшим индексом
     *
     * @return Vector::Integer - из scc, содержащего наименьший номер узла
     */
    vector<int> getLowestIdComponent()
    {
        int min = adjList.size();
        vector<int> currScc;

        for (int i = 0; i < currentSCCs.size(); i++)
            {
            vector<int> scc = currentSCCs[i];
            for (int j = 0; j < scc.size(); j++)
            {
                int node = scc[j];
                if (node < min)
                {
                    currScc = scc;
                    min = node;
                }
            }
        }
        return currScc;
    }

    /**
     * @return Vector[]::Integer - представляющая структуру смежности компонента
     * сильной связности с наименьшей вершиной в просматриваемом в данный момент
     * подграфе
     */
    vector<vector<int> > getAdjList(vector<int> nodes)
    {
        vector<vector<int> > lowestIdAdjacencyList;
        if (nodes.size() > 0)
        {
            lowestIdAdjacencyList.clear();
            if(lowestIdAdjacencyList.size()==0)lowestIdAdjacencyList.resize(adjList.size());
            //            for (int i = 0; i < lowestIdAdjacencyList..size(); i++) {
            //                lowestIdAdjacencyList[i] = new Vector();
            for (int i = 0; i < nodes.size(); i++)
            {
                int node = nodes[i];
                for (int j = 0; j < adjList[node].size(); j++)
                {
                    int succ = adjList[node][j];
                    if (std::find(nodes.begin(), nodes.end(), succ) != nodes.end())
                    {
                        lowestIdAdjacencyList[node].push_back(succ);
                    }
                }
            }
        }
        return lowestIdAdjacencyList;
    }


    /**
     * Ищет компоненты сильной связности, достижимые из заданного узла
     *
     * @param root - корень
     */
    void getStrongConnectedComponents(int root)
    {
        sccCounter++;
        lowlink[root] = sccCounter;
        number[root] = sccCounter;
        visited[root] = true;
        stack.push_back(root);
        for (int i = 0; i < adjList[root].size(); i++)
        {
            int w = adjList[root][i];
            if (!visited[w])
            {
                getStrongConnectedComponents(w);
                lowlink[root] = min(lowlink[root], lowlink[w]);
            }
            else if (number[w] < number[root])
            {
                if (std::find(stack.begin(), stack.end(), w) != stack.end())
                {
                    lowlink[root] = min(lowlink[root], number[w]);
                }
            }
        }


        // найдена компонента сильной связанности - scc
        if ((lowlink[root] == number[root]) && (stack.size() > 0))
        {
            int next = -1;
            vector<int> scc;

            do {
                next = stack[stack.size() - 1];
                stack.erase(stack.begin()+ stack.size() - 1);
                scc.push_back(next);
            } while (number[next] > number[root]);

            // простые компоненты сильной связанности с одним узлом не будут добавлены
            if (scc.size() > 1)
            {
                currentSCCs.push_back(scc);
            }
        }
    }

    /**
     * Вектор смежности исходного графа
     */
    vector<vector<int> > adjListOriginal;

    /**
     * Список смежности просматриваемого в данный момент подграфа
     */
    vector<vector<int> > adjList;

    /**
     * Вспомогательный объект для поиска scc
     */
    vector<bool> visited;

    /**
     * Вспомогательный объект для поиска scc
     */
    vector<int> stack;

    /**
     * Вспомогательный объект для поиска scc
     */
    vector<int> lowlink;

    /**
     * Вспомогательный объект для поиска scc
     */
    vector<int> number;

    /**
     * Вспомогательный объект для поиска scc
     */
    int sccCounter = 0;

    /**
     * Вспомогательный объект для поиска scc
     */
    vector<vector<int> > currentSCCs;

};

#endif /* STRONGCONNECTEDCOMPONENTS_H */
