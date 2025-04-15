#include <iostream>
#include <windows.h>
#include <cctype>

template<typename T> void InputValue(T& value,T min,T max){do{ std::cin>>value;std::cin.ignore(80,'\n'); }while((value<min)||(value>max));}//input valori

int main() {
	unsigned short int f,d;
	char risp;
	do{
		std::cout<<"insert freq [40 - 30000] > ";
		InputValue<unsigned short int>(f,40,30000);
		std::cout<<"insert duration (in millis) > ";
		InputValue<unsigned short int>(d,0,30000);
		Beep(f, d); // freq e durata
    	//Sleep(200);
		
		std::cout<<"Reload the beepFunction? [y/n] > ";
		std::cin>>risp;
		risp = tolower(risp);
	}while(risp!='n');
    return 0;
}
