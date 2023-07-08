#include "Bus.h"


Bus::Bus()
{
	for (auto& i : ram)i = 0x0;

	cpu.connectBus(this);
}

Bus::~Bus()
{

}

void Bus::write(uint16_t addr, uint8_t data)
{	
	if (addr >=0x0000 && addr <= 0xffff)
		ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly) 
{
	if (addr >= 0x0000 && addr <= 0xffff)
		return ram[addr] ;
	return 0;
}