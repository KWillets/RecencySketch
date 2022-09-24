#include "recency_sketch.hpp"
#include <stdio.h>
#include <string>

int main() {
  RecencySketch<int, unsigned long, 100,2> r;
  printf("pre add 33=>%lu\n", r.probe(33));
  r.add(1,1);
  r.add(2,2);
  for(int i = 3; i < 500; i++)
    r.add(i,4);
  unsigned long x=r.probe(1);
  printf("1=>%lu\n", x);
  printf("33=>%lu\n", r.probe(33));

  RecencySketch<std::string, unsigned long, 100,2> s;
  std::string k1 = "one";
  std::string k2 = "two";
  s.add(k1, 1);
  s.add(k2, 2);
  printf("one => %lu\n", s.probe(k1));
}
