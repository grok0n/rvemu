// The Cpu module definition

class Cpu 
{
	private:
		// 32 64-bit integer registers.
		uint64_t xreg [32];
		// System bus transfers data between CPU and peripheral devices.
		Bus bus;
		// Instruction identifiers.
		int opcode; 
		int funct3; 
		int funct7;
		// First register.
		int rs1; 
		// Second register.
		int rs2; 
		// Destination register.
		int rd;
		// Shift amount.
		uint32_t shamt;
		// Load/Store DRAM address.
		uint64_t l_s_addr;
		// Sign extended immediate value.
		uint64_t imm; 
	public:
		// Program counter to hold the memory address of the next intructions to be executed.
		uint64_t pc;

		// Create a new 'Cpu' object.
		Cpu (const std::vector<uint8_t>& binary);

		// Print out the values in all registers (x0-x31).
		void dump_registers ();	

		// Load a value from DRAM.
		uint64_t load (uint64_t addr, uint64_t size);

		// Store a value to DRAM.
		void store (uint64_t addr, uint64_t size, uint64_t value);

		// Get an instruction from DRAM.
		uint64_t fetch ();

		// Execute an instruction after decoding. Return true if an error occurs, else return false.
		void execute (uint64_t instr);
};

