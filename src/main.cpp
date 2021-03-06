#include <fstream>
#include <iostream>
using namespace std;

#include "./lib/message_util.h"

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  if (filename == nullptr) {
    message::danger("No betfile was provided");
    return 1;
  }

  ifstream file(filename);
  if (!file.good()) {
    message::danger("The provided betfile was not found");
    file.close();
    return 1;
  }

  message::info("Reading betfile");
  string line;
  while (getline(file, line)) {
    // TODO: Read file and store content in a const
    cout << line << endl;
  }
  file.close();
  message::success("Betfile loaded");

  return 0;
}
