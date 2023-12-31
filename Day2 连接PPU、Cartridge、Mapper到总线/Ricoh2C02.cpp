#include "Ricoh2C02.h"

Ricoh2c02::Ricoh2c02()
{

}

Ricoh2c02::~Ricoh2c02()
{

}

void Ricoh2c02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
    this->cart = cartridge;
}

uint8_t Ricoh2c02::cpuRead(uint16_t addr,bool rdonly)
{
    uint8_t data = 0x00;

	switch (addr)
	{
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}

	return data;
}
void Ricoh2c02::cpuWrite(uint16_t addr, uint8_t  data){
	switch (addr)
	{
	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		break;
	}
}

uint8_t Ricoh2c02::ppuRead(uint16_t addr, bool rdonly)
{
    uint8_t data = 0x00;
    addr &= 0x3FFF;
    if(cart->ppuWrite(addr,data))
    {

    }
    return data;
}

void Ricoh2c02::ppuWrite(uint16_t addr,uint8_t data)
{
    addr &= 0x3FFF;
    if(cart->ppuWrite(addr,data))
    {

    }
}

void Ricoh2c02::clock()
{
    cycle++;
	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}