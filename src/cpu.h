#include <fstream>
#include <cstdlib> //exit
#include <cstring> //memset
#include <iostream>


class GB_CPU{
public:

	//constructor
	GB_CPU(const std::string & ROM_file){


		//set RAM to zero
		memset(RAM, 0, 0xFFFF);

		//set registers, stack pointer and program counter to zero
		a = f = c = b = e = d = l = h = program_counter = stack_pointer = 0;
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

	//do this once per cycle
	void tick(){
		//fetch

		//
	}

	// unsigned char read_byte(unsigned char * addr){
	// 	unsigned int index = reinterpret_cast<int>(addr);
	// 	return RAM[index];
	// }
	// unsigned short int read_word(unsigned char * addr){
	// 	return RAM[addr] & RAM[addr + 1];
	// }

	// void write_byte(unsigned char * addr, unsigned char val){
	// 	unsigned int index = reinterpret_cast<int>(addr);
	// 	RAM[index] = val;
	// }
	// void write_word(unsigned char * addr, unsigned short int val);


	
	//execute opcode
	void execute_opcode();

private:

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

	unsigned char stack_pointer;
	unsigned char program_counter;

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