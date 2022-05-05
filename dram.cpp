// The implementation of the Dram class

Dram::Dram (const std::vector<uint8_t>& binary)
{
	for (int i=0;i<code.size();i++)
	{
		dram[i] = code[i];
	}
}

// Load bytes in little-endian ordering from DRAM.
uint64_t Dram::load (uint64_t addr, uint64_t size)
{
	switch (size)
	{
		case 8: 
			return load8 (addr);
		case 16:
			return load16 (addr);
		case 32:
			return load32 (addr);
		case 64:
			return load64 (addr);
		default:
			// TODO: Handle the error.
			return 0x0000'0000;
	}
}

// Store bytes in little-endian ordering to DRAM.
void Dram::store (uint64_t addr, uint64_t size, uint64_t value)
{
	switch (size)
	{
		case 8: 
			store8 (addr, value);
		case 16:
			store16 (addr, value);
		case 32:
			store32 (addr, value);
		case 64:
			store64 (addr, value);
		default:
			// TODO: Handle the error.
	}
}

// Load a byte from little endian DRAM
uint64_t Dram::load8 (uint64_t addr)
{
	int index = (int) (addr - DRAM_BASE);	

	return ((uint64_t) dram[index]);
}

// Load a halfword (2 bytes) from little endian DRAM
uint64_t Dram::load16 (uint64_t addr)
{
	int index = (int) (addr - DRAM_BASE);	

	return (uint64_t) dram[index] | (((uint64_t) dram[index + 1]) << 8);
}

// Load a word (4 bytes) from little endian DRAM
uint64_t Dram::load32 (uint64_t addr)
{
	int index = (addr - DRAM_BASE);	

	return (uint64_t) dram[index] 
			| (((uint64_t) dram[index + 1]) << 8)
			| (((uint64_t) dram[index + 2]) << 16)
			| (((uint64_t) dram[index + 3]) << 24);
}

// Load a word (4 bytes) from little endian DRAM
uint64_t Dram::load64 (uint64_t addr)
{
	int index = (addr - DRAM_BASE);	

	return (uint64_t) dram[index] 
			| (((uint64_t) dram[index + 1]) << 8)
			| (((uint64_t) dram[index + 2]) << 16)
			| (((uint64_t) dram[index + 3]) << 24)
			| (((uint64_t) dram[index + 4]) << 32)
			| (((uint64_t) dram[index + 5]) << 40)
			| (((uint64_t) dram[index + 6]) << 48)
			| (((uint64_t) dram[index + 7]) << 56);
}

// Store a byte to little-endian DRAM
void Dram::store8 (uint64_t addr, uint64_t value)
{
	int index = (addr - DRAM_BASE);	
	
	dram[index] = (uint8_t) (value & 0xff);
}

// Store a halfword (2 bytes) to little-endian DRAM
void Dram::store16 (uint64_t addr, uint64_t value)
{
	int index = (addr - DRAM_BASE);

	dram[index] = (uint8_t) (value & 0xff);
	dram[index + 1] = (uint8_t) ((value >> 8) & 0xff);
}

// Store a word (4 bytes) to little-endian DRAM
void Dram::store32 (uint64_t addr, uint64_t value)
{
	int index = (addr - DRAM_BASE);

	dram[index] = (uint8_t) (value & 0xff);
	dram[index + 1] = (uint8_t) ((value >> 8) & 0xff);
	dram[index + 2] = (uint8_t) ((value >> 16) & 0xff);
	dram[index + 3] = (uint8_t) ((value >> 24) & 0xff);
}

// Store a doubleword (8 bytes) to little-endian DRAM
void Dram::store64 (uint64_t addr, uint64_t value)
{
	int index = (addr - DRAM_BASE);

	dram[index] = (uint8_t) (value & 0xff);
	dram[index + 1] = (uint8_t) ((value >> 8) & 0xff);
	dram[index + 2] = (uint8_t) ((value >> 16) & 0xff);
	dram[index + 3] = (uint8_t) ((value >> 24) & 0xff);
	dram[index + 4] = (uint8_t) ((value >> 32) & 0xff);
	dram[index + 5] = (uint8_t) ((value >> 40) & 0xff);
	dram[index + 6] = (uint8_t) ((value >> 48) & 0xff);
	dram[index + 7] = (uint8_t) ((value >> 56) & 0xff);
}
