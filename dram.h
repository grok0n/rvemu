// The dram module that defines the Dram class for dram access

const uint64_t DRAM_SIZE = 1024 * 1024 * 128;

class Dram
{
	private:
		// Dynamic random access memory (DRAM).
		uint8_t dram [DRAM_SIZE];

	public:
		// Create new instance of Dram.
		Dram (const std::vector<uint8_t>& binary);

		// Load bytes in little-endian ordering from DRAM.
		uint64_t load (uint64_t addr, uint64_t size);

		// Store bytes in little-endian ordering to DRAM.
		void store (uint64_t addr, uint64_t size, uint64_t value);

		// Load a byte from little-endian DRAM.
		uint64_t load8 (uint64_t addr);

		// Load a halfword (2 bytes) from little-endian DRAM.
		uint64_t load16 (uint64_t addr);

		// Load a word (4 bytes) from little-endian DRAM.
		uint64_t load32 (uint64_t addr);

		// Load a doubleword (8 bytes) from little-endian DRAM.
		uint64_t load64 (uint64_t addr);

		// Store a byte to little-endian DRAM
		void store8 (uint64_t addr, uint64_t value);
		
		// Store a halfword (2 bytes) to little-endian DRAM
		void store16 (uint64_t addr, uint64_t value);

		// Store a word (4 bytes) to little-endian DRAM
		void store32 (uint64_t addr, uint64_t value);

		// Store a doubleword (8 bytes) to little-endian DRAM
		void store64 (uint64_t addr, uint64_t value);
};
