#include <iostream>
#include <windows.h>

int main() {
	
	for(int i=100;i<4000;i+=20){
		Beep(i,100);
		Sleep(10);
		std::cout<<"freq = "<<i<<std::endl;
	}
	
    return 0;
}
