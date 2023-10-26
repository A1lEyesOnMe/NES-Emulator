#pragma once
#include <cstdint>
#include <array>

#include "Mos6502.h"
#include "Ricoh2C02.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();

	
public: 
	Mos6502 cpu;
	Ricoh2c02 ppu;	

	std::shared_ptr<Cartridge> cart;

	uint32_t nSystemClockCounter = 0;

	uint8_t cpuRam[2048];
	
public: 
	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

public:

	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);

	void reset();

	void clock();
};