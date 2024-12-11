#include "bosque.hpp"

#include <iomanip>
#include <algorithm>

namespace EMST {
void point_set::EMST(void) {
  CyA::arc_vector av;
  compute_arc_vector(av);

  forest st;

  for (const CyA::point &p : *this) {
    sub_tree s;
    s.add_point(p);

    st.push_back(s);
  }

  for (const CyA::weigthed_arc &a : av) {
    int i, j;
    find_incident_subtrees(st, a.second, i, j);

    if (i != j) {
      merge_subtrees(st, a, i, j);
    }
  }

  emst_ = st[0].get_arcs();
}

void point_set::compute_arc_vector(CyA::arc_vector &av) const {
  av.clear();

  const int n = size();

  for (int i = 0; i < n - 1; ++i) {
    const CyA::point &p_i = (*this)[i];

    for (int j = i + 1; j < n; ++j) {
      const CyA::point &p_j = (*this)[j];

      const double dist = euclidean_distance(std::make_pair(p_i, p_j));

      av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));
    }
  }

  std::sort(av.begin(), av.end());
}

void point_set::find_incident_subtrees(const forest& st, const CyA::arc& a, int& i, int& j) const {
  i = -1;
  j = -1;
  for (int k = 0; k < st.size(); ++k) {
    const sub_tree &subarbol = st[k];
    if (subarbol.contains(a.first)) {
      if (i == -1) {
        i = k;
      } else {
        j = k;
        return;
      }
    }
    if (subarbol.contains(a.second)) {
      if (j == -1) {
        j = k;
      } else {
        i = k;
        return;  
      }
    }
  }
}

void point_set::merge_subtrees(forest& st, const CyA::weigthed_arc& a, int i, int j) const {
  sub_tree& subarbol_i = st[i];
  sub_tree& subarbol_j = st[j];
  subarbol_i.merge(subarbol_j, a);
  st.erase(st.begin() + j);
}

double point_set::compute_cost(void) const {
  double cost = 0.0;
  for (const CyA::arc& a : emst_) {
      cost += euclidean_distance(a);
  }
  return cost; 
}

double point_set::euclidean_distance(const CyA::arc& a) const {
  double x = a.second.first - a.first.first;
  double y = a.second.second - a.first.second;
  return double(sqrt(x * x + y * y));  // Pitágoras
}

void point_set::write_tree(std::ostream& os) const {
  for (const auto& arc : emst_) {
    os << '(' << arc.first << ") -> (" << arc.second  << ")\n";
  }
  double cost = compute_cost();
  os << std::fixed << std::setprecision(2) << '\n' <<  cost << '\n';
}


void point_set::write(std::ostream& os) const {
  os << "graph {" << std::endl;
  CyA::point_vector puntos = get_points();
  for (const auto point : puntos) {
    os << "    " << point.first << ',' << point.second << " [pos=\"" << point.first << "," << point.second << "!\"]" << std::endl;
  }

  for (const auto arco : emst_) {
    os << "    " << arco.first.first << ',' << arco.first.second << " -- " << arco.second.first << ',' << arco.second.second << '\n';
  }
  os << "}" << std::endl;
}

}  // namespace EMST