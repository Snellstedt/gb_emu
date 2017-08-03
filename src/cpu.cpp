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

		case 0x1d:{//dec e
			dec_n(&e);
			program_counter += 1;
			clocks += 8;
		} break;

		case 0x1e:{//ld e,d8
			ld_nn_n(&e);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x1f:{//rra
			rra();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x20:{//jr nz,r8
			jr_cc_n();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x21:{//ld hl, d16
			ld_n_nn(&hl);
			program_counter += 3;
			clocks += 12;
		} break;
		case 0x22:{//ld hl+, a
			ldi_hl_a();	
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x23:{//inc hl
			inc_nn(&hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x24:{//inc h
			inc_n(&h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x25:{//dec h
			dec_n(&h);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x26:{//ld h, d8
			ld_nn_n(&h);
			clocks += 8;
			program_counter +=2;
		} break;

		case 0x27:{//daa
			daa();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x28:{//jr z,r8
			jr_cc_n();
			program_counter += 2;
			clocks += 8;
		} break;
		case 0x29:{//add hl,hl
			add_hl_n(hl);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2a:{//ld a, hl+
			ldi_a_hl();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2b:{//dec
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x2c:{//inc l
			inc_n(&l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x2d:{//dec l
			dec_n(&l);
			program_counter += 1;
			clocks += 4;
		} break;

		case 0x2e:{//ld l, d8
			ld_nn_n(&l);
			clocks += 8;
			program_counter +=2;
		} break;
		
		case 0x2f:{//cpl
			cpl();
			program_counter += 1;
			clocks += 4;
		} break;
		
		case 0x30:{//jr nc, r8
			jr_cc_n();
			program_counter += 2;
			clocks += 8;
		} break;
		case 0x31:{//ld sp,d16
			ld_n_nn(&stack_pointer);
			program_counter += 3;
			clocks += 12;
		} break;
		case 0x32:{//ld hld, a
			ldd_hl_a();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x33:{//inc sp
			inc_nn(&stack_pointer);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x34:{//inc (hl)
			inc_n(RAM + hl);
			program_counter += 1;
			clocks += 12;
		} break;
		case 0x35:{//dec (hl)
			dec_n(RAM + hl);
			program_counter += 1;
			clocks += 12;
		} break;
		case 0x36:{//ld (hl), d8
			ld_nn_n(RAM + hl);
			program_counter += 2;
			clocks += 12;
		} break;
		case 0x37:{//scf
			scf();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x38:{//jr c, r8
			jr_cc_n();
			program_counter += 2;
			clocks += 8;
		} break;
		case 0x39:{//add hl,sp
			add_hl_n(stack_pointer);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3a:{//ld a, hl-
			ldd_a_hl();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3b:{//dec sp
			dec_nn(&stack_pointer);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3c:{//inc a
			inc_n(&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x3d:{//dec a
			dec_n(&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x3e:{//ld a,d8
			program_counter += 1;
			ld_a_n(RAM + program_counter);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x3f:{//ccf
			ccf();
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
		case 0x7f:{//ld a,a
			ld_r1_r2(&a,&a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x80:{//add a,b
			add_a_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x81:{//add a,c
			add_a_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x82:{//add a,d
			add_a_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x83:{//add a,e
			add_a_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x84:{//add a,h
			add_a_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x85:{//add a, l
			add_a_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x86:{//add a,(hl)
			add_a_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x87:{//add a,a
			add_a_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x88:{//adc a, b
			adc_a_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x89:{//adc a, c
			adc_a_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x8a:{//adc a, d
			adc_a_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x8b:{//adc a,e
			adc_a_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x8c:{//adc a,h
			adc_a_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x8d:{//adc a,l
			adc_a_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x8e:{//adc a,(hl)
			adc_a_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x8f:{//adc a,a
			adc_a_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x90:{//sub b
			sub_a_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x91:{//sub c
			sub_a_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x92:{//sub d
			sub_a_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x93:{//sub e
			sub_a_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x94:{//sub h
			sub_a_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x95:{//sub l
			sub_a_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x96:{//sub (hl)
			sub_a_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x97:{//sub a
			sub_a_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x98:{//sbc a,b
			sbc_a_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x99:{//sbc a,c
			sub_a_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x9a:{//sbc a,d
			sub_a_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x9b:{//sbd a,e
			sub_a_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x9c:{//sbc a,h
			sub_a_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x9d:{//sbc a,l
			sub_a_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0x9e:{//sbc a, (hl)
			sub_a_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0x9f:{//sbc a,a
			sub_a_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa0:{//and b
			and_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa1:{//and c
			and_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa2:{//and d
			and_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa3:{//and e
			and_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa4:{//and h
			and_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa5:{//and l
			and_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa6:{//and (hl)
			and_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xa7:{//and a
			and_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa8:{//xor b
			xor_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xa9:{//xor c
			xor_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xaa:{//xor d
			xor_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xab:{//xor e
			xor_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xac:{//xor h
			xor_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xad:{//xor l
			xor_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xae:{//xor (hl)
			xor_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xaf:{//xor a
			xor_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb0:{// or b
			or_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb1:{//or c
			or_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb2:{//or d
			or_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb3:{//or e
			or_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb4:{//or h
			or_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb5:{//or l
			or_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb6:{//or (hl)
			or_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xb7:{//or a
			or_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb8:{//cp b
			cp_n(b);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xb9:{//cp c
			cp_n(c);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xba:{//cp d
			cp_n(d);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xbb:{//cp e
			cp_n(e);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xbc:{//cp h
			cp_n(h);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xbd:{//cp l
			cp_n(l);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xbe:{//cp (hl)
			cp_n(RAM[hl]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xbf:{//cp a
			cp_n(a);
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xc0:{//ret nz
			ret();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc1:{//pop bc
			pop_nn(&bc);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc2:{//jp nz, a16
			jp_cc_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xc3:{//jp a16
			jp_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xc4:{//call nz, a16
			call_cc_nn();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc5:{//push bc
			push_nn(bc);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xc6:{//add a,d8
			add_a_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xc7:{//rst 0x0
			rst_n(0x0);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc8:{//ret z
			ret_cc();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xc9:{//ret
			ret();
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xca:{//jp z,a16
			jp_cc_nn();
			program_counter += 1;
			clocks += 8;
		} break;
		//cb leads to more opcodes, see nested switch toward end
		case 0xcc:{//call z,a16
			call_cc_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xcd:{//call a16
			call_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xce:{//adc a,d8
			adc_a_n(RAM[program_counter + 1]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xcf:{//rst 0x08
			rst_n(0x8);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd0:{//ret nc
			ret_cc();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd1:{//pop bc
			pop_nn(&bc);
			program_counter += 1;
			clocks += 12;
		} break;
		case 0xd2:{//jp nc, a16
			jp_cc_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xd3:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd4:{//call nc,a16
			call_cc_nn();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd5:{//push de
			push_nn(de);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd6:{//sub d8
			sub_a_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xd7:{//rst 0x10
			rst_n(0x10);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xd8:{//ret c
			ret_cc();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xd9:{//reti
			reti();
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xda:{//jp c,a16
			jp_cc_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xdb:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xdc:{//call c,a16
			call_cc_nn();
			program_counter += 3;
			clocks += 8;
		} break;
		case 0xdd:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xde:{//sbc a,d8
			sbc_a_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xdf:{//rst 0x18
			rst_n(0x18);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xe0:{//ldh (a8), a
			ldh_n_a(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 12;
		} break;
		case 0xe1:{//pop hl
			pop_nn(&hl);
			program_counter += 1;
			clocks += 12;
		} break;
		case 0xe2:{//ld (c), a
			ld_c_a();
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xe3:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe4:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xe5:{//push hl
			push_nn(hl);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xe6:{//and d8
			and_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xe7:{//rst 0x20
			rst_n(0x20);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xe8:{//add sp,r8
			add_sp_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 16;
		} break;
		case 0xe9:{//jp (hl)
			jp_hl();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xea:{//ld (a16), a
			u16 temp = read_word();
			ld_n_a(&temp);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xeb:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xec:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xed:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xee:{//xor d8
			xor_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xef:{//rst 0x28
			rst_n(0x28);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xf0:{//ldh a, (a8
			ldh_a_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 12;
		} break;
		case 0xf1:{//pop af
			pop_nn(&af);
			program_counter += 1;
			clocks += 12;
		} break;
		case 0xf2:{//ld a, (c)
			ld_a_c();
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xf3:{//di
			di();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xf4:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xf5:{//push af
			push_nn(af);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xf6:{//or d8
			or_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 8;
		} break;
		case 0xf7:{//rst 0x30
			rst_n(0x30);
			program_counter += 1;
			clocks += 16;
		} break;
		case 0xf8:{//ld hl, sp + d8
			ld_hl_sp_n(RAM[program_counter + 1]);
			program_counter += 2;
			clocks += 12;
		} break;
		case 0xf9:{//ld sp, hl
			ld_sp_hl();
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfa:{//ld a, (a16)
			ld_a_n(&RAM[read_word()]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfb:{//ei
			ei();
			program_counter += 1;
			clocks += 4;
		} break;
		case 0xfc:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfd:{//unused
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xfe:{//cp d8
			cp_n(RAM[program_counter + 1]);
			program_counter += 1;
			clocks += 8;
		} break;
		case 0xff:{//rst 0x38
			rst_n(0x38);
			program_counter += 1;
			clocks += 16;
		} break;

		//////////////////////////////////////////////////
		//// prefix CB instructions

		case 0xcb:{
			program_counter += 1;
			u8 op2 = RAM[program_counter];
			switch(op2){
						case 0x00:{//rlc b
							rlc_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x01:{//rlc c
							rlc_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x02:{//rlc d
							rlc_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x03:{//rlc e
							rlc_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x04:{//rlc h
							rlc_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x05:{//rlc l
							rlc_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x06:{//rlc (hl)
							rlc_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x07:{//rlc a
							rlc_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x08:{//rrc b
							rrc_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x09:{//rrc c
							rrc_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0a:{//rrc d
							rrc_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0b:{//rrc e
							rrc_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0c:{//rrc h
							rrc_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0d:{//rrc l
							rrc_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x0e:{//rrc (hl)
							rrc_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x0f:{//rrc a
							rrc_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x10:{//rl b
							rl_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x11:{//rl c
							rl_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x12:{//rl d
							rl_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x13:{//rl e
							rl_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x14:{//rl h
							rl_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x15:{//rl l
							rl_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x16:{//rl (hl) 
							rl_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x17:{//rl a
							rl_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x18:{//rr b
							rr_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x19:{//rr c
							rr_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1a:{//rr d
							rr_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1b:{//rr e
							rr_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1c:{//rr h
							rr_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1d:{//rr l
							rr_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x1e:{//rr (hl)
							rr_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x1f:{//rr a
							rr_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x20:{//sla b
							sla_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x21:{//sla c
							sla_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x22:{//sla d
							sla_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x23:{//sla e
							sla_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x24:{//sla h
							sla_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x25:{//sla l
							sla_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x26:{//sla (hla)
							sla_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x27:{//sla a
							sla_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x28:{//sra b
							sra_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x29:{//sra c
							sra_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x2a:{//sra d
							sra_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x2b:{//sra e
							sra_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x2c:{//sra h
							sra_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x2d:{//sra l
							sra_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x2e:{//sra (hl)
							sra_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x2f:{//sra a
							sra_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x30:{//swap b
							swap_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x31:{//swap c
							swap_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x32:{//swap d
							swap_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x33:{//swap e
							swap_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x34:{//swap h
							swap_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x35:{//swap l
							swap_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x36:{//swap (hl)
							swap_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x37:{//swap a
							swap_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x38:{//srl b
							srl_n(&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x39:{//srl c
							srl_n(&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3a:{//srl d
							srl_n(&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3b:{//srl e
							srl_n(&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3c:{//srl h
							srl_n(&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3d:{//srl l
							srl_n(&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x3e:{//srl (hl)
							srl_n(RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x3f:{//srl a
							srl_n(&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x40:{//bit 0,b
							bit_b_r(0,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x41:{//bit 0,c
							bit_b_r(0,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x42:{//bit 0,d
							bit_b_r(0,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x43:{//bit 0,e
							bit_b_r(0,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x44:{//bit 0,,h
							bit_b_r(0,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x45:{//bit 0,l
							bit_b_r(0,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x46:{//bit 0,(hl)
							bit_b_r(0, RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x47:{//bit 0,a
							bit_b_r(0,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x48:{//bit 1,b
							bit_b_r(1,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x49:{//bit 1,c
							bit_b_r(1,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4a:{//bit 1,d
							bit_b_r(1,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4b:{//bit 1,e
							bit_b_r(1,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4c:{//bit 1,h
							bit_b_r(1,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4d:{//bit 1,l
							bit_b_r(1,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x4e:{//bit 1,(hl)
							bit_b_r(1,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x4f:{//bit 1,a
							bit_b_r(1,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x50:{//bit 2,b
							bit_b_r(2,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x51:{//bit 2,c
							bit_b_r(2,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x52:{//bit 2,d
							bit_b_r(2,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x53:{//bit 2,e
							bit_b_r(2,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x54:{//bit 2,h
							bit_b_r(2,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x55:{//bit 2,l
							bit_b_r(2,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x56:{//bit 2,(hl)
							bit_b_r(2,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x57:{//bit 2,a
							bit_b_r(2,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x58:{//bit 3,b
							bit_b_r(3,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x59:{//bit 3,c
							bit_b_r(3,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5a:{//bit 3,d
							bit_b_r(3,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5b:{//bit 3,e
							bit_b_r(3,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5c:{//bit 3,h
							bit_b_r(3,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5d:{//bit 3,l
							bit_b_r(3,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x5e:{//bit 3,(hl)
							bit_b_r(3,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x5f:{//bit 3,a
							bit_b_r(3,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x60:{//bit 4,b
							bit_b_r(4,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x61:{//bit 4,c
							bit_b_r(4,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x62:{//bit 4,d
							bit_b_r(4,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x63:{//bit 4,e
							bit_b_r(4,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x64:{//bit 4,h
							bit_b_r(4,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x65:{//bit 4,l
							bit_b_r(4,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x66:{//bit 4,(hl)
							bit_b_r(4,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x67:{//bit 4,a
							bit_b_r(4,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x68:{//bit 5,b
							bit_b_r(5,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x69:{//bit 5,c
							bit_b_r(5,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6a:{//bit 5,d
							bit_b_r(5,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6b:{//bit 5,e
							bit_b_r(5,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6c:{//bit 5,h
							bit_b_r(5,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6d:{//bit 5,l
							bit_b_r(5,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x6e:{//bit 5,(hl)
							bit_b_r(5,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x6f:{//bit 5,a
							bit_b_r(5,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x70:{//bit 6,b
							bit_b_r(6,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x71:{//bit 6,c
							bit_b_r(6,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x72:{//bit 6,d
							bit_b_r(6,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x73:{//bit 6,e
							bit_b_r(6,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x74:{//bit 6,h
							bit_b_r(6,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x75:{//bit 6,l
							bit_b_r(6,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x76:{//bit 6,(hl)
							bit_b_r(6,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x77:{//bit 6,a
							bit_b_r(6,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x78:{//bit 7,b
							bit_b_r(7,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x79:{//bit 7,c
							bit_b_r(7,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7a:{//bit 7,d
							bit_b_r(7,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7b:{//bit 7,e
							bit_b_r(7,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7c:{//bit 7,h
							bit_b_r(7,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7d:{//bit 7,l
							bit_b_r(7,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x7e:{//bit 7,(hl)
							bit_b_r(7,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x7f:{//bit 7,a
							bit_b_r(7,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x80:{//res 0,b
							res_b_r(0,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x81:{//res 0,c
							res_b_r(0,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x82:{//res 0,d
							res_b_r(0,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x83:{//res 0,e
							res_b_r(0,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x84:{//res 0,h
							res_b_r(0,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x85:{//res 0,l
							res_b_r(0,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x86:{//res 0,(hl)
							res_b_r(0,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x87:{//res 0,a
							res_b_r(0,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x88:{//res 1,b
							res_b_r(1,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x89:{//res 1,c
							res_b_r(1,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8a:{//res 1,d
							res_b_r(1,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8b:{//res 1,e
							res_b_r(1,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8c:{//res 1,h
							res_b_r(1,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8d:{//res 1,l
							res_b_r(1,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x8e:{//res 1,(hl)
							res_b_r(1,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x8f:{//res 1,a
							res_b_r(1,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x90:{//res 2,b
							res_b_r(2,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x91:{//res 2,c
							res_b_r(2,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x92:{//res 2,d
							res_b_r(2,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x93:{//res 2,e
							res_b_r(2,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x94:{//res 2,h
							res_b_r(2,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x95:{//res 2,l
							res_b_r(2,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x96:{//res 2,(hl)
							res_b_r(2,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x97:{//res 2,a
							res_b_r(2,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x98:{//res 3,b
							res_b_r(3,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x99:{//res 3,c
							res_b_r(3,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9a:{//res 3,d
							res_b_r(3,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9b:{//res 3,e
							res_b_r(3,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9c:{//res 3,h
							res_b_r(3,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9d:{//res 3,l
							res_b_r(3,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0x9e:{//res 3,(hl)
							res_b_r(3,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0x9f:{//res 3,a
							res_b_r(3,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa0:{//res 4,b
							res_b_r(4,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa1:{//res 4,c
							res_b_r(4,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa2:{//res 4,d
							res_b_r(4,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa3:{//res 4,e
							res_b_r(4,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa4:{//res 4,h
							res_b_r(4,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa5:{//res 4,l
							res_b_r(4,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa6:{//res 4,(hl)
							res_b_r(4,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xa7:{//res 4,a
							res_b_r(4,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa8:{//res 5, b
							res_b_r(5,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xa9:{//res 5, c
							res_b_r(5,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xaa:{//res 5, d
							res_b_r(5,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xab:{//res 5, e
							res_b_r(5,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xac:{//res 5, h
							res_b_r(5,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xad:{//res 5, l
							res_b_r(5,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xae:{//res 5, (hl)
							res_b_r(5,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xaf:{//res 5, a
							res_b_r(5,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb0:{//res 6,b
							res_b_r(6,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb1:{//res 6,c
							res_b_r(6,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb2:{//res 6,d
							res_b_r(6,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb3:{//res 6,e
							res_b_r(6,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb4:{//res 6,h
							res_b_r(6,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb5:{//res 6,l
							res_b_r(6,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb6:{//res 6,(hl)
							res_b_r(6,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xb7:{//res 6,a
							res_b_r(6,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb8:{//res 7,b
							res_b_r(7,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xb9:{//res 7,c
							res_b_r(7,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xba:{//res 7,d
							res_b_r(7,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbb:{//res 7,e
							res_b_r(7,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbc:{//res 7,h
							res_b_r(7,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbd:{//res 7,l
							res_b_r(7,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xbe:{//res 7,(hl)
							res_b_r(7,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xbf:{//res 7,a
							res_b_r(7,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc0:{//set 0,b
							set_b_r(0,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc1:{//set 0,c
							set_b_r(0,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc2:{//set 0,d
							set_b_r(0,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc3:{//set 0,e
							set_b_r(0,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc4:{//set 0,h
							set_b_r(0,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc5:{//set 0,l
							set_b_r(0,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc6:{//set 0,(hl)
							set_b_r(0,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xc7:{//set 0,a
							set_b_r(0,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc8:{//set 1,b
							set_b_r(1,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xc9:{//set 1,c
							set_b_r(1,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xca:{//set 1,d
							set_b_r(1,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xcb:{//set 1,e
							set_b_r(1,&e);
							program_counter += 1;
							clocks += 8;
						}break;
						case 0xcc:{//set 1,h
							set_b_r(1,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xcd:{//set 1,l
							set_b_r(1,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xce:{//set 1,(hl)
							set_b_r(1,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xcf:{//set 1,a
							set_b_r(1,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd0:{//set 2,b
							set_b_r(2,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd1:{//set 2,c
							set_b_r(2,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd2:{//set 2,d
							set_b_r(2,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd3:{//set 2,e
							set_b_r(2,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd4:{//set 2,h
							set_b_r(2,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd5:{//set 2,l
							set_b_r(2,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd6:{//set 2,(hl)
							set_b_r(2,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xd7:{//set 2,a
							set_b_r(2,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd8:{//set 3,b
							set_b_r(3,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xd9:{//set 3,c
							set_b_r(3,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xda:{//set 3,d
							set_b_r(3,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdb:{//set 3,e
							set_b_r(3,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdc:{//set 3,h
							set_b_r(3,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xdd:{//set 3,l
							set_b_r(3,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xde:{//set 3,(hl)
							set_b_r(3,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xdf:{//set 3,a
							set_b_r(3,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe0:{//set 4,b
							set_b_r(4,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe1:{//set 4,c
							set_b_r(4,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe2:{//set 4,d
							set_b_r(4,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe3:{//set 4,e
							set_b_r(4,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe4:{//set 4,h
							set_b_r(4,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe5:{//set 4,l
							set_b_r(4,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe6:{//set 4,(hl)
							set_b_r(4,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xe7:{//set 4,a
							set_b_r(4,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe8:{//set 5,b
							set_b_r(5,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xe9:{//set 5,c
							set_b_r(5,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xea:{//set 5,d
							set_b_r(5,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xeb:{//set 5,e
							set_b_r(5,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xec:{//set 5,h
							set_b_r(5,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xed:{//set 5,l
							set_b_r(5,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xee:{//set 5,(hl)
							set_b_r(5,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xef:{//set 5,a
							set_b_r(5,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf0:{//set 6,b
							set_b_r(6,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf1:{//set 6,c
							set_b_r(6,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf2:{//set 6,d
							set_b_r(6,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf3:{//set 6,e
							set_b_r(6,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf4:{//set 6,h
							set_b_r(6,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf5:{//set 6,l
							set_b_r(6,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf6:{//set 6,(hl)
							set_b_r(6,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xf7:{//set 6,a
							set_b_r(6,&a);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf8:{//set 7,b
							set_b_r(7,&b);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xf9:{//set 7,c
							set_b_r(7,&c);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfa:{//set 7,d
							set_b_r(7,&d);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfb:{//set 7,e
							set_b_r(7,&e);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfc:{//set 7,h
							set_b_r(7,&h);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfd:{//set 7,l
							set_b_r(7,&l);
							program_counter += 1;
							clocks += 8;
						} break;
						case 0xfe:{//set 7,(hl)
							set_b_r(7,RAM + hl);
							program_counter += 1;
							clocks += 16;
						} break;
						case 0xff:{//set 7,a
							set_b_r(7,&a);
							program_counter += 1;
							clocks += 8;
						} break;

			}
		} break;



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
