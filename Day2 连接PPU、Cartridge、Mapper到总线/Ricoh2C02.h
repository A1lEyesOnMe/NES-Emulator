#pragma once
#include <cstdint>
#include <memory>

#include "Cartridge.h"

class Ricoh2c02
{
public:
    Ricoh2c02();
    ~Ricoh2c02();

private:
    uint8_t tbName[2][1024];
    uint8_t tbPattern[2][4096];
    uint8_t tbPalette[32];

    int16_t scanline =0;
    int16_t cycle = 0;

public:
    bool frame_complete = false;

public:
	// Communications with Main Bus
	uint8_t cpuRead(uint16_t addr, bool rdonly = false);
	void    cpuWrite(uint16_t addr, uint8_t  data);

	// Communications with PPU Bus
	uint8_t ppuRead(uint16_t addr, bool rdonly = false);
	void    ppuWrite(uint16_t addr, uint8_t data);

private:

	std::shared_ptr<Cartridge> cart;

public:
	// Interface
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void clock();
};
