#include "main.pb.h"
#include<chrono>
#include<fstream>
using namespace std;
int main(){
    auto date =  chrono::duration_cast< chrono::milliseconds >(
      chrono::system_clock::now().time_since_epoch()
    ).count();
    EncryptedBill *ebill = new EncryptedBill();
    Bill *bill = new Bill();
    bill->set_billid(1);
    bill->set_datetime(date);
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