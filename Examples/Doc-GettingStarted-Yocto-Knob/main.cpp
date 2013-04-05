#include "yocto_api.h"
#include "yocto_anbutton.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

static void usage(void)
{
    cout << "usage: demo <serial_number> " << endl;
    cout << "       demo <logical_name>" << endl;
    cout << "       demo any                 (use any discovered device)" << endl;
    u64 now = yGetTickCount();    // dirty active wait loop 
	while (yGetTickCount()-now<3000);
    exit(1);
}

int main(int argc, const char * argv[])
{
    string      errmsg;
    YAnButton   *input1;
    YAnButton   *input5;
    string      target;
    
    if (argc < 2) {
        usage();
    }
    target = (string) argv[1];
    
    // Setup the API to use local USB devices
    if (yRegisterHub("usb", errmsg) != YAPI_SUCCESS) {
        cerr << "RegisterHub error: " << errmsg << endl;
        return 1;
    }
    
    if (target == "any") {
        YAnButton *anbutton = yFirstAnButton();
        if (anbutton==NULL) {
            cout << "No module connected (check USB cable)" << endl;
            return 1;
        }
        target = anbutton->module()->get_serialNumber();
    }   
    input1 = yFindAnButton(target + ".anButton1");
    input5 = yFindAnButton(target + ".anButton5"); 
    
    while(1) {
        if (!input1->isOnline()) {
            cout << "Module not connected (check identification and USB cable)"<< endl;
            break;
        }
        
        if (input1->get_isPressed()) 
            cout << "Button1: pressed    ";
        else 
            cout << "Button1: not pressed";
        cout << " - analog value: " << input1->get_calibratedValue() << endl;
        
        if (input5->get_isPressed()) 
            cout << "Button5: pressed    ";
        else 
            cout << "Button5: not pressed";
        cout << " - analog value: " << input5->get_calibratedValue() << endl;
        
        cout << "(press both buttons simultaneously to exit)" << endl;
        if (input1->get_isPressed() == Y_ISPRESSED_TRUE && 
            input5->get_isPressed() == Y_ISPRESSED_TRUE) 
            break;
        ySleep(1000,errmsg);
    };
    
    return 0;
}
