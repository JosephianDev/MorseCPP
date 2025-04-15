#include <iostream>
#include <stdio.h>
#include <string>

int main(int argc, char *argv[]) {
	if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file.txt>" << std::endl;
        return 1; // Restituisci 1 per indicare un errore
    }else{
    	std::cout << "Usage: " << argv[0] << " " << argv[1] << std::endl;
	}
	
	FILE *fp = fopen(argv[1],"r");
	
	// impossibile aprire il file
	if(fp == NULL) return false;
	
	// leggere linea dopo linea, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    
	//lettura dati dalla prima linea
	fgets(buffer, MAX_LENGTH, fp);
	std::cout<<std::string(buffer)<<std::endl;
	
	// close the file
	fclose(fp);
	
	system("pause");
	return true;
}
