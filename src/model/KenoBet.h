#include <algorithm>
#include <vector>

using number_type = unsigned short int;
using cash_type = float;
using set_of_numbers_type = std::vector<number_type>;

class KenoBet {
 public:
  //! Creates an empty Keno bet.
  KenoBet() : m_wage(0){/*empty*/};

  /*! Adds a number to the spots only if the number is not already there .
   @param spot_ The number we wish to include in the bet.
   @return T if number chosen is successfully inserted ; F otherwise. */
  bool add_number(number_type spot_) {
    if (m_spots.size() >= 15) return false;

    bool contains =
        std::find(m_spots.begin(), m_spots.end(), spot_) != m_spots.end();
    if (contains) return false;

    m_spots.push_back(spot_);
    return true;
  }

  /*! Sets the amount of money the player is betting.
   @param wage_ The wage.
   @return True if we have a wage above zero ; false otherwise. */
  bool set_wage(cash_type wage_) {
    this->m_wage = wage_;
    return wage_ > 0;
  }

  //! Resets a bet to an empty state.
  void reset(void) {
    this->m_spots.clear();
    this->m_wage = 0;
  }

  /*! Retrieves the player's wage on this bet.
   @return The wage value. */
  cash_type get_wage(void) const { return this->m_wage; }

  /*! Returns to the current number of spots in the player's bet.
   @return Number of spots present in the bet. */
  size_t size(void) const { return this->m_spots.size(); }

  /*! Determine how many spots match the hits passed as argument.
   @param hits_ List of hits randomly chosen by the computer.
   @return An vector with the list of hits. */
  set_of_numbers_type get_hits(const set_of_numbers_type& hits_) const {
    set_of_numbers_type intersection;

    for (size_t i = 0; i < size(); i++) {
      const number_type item = m_spots[i];

      bool contains =
          std::find(hits_.begin(), hits_.end(), item) != hits_.end();
      if (contains) intersection.push_back(item);
    }

    return intersection;
  }

  /*! Return a vector <spot_type> with the spots the player has picked so far.
   @return The vector <spot_type> with the player's spots picked so far. */
  set_of_numbers_type get_spots(void) const { return this->m_spots; }

 private:
  set_of_numbers_type m_spots;  //<! The player's bet.
  cash_type m_wage;             //<! The player's wage
};
