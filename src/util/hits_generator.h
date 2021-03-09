#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <vector>

using std::find;
using std::vector;

using type = unsigned short int;

const unsigned short HITS_SIZE = 20;

vector<type> generateHits() {
  vector<type> vect;

  srand(time(0));
  while (vect.size() < HITS_SIZE) {
    type num = rand() % 80 + 1;

    bool contains = find(vect.begin(), vect.end(), num) != vect.end();
    if (!contains) vect.push_back(num);
  }

  return vect;
}
