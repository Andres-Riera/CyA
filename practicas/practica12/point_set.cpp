#include "point_set.hpp"

namespace CyA {

void point_set::quickHull(void) {
  hull_.clear();

  CyA::point min_x_point;
  CyA::point max_x_point;

  x_bounds(min_x_point, max_x_point);

  quickHull(CyA::line(min_x_point, max_x_point), side::LEFT);
  quickHull(CyA::line(min_x_point, max_x_point), side::RIGHT);

  // Remove duplicates
  std::sort(hull_.begin(), hull_.end());
  hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}

void point_set::quickHull(const CyA::line &l, int side) {
  CyA::point farthest;

  if (farthest_point(l, side, farthest)) {
    quickHull(CyA::line(l.first, farthest),
              -find_side(CyA::line(l.first, farthest), l.second));
    quickHull(CyA::line(farthest, l.second),
              -find_side(CyA::line(farthest, l.second), l.first));
  } else {
    hull_.push_back(l.first);
    hull_.push_back(l.second);
  }
}

bool point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
  farthest = CyA::point_vector::at(0);

  double max_dist = 0;

  bool found = false;

  for (const CyA::point &p : *this) {
    const double dist = distance(l, p);

    if (find_side(l, p) == side && dist > max_dist) {
      farthest = p;
      max_dist = dist;
      found = true;
    }
  }

  return found;
}

double point_set::point_2_line(const CyA::line &l, const CyA::point &p) const {
  const CyA::point &p1 = l.first;
  const CyA::point &p2 = l.second;

  return (p.second - p1.second) * (p2.first - p1.first) -
         (p2.second - p1.second) * (p.first - p1.first);
}

double point_set::distance(const CyA::line &l, const CyA::point &p) const {
  return fabs(point_2_line(l, p));
}

int point_set::find_side(const line &l, const point &p) const {
  point p1 = l.first;
  point p2 = l.second;

  double aux = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

  if (aux > 0) {
    return side::LEFT; 
  } else if (aux < 0) {
    return side::RIGHT;
  } else {
    return side::CENTER;
  }
}


void point_set::x_bounds(point &min_x, point &max_x) const {
  double min, max;
  bool first = true;
  for (const CyA::point &p : *this) {
    if (first) {
      min = p.first;
      max = p.first;
      min_x = p;
      max_x = p;
      first = false;
    } else {
      if (p.first < min) {
        min = p.first;
        min_x = p;
      } else if (p.first > max) {
        max = p.first;
        max_x = p;
      }
    }
  }
}

double cross_product(const point &p1, const point &p2, const point &p3) {
  return (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);
}

void point_set::write_hull(std::ostream &os) const {
  os << "graph {" << std::endl;
  
  for (const point &point : *this) {
    os << point.first << ',' << point.second << " [pos=\"" << point.first << "," << point.second << "!\"]" << std::endl;
  }
  
  point min_x = hull_[0];
  for (const point &p : hull_) {
    if (p.first < min_x.first) {
      min_x = p;
    }
  }
  std::vector<point> sorted_hull = hull_;
  std::sort(sorted_hull.begin(), sorted_hull.end(), [&min_x](const point &p1, const point &p2) {
    return cross_product(min_x, p1, p2) > 0;
  });

  std::vector<line> lineas;
  bool first = true;
  point p;
  for(auto punto : sorted_hull) {
    if (first) {
      p = punto;
      first = false;
    } else {
      line aux;
      aux.first = p;
      aux.second = punto;
      p = punto;
      lineas.push_back(aux);
    }
  }
  if (!sorted_hull.empty()) {
    lineas.push_back({sorted_hull.back(), sorted_hull.front()});
  }

  for (auto linea : lineas) {
    os << "    " << linea.first.first << ',' << linea.first.second << " -- " << linea.second.first << ',' << linea.second.second << '\n';
  }
  os << "}" << std::endl;
}

void point_set::write(std::ostream &os) const {
  for (auto p : hull_) {
    os << '(' << p.first << ", " << p.second << ")\n";
  }
}

}  // namespace CyA