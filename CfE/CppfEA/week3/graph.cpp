// Implemntation of Dijkstra's shortest path algorithem
// As per instructions, the solution is divided in two parts.
// First part is implementation of Graph as a class with proper constructors and methods to access edges
// There are also Factory methods to generate graphs, based on input number of nodes, edge density and distance range
// To make this program compact, I have used std utilities where possible

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

const std::string Notes = R"( - - - Implemntation of Dijkstra's shortest path algorithem - - -

 As per instructions, the solution is divided in two parts:
 1.  First part is implementation of Graph as a class with proper constructors and methods to access edges
 2. There are also Factory methods to generate graphs, based on input number of nodes, edge density and distance range
 
 To make this program compact, I have used std utilities where possible. Below will be some explanation:

- std::map<Edge, int> will help us to have a easier way of storing edges, by avoiding duplicate edges 
 (so edges[edge] will be always unique)
 Use of std::map also helps us to use the find method, to easily find if an edge exists

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
            throw std::exception("Invalid edge");
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
    int num_v; // number of vertices
    std::map<Edge, int> edges; //Edge will contain the node pair, and int is the distance (or weight)
public:
    int GetDistanceBetween(int&& v1, int&& v2) const //only rvalue, returns -1 if it cannot find the edge;
    {
        auto edge = Edge{v1, v2};
        if(edges.find(edge) != edges.end())
            return edges.at(edge);
        return -1;//i.e. not found
    }

    Graph(int num_v): num_v(num_v){}
    void AddEdge(const Edge& edge, int&& d){
        edges[edge] = d;
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
       graph.AddEdge(all_edges[i], std::move(d));
    }
    return graph;
}

int main(){
    std::cout << Notes << std::endl;
    //for example a complete graph
    auto graph = GenerateGraph(5, 1, 1, 1);
    std::cout << graph << std::endl;

}