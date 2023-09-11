// Implemntation of Dijkstra's shortest path algorithem
// As per instructions, the solution is divided in two parts.
// First part is implementation of Graph as a class with proper constructors and methods to access edges
// There are also Factory methods to generate graphs, based on input number of nodes, edge density and distance range
// To make this program compact, I have used std utilities where possible

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include <assert.h>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

const std::string Notes = R"( - - - Implemntation of Dijkstra's shortest path algorithem - - -

 As per instructions, the solution is divided in two parts:
 1.  First part is implementation of Graph as a class with proper constructors and methods to access edges
 2. There are also Factory methods to generate graphs, based on input number of nodes, edge density and distance range
 
 To make this program compact, I have used std utilities where possible. Below will be some explanation:

- std::map<Edge, int> will help us to have a easier way of storing edges, by avoiding duplicate edges 
 (so edges[edge] will be always unique)
 Use of std::map also helps us to use the find method, to easily find if an edge exists

- std::set<int> to keep track of unvisited nodes (Q). Since it is easier to search and insert, while avoiding duplicates

- A Struct is used to define Edge, in the process to make it std::map friendly we have to override less than operator as well as == operator
 (this is not necessary for this project, but I thought it would be a good exercise)
 another easy way to avoid it would be to typedef (or using) std::pair<int, int> Edge; and use it as a key in map

- std::shuffle to randomize the all possiblities of edges. This will help us to just walk through first n% of the edges and add them to the graph
it is easy to implement a randomizer function to get a random int also, but this was a simple enoguh routine to keep using

- This will be a bit out of topic of course, but I was exercising overriding the cout operrator in order to broaden my knowledge

- AddEdge uses move symantics, this is unnecessary in scale of our project, however could be a nice exercise to avoid excessive variable declarations
)";

class Edge{
    public:
    int v1, v2;
    Edge(const int& v_1,const int& v_2)
    {
        if(v_1 == v_2)
            assert(false); //No self loops allowed
        if (v_1 < v_2)
        {
            v1 = v_1;
            v2 = v_2;
        } else {
            v1 = v_2;
            v2 = v_1;
        }
    }

    bool operator<(const Edge& other) const
    {
        if(v1 < other.v1)
            return true;
        if(v1 == other.v1 && v2 < other.v2)
            return true;
        return false;
    }
    
    bool operator==(const Edge& other) const
    {
        return (v1 == other.v1 && v2 == other.v2);
    }
};

class Graph
{
    std::map<Edge, int> edges; //Edge will contain the node pair, and int is the distance (or weight)
    int num_v; // number of vertices
    
    inline int getDistanceBetween(const int& v1, const int& v2) const //only rvalue, returns -1 if it cannot find the edge;
    {
        auto edge = Edge{v1, v2};
        if(edges.find(edge) != edges.end())
            return edges.at(edge);
        return -1;//i.e. not found or they are not neighbours   
    }


public:
    Graph(const int& num_vertex): num_v(num_vertex) {}

    int V() const {return num_v;} const //number of vertices
    int E() const {return edges.size();} const //number of edges
    bool adjacent(const int& v1, const int& v2) const {return getDistanceBetween(v1, v2) != -1;} //are they neighbours
    std::vector<int> neighbors(const int& v) const //returns all the neighbours of v
    {
        std::vector<int> n;
        for(int i=0; i<num_v; i++)
        {
            if(i == v)
                continue;
            if(adjacent(v, i))
                n.push_back(i);
        }
        return n;
    }

    // This function also acts as setEdgeValue as in assignment. The way I store edges, they already contain the values
    void add(const Edge& edge, const int& d = 0){
        edges[edge] = d;
    }

    int getEdgeValue(const int& v1, const int& v2) const
    {
        return getDistanceBetween(v1, v2);
    }

    void deleteEdge(const Edge& edge){
        edges.erase(edge);
    }



    friend std::ostream& operator<<(std::ostream& os, const Graph& g)
    {
        os << "Graph with " << g.num_v << " vertices and " << g.edges.size() << " edges" << std::endl;
        os << "Edges: " << std::endl << "-----------------------------" << std::endl;
        os << "v1 \t- \tv2 \t: distance" << std::endl;
        for(auto& e: g.edges)
            os << e.first.v1 << "\t- \t" << e.first.v2 << "\t: " << e.second << std::endl;
        return os;
    }
};

Graph GenerateGraph(int num_vertex, double density, int range_min, int range_max)
{
    auto graph = Graph(num_vertex);
    // since the whole object will be passed we don't need to store it in heap and a pointer
    // we will be basically passing the owenership to whoever called
    // raandom seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(range_min, range_max);

    // generate all the possible edges
    std::vector<Edge> all_edges;
    for(int i=0; i< num_vertex; i++)
        for(int j=i+1; j< num_vertex; j++)
            all_edges.push_back(Edge{i, j});
    // now we have to chose density% of the edges randomly
    std::shuffle(all_edges.begin(), all_edges.end(), gen);
    int num_edges = density * all_edges.size();
    for(int i=0; i< num_edges; i++)
    {
       // chose random distance between range_min and range_max
       auto d = dis(gen);
       graph.add(all_edges[i], d);
    }
    return graph;
}

// The function for shortest path distance
// as per psudo code function in Wiki article found here: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
// as per instructions I am not using priority queue implementation
// Note that variable names of this function is set per the psudo code in the article
int dijkestra(const Graph& graph, const int& v1, const int& v2, std::vector<int>& S)
{
    //1. Assign to every node a tentative distance value: set it to zero for our initial node and to infinity for all other nodes.
    auto dist = std::vector<int>(graph.V(), INT_MAX);
    auto prev = std::vector<int>(graph.V(), -1);

    dist[v1] = 0;

    std::set<int> Q; //unvisited nodes
    for(int i=0; i<graph.V(); i++)
    {
        Q.insert(i);
    }

    while(!Q.empty())
    {
        //2. remove the node with minimum distance set from the unvisited set
        int u = -1;
        int min_dist = INT_MAX;
        for(auto& q: Q)
        {
            if(dist[q] < min_dist)
            {
                min_dist = dist[q];
                u = q;
            }
        }
        if(u != -1)
           Q.erase(u);
        if(u == -1)
            break; //no path found
        if(u == v2)
            break;
        //3. calculated and update distance of all the neighbours of u (that are still in Q)
        auto neighbours = graph.neighbors(u);
        for(auto& neighbour: neighbours)
        {
            if(Q.find(neighbour) == Q.end())
                continue;
            auto d = graph.getEdgeValue(u, neighbour);
            if(d != -1) //i.e. they are neighbors
            {
                auto alt = dist[u] + d;
                if(alt < dist[neighbour])
                {
                    dist[neighbour] = alt;
                    prev[neighbour] = u;
                }
            }
        }
    }

    if(dist[v2] == INT_MAX)
        return -1; //no path found
    S.erase(S.begin(), S.end()); //empty it just in case
    int u = v2;
    while(prev[u] != -1 || u != v1)
    {
        S.push_back(u);
        u = prev[u];
    }
    S.push_back(v1); // add the source as per instructions
    return dist[v2];
}

class ShortestPath{
    const Graph& graph;
    public:
    ShortestPath(const Graph& g):graph(g){};
    std::vector<int> path(const int& v1,const int& v2)
    {
        std::vector<int> seq;
        dijkestra(graph, v1, v2,  seq);
        //reverse seq   
        std::reverse(seq.begin(), seq.end());
        return seq;        
    }
    int pathDistance(const int& v1,const int& v2)
    {
        auto dummy = std::vector<int>();
        return dijkestra(graph, v1, v2, dummy);
    }
};

void outPutPath(const Graph& graph, const int& v1, const int& v2){
    ShortestPath sp(graph);
    auto path = sp.path(v1, v2);
    auto path_dist = sp.pathDistance(v1, v2);
    if(path_dist == -1)
    {
        std::cout << "No path found" << std::endl;
        return;
    }
    std::cout << "Shortest path from " << v1 << " to " << v2 << " is: " << std::endl;
    for(auto& v: path)
        std::cout << " -> " << v ;
    std::cout << std::endl << "Distance: " << path_dist << std::endl;
}

double calculateAverageFromZero(const Graph &graph)
{
    int sum = 0;
    int count = 0;
    ShortestPath sp(graph);
    for (int i = 1; i < graph.V(); i++)
    {
        auto dist = sp.pathDistance(0, i);
        if (dist != -1)
        {
            sum += dist;
            ++count;
        }
    }
    return (double)sum / count;
}

int main(){
std::cout << Notes << std::endl;
//for example of first graph (50 nodes, density 20% and distance range 1 to 10)
auto graph = GenerateGraph(50, .2, 1, 10);

std::cout << "For the graph with 50 nodes, density 20% and distance range 1 to 10" << std::endl;
//std::cout << graph << std::endl;
std::cout << "Average distance from node 0 to all other nodes is: " << calculateAverageFromZero(graph) << std::endl <<std::endl;

//the second example of first graph (50 nodes, density 40% and distance range 1 to 10)
auto graph2 = GenerateGraph(50, .4, 1, 10);
std::cout << "For the graph with 50 nodes, density 40% and distance range 1 to 10" << std::endl;
//std::cout << graph2 << std::endl;
std::cout << "Average distance from node 0 to all other nodes is: " << calculateAverageFromZero(graph2) << std::endl;

}