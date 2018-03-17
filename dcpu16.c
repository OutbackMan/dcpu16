#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

enum { A, B, C, X, Y, Z, I, J, PC, SP, EX };
enum { nbi, SET, ADD, SUB, MUL, DIV, MOD, SHL, SHR, AND, BOR, XOR, IFE, IFN, IFG, IFB };
enum { JSR=0x11 };

typedef struct {
	u16 memory[0x10000];	
	u16 registers[11];
} Emulator;

void emulator__tick(Emulator* emulator, unsigned n) {}

void emulator__op(Emulator* emulator)
{
	emulator__tick(emulator);	
	
	// Get instruction
	u16 v = emulator.memory[emulator.registers[PC]++];
	// Parse instruction
	u16 o = (v & 0x0F);
	u16 aa = (v >> 4) & 0x3F;
	u16 bb = (v >> 10) & 0x3F;
	
	u16 a = (o == nbi) ? v : value(aa);
	u32 wa = a;
	u16 b = value(bb);
	u32 wr;
	// Execute instruction
	switch (o == nbi ? aa + 0x10 : o) {
		case SET: emulator__tick(emulator, 0); a = b; break;
		case AND: emulator__tick(emulator, 0); a &= b; break;
		case BOR: emulator__tick(emulator, 0); a |= b; break;
		case XOR: emulator__tick(emulator, 0); a ^= b; break;
		case ADD: emulator__tick(emulator, 1); wr = a + b; a = wr; reg[EX] = wr >> 16; break;
	}
}

int emulator_create(Emulator* emulator)
{
	return 0;	
}

void emulator_run(Emulator* emulator)
{
	while (true) {
		emulator__op(emulator);	
	}	
}

void emulator_destroy(Emulator* emulator)
{
	return;
}

int main(void)
{
	return 0;	
}
