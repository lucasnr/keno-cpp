#include <iostream>

using namespace std;

#include "./util/betReader.h"
// #include "./util/message_util.h"

int main(int argc, char *argv[]) {
  // if (argv[1] == nullptr) {
  //   message::danger("No bet file was provided");
  //   return 1;
  // }
  // string filename = argv[1];
  string filename = "file.dat";

  KenoBet kenoBet;
  int rounds = readKenoBetFile(filename, &kenoBet);
  if (rounds == 0) return 1;

  return 0;
}
