# enultsexchange

Decentralized exchange for ENU/LTS trading pair.

https://enumivo.com/topic/888-100k-enu-bounty-simple-lts-enu-exchange/?tab=comments#comment-6991

### build contract and abi
> cd contract && ./build.sh

### create contract account
create contract account and update authority to allow enumivo.code (check update_auth.sh example)

### deposit initial ENU/LTS
transfer ENU & LTS to contract account to set the initial price.

### deploy contract
deploy contract.

### start trading ENU/LTS pair
transfer ENU to contract and get LTS back;
transfer LTS to contract and get ENU back;
Assume the contract account balance is x LTS and y ENU, the price is x/y LTS/ENU. 

Each time anyone can buy or sell less than 1% of the account balance.
