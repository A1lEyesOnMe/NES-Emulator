#include "Mos6502.h"
#include "Bus.h"

Mos6502::Mos6502()
{
    using a = Mos6502;
    lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
};

Mos6502::~Mos6502()
{
    
}

//Bus Connect
uint8_t Mos6502::read(uint16_t a)
{
	return bus->read(a,false);
}

void Mos6502::write(uint16_t a ,uint8_t d)
{
	bus->write(a,d);
}



//Flag
uint8_t Mos6502::GetFlag(FLAGS6502 f)
{
	return ((status& f) > 0) ? 1 : 0;
}

void Mos6502::SetFlag(FLAGS6502 f, bool v)
{
	if(v)
		status |= f;
	else 
		status &= ~f;
}

//6502 Funtion
void Mos6502::reset()
{
	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) or lo;

	a = 0;
	x = 0;
	stkp = 0xFD;
	status = 0x00 or U;

	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 0;

}

void Mos6502::irq()
{
	if(GetFlag(I) == 0)
	{
		write(0x0100 + stkp,(pc >> 8) & 0x00FF);
		stkp--;
		write(0x0100 + stkp, pc & 0x00FF);
		stkp--;

		SetFlag(B,0);
		SetFlag(U,1);
		SetFlag(I,1);
		write(0x0100+ stkp,status);
		stkp--;

		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) or lo;

		cycles =7;
	}
}

void Mos6502::nmi()
{
	write(0x100 + stkp,(pc >>8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp, pc & 0x00FF);
	stkp--;

	SetFlag(B,0);
	SetFlag(U,1);
	SetFlag(I,1);
	write(0x0100+ stkp,status);
	stkp--;

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) or lo;

	cycles =8;
}

void Mos6502::clock()
{
	if(cycles == 0)
	{
		opcode = read(pc);
		
		SetFlag(U,true);
		pc++;
		cycles = lookup[opcode].cycles;

		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

		cycles += (additional_cycle1 & additional_cycle2);

		SetFlag(U,true);

	}

	clock_count++;
	cycles--;

}



// Address Mode

uint8_t Mos6502::fetch()
{
	if(!(lookup[opcode].addrmode == &Mos6502::IMP))
		fetched = read(addr_abs);
	return fetched;
}



uint8_t Mos6502::IMP()
{
	fetched = a;
	return 0;
}

uint8_t Mos6502::IMM()
{
	addr_abs =pc++;
	return 0;
}

uint8_t Mos6502::ZP0()
{
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Mos6502::ZPX()
{
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Mos6502::ZPY()
{
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Mos6502::REL()
{
	addr_rel = read(pc);
	pc++;
	if(addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

uint8_t Mos6502::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t Mos6502::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Mos6502::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Mos6502::IND()
{
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if(ptr_lo == 0x00FF) //hardware bug
	{
		addr_abs = (read(ptr & 0xFF00) << 8  | read(ptr + 0));
	}

	return 0;
}

uint8_t Mos6502::IZX()
{
	uint16_t t = read(pc);
	pc++;

	// kind wried 
	decltype(t) lo = read((uint16_t)(t + (uint16_t)x &0x00FF));
	// uint16_t lo = read((uint16_t)(t + (uint16_t)x &0x00FF));
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) &0x00FF);
	
	addr_abs = (hi << 8 ) | lo;
	return 0;

}

uint8_t Mos6502::IZY()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if((addr_abs & 0xFF00) != (hi <<8))
		return 1;
	else
		return 0;
}



// Instruction
//
//
//
//This funtion captures illegal opcodes
uint8_t Mos6502::XXX()
{
	return 0;
}


// Instruction: Add with Carry In
// Function:    A = A + M + C
// Flags Out:   C, V, N, Z
uint8_t Mos6502::ADC()
{
	fetch();

	temp = (uint16_t)a + (uint16_t)fetched +(uint16_t)GetFlag(C);
	SetFlag(C,temp >255);
	
	SetFlag(Z,(temp & 0x00FF) == 0);

	// Overflow
	SetFlag(V,(~(uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^(uint16_t)temp) & 0x0080);

	SetFlag(N,temp & 0x80);

	a = temp & 0x00FF;

	return 1;
}

// Instruction: Subtraction with Borrow In
// Function:    A = A - M - (1 - C)
// Flags Out:   C, V, N, Z
uint8_t Mos6502::SBC()
{
	fetch();
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;

	temp = (uint16_t)a + value +(uint16_t)GetFlag(C);
	SetFlag(C,temp & 0xFF00);
	SetFlag(Z,((temp & 0x00FF) == 0));
	SetFlag(V,(temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
	SetFlag(N,temp & 0x0080);
	a = temp & 0x00FF;
	return 1;

}

// Instruction: Bitwise Logic AND
// Function:    A = A & M
// Flags Out:   N, Z
uint8_t Mos6502::AND()
{
	fetch();
	a = a & fetched;
	SetFlag(Z,a ==0x00);
	SetFlag(N,a & 0x80);
	return 1;
}

// Instruction: Arithmetic Shift Left
// Function:    A = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
uint8_t Mos6502::ASL()
{
	fetch();
	temp = (uint16_t)fetched <<1;
	SetFlag(C,(temp & 0xFF00) > 0);
	SetFlag(Z,(temp & 0x00FF) == 0x00);
	SetFlag(N,temp & 0x80);
	if(lookup[opcode].addrmode == &Mos6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs,temp & 0x00FF);
	return 0;
}

// Instruction: Branch if Carry Clear
// Function:    if(C == 0) pc = address 
uint8_t Mos6502::BCC()
{
	if(GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}


// Instruction: Branch if Carry Set
// Function:    if(C == 1) pc = address
uint8_t Mos6502::BCS()
{
	if(GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Branch if Equal
// Function:    if(Z == 1) pc = address
uint8_t Mos6502::BEQ()
{
	if(GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

uint8_t Mos6502::BIT()
{
	fetch();
	temp = a & fetched;
	SetFlag(Z,(temp & 0x00FF) == 0x00);
	SetFlag(N,fetched & (1 << 7));
	SetFlag(V,fetched & (1 << 6));
	return 0;
}

// Instruction: Branch if Negative
// Function:    if(N == 1) pc = address
uint8_t Mos6502::BMI()
{
	if(GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Branch if Not Equal
// Function:    if(Z == 0) pc = address
uint8_t Mos6502::BNE()
{
	if(GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Branch if Positive
// Function:    if(N == 0) pc = address
uint8_t Mos6502::BPL()
{
	if(GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Break
// Function:    Program Sourced Interrupt
uint8_t Mos6502::BRK()
{
	pc++;
	SetFlag(I,1);
	write(0x0100 + stkp,(pc >> 8) & 0x00FF);
	stkp--;
	write(0x0100 + stkp,pc & 0x00FF);
	stkp--;

	SetFlag(B,1);
	write(0x0100 + stkp,status);
	stkp--;
	SetFlag(B,0);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

// Instruction: Branch if Overflow Clear
// Function:    if(V == 0) pc = address
uint8_t Mos6502::BVC()
{
	if(GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Branch if Overflow Set
// Function:    if(V == 1) pc = address
uint8_t Mos6502::BVS()
{
	if(GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		pc =addr_abs;
	}
	return 0;
}

// Instruction: Clear Carry Flag
// Function:    C = 0
uint8_t Mos6502::CLC()
{
	SetFlag(C,false);
	return 0;
}

// Instruction: Clear Decimal Flag
// Function:    D = 0
uint8_t Mos6502::CLD()
{
	SetFlag(D,false);
	return 0;
}

// Instruction: Disable Interrupts / Clear Interrupt Flag
// Function:    I = 0
uint8_t Mos6502::CLI()
{
	SetFlag(D,false);
	return 0;
}

// Instruction: Clear Overflow Flag
// Function:    V = 0
uint8_t Mos6502::CLV()
{
	SetFlag(V, false);
	return 0;
}

// Instruction: Compare Accumulator
// Function:    C <- A >= M      Z <- (A - M) == 0
// Flags Out:   N, C, Z
uint8_t Mos6502::CMP()
{
	fetch();
	temp = (uint16_t)a - (uint16_t)fetched;
	SetFlag(C, a >=fetched);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	return 1;
}

// Instruction: Compare X Register
// Function:    C <- X >= M      Z <- (X - M) == 0
// Flags Out:   N, C, Z
uint8_t Mos6502::CPX()
{
	fetch();
	temp = (uint16_t)x - (uint16_t)fetched;
	SetFlag(C, x >=fetched);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	return 1;
}

// Instruction: Compare Y Register
// Function:    C <- Y >= M      Z <- (Y - M) == 0
// Flags Out:   N, C, Z
uint8_t Mos6502::CPY()
{
	fetch();
	temp = (uint16_t)y - (uint16_t)fetched;
	SetFlag(C, y >=fetched);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	return 1;
}

// Instruction: Decrement Value at Memory Location
// Function:    M = M - 1
// Flags Out:   N, Z
uint8_t Mos6502::DEC()
{
	fetch();
	temp = fetched -1;
	write(addr_abs,temp & 0x00FF);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);

	return 0;
}

// Instruction: Decrement X Register
// Function:    X = X - 1
// Flags Out:   N, Z
uint8_t Mos6502::DEX()
{
	x--;
	SetFlag(Z,x == 0x00);
	SetFlag(N,x & 0x80);

	return 0;
}

// Instruction: Decrement Y Register
// Function:    Y = Y - 1
// Flags Out:   N, Z
uint8_t Mos6502::DEY()
{
	y--;
	SetFlag(Z,y == 0x00);
	SetFlag(N,y & 0x80);

	return 0;
}

// Instruction: Bitwise Logic XOR
// Function:    A = A xor M
// Flags Out:   N, Z
uint8_t Mos6502::EOR()
{
	fetch();
	a = a ^ fetched;
	SetFlag(Z,a == 0x00);
	SetFlag(N,a & 0x80);
	return 1;
}

// Instruction: Increment Value at Memory Location
// Function:    M = M + 1
// Flags Out:   N, Z
uint8_t Mos6502::INC()
{
	fetch();
	temp = fetched +1;
	write(addr_abs,temp & 0x00FF);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	return 0;
}

// Instruction: Increment X Register
// Function:    X = X + 1
// Flags Out:   N, Z
uint8_t Mos6502::INX()
{
	x++;
	SetFlag(N,x = 0x00);
	SetFlag(Z,x & 0x80);
	return 0;
}

// Instruction: Increment Y Register
// Function:    Y = Y + 1
// Flags Out:   N, Z
uint8_t Mos6502::INY()
{
	y++;
	SetFlag(N,y = 0x00);
	SetFlag(Z,y & 0x80);
	return 0;
}

// Instruction: Jump To Location
// Function:    pc = address
uint8_t Mos6502::JMP()
{
	pc = addr_abs;
	return 0;
}


// Instruction: Jump To Sub-Routine
// Function:    Push current pc to stack, pc = address
uint8_t Mos6502::JSR()
{
	pc--;
	write(0x100 + stkp,(pc >> 8) & 0x00FF);
	stkp--;
	write(0x100 + stkp, pc & 0x00FF);
	stkp--;

	pc =addr_abs;
	return 0;
}

// Instruction: Load The Accumulator
// Function:    A = M
// Flags Out:   N, Z
uint8_t Mos6502::LDA()
{
	fetch();
	a = fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

// Instruction: Load The X Register
// Function:    X = M
// Flags Out:   N, Z
uint8_t Mos6502::LDX()
{
	fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 1;
}

// Instruction: Load The Y Register
// Function:    Y = M
// Flags Out:   N, Z
uint8_t Mos6502::LDY()
{
	fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 1;
}

uint8_t Mos6502::LSR()
{
	fetch();
	SetFlag(C,fetched & 0x0001);
	temp = fetched >>1;
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	if(lookup[opcode].addrmode == &Mos6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs,temp & 0x00FF);
	return 0;
}

uint8_t Mos6502::NOP()
{
	switch(opcode){
		case 0x1C:
		case 0x3C:
		case 0x5C:
		case 0x7C:
		case 0xDC:
		case 0xFC:
				return 1;
				break;
	}
	return 0;
}

// Instruction: Bitwise Logic OR
// Function:    A = A | M
// Flags Out:   N, Z
uint8_t Mos6502::ORA()
{
	fetch();
	a = a | fetched;
	SetFlag(Z,a == 0x00);
	SetFlag(N,a & 0x80);

	return 1;
}

// Instruction: Push Accumulator to Stack
// Function:    A -> stack
uint8_t Mos6502::PHA()
{
	write(0x0100 + stkp, a);
	stkp--;
	return 0;
}

// Instruction: Push Status Register to Stack
// Function:    status -> stack
// Note:        Break flag is set to 1 before push
uint8_t Mos6502::PHP()
{
	write(0x0100 + stkp,status | B | U);
	SetFlag(B,0);
	SetFlag(U,0);
	stkp--;
	return 0;
}

// Instruction: Pop Accumulator off Stack
// Function:    A <- stack
// Flags Out:   N, Z
uint8_t Mos6502::PLA() //我超！！ PLA！
{
	stkp++;
	a = read(0x0100 + stkp);
	SetFlag(Z,a == 0x00);
	SetFlag(N,a & 0x80);
	return 0;
}

// Instruction: Pop Status Register off Stack
// Function:    Status <- stack
uint8_t Mos6502::PLP()
{
	stkp++;
	status = read(0x0100 + stkp);
	SetFlag(U,1);
	return 0;
}

uint8_t Mos6502::ROL()
{
	fetch();
	temp = (uint16_t)(fetched << 1) | GetFlag(C);
	SetFlag(C,temp & 0xFF00);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	if (lookup[opcode].addrmode == &Mos6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Mos6502::ROR()
{
	fetch();
	temp = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1);
	SetFlag(C,fetched & 0x01);
	SetFlag(Z,(temp & 0x00FF) == 0x0000);
	SetFlag(N,temp & 0x0080);
	if (lookup[opcode].addrmode == &Mos6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}


uint8_t Mos6502::RTI()
{
	stkp++;
	status = read(0x0100 + stkp);
	status &= ~B;
	status &= ~U;

	stkp++;
	pc = (uint16_t)read(0x0100 + stkp);
	stkp++;
	pc |= (uint16_t)read(0x0100 + stkp) << 8;
	return 0;
}

uint8_t Mos6502::RTS()
{
	stkp++;
	pc = (uint16_t)read(0x0100 + stkp);
	stkp++;
	pc |= (uint16_t)read(0x0100 + stkp) << 8;
	pc++;
	return 0;

}

// Instruction: Set Carry Flag
// Function:    C = 1
uint8_t Mos6502::SEC()
{
	SetFlag(C,true);
	return 0;
}

// Instruction: Set Decimal Flag
// Function:    D = 1
uint8_t Mos6502::SED()
{
	SetFlag(C,true);
	return 0;
}

// Instruction: Set Interrrupt Flag
// Function:    I = 1
uint8_t Mos6502::SEI()
{
	SetFlag(I,true);
	return 0;
}

// Instruction: Store Accumulator at Address
// Function:    M = A
uint8_t Mos6502::STA()
{
	write(addr_abs,a);
	return 0;
}

// Instruction: Store X Register at Address
// Function:    M = X
uint8_t Mos6502::STX()
{
	write(addr_abs,x);
	return 0;
}

// Instruction: Store Y Register at Address
// Function:    M = Y
uint8_t Mos6502::STY()
{
	write(addr_abs,y);
	return 0;
}

// Instruction: Transfer Accumulator to X Register
// Function:    X = A
// Flags Out:   N, Z
uint8_t Mos6502::TAX()
{
	x = a;
	SetFlag(Z,x = 0x00);
	SetFlag(N,x & 0x80);
	return 0;
}

// Instruction: Transfer Accumulator to Y Register
// Function:    Y = A
// Flags Out:   N, Z
uint8_t Mos6502::TAY()
{
	y = a;
	SetFlag(Z,y = 0x00);
	SetFlag(N,y & 0x80);
	return 0;
}

// Instruction: Transfer Stack Pointer to X Register
// Function:    X = stack pointer
// Flags Out:   N, Z
uint8_t Mos6502::TSX()
{
	x = stkp;
	SetFlag(Z,x = 0x00);
	SetFlag(N,x & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Accumulator
// Function:    A = X
// Flags Out:   N, Z
uint8_t Mos6502::TXA()
{
	a =  x;
	SetFlag(Z,a = 0x00);
	SetFlag(N,a & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Stack Pointer
// Function:    stack pointer = X
uint8_t Mos6502::TXS()
{
	stkp =x;
	return 0;
}

// Instruction: Transfer Y Register to Accumulator
// Function:    A = Y
// Flags Out:   N, Z
uint8_t Mos6502::TYA()
{
	a =  y;
	SetFlag(Z,a = 0x00);
	SetFlag(N,a & 0x80);
	return 0;
}

/////////////////////////////////////////////
// I dont get it.
bool Mos6502::complete()
{
	return cycles ==0;
}


