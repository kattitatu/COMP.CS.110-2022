#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data *card = new Card_data();
    card->data = id;
    card->next = top_;
    top_ = card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data *current_card = top_;
    uint index = 1;
    while(current_card != nullptr){
        s << index <<  ": " << current_card->data << std::endl;
        index++;
        current_card = current_card->next;
    }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr){
        return false;
    }
    Card_data *top_most = top_;
    top_ = top_ ->next;
    id = top_most->data;
    delete top_most;
    return true;
}

bool Cards::bottom_to_top()
{
    if(top_ == nullptr){
        return false;
    }
    Card_data *current_card = top_;
    Card_data *second_last_card = current_card;
    while(current_card->next != nullptr){

        second_last_card = current_card;
        current_card = current_card->next;
    }
    second_last_card->next = nullptr;
    current_card->next = top_;
    top_ = current_card;
    return true;
}

bool Cards::top_to_bottom()
{
    if(top_ == nullptr)
    {
        return false;
    }
    if(top_-> next == nullptr){
        return true;
    }
    Card_data *current_card = top_;
    while(current_card->next != nullptr){
        current_card = current_card->next;
    }
    Card_data *new_top_card = top_->next;
    current_card->next = top_;
    top_->next = nullptr;
    top_ =  new_top_card;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}


Cards::~Cards()
{
    Card_data *current_card = top_;
    while(current_card != nullptr){
        top_ = top_->next;
        delete current_card;
        current_card = top_;
    }

}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    if(top==nullptr){
        return 1;
    }
    int index =  recursive_print(top->next, s);

    s << index << ": " << top->data << std::endl;
    return index+1;
}
