#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"
#include "graph.hpp"

TEST_CASE("dapat menambah dan menghapus vertex", "[case_1]") {
  strukdat::graph<int> g;
  g.add_vertex(1);
  g.add_vertex(2);
  REQUIRE(g.order() == 2);

  g.add_vertex(2);
  REQUIRE(g.order() == 2);

  g.add_vertex(3);
  REQUIRE(g.order() == 3);

  g.remove_vertex(2);
  REQUIRE(g.order() == 2);
}

TEST_CASE("dapat menambah dan menghapus edge", "[case_2]") {
  strukdat::graph<int> g;

  g.add_vertex(1);
  g.add_vertex(2);
  g.add_vertex(3);

  g.add_edge(1, 2);
  REQUIRE(!g.is_edge(1, 3));

  g.add_edge(1, 3);
  REQUIRE(g.is_edge(1, 2));
  REQUIRE(g.is_edge(1, 3));
  REQUIRE(g.is_edge(2, 1));
  REQUIRE(!g.is_edge(2, 3));
}

TEST_CASE("dapat melakukan bfs traversal", "[case_3]") {
  strukdat::graph<int> g;

  g.add_vertex('a');
  g.add_vertex('b');
  g.add_vertex('c');
  g.add_vertex('d');
  g.add_vertex('e');

  g.add_edge('a', 'b');
  g.add_edge('a', 'c');
  g.add_edge('b', 'd');
  g.add_edge('c', 'e');

  std::vector<char> ans;
  const std::vector<char> sol1 = {'a', 'b', 'c', 'd', 'e'};
  const std::vector<char> sol2 = {'a', 'c', 'b', 'e', 'd'};

  g.bfs('a', [&ans](char a) { ans.push_back(a); });
  REQUIRE((std::equal(ans.begin(), ans.end(), sol1.begin(), sol1.end()) ||
           std::equal(ans.begin(), ans.end(), sol2.begin(), sol2.end())));
}

TEST_CASE("dapat melakukan dfs traversal", "[case_4]") {
  strukdat::graph<int> g;

  g.add_vertex('a');
  g.add_vertex('b');
  g.add_vertex('c');
  g.add_vertex('d');
  g.add_vertex('e');

  g.add_edge('a', 'b');
  g.add_edge('a', 'c');
  g.add_edge('b', 'd');
  g.add_edge('c', 'e');

  std::vector<char> ans;
  const std::vector<char> sol1 = {'a', 'b', 'd', 'c', 'e'};
  const std::vector<char> sol2 = {'a', 'c', 'e', 'b', 'd'};

  g.dfs('a', [&ans](char a) { ans.push_back(a); });
  REQUIRE((std::equal(ans.begin(), ans.end(), sol1.begin(), sol1.end()) ||
           std::equal(ans.begin(), ans.end(), sol2.begin(), sol2.end())));
}