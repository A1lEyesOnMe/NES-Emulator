#include "Bus.h"

Bus::Bus(){

    cpu.ConnectBus(this);
}

Bus::~Bus()
{
}


void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	// Connects cartridge to both Main Bus and CPU Bus
	this->cart = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::cpuWrite(uint16_t addr,uint8_t data){
    if(cart->cpuWrite(addr,data))

    if(addr >= 0x0000 && addr <<0x1FFF)
        cpuRam[addr & 0x7FF] = data;

    else if( addr >= 0x2000 && addr  <= 0x3FFF)
        ppu.cpuWrite(addr & 0x7FF, data);
}

uint8_t Bus::cpuRead(uint16_t addr,bool bReadOnly){
    uint8_t data =0x00;
    if (cart->cpuRead(addr, data))

	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		
		data = cpuRam[addr & 0x07FF];
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		data = ppu.cpuRead(addr & 0x0007, bReadOnly);
	}

	return data;
}


void Bus::reset(){
    cpu.reset();
    nSystemClockCounter = 0;
}
void Bus::clock(){
    ppu.clock();
    if (nSystemClockCounter % 3 == 0)
	{
		cpu.clock();
	}

	nSystemClockCounter++;
}