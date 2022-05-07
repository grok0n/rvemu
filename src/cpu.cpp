#include "cpu.h"
#include <iostream>
#include <iomanip>

// Create a new 'Cpu' object.
Cpu::Cpu (const std::vector<uint8_t>& binary)
	: bus (binary)
{
	// Set the stack pointer (sp) to end of dram.
	xreg[2] = DRAM_BASE + DRAM_SIZE;

	// Set pc to start of DRAM address.
	pc = DRAM_BASE;
}

// Print out the values in all register (x0-x31).
void Cpu::dump_registers ()
{
	std::string output;
	std::string abi[] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5",  "t6"};

	for (int i=0;i<8;i++)
	{
		for (int j=0;j<4;j++)
		{
			int index = i*4 + j;
			std::cout << "x" << index << " (" << abi[index] << ") =\t"  << std::hex << std::setfill ('0') << std::setw (16) << xreg[index] << ",\t";
		}
		std::cout << '\n';
	}
}

uint64_t Cpu::load (uint64_t addr, uint64_t size)
{
	return bus.load (addr, size);
}

void Cpu::store (uint64_t addr, uint64_t size, uint64_t value)
{
	return bus.store (addr, size, value);
}

uint64_t Cpu::fetch ()
{
	return bus.load (pc, 32);
	// TODO: Handle errors
}

// Load instructions.
void Cpu::instr_lb ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int8_t) load (l_s_addr, 8)));
}

void Cpu::instr_lh ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int16_t) load (l_s_addr, 16)));
}

void Cpu::instr_lw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) load (l_s_addr, 32)));
} 

void Cpu::instr_ld ()
{
	xreg[rd] = load (l_s_addr, 64);
}

void Cpu::instr_lbu ()
{
	xreg[rd] = load (l_s_addr, 8);
}

void Cpu::instr_lhu ()
{
	xreg[rd] = load (l_s_addr, 16);
}

void Cpu::instr_lwu ()
{
	xreg[rd] = load (l_s_addr, 32);
}

// Integer register-immediate instructions.
void Cpu::instr_addi ()
{
	xreg[rd] = xreg[rs1] + imm;
}


void Cpu::instr_slli ()
{
	xreg[rd] = xreg[rs1] << shamt;
}

void Cpu::instr_slti ()
{
	xreg[rd] = (((int64_t) xreg[rs1]) < ((int64_t) imm)) ? 1 : 0;
}

void Cpu::instr_sltiu ()
{
	xreg[rd] = (xreg[rs1] < imm) ? 1 : 0;
}

void Cpu::instr_xori ()
{
	xreg[rd] = xreg[rs1] ^ imm;
}

void Cpu::instr_srli ()
{
	xreg[rd] = xreg[rs1] >> shamt;
}

void Cpu::instr_srai ()
{
	xreg[rd] = (uint64_t) (((int64_t) xreg[rs1]) >> shamt);
}

void Cpu::instr_ori ()
{
	xreg[rd] = xreg[rs1] | imm;
}

void Cpu::instr_andi ()
{
	xreg[rd] = xreg[rs1] & imm;
}

void Cpu::instr_auipc ()
{
	xreg[rd] = (pc - imm) + 4;
}

void Cpu::instr_lui ()
{
	xreg[rd] = imm;
}

void Cpu::instr_addiw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) (xreg[rs1] + imm)));
}

void Cpu::instr_slliw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) (xreg[rs1] << shamt)));
}

void Cpu::instr_srliw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) (((uint32_t) xreg[rs1]) >> shamt)));
}

void Cpu::instr_sraiw ()
{
	xreg[rd] = (uint64_t) ((int64_t) (((int32_t) xreg[rs1]) >> shamt));
}

// Memory store instructions.
void Cpu::instr_sb ()
{
	store (l_s_addr, 8, xreg[rs2]);
}

void Cpu::instr_sh ()
{
	store (l_s_addr, 16, xreg[rs2]);
}

void Cpu::instr_sw ()
{
	store (l_s_addr, 32, xreg[rs2]);
}

void Cpu::instr_sd ()
{
	store (l_s_addr, 64, xreg[rs2]);
}

// Integer register-register instructions.
void Cpu::instr_add ()
{
	xreg[rd] = (uint64_t) (((int64_t) xreg[rs1]) + ((int64_t) xreg[rs1]));
}

void Cpu::instr_sub ()
{
	xreg[rd] = (uint64_t) (((int64_t) xreg[rs1]) - ((int64_t) xreg[rs2]));
}

void Cpu::instr_sll ()
{
	xreg[rd] = xreg[rs1] << shamt;
}

void Cpu::instr_slt ()
{
	xreg[rd] = (((int64_t) xreg[rs1]) < ((int64_t) xreg[rs2])) ? 1 : 0;
}

void Cpu::instr_sltu ()
{
	xreg[rd] = (xreg[rs1] < xreg[rs2]) ? 1 : 0;
}

void Cpu::instr_xor ()
{
	xreg[rd] = xreg[rs1] ^ xreg[rs2];
}

void Cpu::instr_srl ()
{
	xreg[rd] = xreg[rs1] >> shamt;
}

void Cpu::instr_sra ()
{
	xreg[rd] = (uint64_t) (((int64_t) xreg[rs1]) >> shamt);
}

void Cpu::instr_or ()
{
	xreg[rd] = xreg[rs1] | xreg[rs2];
}

void Cpu::instr_and ()
{
	xreg[rd] = xreg[rs1] & xreg[rs2];
}

void Cpu::instr_addw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) (xreg[rs1] + xreg[rs2])));
}

void Cpu::instr_subw ()
{
	xreg[rd] = (uint64_t) ((int64_t) ((int32_t) (xreg[rs1] - xreg[rs2])));
}

void Cpu::instr_sllw ()
{
	xreg[rd] = (uint64_t) ((int32_t) (((uint32_t) xreg[rs1]) << shamt));
}

void Cpu::instr_srlw ()
{
	xreg[rd] = (uint64_t) ((int32_t) (((uint32_t) xreg[rs1]) >> shamt));
}

void Cpu::instr_sraw ()
{
	xreg[rd] = (uint64_t) (((int32_t) xreg[rs1]) >> ((int32_t) shamt));
}

// Conditional branch operations.
void Cpu::instr_beq ()
{
	if (xreg[rs1] == xreg[rs2]) pc = (pc + imm) - 4;
}

void Cpu::instr_bne ()
{
	if (xreg[rs1] != xreg[rs2]) pc = (pc + imm) - 4;
}

void Cpu::instr_blt ()
{
	if (((int64_t) xreg[rs1]) < ((int64_t) xreg[rs2])) pc = (pc + imm) - 4;
}

void Cpu::instr_bge ()
{

	if (((int64_t) xreg[rs1]) >= ((int64_t) xreg[rs2])) pc = (pc + imm) - 4;
}

void Cpu::instr_bltu ()
{
	if (xreg[rs1] < xreg[rs2]) pc = (pc + imm) - 4;
}

void Cpu::instr_bgeu ()
{
	if (xreg[rs1] >= xreg[rs2]) pc = (pc + imm) - 4;
}

// Unconditional jumps.
void Cpu::instr_jalr ()
{
	pc = (xreg[rs1] + imm) & !1;
}

void Cpu::instr_jal ()
{
	pc = (pc + imm) - 4;
}

// Execute an instruction after decoding. Return true if an error occurs, else return false.
void Cpu::execute (uint64_t instr)
{
	// Instruction description variables.
	opcode = (int) (instr & 0x7f);	
	funct3 = (int) ((instr >> 12) & 0x7);
	funct7 = (int) ((instr >> 25) & 0x7f);
	rd = (int) ((instr >> 7) & 0x17);
	rs1 = (int) ((instr >> 15) & 0x17);
	rs2 = (int) ((instr >> 20) & 0x17);

	// Emulate register x0 always being hardwired to 0.
	xreg[0] = 0;

	// Decode and execute.
	switch (opcode)
	{
		case 0x03:
			// imm[11:0] = instr[31:20]. Signed extended immediate.
			imm = (uint64_t) (((int64_t) ((int32_t) instr)) >> 20); 
			l_s_addr = xreg[rs1] + imm;

			switch (funct3)
			{
				case 0x0: instr_lb (); break;
				case 0x1: instr_lh (); break;
				case 0x2: instr_lw (); break;
				case 0x3: instr_ld (); break;
				case 0x4: instr_lbu (); break;
				case 0x5: instr_lhu (); break;
				case 0x6: instr_lwu (); break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x13:
			// imm[11:0] = instr[31:20]. Signed extended immediate.
			imm = (uint64_t) (((int64_t) ((int32_t) instr)) >> 20);
			// shamt is encoded in the lower 6 bits of the I-immediate field for RV64I.
			shamt = (uint32_t) (imm & 0x3f);

			switch (funct3)
			{
				case 0x0: instr_addi (); break;
				case 0x1: instr_slli (); break;
				case 0x2: instr_slti (); break;
				case 0x3: instr_sltiu (); break;
				case 0x4: instr_xori (); break;
				case 0x5: 
					switch (funct7)
					{
						case 0x00: instr_srli (); break;
						case 0x10: instr_srai (); break;	
						// TODO: Handle invalid instruction case.
					}
					break;
				case 0x6: instr_ori (); break;
				case 0x7: instr_andi (); break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x17:
			// imm[31:12] = instr[31:12]. Signed extend immediate.
			imm = ((uint64_t) ((int64_t) ((int32_t) (instr & 0xfffff000))));
			instr_auipc ();
			break;
		case 0x1b:
			imm = (uint64_t) (((int64_t) ((int32_t) instr)) >> 20);
			// shamt is encoded in the lower 5 bits of the I-immediate field for RV64I.
			shamt = (uint32_t) (imm & 0x1f);

			switch (funct3)
			{
				case 0x0: instr_addiw (); break;
				case 0x1: instr_slliw (); break;
				case 0x5:
					switch (funct7)
					{
						case 0x00: instr_srliw (); break;
						case 0x20: instr_sraiw (); break;
						// TODO: Handle invalid instruction case.
					}
					break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x23:
			// imm[11:5] = instr[31:25], imm[4:0] = instr[11:7]
			imm = ((uint64_t) (((int64_t) ((int32_t) (instr & 0xfe000000))) >> 20)) | ((instr >> 7) & 0x1f);
			l_s_addr = xreg[rs1] + imm;

			switch (funct3)
			{
				case 0x0: instr_sb (); break;
				case 0x1: instr_sh (); break;
				case 0x2: instr_sw (); break;
				case 0x3: instr_sd (); break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x33:
			// shamt is given by rs2[5:0].
			shamt = (uint32_t) ((uint64_t) (xreg[rs2] & 0x3f));

			switch (funct3)
			{
				case 0x0:
					switch (funct7)
					{
						case 0x00: instr_add (); break;
						case 0x20: instr_sub (); break;
						// TODO: Handle invalid instruction case.
					}
					break;
				case 0x1: instr_sll (); break;
				case 0x2: instr_slt (); break;
				case 0x3: instr_sltu (); break;
				case 0x4: instr_xor (); break;
				case 0x5:
					switch (funct7)
					{
						case 0x00: instr_srl (); break;
						case 0x20: instr_sra (); break;
						// TODO: Handle invalid instruction case.
					}
					break;
				case 0x6: instr_or (); break;
				case 0x7: instr_and (); break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x37:
			imm = (uint64_t) ((int64_t) ((int32_t) (instr & 0xfffff000)));
			instr_lui ();
			break;
		case 0x3b:
			// shamt is given by rs2[4:0].
			shamt = (uint32_t) (xreg[rs2] & 0x1f);

			switch (funct3)
			{
				case 0x0:
					switch (funct7)
					{
						case 0x00: instr_addw (); break;
						case 0x20: instr_subw (); break; 
						// TODO: Handle invalid instruction case.
					}
					break;
				case 0x1: instr_sllw (); break;
				case 0x5:
					switch (funct7)
					{
						case 0x00: instr_srlw (); break;
						case 0x20: instr_sraw (); break; 
						// TODO: Handle invalid instruction case.
					}
					break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x63:
			// imm[12] = instr[31], imm[10:5] = instr[30:25], imm[4:1] = instr[11:8], imm[11] = instr[7].
			imm = ((uint64_t) (((int64_t) ((int32_t) (instr & 0x80000000))) >> 19)) 
				| ((instr & 0x80) << 4) // imm[11].
				| ((instr >> 20) & 0x7e0) // imm[10:5].
				| ((instr >> 7) & 0x1e); // imm[4:1].

			switch (funct3)
			{
				case 0x0: instr_beq (); break;
				case 0x1: instr_bne (); break;
				case 0x4: instr_blt (); break;
				case 0x5: instr_bge (); break;
				case 0x6: instr_bltu (); break;
				case 0x7: instr_bgeu (); break;
				// TODO: Handle invalid instruction case.
			}
			break;
		case 0x67:
			imm = (uint64_t) (((int64_t) ((int32_t) (instr & 0xfff00000))) >> 20);
			instr_jalr (); 
			break;
		case 0x6f:
			imm = ((uint64_t) (((int64_t) ((int32_t) (instr & 0x80000000))) >> 11)) // imm[20].
				| (instr & 0xff000) // imm[19:12].
				| ((instr >> 9) & 0x800) // imm[11].
				| ((instr >> 20) & 0x7fe); // imm[10:1].
			break;

			instr_jal ();
		// TODO: Handle invalid instruction case.
	};
}
