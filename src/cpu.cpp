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

void GB_CPU::execute_opcode(u8 op){
	switch (op){

		case 0x00:{//nop
			nop();
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x01:{//ld bc, d16
			ld_nn_n(&bc, RAM[program_counter + 1]);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x02:{//ld (bc), a
		} break;
		case 0x03:{//inc bc
		} break;
		case 0x04:{//inc b
		} break;
		case 0x05:{//dec b
		} break;
		case 0x06:{//ld b, d8
		} break;
		case 0x07:{//rlca
		} break;
		case 0x08:{
		} break;
		case 0x09:{
		} break;
		case 0x0a:{
		} break;
		case 0x0b:{
		} break;
		case 0x0c:{
		} break;
		case 0x0d:{
		} break;
		case 0x0e:{
		} break;
		case 0x0f:{
		} break;
		case 0x10:{
		} break;
		case 0x11:{
		} break;
		case 0x12:{
		} break;
		case 0x13:{
		} break;
		case 0x14:{
		} break;
		case 0x15:{
		} break;
		case 0x16:{
		} break;
		case 0x17:{
		} break;
		case 0x18:{
		} break;
		case 0x19:{
		} break;
		case 0x1a:{
		} break;
		case 0x1b:{
		} break;
		case 0x1c:{
		} break;
		case 0x1d:{
		} break;
		case 0x1e:{
		} break;
		case 0x1f:{
		} break;
		case 0x20:{
		} break;
		case 0x21:{
		} break;
		case 0x22:{
		} break;
		case 0x23:{
		} break;
		case 0x24:{
		} break;
		case 0x25:{
		} break;
		case 0x26:{
		} break;
		case 0x27:{
		} break;
		case 0x28:{
		} break;
		case 0x29:{
		} break;
		case 0x30:{
		} break;
		case 0x3a:{
		} break;
		case 0x3b:{
		} break;
		case 0x3c:{
		} break;
		case 0x3d:{
		} break;
		case 0x3e:{
		} break;
		case 0x3f:{
		} break;
		case 0x40:{
		} break;
		case 0x41:{
		} break;
		case 0x42:{
		} break;
		case 0x43:{
		} break;
		case 0x44:{
		} break;
		case 0x45:{
		} break;
		case 0x46:{
		} break;
		case 0x47:{
		} break;
		case 0x48:{
		} break;
		case 0x49:{
		} break;
		case 0x4a:{
		} break;
		case 0x4b:{
		} break;
		case 0x4c:{
		} break;
		case 0x4d:{
		} break;
		case 0x4e:{
		} break;
		case 0x4f:{
		} break;
		case 0x50:{
		} break;
		case 0x51:{
		} break;
		case 0x52:{
		} break;
		case 0x53:{
		} break;
		case 0x54:{
		} break;
		case 0x55:{
		} break;
		case 0x56:{
		} break;
		case 0x57:{
		} break;
		case 0x58:{
		} break;
		case 0x59:{
		} break;
		case 0x5a:{
		} break;
		case 0x5b:{
		} break;
		case 0x5c:{
		} break;
		case 0x5d:{
		} break;
		case 0x5e:{
		} break;
		case 0x5f:{
		} break;
		case 0x60:{
		} break;
		case 0x61:{
		} break;
		case 0x62:{
		} break;
		case 0x63:{
		} break;
		case 0x64:{
		} break;
		case 0x65:{
		} break;
		case 0x66:{
		} break;
		case 0x67:{
		} break;
		case 0x68:{
		} break;
		case 0x69:{
		} break;
		case 0x6a:{
		} break;
		case 0x6b:{
		} break;
		case 0x6c:{
		} break;
		case 0x6d:{
		} break;
		case 0x6e:{
		} break;
		case 0x6f:{
		} break;
		case 0x70:{
		} break;
		case 0x71:{
		} break;
		case 0x72:{
		} break;
		case 0x73:{
		} break;
		case 0x74:{
		} break;
		case 0x75:{
		} break;
		case 0x76:{
		} break;
		case 0x77:{
		} break;
		case 0x78:{
		} break;
		case 0x79:{
		} break;
		case 0x7a:{
		} break;
		case 0x7b:{
		} break;
		case 0x7c:{
		} break;
		case 0x7d:{
		} break;
		case 0x7e:{
		} break;
		case 0x7f:{
		} break;
		case 0x80:{
		} break;
		case 0x81:{
		} break;
		case 0x82:{
		} break;
		case 0x83:{
		} break;
		case 0x84:{
		} break;
		case 0x85:{
		} break;
		case 0x86:{
		} break;
		case 0x87:{
		} break;
		case 0x88:{
		} break;
		case 0x89:{
		} break;
		case 0x8a:{
		} break;
		case 0x8b:{
		} break;
		case 0x8c:{
		} break;
		case 0x8d:{
		} break;
		case 0x8e:{
		} break;
		case 0x8f:{
		} break;
		case 0x90:{
		} break;
		case 0x91:{
		} break;
		case 0x92:{
		} break;
		case 0x93:{
		} break;
		case 0x94:{
		} break;
		case 0x95:{
		} break;
		case 0x96:{
		} break;
		case 0x97:{
		} break;
		case 0x98:{
		} break;
		case 0x99:{
		} break;
		case 0x9a:{
		} break;
		case 0x9b:{
		} break;
		case 0x9c:{
		} break;
		case 0x9d:{
		} break;
		case 0x9e:{
		} break;
		case 0x9f:{
		} break;
		case 0xa0:{
		} break;
		case 0xa1:{
		} break;
		case 0xa2:{
		} break;
		case 0xa3:{
		} break;
		case 0xa4:{
		} break;
		case 0xa5:{
		} break;
		case 0xa6:{
		} break;
		case 0xa7:{
		} break;
		case 0xa8:{
		} break;
		case 0xa9:{
		} break;
		case 0xaa:{
		} break;
		case 0xab:{
		} break;
		case 0xac:{
		} break;
		case 0xae:{
		} break;
		case 0xaf:{
		} break;
		case 0xb0:{
		} break;
		case 0xb1:{
		} break;
		case 0xb2:{
		} break;
		case 0xb3:{
		} break;
		case 0xb4:{
		} break;
		case 0xb5:{
		} break;
		case 0xb6:{
		} break;
		case 0xb7:{
		} break;
		case 0xb8:{
		} break;
		case 0xb9:{
		} break;
		case 0xba:{
		} break;
		case 0xbb:{
		} break;
		case 0xbc:{
		} break;
		case 0xbd:{
		} break;
		case 0xbe:{
		} break;
		case 0xbf:{
		} break;
		case 0xc0:{
		} break;
		case 0xc1:{
		} break;
		case 0xc2:{
		} break;
		case 0xc3:{
		} break;
		case 0xc4:{
		} break;
		case 0xc5:{
		} break;
		case 0xc6:{
		} break;
		case 0xc7:{
		} break;
		case 0xc8:{
		} break;
		case 0xc9:{
		} break;
		case 0xca:{
		} break;
		//cb leads to more opcodes, see nested switch toward end
		case 0xcc:{
		} break;
		case 0xcd:{
		} break;
		case 0xce:{
		} break;
		case 0xcf:{
		} break;
		case 0xd0:{
		} break;
		case 0xd1:{
		} break;
		case 0xd2:{
		} break;
		case 0xd3:{
		} break;
		case 0xd4:{
		} break;
		case 0xd5:{
		} break;
		case 0xd6:{
		} break;
		case 0xd7:{
		} break;
		case 0xd8:{
		} break;
		case 0xd9:{
		} break;
		case 0xda:{
		} break;
		case 0xdb:{
		} break;
		case 0xdc:{
		} break;
		case 0xdd:{
		} break;
		case 0xde:{
		} break;
		case 0xdf:{
		} break;
		case 0xe0:{
		} break;
		case 0xe1:{
		} break;
		case 0xe2:{
		} break;
		case 0xe3:{
		} break;
		case 0xe4:{
		} break;
		case 0xe5:{
		} break;
		case 0xe6:{
		} break;
		case 0xe7:{
		} break;
		case 0xe8:{
		} break;
		case 0xe9:{
		} break;
		case 0xea:{
		} break;
		case 0xeb:{
		} break;
		case 0xec:{
		} break;
		case 0xed:{
		} break;
		case 0xee:{
		} break;
		case 0xef:{
		} break;
		case 0xf0:{
		} break;
		case 0xf1:{
		} break;
		case 0xf2:{
		} break;
		case 0xf3:{
		} break;
		case 0xf4:{
		} break;
		case 0xf5:{
		} break;
		case 0xf6:{
		} break;
		case 0xf7:{
		} break;
		case 0xf8:{
		} break;
		case 0xf9:{
		} break;
		case 0xfa:{
		} break;
		case 0xfb:{
		} break;
		case 0xfc:{
		} break;
		case 0xfd:{
		} break;
		case 0xfe:{
		} break;
		case 0xff:{
		} break;

		case 0xcb:{
			program_counter += 1;
			u8 op2 = RAM[program_counter];
			switch(op2){
						case 0x00:{//nop
						} break;
						case 0x01:{//ld bc, d16
						} break;
						case 0x02:{//ld (bc), a
						} break;
						case 0x03:{//inc bc
						} break;
						case 0x04:{//inc b
						} break;
						case 0x05:{//dec b
						} break;
						case 0x06:{//ld b, d8
						} break;
						case 0x07:{//rlca
						} break;
						case 0x08:{
						} break;
						case 0x09:{
						} break;
						case 0x0a:{
						} break;
						case 0x0b:{
						} break;
						case 0x0c:{
						} break;
						case 0x0d:{
						} break;
						case 0x0e:{
						} break;
						case 0x0f:{
						} break;
						case 0x10:{
						} break;
						case 0x11:{
						} break;
						case 0x12:{
						} break;
						case 0x13:{
						} break;
						case 0x14:{
						} break;
						case 0x15:{
						} break;
						case 0x16:{
						} break;
						case 0x17:{
						} break;
						case 0x18:{
						} break;
						case 0x19:{
						} break;
						case 0x1a:{
						} break;
						case 0x1b:{
						} break;
						case 0x1c:{
						} break;
						case 0x1d:{
						} break;
						case 0x1e:{
						} break;
						case 0x1f:{
						} break;
						case 0x20:{
						} break;
						case 0x21:{
						} break;
						case 0x22:{
						} break;
						case 0x23:{
						} break;
						case 0x24:{
						} break;
						case 0x25:{
						} break;
						case 0x26:{
						} break;
						case 0x27:{
						} break;
						case 0x28:{
						} break;
						case 0x29:{
						} break;
						case 0x30:{
						} break;
						case 0x3a:{
						} break;
						case 0x3b:{
						} break;
						case 0x3c:{
						} break;
						case 0x3d:{
						} break;
						case 0x3e:{
						} break;
						case 0x3f:{
						} break;
						case 0x40:{
						} break;
						case 0x41:{
						} break;
						case 0x42:{
						} break;
						case 0x43:{
						} break;
						case 0x44:{
						} break;
						case 0x45:{
						} break;
						case 0x46:{
						} break;
						case 0x47:{
						} break;
						case 0x48:{
						} break;
						case 0x49:{
						} break;
						case 0x4a:{
						} break;
						case 0x4b:{
						} break;
						case 0x4c:{
						} break;
						case 0x4d:{
						} break;
						case 0x4e:{
						} break;
						case 0x4f:{
						} break;
						case 0x50:{
						} break;
						case 0x51:{
						} break;
						case 0x52:{
						} break;
						case 0x53:{
						} break;
						case 0x54:{
						} break;
						case 0x55:{
						} break;
						case 0x56:{
						} break;
						case 0x57:{
						} break;
						case 0x58:{
						} break;
						case 0x59:{
						} break;
						case 0x5a:{
						} break;
						case 0x5b:{
						} break;
						case 0x5c:{
						} break;
						case 0x5d:{
						} break;
						case 0x5e:{
						} break;
						case 0x5f:{
						} break;
						case 0x60:{
						} break;
						case 0x61:{
						} break;
						case 0x62:{
						} break;
						case 0x63:{
						} break;
						case 0x64:{
						} break;
						case 0x65:{
						} break;
						case 0x66:{
						} break;
						case 0x67:{
						} break;
						case 0x68:{
						} break;
						case 0x69:{
						} break;
						case 0x6a:{
						} break;
						case 0x6b:{
						} break;
						case 0x6c:{
						} break;
						case 0x6d:{
						} break;
						case 0x6e:{
						} break;
						case 0x6f:{
						} break;
						case 0x70:{
						} break;
						case 0x71:{
						} break;
						case 0x72:{
						} break;
						case 0x73:{
						} break;
						case 0x74:{
						} break;
						case 0x75:{
						} break;
						case 0x76:{
						} break;
						case 0x77:{
						} break;
						case 0x78:{
						} break;
						case 0x79:{
						} break;
						case 0x7a:{
						} break;
						case 0x7b:{
						} break;
						case 0x7c:{
						} break;
						case 0x7d:{
						} break;
						case 0x7e:{
						} break;
						case 0x7f:{
						} break;
						case 0x80:{
						} break;
						case 0x81:{
						} break;
						case 0x82:{
						} break;
						case 0x83:{
						} break;
						case 0x84:{
						} break;
						case 0x85:{
						} break;
						case 0x86:{
						} break;
						case 0x87:{
						} break;
						case 0x88:{
						} break;
						case 0x89:{
						} break;
						case 0x8a:{
						} break;
						case 0x8b:{
						} break;
						case 0x8c:{
						} break;
						case 0x8d:{
						} break;
						case 0x8e:{
						} break;
						case 0x8f:{
						} break;
						case 0x90:{
						} break;
						case 0x91:{
						} break;
						case 0x92:{
						} break;
						case 0x93:{
						} break;
						case 0x94:{
						} break;
						case 0x95:{
						} break;
						case 0x96:{
						} break;
						case 0x97:{
						} break;
						case 0x98:{
						} break;
						case 0x99:{
						} break;
						case 0x9a:{
						} break;
						case 0x9b:{
						} break;
						case 0x9c:{
						} break;
						case 0x9d:{
						} break;
						case 0x9e:{
						} break;
						case 0x9f:{
						} break;
						case 0xa0:{
						} break;
						case 0xa1:{
						} break;
						case 0xa2:{
						} break;
						case 0xa3:{
						} break;
						case 0xa4:{
						} break;
						case 0xa5:{
						} break;
						case 0xa6:{
						} break;
						case 0xa7:{
						} break;
						case 0xa8:{
						} break;
						case 0xa9:{
						} break;
						case 0xaa:{
						} break;
						case 0xab:{
						} break;
						case 0xac:{
						} break;
						case 0xae:{
						} break;
						case 0xaf:{
						} break;
						case 0xb0:{
						} break;
						case 0xb1:{
						} break;
						case 0xb2:{
						} break;
						case 0xb3:{
						} break;
						case 0xb4:{
						} break;
						case 0xb5:{
						} break;
						case 0xb6:{
						} break;
						case 0xb7:{
						} break;
						case 0xb8:{
						} break;
						case 0xb9:{
						} break;
						case 0xba:{
						} break;
						case 0xbb:{
						} break;
						case 0xbc:{
						} break;
						case 0xbd:{
						} break;
						case 0xbe:{
						} break;
						case 0xbf:{
						} break;
						case 0xc0:{
						} break;
						case 0xc1:{
						} break;
						case 0xc2:{
						} break;
						case 0xc3:{
						} break;
						case 0xc4:{
						} break;
						case 0xc5:{
						} break;
						case 0xc6:{
						} break;
						case 0xc7:{
						} break;
						case 0xc8:{
						} break;
						case 0xc9:{
						} break;
						case 0xca:{
						} break;
						//cb leads to more opcodes, see nested switch toward end
						case 0xcc:{
						} break;
						case 0xcd:{
						} break;
						case 0xce:{
						} break;
						case 0xcf:{
						} break;
						case 0xd0:{
						} break;
						case 0xd1:{
						} break;
						case 0xd2:{
						} break;
						case 0xd3:{
						} break;
						case 0xd4:{
						} break;
						case 0xd5:{
						} break;
						case 0xd6:{
						} break;
						case 0xd7:{
						} break;
						case 0xd8:{
						} break;
						case 0xd9:{
						} break;
						case 0xda:{
						} break;
						case 0xdb:{
						} break;
						case 0xdc:{
						} break;
						case 0xdd:{
						} break;
						case 0xde:{
						} break;
						case 0xdf:{
						} break;
						case 0xe0:{
						} break;
						case 0xe1:{
						} break;
						case 0xe2:{
						} break;
						case 0xe3:{
						} break;
						case 0xe4:{
						} break;
						case 0xe5:{
						} break;
						case 0xe6:{
						} break;
						case 0xe7:{
						} break;
						case 0xe8:{
						} break;
						case 0xe9:{
						} break;
						case 0xea:{
						} break;
						case 0xeb:{
						} break;
						case 0xec:{
						} break;
						case 0xed:{
						} break;
						case 0xee:{
						} break;
						case 0xef:{
						} break;
						case 0xf0:{
						} break;
						case 0xf1:{
						} break;
						case 0xf2:{
						} break;
						case 0xf3:{
						} break;
						case 0xf4:{
						} break;
						case 0xf5:{
						} break;
						case 0xf6:{
						} break;
						case 0xf7:{
						} break;
						case 0xf8:{
						} break;
						case 0xf9:{
						} break;
						case 0xfa:{
						} break;
						case 0xfb:{
						} break;
						case 0xfc:{
						} break;
						case 0xfd:{
						} break;
						case 0xfe:{
						} break;
						case 0xff:{
						} break;

			}
		} break;
//use this commented code for functions, then  delete
			// case 0x0:{ //NOP
			// 	++program_counter;
			// 	break;
			// }

			// case 0xc3:{ //jmp too NNNN
			// 	program_counter = read_word();
			// 	break;
			// }

			// case 0xaf:{//XOR A with A, result in a
			// 	//this effectively zeros out a
			// 	a = 0;
			// 	//deal with flags
			// 	//if result is zero, set z_flag
			// 	z_flag = true;
			// 	c_flag = false;
			// 	n_flag = false;
			// 	h_flag = false;
				
			// 	program_counter++;
			// 	break;
			// }

			// case 0x21:{
			// 	//LD HL
			// 	hl = read_word();
			// 	program_counter += 3;
			// 	break;
			// }

			// case 0x0e:{
			// 	//LD C
			// 	c = RAM[program_counter + 1];
			// 	program_counter += 2;
			// 	break;
			// }

			// case 0x06:{
			// 	//LD B
			// 	b = RAM[program_counter + 1];
			// 	program_counter += 2;
			// 	break;
			// }

			// case 0x32:{
			// 	// LD HL- A
			// 	// LD (HLD),A     - Put A into memory address HL. Decrement HL.
			// 	RAM[hl] = a;
			// 	--hl;
			// 	program_counter += 1;				
			// 	break;
			// }

			// case 0x05:{
			// 	// DEC B - Decrement register B
			// 	--b;
			// 	++program_counter;
			// 	if(b == 0) z_flag = true;
			// 	n_flag = true;
			// 	//TODO: settle H flag
			// 	break;
			// }

			// case 0x20:{
			// 	//JR NZ, r8
			// 	//jump of Z flag is reset
			// 	if(!z_flag){
			// 		int offset = static_cast<int>(RAM[program_counter + 1]);
			// 		program_counter += offset;
			// 		break;
			// 	}
			// 	program_counter += 2;
			// 	break;
			// }

			// case 0x0d:{
			// 	//DEC c
			// 	--c;
			// 	if(c == 0) z_flag = true;
			// 	n_flag = true;
			// 	//TODO: settle h flag
			// 	++program_counter;
			// 	break;
			// }

			// case 0x3e:{
			// 	//load immediate value to a
			// 	a = RAM[program_counter +1];
			// 	program_counter += 2;
			// 	break;
			// }

			// case 0xf3:{
			// 	//LD A,(C)       - Put value at address $FF00 + register C into A.
			// 	a = RAM[0xFF00 + c];
			// 	program_counter += 2;
			// 	break;
			// }

			// case 0x0f:{
			// 	// RRC A          - Rotate A right. Old bit 0 to Carry flag.
			// 	if (a%2) c_flag = true;
			// 	else c_flag = false;
			// 	a >>= 1;
			// 	if(!a) z_flag = true;
			// 	n_flag = false;
			// 	h_flag = false;
			// 	program_counter += 1;				
			// 	break;
			// }



			default:{
				std::cout << "Unrecognized opcode: 0x" << std::hex << op 
				<< "\n at address: 0x" << std::hex << program_counter << std::endl;
				
				exit(1);
			}



	}//end switch
}//end execute opcode

	//opcode helper functions////////////////////////////////

	//8 bit loads
inline void GB_CPU::ld_nn_n(u16 * nn, u8 n){
	*nn = n;//n = 8 bit immediate value
}

inline void GB_CPU::ld_r1_r2(u8 * r1, u8 * r2){
	*r1 = *r2;
}

inline void GB_CPU::ld_a_n(u16 * n){
	a = *n;
}

inline void GB_CPU::ld_n_a(u16 * n){
	*n = a;
}

inline void GB_CPU::ld_a_c(){
	a = RAM[0xFF00 + c];
}

inline void GB_CPU::ld_c_a(){
	RAM[0xFF00 + c] = a;
}

inline void GB_CPU::ldd_a_hl(){
	a = RAM[hl];
	--hl;
}

inline void GB_CPU::ldd_hl_a(){
	RAM[hl] = a;
	--hl;
}

inline void GB_CPU::ldi_a_hl(){
	a = RAM[hl];
	++hl;
}

inline void GB_CPU::ldi_hl_a(){
	RAM[hl] = a;
	++hl;
}

inline void GB_CPU::ldh_n_a(u16 n){
	RAM[n] = a;
}
inline void GB_CPU::ldh_a_n(u16 n){
	a = RAM[n];
}

	//16 bit loads
inline void GB_CPU::ld_n_nn(u16 * n){
	program_counter +=2;
	*n = read_word();
}

inline void GB_CPU::ld_sp_hl(){
	stack_pointer = hl;
}

inline void GB_CPU::ld_hl_sp_n(int n){
	hl = stack_pointer + static_cast<u16>(RAM[program_counter +1]);
}

inline void GB_CPU::ld_nn_sp(int nn){
	RAM[read_word()] = stack_pointer; 
}
inline void GB_CPU::push_nn(u16 nn){
	RAM[stack_pointer] = nn;
	----stack_pointer; 
}
inline void GB_CPU::pop_nn(u16 nn){
	nn = RAM[stack_pointer];
	++++stack_pointer;
}
	//8 bit ALU
inline void GB_CPU::add_a_n(u8 n){
	//check for carry in bit 3

	//check for carry in bit 7

	a += n;
	if (a == 0) z_flag = true;
	else n_flag = false;
}

inline void GB_CPU::adc_a_n(u8 n){

}
inline void GB_CPU::sub_a_n(u8 n){
	a = ~a;
	a += n;
	if (a == 0) z_flag = true;
	else n_flag = false;
}
inline void GB_CPU::sbc_a_n(u8 n){
	a = ~a;
	a += n;
	if (a == 0) z_flag = true;
	else n_flag = false;
}
inline void GB_CPU::and_n(u8 n){
	a &= n;
	if (a == 0) z_flag = true;
	else n_flag = false;
	h_flag = true;
	n_flag = false;
	c_flag = false;

}
inline void GB_CPU::or_n(u8 n){
	a |= n;
	if (a == 0) z_flag = true;
	else n_flag = false;
	h_flag = false;
	n_flag = false;
	c_flag = false;

}
inline void GB_CPU::xor_n(u8 n){
	a ^= n;
	if (a == 0) z_flag = true;
	else n_flag = false;
	h_flag = false;
	n_flag = false;
	c_flag = false;

}
inline void GB_CPU::cp_n(u8 n){
	if(a == n) z_flag = true;
	n_flag = true;
	// figure out h_flag
	if(a < n) c_flag = true;
}
inline void GB_CPU::inc_n(u8 * n){
	++(*n);
	if(*n == 0) z_flag = true;
	n_flag = false;
	//figure out h flag
	//c flag not affected
}
inline void GB_CPU::dec_n(u8 * n){
	--(*n);
	if(*n == 0) z_flag = true;
	n_flag = true;
	//figure out h flag
	//c flag not affected
}
	//16 bit arithmetic
inline void GB_CPU::add_hl_n(u16  n){
	hl += n;
	//z flag not affected
	n_flag = false;
	//figure out h and c flags
}
inline void GB_CPU::add_sp_n(u16 n){
	stack_pointer += RAM[program_counter + 1];
	z_flag = false;
	n_flag = false;
	//figure out h and c flags
}
inline void GB_CPU::inc_nn(u16 * nn){
	++(*nn);
}
inline void GB_CPU::dec_nn(u16 * nn){
	--(*nn);
}
	//misc
inline void GB_CPU::swap_n(u8 * n){
	u8 temp = *n;
	temp << 4;
	*n >> 4;
	*n += temp;
	if(*n == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
	c_flag = false;
}
inline void GB_CPU::daa(){
	//TODO: need to do homework here
}
inline void GB_CPU::cpl(){
	a = ~a;
	//z flag not affected
	n_flag = true;
	h_flag = true;
	//c flag not affected
}
inline void GB_CPU::ccf(){
	if(c_flag) c_flag = false;
	else c_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::scf(){
	c_flag = true;
	n_flag = false;
	h_flag = false;

}
inline void GB_CPU::nop(){
	//move along, nothing to see here...
}
inline void GB_CPU::halt(){
	//TODO: wait for interrupt
}
inline void GB_CPU::stop(){
	//TODO: wait for button press
}
inline void GB_CPU::di(){
	//TODO: disable interrupts
}
inline void GB_CPU::ei(){
	//TODO: enable interrupts
}
	//rotates and shifts

	//TODO: rotates are probably buggy af, double check these
inline void GB_CPU::rlca(){
	if(a > 128) c_flag = true;
	else c_flag = false;
	a << 1;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::rla(){
	//TODO: see how is different from previous instruction
	if(a > 128) c_flag = true;
	else c_flag = false;
	a << 1;
	if(a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::rrcs(){
	if(a%2) c_flag = true;
	else c_flag = false;
	a >> 1;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;

}
inline void GB_CPU::rra(){
	//TODO: see how this is different from previous
	if(a%2) c_flag = true;
	else c_flag = false;
	a >> 1;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;

}
inline void GB_CPU::rlc_n(u8 n){}
inline void GB_CPU::rl_n(u8 n){}
inline void GB_CPU::rrc_n(u8 n){}
inline void GB_CPU::rr_n(u8 n){}
inline void GB_CPU::sla_n(u8 n){}
inline void GB_CPU::sra_n(u8 n){}
inline void GB_CPU::srl_n(u8 n){}
	//bit opcodes
inline void GB_CPU::bit_b_r(){}
inline void GB_CPU::set_b_r(){}
inline void GB_CPU::res_b_r(){}
	//jumps
inline void GB_CPU::jp_nn(u16 nn){}
inline void GB_CPU::jp_cc_nn(bool cc, u16 nn){}
inline void GB_CPU::jp_hl(){}
inline void GB_CPU::jr_n(u8 n){}
inline void GB_CPU::jr_cc_n(bool cc, u8 n){}

	//calls
inline void call_nn(u16 nn){}
inline void call_cc_nn(bool cc, u16 nn){}
	//restarts
inline void rst_n(u8 n){}
	//returns
inline void ret(){}
inline void ret_cc(bool cc){}
inline void reti(){}
