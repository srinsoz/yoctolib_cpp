#include "yocto_api.h"
#include "yocto_relay.h"
#include <iostream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

static void usage(void)
{
    cout << "usage: demo <serial_number>  [ A | B ]" << endl;
    cout << "       demo <logical_name> [ A | B ]" << endl;
    cout << "       demo any [ A | B ]                (use any discovered device)" << endl;
    u64 now = yGetTickCount();    // dirty active wait loop 
	while (yGetTickCount()-now<3000);
    exit(1);
}

int main(int argc, const char * argv[])
{
    string  errmsg;
    string  target;
    YRelay  *relay;
    char    state;

    if (argc < 3) {
        usage();
    }
    target = (string) argv[1];
    state = toupper(argv[2][0]);

    // Setup the API to use local USB devices
    if (yRegisterHub("usb", errmsg) != YAPI_SUCCESS) {
        cerr << "RegisterHub error: " << errmsg << endl;
        return 1;
    }
    
    if (target == "any") {
        relay = yFirstRelay();
        if (relay==NULL) {
            cout << "No module connected (check USB cable)" << endl;
            return 1;
        }
    }else{
        relay =  yFindRelay(target + ".relay1");
    }

    if (relay->isOnline()) {
        relay->set_state(state == 'A' ? Y_STATE_A : Y_STATE_B);
    } else {
        cout << "Module not connected (check identification and USB cable)" << endl;
    }
        
    return 0;
}
