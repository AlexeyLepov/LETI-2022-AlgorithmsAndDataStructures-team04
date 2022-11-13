#ifndef ELEMENTARYCYCLESSEARCH_H
#define ELEMENTARYCYCLESSEARCH_H

#include "StrongConnectedComponents.h"

class ElementaryCyclesSearch
{
public:

    ElementaryCyclesSearch()
    {
    }

    ElementaryCyclesSearch(const ElementaryCyclesSearch& orig)
    {
    }

    virtual ~ElementaryCyclesSearch()
    {
    }

    /**
     * Конструктор
     *
     * @param матрица смежности графа
     * @param graphNodes массив узлов графа; используется для постройки элементарных циклов содержащих объекты исходного графа
     */
    ElementaryCyclesSearch(vector<vector<bool> > matrix, vector<string> gNodes)
    {
        graphNodes = gNodes;
        adjList = getAdjacencyList(matrix);
    }

    /**
     * Возвращает объект с векторами узлов всех элементарных циклов графа
     *
     * @return Vector::Vector::Object с Векторами (Vectors) узлов всех элементарных циклов
     */
    vector<vector<string> > getElementaryCycles()
    {
        blocked.clear();
        B.clear();
        if(blocked.size()==0) blocked.resize(adjList.size());
        if(B.size()==0)B.resize(adjList.size());
        StrongConnectedComponents *sccs = new StrongConnectedComponents(adjList);
        int s = 0;

        while (true)
        {
            SCCResult *sccResult = sccs->getAdjacencyList(s);
            if (sccResult != NULL && sccResult->getAdjList().size() > 0)
            {
                vector<vector<int> > scc = sccResult->getAdjList();
                s = sccResult->getLowestNodeId();
                for (int j = 0; j < scc.size(); j++)
                {
                    if (scc[j].size() > 0)
                    {
                        blocked[j] = false;
                        B[j].clear();
                    }
                }

                findCycles(s, s, scc);
                s++;
            }
            else
            {
                break;
            }
        }
        return cycles;
    }

private:
    /**
     * Вектор циклов
     */
    vector<vector<string> > cycles;

    /**
     * Вектор смежности графа
     */
    vector<vector <int> > adjList;

    /**
     * Узлы графа
     */
    vector<string> graphNodes;

    /**
     * Заблокированные узлы, используемые алгоритмом Джонсона
     */
    vector<bool> blocked;

    /**
     * B-векторы, используемые алгоритмом Джонсона
     */
    vector<vector<int> > B;

    /**
     * Стек для узлов, используемый алгоритмом Джонсона
     */
    vector<int> stack;

    /**
     * Вычисляет циклы, содержащие данный узел в компоненте сильной связности. Метод рекурсивно вызывает сам себя
     *
     * @param v
     * @param s
     * @param список смежности adjList с подграфом сильно связанного компонента s
     * @return true, если цикл найден; false - иначе
     */
    bool findCycles(int v, int s, vector<vector <int> > adjList)
    {
        bool f = false;
        stack.push_back(v);
        blocked[v] = true;

        if(v == 13 || v == 9)
            v = v+1-1;

        for (int i = 0; i < adjList[v].size(); i++)
        {
            int w = adjList[v][i];
            // Найти цикл
            if (w == s)
            {
                vector<string> cycle;
                for (int j = 0; j < stack.size(); j++)
                {
                    int index = (stack[j]);
                    cycle.push_back(graphNodes[index]);
                }
                cycles.push_back(cycle);
                f = true;
            }
            else if (!blocked[w])
            {
                if (findCycles(w, s, adjList))
                {
                    f = true;
                }
            }
        }

        if (f)
        {
            unblock(v);
        }
        else
        {
            for (int i = 0; i < adjList[v].size(); i++)
            {
                int w = (adjList[v][i]);
                if (std::find(B[w].begin(), B[w].end(), v) == B[w].end())
                {
                    B[w].push_back(v);
                }

            }
        }
        stack.erase(std::remove(stack.begin(), stack.end(), v), stack.end());
        return f;
    }

    /**
     * Рекурсивное разблокирование всех заблокированных узлов, начиная с данного узла.
     *
     * @param node - узел для разблокировки
     */
    void unblock(int node)
    {
        blocked[node] = false;
        //vector<int> Bnode = B[node];

        while (B[node].size() > 0)
        {
            int w = B[node][0];
            B[node].erase(B[node].begin() + 0);
            if (blocked[w])
            {
                unblock(w);
            }
        }
    }
};

#endif /* ELEMENTARYCYCLESSEARCH_H */
