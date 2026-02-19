#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>


using namespace std;


struct GiftStruct{
    int price;
    string name;
};

typedef vector<GiftStruct> giftStore;



struct WishList{
    int budget;
    vector<string> items;
};

bool DataGift(const string& filename, vector<GiftStruct>& giftStore){
    //Precondition
    assert(true);
    //Postcondition
    //Has extracted the whole gift shop file 
    ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    GiftStruct result;
    string line;

    while (getline(file, line)) {
        istringstream stream(line);
        stream >> result.price;
        getline(stream >> ws, result.name); 
        giftStore.push_back(result);
    }

    return true;
}

bool DataWish(const string& filename, WishList& list){
    //Precondition
    assert (true);
    //postcondition:
    //has extracted the whole file of specific wishlist
    
    ifstream file(filename);

    if(!file.is_open()){
        return false;
    }

    file >> list.budget; 
    file.ignore();

    string line;
    while(getline(file,line)){
        list.items.push_back(line);
    }
    return true;
}

int gift_from_store(const giftStore& gift_list, string val){
    //Precondition
    assert (true);
    //Postcondtion 
    //returns the price of the item in wishlist
    for(int i = 0; i < ssize(gift_list); i++){
        if (gift_list.at(i).name == val){
            return gift_list.at(i).price;
        }
    }
    return 0;
}

int gifts (const giftStore& store_gift, WishList wishlist, int nr_gift, vector<string>& giftset){
    //Preconditon
    assert(true);
    //Postcondtion returns the budget thats left
    
    if (nr_gift >= ssize(wishlist.items)) {
        return wishlist.budget;
    }

    int current_gift_price = gift_from_store(store_gift, wishlist.items[nr_gift]);
    
    vector<string> giftset_without = giftset;
    int budget_without_gift = gifts(store_gift, wishlist, nr_gift + 1, giftset_without);

    vector<string> giftset_with = giftset;
    int budget_with_gift = wishlist.budget;
    if (current_gift_price > 0 && current_gift_price <= wishlist.budget) {
        wishlist.budget -= current_gift_price;
        budget_with_gift = gifts(store_gift, wishlist, nr_gift + 1, giftset_with);
        wishlist.budget += current_gift_price;

        if (budget_with_gift >= 0) {
            giftset_with.push_back(wishlist.items[nr_gift]);
        }
    }
    
    if (budget_with_gift >= 0 && budget_with_gift < budget_without_gift) {
        giftset = giftset_with;
        return budget_with_gift;
    } else {
        giftset = giftset_without;
        return budget_without_gift;
    }
}





#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
    (Andrew ... Fabienne) has been computed and printed to `cout`
*/
    
    giftStore store;
    WishList wishlist;
    vector<string> gifts_getting;

    string name[6] = {"Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne"};
    ofstream out("best gifts.txt");


    DataGift("giftstore.txt", store);
    for(int i = 0; i < 6; i++){
        wishlist.items.clear();
        DataWish(name[i]+".txt", wishlist);

       int remainder = gifts(store,wishlist, 0, gifts_getting);

        out << name[i] << endl;
        out<< remainder << endl;
        for(int k = 0; k < ssize(gifts_getting); k++){
            out << gifts_getting.at(k) << endl;
        }
        out << "\n";
        gifts_getting.clear();
    }
    out.close();
    return 0;
}
#endif



