#include <iostream>
#include "MCT.cpp"

//input valori
template<typename T>void InputValue(T& value,T min,T max){
	do{
		std::cin>>value;std::cin.ignore(80,'\n');
		if((value<min)||(value>max)) std::cout<<"Value out of range, please enter the value again : ";
	}while((value<min)||(value>max));
}

int main(int argc, char *argv[]) {
	char risp;
	std::string tmp;
	unsigned short int tmp2;
	char tmp3;
	
	system("title MorseCodeTranslator by JoJo");
	
	MCT m;
	do{
		m.reset();
		do{
			system("cls");
			m.getInfo();
			std::cout<<std::endl;
			std::cout<<"(1) Input string"<<std::endl;
			std::cout<<"(2) Input sound frequency"<<std::endl;
			std::cout<<"(3) Input dot time (in millisec)"<<std::endl;
			std::cout<<"(4) Input dot char"<<std::endl;
			std::cout<<"(5) Input dash char"<<std::endl;
			std::cout<<"(6) Morse code of saved string (only text)"<<std::endl;
			std::cout<<"(7) Morse code of saved string (with BEEPs)"<<std::endl;
			std::cout<<"(r) Read the morse code"<<std::endl;
			std::cout<<"(s) Save on a file (STRING.morse)"<<std::endl;
			std::cout<<"(a) Append content on a file (STRING.morse)"<<std::endl;
			std::cout<<"(o) Open a file (*.morse)"<<std::endl;
			std::cout<<"(q) Reload everything or close program"<<std::endl;
			
			std::cout<<"Make your choise: ";
			std::cin>>risp;
			std::cin.ignore(256, '\n');
			switch(risp){
			case '1':
				std::cout<<std::endl<<"Old phrase: \""<<m.getPhrase()<<"\"."<<std::endl;
				std::cout<<"Insert new phrase: ";
				std::getline(std::cin, tmp);
				m.setPhrase(tmp);
				break;
			case '2':
				std::cout<<std::endl<<"Old sound freq: "<<m.getSoundFreq()<<" hz"<<std::endl;
				std::cout<<"Insert new sound freq (range 100hz-900hz) : ";
				InputValue<unsigned short int>(tmp2,99,901);
				m.setSoundFreq(tmp2);
				break;
			case '3':
				std::cout<<std::endl<<"Old DOT duration time: "<<m.getDotTime()<<" ms"<<std::endl;
				std::cout<<"Insert new DOT duration time (range 100ms-250ms) : ";
				InputValue<unsigned short int>(tmp2,99,251);
				m.setDotTime(tmp2);
				break;
			case '4':
				std::cout<<std::endl<<"Old DOT char: \'"<<m.getDotChar()<<"\'."<<std::endl;
				std::cout<<"Insert new DOT char: ";
				do{
					std::cin>>tmp3;std::cin.ignore(80,'\n');
					if(tmp3==m.getDashChar()) std::cout<<"Same as DASH character, please select another character : ";
					else if(tmp3==47) std::cout<<"The Slash \'/\' is an invalid character, please select another character : ";
				}while(tmp3==m.getDashChar()||(tmp3==47));
				m.setDotChar(tmp3);
				break;
			case '5':
				std::cout<<std::endl<<"Old DASH char: \'"<<m.getDashChar()<<"\'."<<std::endl;
				std::cout<<"Insert new DASH char: ";
				do{
					std::cin>>tmp3;std::cin.ignore(80,'\n');
					if(tmp3==m.getDotChar()) std::cout<<"Same as DOT character, please select another character : ";
					else if(tmp3==47) std::cout<<"The Slash \'/\' is an invalid character, please select another character : ";
				}while(tmp3==m.getDotChar()||(tmp3==47));
				m.setDashChar(tmp3);
				break;
			case '6':
				std::cout<<std::endl<<"The phrase: \""<<m.getPhrase()<<"\" ."<<std::endl;
				std::cout<<"In MORSE become : "<<m.translate(TEXT_TO_MORSE, m.getPhrase(), false, false)<<std::endl;
				if(m.getDotChar()!=46 && m.getDashChar()!=45)
					std::cout<<"with custom chars : "<<m.translate(TEXT_TO_MORSE, m.getPhrase(), true, false)<<std::endl;
				system("pause");
				break;
			case '7':
				std::cout<<std::endl<<"The phrase: \""<<m.getPhrase()<<"\"."<<std::endl;
				std::cout<<"In MORSE become : "<<m.translate(TEXT_TO_MORSE, m.getPhrase(), false, true)<<std::endl;
				system("pause");
				break;
			case 'r':
				m.readMorse(m.translate(TEXT_TO_MORSE,m.getPhrase(),false,false),true);
				break;
			case 's':
				std::cout<<"Custom filename? [y/n] : ";
				std::cin>>tmp3;std::cin.ignore(80,'\n');
				if(tmp3=='y' || tmp3=='Y'){
					std::cout<<"Insert filename: ";
					std::getline(std::cin, tmp);
					if(tmp.size()<3) tmp=m.getPhrase();//se minore di 3 caratteri imposta la frase come nome
				}else tmp=m.getPhrase();
				
				if(m.writeFile(tmp)) std::cout<<std::endl<<"File "<<tmp<<".morse saved successfully."<<std::endl;
				else std::cout<<"Error with saving file "<<tmp<<".morse"<<std::endl;
				system("pause");
				break;
			case 'o':
				std::cout<<"Insert filename (without extension): ";
				std::getline(std::cin, tmp);
				std::cout<<"Current read settings (or file setting)? [y/n]"<<std::endl;
				std::cout<<"{Y: for CURRENT READ SETTING}"<<std::endl;
				std::cout<<"{N: for FILE READ SETTING}"<<std::endl;
				std::cout<<"Make your choise : ";
				std::cin>>tmp3;std::cin.ignore(80,'\n');
				if(tmp3=='y' || tmp3=='Y') tmp2=true;
				else tmp2=false;
				
				if(m.readFile(tmp,tmp2)) std::cout<<std::endl<<"File "<<tmp<<".morse read successfully."<<std::endl;
				else std::cout<<"Error with reading file "<<tmp<<".morse"<<std::endl;
				system("pause");
				break;
			case 'a':
				std::cout<<"Insert filename (without extension): ";
				std::getline(std::cin, tmp);
				
				if(m.appendToFile(tmp)) std::cout<<std::endl<<"Phrase "<<m.getPhrase()<<" successfully appended to file "<<tmp<<".morse ."<<std::endl;
				else std::cout<<"Error with appending to file "<<tmp<<".morse"<<std::endl;
				system("pause");
				break;
			};
		}while(risp!='q' && risp!='Q');

		std::cout<<"Reload the program? [y/n] > ";
		std::cin>>risp;
	}while(risp!='n' && risp!='N');
    return 0;
}
