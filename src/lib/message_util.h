#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
using namespace std;

#include "./text_color.h"
using namespace Color;

namespace message {

void print(const string& msg, short color) {
  std::cout << tcolor(msg, color) << endl;
}

void danger(const string& msg) { print(msg, RED); }
void info(const string& msg) { print(msg, BLUE); }
void success(const string& msg) { print(msg, GREEN); }
void warning(const string& msg) { print(msg, YELLOW); }

}  // namespace message

#endif
