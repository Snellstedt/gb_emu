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
			ld_n_nn(&bc);
			clocks += 12;
			program_counter +=2;
		} break;

		case 0x02:{//ld (bc), a
			ld_nn_n(RAM + bc);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x03:{//inc bc
			inc_nn(&bc);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x04:{//inc b
			inc_n(&b);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x05:{//dec b
			dec_n(&b);
			program_counter +=1;
			clocks += 8;
		} break;

		case 0x06:{//ld b, d8
			ld_nn_n(&b);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x07:{//rlca
			rlca();
			program_counter += 1;
			clocks +=4;
		} break;

		case 0x08:{//ld (a16), sp
			ld_nn_sp(read_word());
			program_counter +=3;
			clocks +=20;
		} break;

		case 0x09:{//add hl,bc
			add_hl_n(bc);
			program_counter += 1;
			program_counter +=8;
		} break;

		case 0x0a:{//ld a, (bc)
			ld_a_n(RAM + bc);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x0b:{//dec bc
			dec_nn(&bc);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x0c:{//inc c
			inc_n(&c);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x0d:{//dec c
			dec_n(&c);
			program_counter += 1;
			clocks +=4;
		} break;

		case 0x0e:{ //ld c, d8
			ld_nn_n(&c);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x0f:{//rrca
			rrca();
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x10:{//stop
			stop();
			program_counter += 2;
			clocks += 4;
		} break;
	
		case 0x11:{//ld de,d16
			ld_n_nn(&de);
			program_counter += 3;
			clocks += 12;
		} break;

		case 0x12:{//ld (de), a
			ld_nn_n(RAM + de);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x13:{//inc de
			inc_nn(&de);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x14:{//inc d
			inc_n(&d);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x15:{//dec d
			dec_n(&d);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x16:{//ld d, d8
			ld_nn_n(&d);
			clocks += 8;
			program_counter +=2;
		} break;
	
		case 0x17:{//rla
			rla();
			program_counter +=1;
			clocks += 4;
		} break;

		case 0x18:{//jr r8
			jr_n();
			program_counter += 2;
			clocks += 12;
		} break;

		case 0x19:{//add hl,de
			add_hl_n(de);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x1a:{//ld a, (de)
			ld_a_n(RAM + de);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x1b:{//dec de
			dec_nn(&de);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x1c:{//inc e
			inc_n(&e);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x1d:{
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x1e:{//ld e,d8
			ld_nn_n(&e);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x1f:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x20:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x21:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x22:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x23:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x24:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x25:{
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x26:{//ld h, d8
			ld_nn_n(&h);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x27:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x28:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x29:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2a:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2b:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2c:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2d:{
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x2e:{//ld l, d8
			ld_nn_n(&l);
			clocks += 8;
			program_counter +=2;
		} break;
		
		case 0x2f:{//rra
			program_counter += 1;
			clocks += 8;
		} break;
		
		case 0x30:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3a:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3b:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3c:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3d:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3e:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3f:{
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x40:{//ld b,b
			ld_r1_r2(&b, &b);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x41:{//ld b,c
			ld_r1_r2(&b, &c);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x42:{//ld b,d
			ld_r1_r2(&b, &d);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x43:{//ld b,e
			ld_r1_r2(&b, &e);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x44:{//ld b,h
			ld_r1_r2(&b, &h);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x45:{//ld b,l
			ld_r1_r2(&b, &l);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x46:{//ld b, (hl)
			ld_r1_r2(&b, RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		
		case 0x47:{//ld b,a
			ld_r1_r2(&b, &a);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x48:{//ld c,b
			ld_r1_r2(&c,&b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x49:{//ld c,c
			ld_r1_r2(&c,&c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x4a:{//ld c,d 
			ld_r1_r2(&c,&d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x4b:{//ld c, e
			ld_r1_r2(&c,&e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x4c:{//ld c, h
			ld_r1_r2(&c,&h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x4d:{//ld c, l
			ld_r1_r2(&c,&l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x4e:{// ld c, (hl)
			ld_r1_r2(&c, RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x4f:{// ld c,a
			ld_r1_r2(&c, &a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x50:{//ld d,b
			ld_r1_r2(&d,&b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x51:{//ld d,c
			ld_r1_r2(&d,&c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x52:{//ld d,d
			ld_r1_r2(&d,&d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x53:{//ld d,e
			ld_r1_r2(&d,&e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x54:{//ld d,h
			ld_r1_r2(&d,&h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x55:{//ld d,l
			ld_r1_r2(&d,&l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x56:{//ld d, hl
			ld_r1_r2(&d,RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x57:{//ld d,a 
			ld_r1_r2(&d,&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x58:{//ld e,b
			ld_r1_r2(&e,&b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x59:{//ld e,c
			ld_r1_r2(&e,&c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x5a:{//ld e,d
			ld_r1_r2(&e, &d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x5b:{//ld e,e
			ld_r1_r2(&e, &e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x5c:{//ld e,h
			ld_r1_r2(&e, &h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x5d:{//ld e,l
			ld_r1_r2(&e, &l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x5e:{//ld e, (hl)
			ld_r1_r2(&e,RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x5f:{//ld e,a
			ld_r1_r2(&e, &a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x60:{//ld h,b
			ld_r1_r2(&h, &b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x61:{//ld h,c
			ld_r1_r2(&h,&c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x62:{//ld h,d
			ld_r1_r2(&h,&d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x63:{//ld h, e
			ld_r1_r2(&h, &e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x64:{//ld h,h
			ld_r1_r2(&h, &h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x65:{//ld h,l
			ld_r1_r2(&h,&l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x66:{//ld h, (hl)
			ld_r1_r2(&h,RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x67:{//ld h,a
			ld_r1_r2(&h, &a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x68:{//ld l,b
			ld_r1_r2(&l, &b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x69:{//ld l,c
			ld_r1_r2(&l, &c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x6a:{//ld l,d
			ld_r1_r2(&l, &d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x6b:{//ld l,e
			ld_r1_r2(&l, &e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x6c:{//ld l,h
			ld_r1_r2(&l, &h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x6d:{//ld l, l
			ld_r1_r2(&l, &l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x6e:{//ld l,hl
			ld_r1_r2(&l, RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x6f:{//ld l,a 
			ld_r1_r2(&l,&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x70:{//ld (hl), b
			ld_r1_r2(RAM + hl, &b);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x71:{//ld (hl),c
			ld_r1_r2(RAM + hl, &c);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x72:{//ld (hl), d
			ld_r1_r2(RAM + hl, &d);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x73:{//ld (hl), e
			ld_r1_r2(RAM + hl, &e);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x74:{//ld (hl), h
			ld_r1_r2(RAM + hl, &h);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x75:{//ld (hl), l
			ld_r1_r2(RAM + hl, &l);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x76:{// halt
			halt();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x77:{//ld (hl),a
			ld_r1_r2(RAM + hl, &a);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x78:{// la a,b
			ld_r1_r2(&a,&b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x79:{//ld a,c
			ld_r1_r2(&a,&c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x7a:{//ld a,d
			ld_r1_r2(&a,&d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x7b:{//ld a,e
			ld_r1_r2(&a,&e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x7c:{//ld a,h
			ld_r1_r2(&a,&h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x7d:{//ld a,l
			ld_r1_r2(&a,&l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x7e:{//ld a,hl
			ld_r1_r2(&a,RAM + hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x7f:{
			ld_r1_r2(&a,&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x80:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x81:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x82:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x83:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x84:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x85:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x86:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x87:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x88:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x89:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8a:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8b:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8c:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8d:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8e:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8f:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x90:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x91:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x92:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x93:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x94:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x95:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x96:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x97:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x98:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x99:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9a:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9b:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9c:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9d:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9e:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9f:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa8:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa9:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xaa:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xab:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xac:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xae:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xaf:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb8:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb9:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xba:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbb:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbc:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbd:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbe:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbf:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc8:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc9:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xca:{
			program_counter += 1;
			clocks += 8;
		} break;
		//cb leads to more opcodes, see nested switch toward end
		case 0xcc:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xcd:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xce:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xcf:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd8:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd9:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xda:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xdb:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xdc:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xdd:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xde:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xdf:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe8:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe9:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xea:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xeb:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xec:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xed:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xee:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xef:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf0:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf1:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf2:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf3:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf4:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf5:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf6:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf7:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf8:{
			ld_hl_sp_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 12;
		} break;
		case 0xf9:{
			ld_sp_hl();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfa:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfb:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfc:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfd:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfe:{
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xff:{
			program_counter += 1;
			clocks += 8;
		} break;

		case 0xcb:{
			program_counter += 1;
			u8 op2 = RAM[program_counter];
			switch(op2){
						case 0x00:{//nop
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x01:{//ld bc, d16
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x02:{//ld (bc), a
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x03:{//inc bc
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x04:{//inc b
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x05:{//dec b
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x06:{//ld b, d8
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x07:{//rlca
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x08:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x09:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x10:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x11:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x12:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x13:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x14:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x15:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x16:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x17:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x18:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x19:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x20:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x21:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x22:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x23:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x24:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x25:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x26:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x27:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x28:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x29:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x30:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x40:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x41:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x42:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x43:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x44:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x45:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x46:{
							program_counter += 1;
							clocks += 8;
						} break;

						case 0x47:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x48:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x49:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x50:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x51:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x52:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x53:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x54:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x55:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x56:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x57:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x58:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x59:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x60:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x61:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x62:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x63:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x64:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x65:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x66:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x67:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x68:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x69:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x70:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x71:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x72:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x73:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x74:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x75:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x76:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x77:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x78:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x79:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x80:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x81:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x82:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x83:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x84:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x85:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x86:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x87:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x88:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x89:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x90:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x91:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x92:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x93:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x94:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x95:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x96:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x97:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x98:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x99:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9a:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9b:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9c:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9d:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9e:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9f:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xaa:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xab:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xac:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xae:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xaf:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xba:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbb:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbc:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbd:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbe:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbf:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xca:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xcb:{
							program_counter += 1;
							clocks += 8;
						}break;
						case 0xcc:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xcd:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xce:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xcf:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xda:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdb:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdc:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdd:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xde:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdf:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xea:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xeb:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xec:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xed:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xee:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xef:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf0:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf1:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf2:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf3:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf4:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf5:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf6:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf7:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf8:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf9:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfa:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfb:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfc:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfd:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfe:{
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xff:{
							program_counter += 1;
							clocks += 8;
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
inline void GB_CPU::ld_nn_n(u8 * nn){
	*nn = RAM[program_counter + 1];
}

inline void GB_CPU::ld_r1_r2(u8 * r1, u8 * r2){
	*r1 = *r2;
}

inline void GB_CPU::ld_a_n(u8 * n){
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
	program_counter -=2;
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
//todo: fix
inline void GB_CPU::push_nn(u16 nn){
	u8 h,l;
	l += nn;
	nn >> 4;
	h += nn;
	RAM[stack_pointer] = l;
	--stack_pointer; 
	RAM[stack_pointer] = h;
	--stack_pointer; 
}
//todo: fix
inline void GB_CPU::pop_nn(u16 * nn){
	u8 h, l;
	h = RAM[stack_pointer];
	++stack_pointer;
	l = RAM[stack_pointer];
	++stack_pointer;
	*nn = h;
	*nn << 4;
	*nn += l;

}
	//8 bit ALU
inline void GB_CPU::add_a_n(u8 n){
	//check for carry in bit 3
	if(a & 0x4 && n & 0x4) h_flag = true; 
	//check for carry in bit 7
	if(a & 0xf && n & 0xf) c_flag = true; 
	a += n;
	if (a == 0) z_flag = true;
	else n_flag = false;
}

//TODO: bug warning
inline void GB_CPU::adc_a_n(u8 n){
	//check for carry in bit 3
	if(a & 0x4 && n & 0x4) h_flag = true; 
	//check for carry in bit 7
	if(a & 0xf && n & 0xf) c_flag = true; 
	n_flag = false;
	a += n;
	if(c_flag) ++a;
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
	if(a & 0x4 && n & 0x4) h_flag = true; 

	if(a == n) z_flag = true;
	n_flag = true;
	if(a < n) c_flag = true;// TODO: Check this
}
inline void GB_CPU::inc_n(u8 * n){
	if(*n & 0x4) h_flag = true;
	++(*n);
	if(*n == 0) z_flag = true;
	n_flag = false;
	//c flag not affected
}
inline void GB_CPU::dec_n(u8 * n){
	if(*n & 0x4) h_flag = true;
	--(*n);
	if(*n == 0) z_flag = true;
	n_flag = true;
	//c flag not affected
}
	//16 bit arithmetic
inline void GB_CPU::add_hl_n(u16  n){
	//check for carry in bit 3
	if(hl & 0x4 && n & 0x4) h_flag = true; 
	//check for carry in bit 7
	if(hl & 0xf && n & 0xf) c_flag = true; 
	hl += n;
	//z flag not affected
	n_flag = false;
	//figure out h and c flags
}
inline void GB_CPU::add_sp_n(u16 n){
	//check for carry in bit 3
	if(stack_pointer & 0x4 && n & 0x4) h_flag = true; 
	//check for carry in bit 7
	if(stack_pointer & 0xf && n & 0xf) c_flag = true; 
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
	u8 cf = 0;
	u8 a_temp = a;
	if(a > 0x99 || c_flag){
		c_flag = true;
		cf += 0x60;
	}
	else{
		c_flag = false;
	}
	if(a & 0x0f > 9 || h_flag){
		cf += 0x06;

	}
	if(!n_flag){
		a += cf;
	}
	else{
		a -= cf;
	}
	if(a == 0) z_flag = true;
	if(a ^ a_temp) h_flag = true;

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
	ei_flag = false;
}
inline void GB_CPU::ei(){
	//TODO: enable interrupts
	ei_flag = true;
}
	//rotates and shifts

	//TODO: rotates are probably buggy af, double check these
inline void GB_CPU::rlca(){
	if(a & 0xf) c_flag = true;
	a << 1;
	if(c_flag) ++a;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::rla(){
	if(c_flag) ++a;
	if(a & 0xf) c_flag = true;
	a << 1;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::rrca(){
	if(a & 0x1) c_flag = true;
	a >> 1;
	if(c_flag) ++a;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;

}
inline void GB_CPU::rra(){
	if(c_flag) ++a;
	if(a & 0x1) c_flag = true;
	a >> 1;
	if (a == 0) z_flag = true;
	n_flag = false;
	h_flag = false;

}
inline void GB_CPU::rlc_n(u8 * n){
	if(*n & 0xf) c_flag = true;
	*n << 1;
	if(c_flag) ++(*n);
	if ((*n) == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
	
}
inline void GB_CPU::rl_n(u8 * n){
	if(c_flag) ++(*n);
	if(*n & 0xf) c_flag = true;
	*n << 1;
	if ((*n) == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
	
}
inline void GB_CPU::rrc_n(u8 * n){
	if(*n & 0x1) c_flag = true;
	*n >> 1;
	if(c_flag) ++(*n);
	if ((*n) == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
	
}
inline void GB_CPU::rr_n(u8 * n){
	if(c_flag) ++(*n);
	if(*n & 0x1) c_flag = true;
	*n >> 1;
	if ((*n) == 0) z_flag = true;
	n_flag = false;
	h_flag = false;
	
}

inline void GB_CPU::sla_n(u8 * n){
	if(*n & 0xf) c_flag = true;
	else c_flag = false;
	*n << 1;
	if(!(*n)) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::sra_n(u8 * n){
	//test MSB
	u8 temp = 0;
	if(*n & 0xf) temp += 0xf;
	if(*n & 0x1) c_flag = true;
	*n >> 1;
	*n += temp;
	if(!(*n)) z_flag = true;
	n_flag = false;
	h_flag = false;
}
inline void GB_CPU::srl_n(u8 * n){
	if(*n & 0x1) c_flag = true;
	else c_flag = false;
	*n >> 1;
	if(!(*n)) z_flag = true;
	n_flag = false;
	h_flag = false;
	
}
	//bit opcodes
inline void GB_CPU::bit_b_r(u8 b, u8 * n){
	switch(b){
		case 0:{*n & 0x01 ? z_flag = false : z_flag = true ;}break;
		case 1:{*n & 0x02 ? z_flag = false : z_flag = true ;}break;
		case 2:{*n & 0x04 ? z_flag = false : z_flag = true ;}break;
		case 3:{*n & 0x08 ? z_flag = false : z_flag = true ;}break;
		case 4:{*n & 0x10 ? z_flag = false : z_flag = true ;}break;
		case 5:{*n & 0x20 ? z_flag = false : z_flag = true ;}break;
		case 6:{*n & 0x40 ? z_flag = false : z_flag = true ;}break;
		case 7:{*n & 0x80 ? z_flag = false : z_flag = true ;}break;
	}
	n_flag = false;
	h_flag = true;
}
inline void GB_CPU::set_b_r(u8 b, u8 * n){
	switch(b){
		case 0:{if(!(*n & 0x01)) *n += 0x01;}break;
		case 1:{if(!(*n & 0x02)) *n += 0x02;}break;
		case 2:{if(!(*n & 0x04)) *n += 0x04;}break;
		case 3:{if(!(*n & 0x08)) *n += 0x08;}break;
		case 4:{if(!(*n & 0x10)) *n += 0x10;}break;
		case 5:{if(!(*n & 0x20)) *n += 0x20;}break;
		case 6:{if(!(*n & 0x40)) *n += 0x40;}break;
		case 7:{if(!(*n & 0x80)) *n += 0x80;}break;
	}
}
inline void GB_CPU::res_b_r(u8 b, u8 * n){
		switch(b){
		case 0:{if((*n & 0x01)) *n -= 0x01;}break;
		case 1:{if((*n & 0x02)) *n -= 0x02;}break;
		case 2:{if((*n & 0x04)) *n -= 0x04;}break;
		case 3:{if((*n & 0x08)) *n -= 0x08;}break;
		case 4:{if((*n & 0x10)) *n -= 0x10;}break;
		case 5:{if((*n & 0x20)) *n -= 0x20;}break;
		case 6:{if((*n & 0x40)) *n -= 0x40;}break;
		case 7:{if((*n & 0x80)) *n -= 0x80;}break;
	}

}
	//jumps
inline void GB_CPU::jp_nn(){
	program_counter = read_word();
}
inline void GB_CPU::jp_cc_nn(){
	switch(RAM[program_counter]){
		case 0xc2:{if(!z_flag) program_counter = read_word();}break;
		case 0xca:{if(z_flag) program_counter = read_word();}break;
		case 0xd2:{if(!c_flag) program_counter = read_word();}break;
		case 0xda:{if(c_flag) program_counter -read_word();}break;
	}

}
inline void GB_CPU::jp_hl(){
	program_counter = hl;
}
inline void GB_CPU::jr_n(){
	program_counter += RAM[program_counter + 1];
}
inline void GB_CPU::jr_cc_n(){
	//TODO
	int jump = static_cast<int>(RAM[program_counter + 1]);
	switch(RAM[program_counter]){
		case 0x20:{if(!z_flag) program_counter += jump ;}break;
		case 0x28:{if(z_flag) program_counter += jump ;}break;
		case 0x30:{if(!c_flag) program_counter += jump ;}break;
		case 0x38:{if(c_flag) program_counter += jump ;}break;
	}
}

	//calls
inline void GB_CPU::call_nn(){
	push_nn(program_counter + 3);
	program_counter = read_word();
}
inline void GB_CPU::call_cc_nn(){
	switch(RAM[program_counter]){
		case 0xc4:{if(!z_flag) call_nn();}break;
		case 0xcc:{if(z_flag) call_nn();}break;
		case 0xd4:{if(!c_flag) call_nn();}break;
		case 0xdc:{if(c_flag) call_nn();}break;
	}

}
	//restarts
inline void GB_CPU::rst_n(u8 n){
	push_nn(program_counter);
	program_counter = n;
}
	//returns
inline void GB_CPU::ret(){
	pop_nn(&program_counter);
}
inline void GB_CPU::ret_cc(){
	switch(RAM[program_counter]){
		case 0xc0:{if(!z_flag) ret();}break;
		case 0xc8:{if(z_flag) ret();}break;
		case 0xd0:{if(!c_flag) ret();}break;
		case 0xd8:{if(c_flag) ret();}break;
	}
}
inline void GB_CPU::reti(){
	ret();
	ei_flag = true;
}
