#include <fstream>
#include <iomanip>
#include <sstream>

#include "../model/KenoBet.h"
#include "./message_util.h"
#include "./string_utils.h"

/**
 * @param filename The name of the file to be read
 * @param bet The bet object to set the contents of the file
 * @return The number of rounds, or 0 if the file is somehow not valid
 */
unsigned int readKenoBetFile(const string filename, KenoBet* bet) {
  ifstream file(filename);
  if (!file.good()) {
    message::danger("The provided bet file was not found");
    file.close();
    return 0;
  }

  string message =
      "Preparing to read bet file [" + filename + "], please wait...";
  stringstream separator;
  separator << setw(message.length()) << setfill('-') << "";
  message::info(message);
  message::info(separator.str());

  cash_type wage;
  unsigned int rounds = 0;
  bool bWage = false, bRounds = false;

  string line, spots;
  while (getline(file, line)) {
    if (line.empty()) continue;

    if (!bWage) {
      bWage = true;
      wage = atof(trim(line).c_str());
      continue;
    }

    if (!bRounds) {
      bRounds = true;
      rounds = atoi(trim(line).c_str());
      continue;
    }

    spots = trim(line);
  }
  file.close();

  vector<string> vSpots = split(spots, ' ');

  if (wage <= 0 || vSpots.size() == 0 || rounds <= 0) {
    message::danger("Error reading bet file!");
    return 0;
  }

  bet->set_wage(wage);
  for (size_t i = 0; i < vSpots.size(); i++) {
    auto spot = atoi(vSpots[i].c_str());
    bet->add_number(spot);
  }

  if (bet->get_spots().empty()) {
    message::danger("Error reading bet file!");
    return 0;
  }

  message::success("Bet successfully read!");
  return rounds;
}
