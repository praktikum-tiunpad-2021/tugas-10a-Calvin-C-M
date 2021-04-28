/*
 * Bebas disini bisa masukin apa aja.
 * Misal mau testing atau debugging sendiri.
 *
 * Disini ada contoh code, boleh dihapus.
 */

#include <iostream>

#include "graph.hpp"

int main() {
  strukdat::graph<char> g;

  g.add_vertex('a');
  g.add_vertex('b');
  g.add_vertex('c');
  g.add_vertex('d');
  g.add_vertex('e');

  g.add_edge('a', 'b');
  g.add_edge('a', 'c');
  g.add_edge('b', 'd');
  g.add_edge('c', 'e');

  g.bfs('a', [](char a) { std::cout << a << ' '; });

  return 0;
}
