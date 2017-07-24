#include <iostream>
#include <cstdlib> 
#include "cpu.h"

void GB_CPU::reset(){
		

		af = 0x01B0;
		bc = 0x0013;
		de = 0x00D8;
		hl = 0x014D;
		stack_pointer = 0xFFFE;
		program_counter = 0x100;

		RAM[0xFF05] = 0x00; //TIMA
		RAM[0xFF06] = 0x00; //TMA
		RAM[0xFF07] = 0x00; //TAC
		RAM[0xFF10] = 0x80; //NR10
		RAM[0xFF11] = 0xBF; //NR11
		RAM[0xFF12] = 0xF3; //NR12
		RAM[0xFF14] = 0xBF; //NR14
		RAM[0xFF16] = 0x3F; //NR16
		RAM[0xFF17] = 0x00; //NR17
		RAM[0xFF19] = 0xBF; //NR24
		RAM[0xFF1A] = 0x7F; //NR30
		RAM[0xFF1B] = 0xFF; //NR31
		RAM[0xFF1C] = 0x9F; //NR32
		RAM[0xFF1E] = 0xBF; //NR33
		RAM[0xFF20] = 0xFF; //NR41
		RAM[0xFF21] = 0x00; //NR42
		RAM[0xFF22] = 0x00; //NR43
		RAM[0xFF23] = 0xBF; //NR30
		RAM[0xFF24] = 0x77; //NR50
		RAM[0xFF25] = 0xF3; //NR51

		RAM[0xFF26] = 0x80; //NR43// fix this

		RAM[0xFF40] = 0x91; //LCDC
		RAM[0xFF42] = 0x00; //SCY
		RAM[0xFF43] = 0x00; //SCX
		RAM[0xFF45] = 0x00; //LYC
		RAM[0xFF47] = 0xFC; //BGP
		RAM[0xFF48] = 0xFF; //OBP0
		RAM[0xFF49] = 0xFF; //OBP1
		RAM[0xFF4A] = 0x00; //WY
		RAM[0xFF4B] = 0x00; //WX
		RAM[0xFFFF] = 0x00; //IE
		


}


unsigned short GB_CPU::read_word(){
	//get high part
	unsigned short target  = RAM[program_counter + 2];
	target <<= 8; //shift to the high byte
	//get low part
	target += RAM[program_counter + 1];
	//GO!
	return target;
}

void GB_CPU::execute_opcode(unsigned int op){
	switch (op){

			case 0x0:{ //NOP
				++program_counter;
				break;
			}

			case 0xc3:{ //jmp too NNNN
				program_counter = read_word();
				break;
			}

			case 0xaf:{//XOR A with A, result in a
				//this effectively zeros out a
				a = 0;
				//deal with flags
				//if result is zero, set z_flag
				z_flag = true;
				c_flag = false;
				n_flag = false;
				h_flag = false;
				
				program_counter++;
				break;
			}

			case 0x21:{
				//LD HL
				hl = read_word();
				program_counter += 3;
				break;
			}

			case 0x0e:{
				//LD C
				c = RAM[program_counter + 1];
				program_counter += 2;
				break;
			}

			case 0x06:{
				//LD B
				b = RAM[program_counter + 1];
				program_counter += 2;
				break;
			}

			case 0x32:{
				// LD HL- A
				// LD (HLD),A     - Put A into memory address HL. Decrement HL.
				RAM[hl] = a;
				--hl;
				program_counter += 1;				
				break;
			}

			case 0x05:{
				// DEC B - Decrement register B
				--b;
				++program_counter;
				if(b == 0) z_flag = true;
				n_flag = true;
				//TODO: settle H flag
				break;
			}

			case 0x20:{
				//JR NZ, r8
				//jump of Z flag is reset
				if(!z_flag){
					int offset = static_cast<int>(RAM[program_counter + 1]);
					program_counter += offset;
					break;
				}
				program_counter += 2;
				break;
			}

			case 0x0d:{
				//DEC c
				--c;
				if(c == 0) z_flag = true;
				n_flag = true;
				//TODO: settle h flag
				++program_counter;
				break;
			}

			case 0x3e:{
				//load immediate value to a
				a = RAM[program_counter +1];
				program_counter += 2;
				break;
			}

			case 0xf3:{
				//LD A,(C)       - Put value at address $FF00 + register C into A.
				a = RAM[0xFF00 + c];
				program_counter += 2;
				break;
			}

			case 0x0f:{
				
				break;
			}



			default:{
				std::cout << "Unrecognized opcode: 0x" << std::hex << op 
				<< "\n at address: 0x" << std::hex << program_counter << std::endl;
				
				exit(1);
			}



	}//end switch
}//end execute opcode