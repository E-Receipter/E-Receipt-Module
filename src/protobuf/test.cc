#include "main.pb.h"
#include<fstream>
using namespace std;
int main(){
    EncryptedBill *ebill = new EncryptedBill();
    Bill *bill = new Bill();
    bill->set_id(1);
    bill->set_datetime(1);
    for(int i=0;i<10;i++){
        Item* a = bill->add_items();
        a->set_name("random");
        a->set_price(12.11);
        a->set_qty(1);
    }
    ebill ->set_shopid(1);
    ebill->set_encryptedbill(bill->SerializeAsString());
    fstream output("test.txt", ios::out | ios::trunc | ios::binary);
    if (!ebill->SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }
    return 0;
}