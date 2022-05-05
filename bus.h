/// The bus module contains the sytem bus which accesses the main memory and other peripherals.

// The address which DRAM stars, (same as QEMU virt machine).
const uint64_t DRAM_BASE = 0x8000'0000;

// The system bus.
class Bus
{
	private:
		Dram dram;

	public:
		// Create a new instance of Bus.
		Bus (const std::vector<uint8_t>& binary);

		// Load data unto system bus.
		uint64_t load (uint64_t addr, uint64_t size);

		// Store data through the system bus.
		void store (uint64_t addr, uint64_t size, uint64_t value);
};
