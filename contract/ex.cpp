#include "ex.hpp"

#include <cmath>
#include <enulib/action.hpp>
#include <enulib/asset.hpp>
#include <enu.token/enu.token.hpp>

using namespace enumivo;
using namespace std;

void ex::buyLTS(const currency::transfer &transfer) {
  if (transfer.to != _self) {
    return;
  }

  // get ENU balance
  auto enu_balance = enumivo::token(N(enu.token)).
	   get_balance(_self, enumivo::symbol_type(ENU_SYMBOL).name()).amount;

  // check purchase limit, not exceed 1% at each time
  auto amount = transfer.quantity.amount;
  enumivo_assert(amount * 100 <= (enu_balance - amount), "Purchase too munch, should be less than 1% at each time");

  // get LTS balance
  auto lts_balance = enumivo::token(N(ltsonenumivo)).
	   get_balance(_self, enumivo::symbol_type(LTS_SYMBOL).name()).amount;


  // calculate LTS to buy
  auto lts_buy = amount * lts_balance / (enu_balance - amount);
  auto fee = lts_buy / 1000;
  auto lts_transfer_amount = lts_buy - fee;
  auto to = transfer.from;

  auto quantity = asset(lts_transfer_amount, LTS_SYMBOL);

  action(permission_level{_self, N(active)}, N(ltsonenumivo), N(transfer),
         std::make_tuple(_self, to, quantity,
                         std::string("Buy LTS from exchange")))
      .send();
}

void ex::sellLTS(const currency::transfer &transfer) {
  if (transfer.to != _self) {
    return;
  }

  // get LTS balance
  auto lts_balance = enumivo::token(N(ltsonenumivo)).
	   get_balance(_self, enumivo::symbol_type(LTS_SYMBOL).name()).amount;

  // check purchase limit, not exceed 1% at each time
  auto amount = transfer.quantity.amount;
  enumivo_assert(amount * 100 <= (lts_balance - amount), "Sell too munch, should be less than 1% at each time");

  // get ENU balance
  auto enu_balance = enumivo::token(N(enu.token)).
	   get_balance(_self, enumivo::symbol_type(ENU_SYMBOL).name()).amount;

  // calculate ENU to transfer
  auto enu_buy = amount * enu_balance / (lts_balance - amount);
  auto fee = enu_buy / 1000;
  auto enu_transfer_amount = enu_buy - fee;
  auto to = transfer.from;

  auto quantity = asset(enu_transfer_amount, ENU_SYMBOL);

  action(permission_level{_self, N(active)}, N(enu.token), N(transfer),
         std::make_tuple(_self, to, quantity,
                         std::string("Sell LTS to exchange")))
      .send();
}

void ex::apply(account_name contract, action_name act) {
  if (contract == N(enu.token) && act == N(transfer)) {
    // React to transfer notification.
    // DANGER: All methods MUST check whethe token symbol is acceptable.

    auto transfer = unpack_action_data<currency::transfer>();
    enumivo_assert(transfer.quantity.symbol == ENU_SYMBOL,
                 "must pay with ENU token");
    buyLTS(transfer);
    return;
  }

  if (contract == N(ltsonenumivo) && act == N(transfer)) {
    // React to transfer notification.
    // DANGER: All methods MUST check whethe token symbol is acceptable.

    auto transfer = unpack_action_data<currency::transfer>();
    enumivo_assert(transfer.quantity.symbol == LTS_SYMBOL,
                 "must pay with LTS token");
    sellLTS(transfer);
    return;
  }

  if (contract != _self) return;

}

extern "C" {
[[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  ex enults(receiver);
  enults.apply(code, action);
  enumivo_exit(0);
}
}
