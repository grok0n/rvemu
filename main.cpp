#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

#include <vector>

#include "cpu.h"


int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: rvemu <filename>\n";
        return 0;
    }
		
	std::string fname = argv[1];
	std::streampos size;
	std::vector<uint8_t> code;
	
   	// Load Binary data from file .
    std::ifstream bin_file (fname, std::ios::binary);

	if (bin_file.good())
	{
		// Read Binary data using streambuffer iterators.
		std::vector<uint8_t> v_buf((std::istreambuf_iterator<char>(bin_file)), (std::istreambuf_iterator<char>()));
		code = v_buf;
		bin_file.close();
	}
	else
	{
		std::cerr << "Cannot open target binary file!\n";
		throw std::exception ();
	}

	Cpu cpu (code);

	while (true)
	{
		// 1. Fetch.
		uint64_t instr = cpu.fetch ();

		// 2. Increment program counter by 4 bytes.
		cpu.pc += 4;
			
		// 3. Decode.
		// 4. Execute.
		cpu.execute (instr);

		if (cpu.pc == 0) break; // Avoid an infinite loop.
	}

	cpu.dump_registers ();
}
