#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

namespace strukdat {

template <typename VertexType>
class graph {
  /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
  using list_type = std::unordered_set<VertexType>;
  using adj_list_type = std::unordered_map<VertexType, list_type>;

 public:
  /**
   * @brief Default constructor.
   *
   * @constructor
   */
  graph() {}

  /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
  void add_vertex(const VertexType &val) {
    // Contoh implementasi. (BOLEH DIUBAH)
    // inisialisasi _adj_list[val] dengan list kosong
    _adj_list.insert(std::make_pair(val, list_type()));
  }

  void remove_vertex(const VertexType &val) {
    _adj_list.erase(val);
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    _adj_list[val1].insert(val2);
    _adj_list[val2].insert(val1);
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    std::unordered_set<VertexType> &adj1 = _adj_list[val1],
                                   &adj2 = _adj_list[val2];

    auto it = std::find(adj1.begin(), adj1.end(), val2);
    if(it != adj1.end())
    { adj1.erase(it); }

    it = std::find(adj2.begin(), adj2.end(), val1);
    if(it != adj2.end())
    { adj2.erase(it); }
  }

  /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
  size_t order() const {
    return _adj_list.size();
  }

  /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
  bool is_edge(const VertexType &val1, const VertexType &val2) const {
    if(_adj_list.at(val1).find(val2) == _adj_list.at(val1).end())
    { return false; }

    if(_adj_list.at(val2).find(val1) == _adj_list.at(val2).end())
    { return false; }

    return true;
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {

    adj_list_type adj_temp = _adj_list;
    std::unordered_map<VertexType, bool> visited;
    for(auto i = adj_temp.begin(); i != adj_temp.end(); i++)
    {
      visited.insert(std::make_pair(i->first, false));
    }
    
    std::vector<VertexType> q;
    VertexType key = root;
    q.push_back(key);
    visited[key] = true;
				
    while(!q.empty())
    {
      key = q.front();
      q.erase(q.begin());
      func(key);
      
      for(auto i = adj_temp[key].begin(); i != adj_temp[key].end(); i++)
      {
        if(visited[*i] == false)
        {
          visited[*i] = true;
          q.push_back(*i);
        }
      }
    }
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void dfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType, bool> visited;
    for (auto i = _adj_list.begin(); i != _adj_list.end(); i++) 
    {
      visited.insert(std::make_pair(i->first, false));
    }

    std::stack<VertexType> stack;
    stack.push(root);
    while (!stack.empty())
    {
      VertexType key = stack.top();
      stack.pop();

      if (!visited[key]) 
      {
        func(key);
        visited[key] = true;
      }

      for (auto i = _adj_list.at(key).begin(); i != _adj_list.at(key).end(); i++)
      {
        if (!visited[*i])
        {
          stack.push(*i);
        }
      }
    }
  }

 private:
  /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
  adj_list_type _adj_list;
};

}  // namespace strukdat