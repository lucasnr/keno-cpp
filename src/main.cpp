#include <iostream>

using namespace std;

#include "./util/bet_reader.h"
#include "./util/hits_generator.h"

const double PAYOUT_TABLE[15][16] = {
    {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {0, 1, 2, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},
    {0, 0.5, 2, 6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},
    {0, 0.5, 1, 3, 15, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
    {0, 0.5, 1, 2, 3, 30, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75},
    {0, 0.5, 0.5, 1, 6, 12, 36, 100, 100, 100, 100, 100, 100, 100, 100, 100},
    {0, 0.5, 0.5, 1, 3, 6, 19, 90, 720, 720, 720, 720, 720, 720, 720, 720},
    {0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200, 1200, 1200, 1200, 1200, 1200, 1200},
    {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800, 1800, 1800, 1800, 1800, 1800},
    {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000, 3000, 3000, 3000, 3000},
    {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000, 4000, 400, 4000},
    {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000, 6000, 6000},
    {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500, 7500},
    {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}};

int main(int argc, char *argv[]) {
  if (argv[1] == nullptr) {
    message::danger("No bet file was provided");
    return 1;
  }
  string filename = argv[1];

  KenoBet bet;
  unsigned int rounds = readKenoBetFile(filename, &bet);
  if (rounds == 0) return 1;

  cash_type balance = 0.0;

  auto wagePerRound = (bet.get_wage() / rounds);
  stringstream wage, sWagePerRound;
  wage << "$" << bet.get_wage();
  sWagePerRound << "$" << wagePerRound;

  cout << "You are going to wage a total of "
       << message::inline_success(wage.str()) << " dollars." << endl;

  cout << "Going for a total of " << message::inline_success(to_string(rounds))
       << " rounds, waging " << message::inline_success(sWagePerRound.str())
       << " per round." << endl;

  auto size = bet.size();
  auto spots = bet.get_spots();

  stringstream value, separator;
  for (size_t i = 0; i < size; i++) value << spots[i] << " ";

  cout << "Your bet has " << message::inline_success(to_string(size))
       << " numbers. They are: [ " << message::inline_info(value.str()) << "]"
       << endl;

  // ======= HEADER ========
  message::info("-------+---------");
  cout << "Hits   " << tcolor("|", BLUE) << " Payout" << endl;
  message::info("-------+---------");
  for (size_t i = 0; i <= size; i++) {
    cout << setw(7) << setfill(' ') << left << i << tcolor("|", BLUE) << " ";
    cout << PAYOUT_TABLE[size - 1][i] << endl;
  }
  // ======= HEADER ========

  string sRounds = message::inline_info(to_string(rounds));
  string sWage = message::inline_info(sWagePerRound.str());

  separator << setw(50) << setfill('-') << "";
  for (size_t i = 1; i <= rounds; i++) {
    message::info(separator.str());
    cout << "This is round " << message::inline_info("#" + to_string(i))
         << " of " << sRounds << ", and your wage is " << sWage
         << ". Good luck!" << endl;

    // ======= DISPLAYS HITS =======
    auto random = generateHits();
    value.str(string());
    for (size_t i = 0; i < HITS_SIZE; i++) {
      value << random[i] << " ";
    }

    cout << "The hits are: [ " << message::inline_info(value.str()) << "]"
         << endl
         << endl;

    bool danger = true;
    auto hits = bet.get_hits(random);
    if (hits.empty())
      message::danger("You did not hit anything!");
    else {
      danger = false;
      cout << "You hit the following number(s): [ ";
      value.str(string());
      for (size_t i = 0; i < hits.size(); i++) value << hits[i] << " ";
      cout << message::inline_info(value.str()) << "]" << endl;
    }
    // ======= DISPLAYS HITS =======

    // ======= DISPLAYS GAIN IN THIS ROUND =======
    cout << "Payout rate is ";
    auto rate = PAYOUT_TABLE[size - 1][hits.size()];
    value.str(string());
    value << rate;
    if (danger)
      cout << message::inline_danger(value.str());
    else
      cout << message::inline_info(value.str());

    cout << ", thus you came out with: ";
    value.str(string());
    value << (wagePerRound * rate);
    string cameOut = "$" + value.str();
    if (danger)
      cout << message::inline_danger(cameOut) << endl;
    else
      cout << message::inline_info(cameOut) << endl;

    balance += (wagePerRound * rate);
    value.str(string());
    value << balance;
    // ======= DISPLAYS GAIN IN THIS ROUND =======

    // ======= DISPLAYS BALANCE =======
    danger = balance < bet.get_wage();
    cout << "Your net balance so far is: ";
    if (danger)
      cout << message::inline_danger("$" + value.str());
    else
      cout << message::inline_success("$" + value.str());

    cout << " dollars." << endl;
    // ======= DISPLAYS BALANCE =======
  }

  cout << endl;
  message::warning("End of rounds!");
  message::info(separator.str());
  cout << endl << endl;

  message::info("===== SUMMARY =====");
  cout << "You spent in this game a total of "
       << message::inline_info(wage.str()) << " dollars." << endl;

  auto diff = balance - bet.get_wage();
  value.str(string());
  value << (diff >= 0 ? diff : diff * -1);

  if (diff > 0)
    message::success("Hooray, you won " + value.str() +
                     " dollars. See you next time! ;-)");
  else if (diff < 0)
    message::danger("Too bad, you lost " + value.str() +
                    " dollars. More luck on the next time! ;-)");
  else
    message::warning(
        "Well... At least you did not lose anything. More luck on the next "
        "time! ;-)");
  return 0;
}
