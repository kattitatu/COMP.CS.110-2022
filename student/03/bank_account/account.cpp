#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    name_(owner), credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;
void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const{
    std::cout << name_ << " : " << iban_ << " : " << balance_ << " euros"<< std::endl;
}

void Account::set_credit_limit(int amount){
    if (credit_){
        credit_limit_ = amount;
    }
    else{
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        std::cout << std::endl;
    }
}

void Account::save_money(int save_amount){
    balance_ += save_amount;
}
bool Account::take_money(int take_amount){
    if (balance_ - take_amount < 0){
        if (credit_){
            if (balance_ - take_amount < credit_limit_ * (-1)){
                std::cout << "Cannot take money: credit limit overflow"<< std::endl;
                return false;
            }
            else{

                std::cout << take_amount << " euros taken: new balance of " << iban_ << " is " << balance_ - take_amount << " euros" << std::endl;
                balance_ = balance_ - take_amount;
                return true;
            }

        }
        else{
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return false;
        }
    }
    else{
        std::cout << take_amount << " euros taken: new balance of " << iban_ << " is " << balance_ - take_amount << " euros " << std::endl;
        balance_ = balance_ - take_amount;
        return true;
    }
}
void Account::transfer_to(Account& target, int transfer_amount){
        if (take_money(transfer_amount)){
            target.balance_ += transfer_amount;
        }
        else{
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }

    }

