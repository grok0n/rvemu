// The implementation of the Bus module
#include "bus.h"

// Create a new instance of Bus.
Bus::Bus (const std::vector<uint8_t>& binary)
{
	dram = Dram (code);
}

// Load data unto system bus
uint64_t Bus::load (uint64_t addr, uint64_t size)
{
	// load data from main memory
	if (DRAM_BASE <= addr)
	{
		return dram.load (addr, size);
	}

	throw std::exception ();
	// TODO: Handle the error.
}

// Store data through the system bus.
void Bus::store (uint64_t addr, uint64_t size, uint64_t value)
{
	// store data to main memory
	if (DRAM_BASE <= addr)
	{
		dram.store (addr, size, value);		
	}

	// TODO: Handle the error.
}
