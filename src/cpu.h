#pragma once

#include <fstream>
#include <cstdlib> //exit
#include <cstring> //memset
#include <iostream>
#include <ctime>

using u8 = unsigned char;
using u16 = unsigned short;
using i32 = int;
class GB_CPU{
public:

	//constructor 
	GB_CPU(const std::string & ROM_file, bool debug_in){

		//turn on debugging
		debug = debug_in;

		//set RAM to zero
		memset(RAM, 0, 0xFFFF);

		//set registers, stack pointer and program counter to zero

		//open ROM
        std::ifstream file;
        file.open(ROM_file.c_str(), std::ios::in|std::ios::binary);

        if(!file){
        	std::cerr << "Unable to load ROM\n";
        	exit(1);
        }

    // get length of file:
	file.seekg (0, file.end);
	int length = file.tellg();
	file.seekg (0, file.beg);
	//in the future, load 1st half into RAM and 2nd half into bank, for now just dump the whole damn thing
	file.read(reinterpret_cast<char*>(RAM), length);
	
	file.close();
	//debug: should print out title of game
	for(int i = 0x0; i < 0xF; ++i){
		
		std::cout << RAM[0x134 + i];
	}
	std::cout << '\n';
	
	
	
}

void reset();


//do this once per cycle
void tick(){
	//check interrupts
	char a;
	//fetch
	op = RAM[program_counter];
	
	execute_opcode(op);
	//execute
	if(debug){
		
		std::cout << std::hex <<
		" ( " << static_cast<u16>(RAM[program_counter]) << ' ' << static_cast<u16>(RAM[program_counter + 1]) << 
				' ' << static_cast<u16>(RAM[program_counter + 2]) << " ) \n" <<
			
				 "Current opcode: " << static_cast<u16>(op) << ' ' << 
				"    Program counter: " << program_counter << "    Stack pointer: " <<
				stack_pointer << 
				'\n' <<
				"8-bit Register status: \n    a: " << static_cast<u16>(a) << 
				" b: " << static_cast<u16>(b) << 
				" c: " << static_cast<u16>(c) << 
				" d: " << static_cast<u16>(d) << 
				" e: " << static_cast<u16>(e) << 
				" f: " << static_cast<u16>(f) << 
				" h: " << static_cast<u16>(h) << 
				" l: " << static_cast<u16>(l) << 
				'\n' <<
				"16 bit register status: \n    af: " << af <<
				" bc: " << bc <<
				" de: " << de << 
				" hl: " << hl <<
				'\n' <<
				"Flags: \n" <<
				"    Zero: " << z_flag <<
				" Carry: " << c_flag <<
				" Half Carry: " << h_flag <<
				" Subtract: " << n_flag << 
				"\n\n";



			std::cin.get();
		}
		// program_counter += 1;
	}

	



	

private:

	//execute opcode
	void execute_opcode(u8 op);

	//opcode helper functions////////////////////////////////

	//8 bit loads
	inline void ld_nn_n(u8 * nn);
	inline void ld_r1_r2(u8 * r1, u8 * r2);
	inline void ld_r1_r2_hl(u8 * r1, u8 * r2);
	inline void ld_r1_r2_hl_n(u8 * r1, u8 * r2);
	inline void ld_a_n(u8 * n);
	inline void ld_a_n_addr(u8 * n);
	inline void ld_a_n_imm();
	inline void ld_a_n_addr_nn();
	inline void ld_n_a(u16 * n);
	inline void ld_n_a_addr(u16 n);
	inline void ld_n_a_addr_nn();
	inline void ld_a_c();
	inline void ld_c_a();
	inline void ldd_a_hl();
	inline void ldd_hl_a();
	inline void ldi_a_hl();
	inline void ldi_hl_a();
	inline void ldh_n_a();
	inline void ldh_a_n();

	//16 bit loads
	inline void ld_n_nn(u16 * n);
	inline void ld_sp_hl();
	inline void ld_hl_sp_n();
	inline void ld_nn_sp();
	inline void push_nn(u16 nn);
	inline void pop_nn(u16 * nn);

	//8 bit ALU
	inline void add_a_n(u8 n);
	inline void add_a_addr();
	inline void add_a_imm();
	inline void adc_a_n(u8 n);
	inline void adc_a_addr();
	inline void adc_a_imm();
	inline void sub_a_n(u8 n);
	inline void sub_a_addr();
	inline void sub_a_imm();
	inline void sbc_a_n(u8 n);
	inline void sbc_a_addr();
	inline void sbc_a_imm();
	inline void and_n(u8 n);
	inline void and_addr();
	inline void and_imm();
	inline void or_n(u8 n);
	inline void or_addr();
	inline void or_imm();
	inline void xor_n(u8 n);
	inline void xor_addr();
	inline void xor_imm();
	inline void cp_n(u8 n);
	inline void cp_addr();
	inline void cp_imm( );
	inline void inc_n(u8 * n);
	inline void inc_addr();
	inline void dec_n(u8 * n);
	inline void dec_addr();

	//16 bit arithmetic
	inline void add_hl_n(u16 n);
	inline void add_sp_n(u16 n);
	inline void inc_nn(u16 * nn);
	inline void dec_nn(u16 * nn);

	//misc
	inline void swap_n(u8 * n);
	inline void swap_addr();
	inline void daa();
	inline void cpl();
	inline void ccf();
	inline void scf();
	inline void nop();
	inline void halt();
	inline void stop();
	inline void di();
	inline void ei();

	//rotates and shifts
	inline void rlca();
	inline void rla();
	inline void rrca();
	inline void rra();
	inline void rlc_n(u8 * n);
	inline void rlc_addr();
	inline void rl_n(u8 * n);
	inline void rl_addr();
	inline void rrc_n(u8 * n);
	inline void rrc_addr();
	inline void rr_n(u8 * n);
	inline void rr_addr();
	inline void sla_n(u8 * n);
	inline void sla_addr();
	inline void sra_n(u8 * n);
	inline void sra_addr();
	inline void srl_n(u8 * n);
	inline void srl_addr();

	//bit opcodes
	inline void bit_b_r(u8 b, u8 * n);
	inline void set_b_r(u8 b, u8 * n);
	inline void res_b_r(u8 b, u8 * n);

	//jumps
	inline void jp_nn();
	inline void jp_cc_nn();
	inline void jp_hl();
	inline void jr_n();
	inline void jr_cc_n();

	//calls
	inline void call_nn();
	inline void call_cc_nn();

	//restarts
	inline void rst_n(u8 n);

	//returns
	inline void ret();
	inline void ret_cc();
	inline void reti();



	//flag ops
	inline void set_c_flag();
	inline void set_h_flag();
	inline void set_s_flag();
	inline void set_z_flag();
	
	inline void reset_c_flag();
	inline void reset_h_flag();
	inline void reset_s_flag();
	inline void reset_z_flag();

	bool test_c_flag();
	bool test_h_flag();
	bool test_s_flag();
	bool test_z_flag();
	

	//gets 2 byte word in little endian
	unsigned short read_word();


	// Complete horizontal line timing = 108.7 µsec
	// V-Blank = 1.09 msec
	// Mode 2 = 19.31 µsec (~20 machine cycles)
	// Mode 3 = Variable between 41.37 µsec - 70.69 µsec
	// Mode 0 = H-Blank = 108.7 µsec - 19.31 - Mode 3

	// Mode 0 minimum = 18.72 µsec (10 sprites on a line)
	// Mode 0 maximum = 48.64 µsec (no sprites on a line)

	//RAM bank

	/*

General Memory Map -- taken from pandocs
  0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
  4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
  8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
  A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
  C000-CFFF   4KB Work RAM Bank 0 (WRAM)
  D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
  E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
  FE00-FE9F   Sprite Attribute Table (OAM)
  FEA0-FEFF   Not Usable
  FF00-FF7F   I/O Ports
  FF80-FFFE   High RAM (HRAM)
  FFFF        Interrupt Enable Register
	*/

	//RAM is a terrible naming choice for the memory map, but oh well
	unsigned char RAM[0xFFFF];
	u8 op;

	bool debug;

	//flags
	bool z_flag;//zero 
	bool n_flag;//subtract
	bool h_flag;//half carry
	bool c_flag;//carry

	bool ei_flag;//enable interrupts
	bool halt_flag;
	bool stop_flag;

	unsigned short stack_pointer;
	unsigned short program_counter;
	unsigned long clocks;

	//registers - same method as Cinoop, credit given to cturt
	struct regs{

		struct {
			union {
				struct {
					unsigned char f;
					unsigned char a;
				};
				unsigned short af;
			};
		};
		
		struct {
			union {
				struct {
					unsigned char c;
					unsigned char b;
				};
				unsigned short bc;
			};
		};
		
		struct {
			union {
				struct {
					unsigned char e;
					unsigned char d;
				};
				unsigned short de;
			};
		};
		
		struct {
			union {
				struct {
					unsigned char l;
					unsigned char h;
				};
				unsigned short hl;
			};
		};
	};
		
		
		
	};//end class