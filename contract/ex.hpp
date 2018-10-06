#include <enulib/currency.hpp>
#include <enulib/enu.hpp>
#include <vector>

#define ENU_SYMBOL S(4, ENU)  // MainNet and TestNet use EOS
#define LTS_SYMBOL S(4, LTS)  // MainNet and TestNet use EOS

using namespace enumivo;

class ex : public contract {
 public:
  ex(account_name self)
      : contract(self) {}

  void buyLTS(const currency::transfer& transfer);
  void sellLTS(const currency::transfer& transfer);

  void apply(account_name contract, action_name act);

};
