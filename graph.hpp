#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>

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
    if (!g.adjList[val].empty()) {
      g.adjList[val].clear();
      for(int i = 1; i < g.adjList.size(); ++i) {
        if (g.adjList[i].empty()) continue;
        auto it = std::find(g.adjList[i].begin(), g.adjList[i].end(), val);
        if (it != g.adjList[i].end()) {
          g.adjList[i].erase(it);
        }
      }
    }
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    vector<int> &adj1 = g.adjList[val1], &adj2 = g.adjList[val2];
    auto it = std::find(adj1.begin(), adj1.end(), val2);
    if (it == adj1.end()) {
      adj1.push_back(val2);
      std::sort(adj1.begin(), adj1.end());
    }
    it = std::find(adj2.begin(), adj2.end(), val1);
    if (it == adj2.end()) {
      adj2.push_back(val1);
      std::sort(adj2.begin(), adj2.end());
    }
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    vector<int> &adj1 = g.adjList[val1], &adj2 = g.adjList[val2];
    auto it = std::find(adj1.begin(), adj1.end(), val2);
    if (it != adj1.end()) {
      adj1.erase(it);
    }
    it = std::find(adj2.begin(), adj2.end(), val1);
    if (it != adj2.end()) {
      adj2.erase(it);
    }
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
    // TODO: Implementasikan!
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
    // TODO: Implementasikan!
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    vector<bool> visited(g.adjList.size(), false);
    queue<int> queue;
    queue.push(root);
    visited[root] = true;
    while (!queue.empty()) {
      root = queue.front();
      queue.pop();
      for (auto i = g.adjList[root].begin();
        i != g.adjList[root].end();
        ++i) {
       if (!visited[*i]) {
        visited[*i] = true;
        queue.push(*i);
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
    vector<bool> visited(g.adjList.size(), false);
    stack<int> stack;
    stack.push(root);
    while (!stack.empty()) {
      if(!visited[root]) {
        visited[root] = true;
      }
      vector<int>::iterator i;
      for (i = g.adjList[root].begin(); i != g.adjList[root].end(); ++i) {
        if (!visited[*i]) {
          root = *i;
          stack.push(root);
          break;
        }
      }
      if (i == g.adjList[root].end()) {
        root = stack.top();
        stack.pop();
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
