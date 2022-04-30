#include "cpu.h"
#include "bus.h"
#include "ram.h"

#include <iostream>
#include <fstream>

int main (int argc, char** argv)
{
    if (argc != 1)
    {
        std::cerr << "Usage: rvemu <filename>\n";
        return 0;
    }

	string fname = argv[0];
	streampos size;
	
    
    // load in ROM File 
   
    ifstream file (fname, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		siz
	}
}
