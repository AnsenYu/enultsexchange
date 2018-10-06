# enultsexchange

Decentralized exchange for ENU/LTS trading pair.

https://enumivo.com/topic/888-100k-enu-bounty-simple-lts-enu-exchange/?tab=comments#comment-6991

### build contract and abi
> cd contract
> ./build.sh

### create contract account
create account and update authority

### deposit initial ENU/LTS
transfer ENU & LTS to account

### deploy contract
set contract

### start trade ENU/LTS pair
transfer ENU to contract and get LTS back;
transfer LTS to contract and get ENU back;
Assume the contract account balance is x LTS and y ENU, the price is x/y LTS/ENU. 

Each time anyone can buy or sell less than 1% of the account balance.
