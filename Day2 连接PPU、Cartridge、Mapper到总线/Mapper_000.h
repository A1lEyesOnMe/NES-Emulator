#pragma once
#include "Mapper.h"

class Mapper_000 : public Mapper
{
public:
    Mapper_000(uint8_t prgBanks,uint8_t chrBanks);
    ~Mapper_000();

public:
    virtual bool cpuMapRead(uint16_t addr, uint32_t& mapper_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t& mapper_addr) = 0;

    virtual bool ppuMapRead(uint16_t addr, uint32_t& mapper_addr) = 0;
    virtual bool ppuMapWrite(uint16_t addr, uint32_t& mapper_addr) = 0;


};