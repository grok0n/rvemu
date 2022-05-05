// The Cpu module definition
#include "bus.h"

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

		// RV64I Instructions
		/// CPU Load instuctions.
		void instr_lb ();
		void instr_lh ();
		void instr_lw ();
		void instr_ld ();
		void instr_lbu ();
		void instr_lhu ();
		void instr_lwu ();

		/// Integer register-immediate instructions.
		void instr_addi ();
		void instr_slli ();
		void instr_slti ();
		void instr_sltiu ();
		void instr_xori ();
		void instr_srli ();
		void instr_srai ();
		void instr_ori ();
		void instr_andi ();
		void instr_auipc ();
		void instr_lui ();
		void instr_addiw ();
		void instr_slliw ();
		void instr_srliw ();
		void instr_sraiw ();

		/// Memory store instructions.
		void instr_sb ();
		void instr_sh ();
		void instr_sw ();
		void instr_sd ();

		/// Integer register-register instructions.
		void instr_add ();
		void instr_sub ();
		void instr_sll ();
		void instr_slt ();
		void instr_sltu ();
		void instr_xor ();
		void instr_srl ();
		void instr_sra ();
		void instr_or ();
		void instr_and ();
		void instr_addw ();
		void instr_subw ();
		void instr_sllw ();
		void instr_srlw ();
		void instr_sraw ();

		// Conditional branch operations.
		void instr_beq ();
		void instr_bne ();
		void instr_blt ();
		void instr_bge ();
		void instr_bltu ();
		void instr_bgeu ();

		// Unconditional jumps.
		void instr_jalr ();
		void instr_jal ();
};
