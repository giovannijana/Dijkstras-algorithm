/**************************************************************************************************/
// Test File for PP5
// Requires the Catch2 header file
// How to compile: g++ -std=c++17 -Wall -I$(CATCH_SINGLE_INCLUDE) (All cpp files)
// Example if Catch2 and source files are in this directory and at directory level: 
//    Example: g++ -std=c++17 -Wall *.cpp
// To see what tests were successful and failed, run your executable with the -s flag
//    Example: a.out -s
// A successful test should output: All tests passed (18 assertions in 1 test case)
/**************************************************************************************************/


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>
#include <tuple>

#include "Graph.hpp"

struct EdgeStruct { std::string a; std::string b; unsigned long w; };

TEST_CASE("Project 5 Test Cases for Dijkstra's Algorithm") {
  Graph g;

  std::vector<std::string> vertices1 { "1", "2", "3", "4", "5", "6" };
  std::vector<EdgeStruct> edges1 {
    {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
    {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9},
  };

  std::vector<std::string> vertices2 { 
    "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
  };
  std::vector<EdgeStruct> edges2 {
    {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
    {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
    {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
  };

  std::vector<std::string> vertices3 { 
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
  };
  std::vector<EdgeStruct> edges3 {
    {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1}, 
    {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1}, 
    {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}
  };

  SECTION("Should calculate the distance of the shortest path for graph 1") {
    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path;
    REQUIRE(g.shortestPath("1", "5", path) == 20);
    path.clear();

    REQUIRE(g.shortestPath("3", "6", path) == 2);
    path.clear();
    
    REQUIRE(g.shortestPath("5", "2", path) == 21);
    path.clear();
  }

  SECTION("Should have the labels for the shortest path for graph 1") {
    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path; std::vector<std::string> correctPath; 
    
    g.shortestPath("1", "5", path); correctPath = { "1", "3", "6", "5" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();

    g.shortestPath("3", "6", path); correctPath = { "3", "6" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();
    
    g.shortestPath("5", "2", path); correctPath = { "5", "4", "2" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();
  }

  SECTION("Should calculate the distance of the shortest path for graph 2") {
    for (const auto label : vertices2) g.addVertex(label);
    for (const auto &e : edges2) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path;
    REQUIRE(g.shortestPath("ENB", "SUN", path) == 2885);
    path.clear();

    REQUIRE(g.shortestPath("LIB", "CAS", path) == 1532);
    path.clear();
    
    REQUIRE(g.shortestPath("MSC", "SUB", path) == 4727);
    path.clear(); 
  }

  SECTION("Should have the labels for the shortest path for graph 2") {
    for (const auto label : vertices2) g.addVertex(label);
    for (const auto &e : edges2) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path; std::vector<std::string> correctPath; 
    
    g.shortestPath("ENB", "SUN", path); correctPath = { "ENB", "SUN" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();

    g.shortestPath("LIB", "CAS", path); correctPath = { "LIB", "ENB", "CAS" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();
    
    g.shortestPath("MSC", "SUB", path); correctPath = { "MSC", "LIB", "SUN", "SUB" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();
  }

  SECTION("Should calculate the distance of the shortest path for graph 3") {
    for (const auto label : vertices3) g.addVertex(label);
    for (const auto &e : edges3) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path;
    REQUIRE(g.shortestPath("1", "12", path) == 6);
    path.clear();

    REQUIRE(g.shortestPath("3", "11", path) == 4);
    path.clear();

    g.removeVertex("3");
    REQUIRE(g.shortestPath("8", "7", path) == 12);
    path.clear();
  }

  SECTION("Should have the labels for the shortest path for graph 3") {
    for (const auto label : vertices3) g.addVertex(label);
    for (const auto &e : edges3) g.addEdge(e.a, e.b, e.w);

    std::vector<std::string> path; std::vector<std::string> correctPath; 
    
    g.shortestPath("1", "12", path); correctPath = { "1", "2", "3", "7", "12" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();

    g.shortestPath("3", "11", path); correctPath = { "3", "2", "6", "11" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();

    g.removeVertex("3");
    g.shortestPath("8", "7", path); correctPath = { "8", "9", "10", "11", "12", "7" };
    REQUIRE(path == correctPath);
    path.clear(); correctPath.clear();
  }
}



