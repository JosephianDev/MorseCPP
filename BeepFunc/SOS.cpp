#include <windows.h>

int main() {
	Sleep(500);
	
	Beep(800, 100);
	Beep(800, 100);
	Beep(800, 100);
	
	Sleep(100);
	
	Beep(800, 100*3);
	Beep(800, 100*3);
	Beep(800, 100*3);
	
	Sleep(100);
	
	Beep(800, 100);
	Beep(800, 100);
	Beep(800, 100);
	
    return 0;
}
