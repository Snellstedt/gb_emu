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
	GB_CPU(const std::string & ROM_file){


		//set RAM to zero
		memset(RAM, 0, 0xFFFF);

		//set registers, stack pointer and program counter to zero
		a = f = c = b = e = d = l = h = program_counter = stack_pointer = 0;
		z_flag = n_flag = h_flag = c_flag = false;

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
		//delay to keep clock in sync

		//check interrupts

		//fetch
		u8 op = RAM[program_counter];
		//decode
		execute_opcode(op);
		//execute
		// program_counter += 1;
	}

	



	

private:

	//execute opcode
	void execute_opcode(u8 op);

	//opcode helper functions////////////////////////////////

	//8 bit loads
	void ld_nn_n(u16 nn, u8 n);
	void ld_r1_r2(u8 r1, u8 r2);
	void ld_a_n(u16 n);
	void ld_a_c();
	void ld_c_a();
	void ldd_a_hl();
	void ldd_hl_a();
	void ldi_a_hl();
	void ldi_hl_a();
	void ldh_n_a();
	void ldh_a_n();

	//16 bit loads
	void ld_n_nn(u8 n);
	void ld_sp_hl();
	void ld_hl_sp_n(int n);
	void ld_nn_sp(int nn);
	void push_nn(u16 nn);
	void pop_nn(u16 nn);

	//8 bit ALU
	void add_a_n(u8 n);
	void adc_a_n(u8 n);
	void sub_a_n(u8 n);
	void sbc_a_n(u8 n);
	void and_n(u8 n);
	void or_n(u8 n);
	void xor_n(u8 n);
	void cp_n(u8 n);
	void inc_n(u8 n);
	void dec_n(u8 n);

	//16 bit arithmetic
	void add_hl_n(u16 n);
	void add_sp_n(u16 n);
	void inc_nn(u16 nn);
	void dec_nn(u16 nn);

	//misc
	void swap_n(u8 n);
	void daa();
	void cpl();
	void ccf();
	void scf();
	void nop();
	void halt();
	void stop();
	void di();
	void ei();

	//rotates and shifts
	void rlca();
	void rla();
	void rrcs();
	void rra();
	void rlc_n(u8 n);
	void rl_n(u8 n);
	void rrc_n(u8 n);
	void rr_n(u8 n);
	void sla_n(u8 n);
	void sra_n(u8 n);
	void srl_n(u8 n);

	//bit opcodes
	void bit_b_r();
	void set_b_r();
	void res_b_r();

	//jumps
	void jp_nn(u16 nn);
	void jp_cc_nn(bool cc, u16 nn);
	void jp_hl();
	void jr_n(u8 n);
	void jr_cc_n(bool cc, u8 n);

	//calls
	void call_nn(u16 nn);
	void call_cc_nn(bool cc, u16 nn);

	//restarts
	void rst_n(u8 n);

	//returns
	void ret();
	void ret_cc(bool cc);
	void reti();





















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
	unsigned char RAM[0xFFFF];

	//flags
	bool z_flag;//zero 
	bool n_flag;//subtract
	bool h_flag;//half carry
	bool c_flag;//carry

	unsigned int stack_pointer;
	unsigned int program_counter;

	//registers - same method as Cinoop, credit given to cturt
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
	


};//end class