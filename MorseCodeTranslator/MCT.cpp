#pragma once

#include <iostream> // per il resto
#include <stdio.h> // per l'uso dei file
#include <string> // per la gestione della frase e delle traduzioni
#include <sstream> // per le traduzioni
#include <windows.h> //per Beep e Sleep
#include <conio.h>//per terminare la procedura read (con ESC) se il testo è troppo lungo

const std::string morse_ch[26]={  // i - 65 (A in ascii)
	/* A */ ".-",				/* B */ "-...", 				/* C */ "-.-.",
	/* D */ "-..",				/* E */ ".",	 				/* F */ "..-.",
	/* G */ "--.",				/* H */ "....", 				/* I */ "..",
	/* J */ ".---",				/* K */ "-.-",	 				/* L */ ".-..",
	/* M */ "--",				/* N */ "-.",	 				/* O */ "---",
	/* P */ ".--.",				/* Q */ "--.-", 				/* R */ ".-.",
	/* S */ "...",				/* T */ "-",	 				/* U */ "..-",
	/* V */ "...-",				/* W */ ".--", 					/* X */ "-..-",
	/* Y */ "-.--",				/* Z */ "--.."
};
const std::string morse_num[10]={  // i - 48 (0 in ascii)
	"-----",// 0
	".----",// 1
	"..---",// 2
	"...--",// 3
	"....-",// 4
	".....",// 5
	"-....",// 6
	"--...",// 7
	"---..",// 8
	"----." // 9
};

enum mode {
	TEXT_TO_MORSE,
	MORSE_TO_TEXT
};

struct CONFIGURATION {
	unsigned short int sf;
	unsigned short int dt;
	char dt_ch;
	char dsh_ch;
};

class MCT {
private:
    unsigned short int SOUND_FREQUENCY;
    unsigned short int DOT_TIME;	//DASH_TIME = DOT_TIME * 3;
    char DOT_CHAR;
    char DASH_CHAR;
    std::string PHRASE;
	
	std::string text2morse(std::string str){
		std::stringstream res;
		for(int i=0;i<str.size();i++){
			//controlla se si tratta di un numero
			if(str[i]>=48 && str[i]<=57) res<<morse_num[str[i]-48];
			//controlla invece se si tratta di una lettera
			else if(str[i]>=65 && str[i]<=90) res<<morse_ch[str[i]-65];
			// controlla se si tratta di uno spazio
			else if(str[i]==32) res<<'/';
			//resto dei caratteri
			else res<<str[i];
			
			//aggiungiamo lo spazio tra lettera e altra
			res<<' ';
		}
		return res.str();
	}
	
	std::string morse2text(std::string str){
		std::stringstream res;
		std::stringstream tmp(str);
		std::string w;
		
		while(tmp >> w){
        	if(w=="/") res<<(char)32;
        	else{
        		//controlla se si tratta di una lettera
				for(int j=0;j<26;j++) if(w==morse_ch[j]) res<<(char)(j+65);
				//controlla se si tratta di un numero
				for(int x=0;x<10;x++) if(w==morse_num[x]) res<<(char)(x+48);
			}
    	}
		return res.str();
	}
	
	std::string trasformCustomChar(std::string str){ //da morse originale a customizzato
		for(int i=0;i<str.size();i++){
			if(str[i]==45)//45 è -
				str[i]=DASH_CHAR;
			if(str[i]==46)//46 è .
				str[i]=DOT_CHAR;
		}
		return str;
	}
	
	std::string fromCustomChar(std::string str){ //da morse customizzato a originale
		for(int i=0;i<str.size();i++){
			if(str[i]==DASH_CHAR)
				str[i]=45;//45 è -
			if(str[i]==DOT_CHAR)
				str[i]=46;//46 è .
		}
		return str;
	}
	
	CONFIGURATION getConfByFile(std::string filename){
		filename.append(".morse");//estensione fissa *.morse
		FILE *fp = fopen(filename.c_str(), "r");
		
		// impossibile aprire il file
	    if(fp == NULL) return {};
	
	    // leggere linea dopo linea, max 256 bytes
	    const unsigned MAX_LENGTH = 256;
	    char buffer[MAX_LENGTH];
	    
		//lettura dati dalla prima linea
		fgets(buffer, MAX_LENGTH, fp);
		
		// close the file
	    fclose(fp);
		
		if(buffer[0]=='#'){ //lettura dati corretta
			std::stringstream tmp(buffer);
			std::string w;
			//formato prima linea :          # snd_frq dt_time dt_ch dsh_ch
			unsigned short int sf,dt;
			char dt_ch,dsh_ch;
			
			tmp>>w>>sf>>dt>>dt_ch>>dsh_ch;
			CONFIGURATION c{sf,dt,dt_ch,dsh_ch};
			return c;
		}else return {};
	}
	
public:
    MCT(){
        reset();
    }
	void reset(){
		SOUND_FREQUENCY = 800;
        DOT_TIME = 100;
        DOT_CHAR = '.';
        DASH_CHAR = '-';
		PHRASE = "HELLO WORLD";
	}
    void getInfo(){
        std::cout<<"Sound frequency: "<<getSoundFreq()<<std::endl;
        std::cout<<"Time of DOT (DOT duration in millisec): "<<getDotTime()<<std::endl;
        std::cout<<"DOT char: "<<getDotChar()<<std::endl;
        std::cout<<"DASH char: "<<getDashChar()<<std::endl;
        std::cout<<"Saved PHRASE: "<<getPhrase()<<std::endl;
    }
    //translator
    std::string translate(mode m, std::string str, bool custom=true, bool with_beep=false){
    	std::string res;
		if(m==TEXT_TO_MORSE){
			if(custom) res=trasformCustomChar(text2morse(str));
			else res=text2morse(str);
			
			//lettura con beep solo per text to morse
    		if(with_beep) {
    			if(custom) readMorse(fromCustomChar(res));
    			else readMorse(res);
			}
		}
    	else if(m==MORSE_TO_TEXT){
    		if(custom) res=fromCustomChar(morse2text(str));
			else res=morse2text(str);
		}
    	else return NULL;
    	
    	return res;
	}
    //read morse
    void readMorse(std::string morse, bool with_script=false){
    	if(with_script) std::cout<<std::endl;
		for(int i=0;i<morse.size();i++){
			if(with_script) std::cout<<morse[i];
			
			if(morse[i]==DASH_CHAR)//45 è -
				Beep(SOUND_FREQUENCY, DOT_TIME*3);//tempo del dash
			if(morse[i]==DOT_CHAR)//46 è .
				Beep(SOUND_FREQUENCY, DOT_TIME);//tempo del dot
			if(morse[i]==47)//47 è /
				Sleep(DOT_TIME*7);//tempo tra le parole
			if(morse[i]==32)//32 è Spazio
				Sleep(DOT_TIME*3);//tempo tra le lettere
			
			Sleep(DOT_TIME);//spazio tra punti stessa lettera
			
			//controlla se il tasto premuto per terminare la procedura
			if(_kbhit()){
	            char key = _getch();
	            if(key==27){// Codice ASCII per 'Esc'
	                std::cerr<<std::endl<<"Procedura terminata."<<std::endl;
	                break;
	            }
        	}
		}
	}
	
    //files manager
    bool readFile(std::string filename_base, bool customRead=false){
    	std::string filename = filename_base+".morse";//estensione fissa *.morse
		FILE *fp = fopen(filename.c_str(), "r");
		
		// impossibile aprire il file
	    if(fp == NULL) return false;
	
	    // leggere linea dopo linea, max 256 bytes
	    const unsigned MAX_LENGTH = 256;
	    char buffer[MAX_LENGTH];
	    
		//lettura dati dalla prima linea
		fgets(buffer, MAX_LENGTH, fp);
		if(buffer[0]=='#'){ //lettura dati corretta
			CONFIGURATION c = getConfByFile(filename_base);
			//imposto i caratteri custom
			if(c.dt_ch!=32 && c.dt_ch!=47 && c.dt_ch!=c.dsh_ch) DOT_CHAR=c.dt_ch;
			if(c.dsh_ch!=32 && c.dsh_ch!=47 && c.dsh_ch!=c.dt_ch) DASH_CHAR=c.dsh_ch;
			
			//continua lettura
			if(customRead==false){//leggi la configurazione del file e impostala
				std::cout<<std::endl<<"File read preset is being set up.."<<std::endl;
				
				if(c.sf>99 && c.sf<901) SOUND_FREQUENCY=c.sf;
				if(c.dt>99 && c.dt<251) DOT_TIME=c.dt;
			}else std::cout<<std::endl<<"Current reading preset is being used.."<<std::endl;
			
			std::cout<<"Preset: "<<'#'<<(char)32<<SOUND_FREQUENCY<<(char)32<<DOT_TIME<<(char)32<<DOT_CHAR<<(char)32<<DASH_CHAR<<std::endl;
			while (fgets(buffer, MAX_LENGTH, fp))
	        	readMorse(std::string(buffer),true);
				
		}else return false;
	
	    // close the file
	    fclose(fp);
	    return true;
	}
	bool writeFile(std::string filename){
		filename.append(".morse");//estensione fissa *.morse
		FILE *fp = fopen(filename.c_str(), "w");
	    
		// impossibile aprire il file
		if (fp == NULL) return false;
		
		std::stringstream ss;
		ss<<'#'<<(char)32<<SOUND_FREQUENCY<<(char)32<<DOT_TIME<<(char)32<<DOT_CHAR<<(char)32<<DASH_CHAR<<std::endl;
		
	    // scrivere nel file
	    fprintf(fp, ss.str().c_str());//prima linea uguale per tutti i file
	    //formato prima linea :          # snd_frq dt_time dt_ch dsh_ch
	    
		//inserisco il morse
		fprintf(fp, translate(TEXT_TO_MORSE,PHRASE,true,false).c_str());
	
	    // chiudo il file
	    fclose(fp);
	    return true;
	}
    bool appendToFile(std::string filename_base){
    	//prendo la configurazione del file e imposto i caratteri
		CONFIGURATION c = getConfByFile(filename_base);
		//imposto i caratteri custom
		if(c.dt_ch!=32 && c.dt_ch!=47 && c.dt_ch!=c.dsh_ch) DOT_CHAR=c.dt_ch;
		if(c.dsh_ch!=32 && c.dsh_ch!=47 && c.dsh_ch!=c.dt_ch) DASH_CHAR=c.dsh_ch;
    	
    	//eseguo l'effettivo append
    	std::string filename = filename_base+".morse";//estensione fissa *.morse
		FILE *fp = fopen(filename.c_str(), "r");
		
		// impossibile aprire il file
		if (fp == NULL) return false;
		
		//inserisco il morse
		fprintf(fp, translate(TEXT_TO_MORSE,PHRASE,true,false).c_str());
	
	    // chiudo il file
	    fclose(fp);
	    return true;
	}
    
    //getters and setters
    void setPhrase(std::string newPhrase){
    	//trasforma tutta la frase in maiuscolo
    	for(int i=0;i<newPhrase.size();i++)
			newPhrase[i]=toupper(newPhrase[i]);
        PHRASE = newPhrase;
    }
    std::string getPhrase(){
        return PHRASE;
    }
    void setSoundFreq(unsigned short int snd_freq){
    	SOUND_FREQUENCY = snd_freq;
	}
	unsigned short int getSoundFreq(){
		return SOUND_FREQUENCY;
	}
	void setDotTime(unsigned short int dt_time){
		DOT_TIME = dt_time;
	}
	unsigned short int getDotTime(){
		return DOT_TIME;
	}
	void setDotChar(char dt_char){
		DOT_CHAR = dt_char;
	}
	char getDotChar(){
		return DOT_CHAR;
	}
	void setDashChar(char dsh_char){
		DASH_CHAR = dsh_char;
	}
	char getDashChar(){
		return DASH_CHAR;
	}
};
