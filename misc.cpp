
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string IDName(string str1, string str2){
    str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end()); 
    str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end()); 
    string str3 = str1+str2;
    transform(str3.begin(), str3.end(), str3.begin(), ::tolower);
    return str3;
}




