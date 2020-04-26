#include "memory_map.h"


MemoryMap::MemoryMap() {
    // 32 kB Cartridge ROM Bank #0
    m_address_space[0] = 0x0000;
    // 32 kB Cartridge Switchable ROM Bank
    m_address_space[1] = 0x4000;
    // Video RAM
    m_address_space[2] = 0x8000;
    // Switchable RAM Bank
    m_address_space[3] = 0xA000;
    // Internal RAM
    m_address_space[4] = 0xC000;
    // Echo RAM
    m_address_space[5] = 0xE000;
    // Sprite Attributes
    m_address_space[6] = 0xFE00;
    // Unusable
    m_address_space[7] = 0xFEA0;
    // I/O Ports
    m_address_space[8] = 0xFF00;
    // Unusable
    m_address_space[9] = 0xFF4C;
    // High RAM
    m_address_space[10] = 0xFF80;
    // Interrupt Enable Register
    m_address_space[11] = 0xFFFF;
}

MemoryMap::~MemoryMap() {
    for (int i = 1; i < m_memory_map.size(); i++) {
        delete (Memory *)m_memory_map.find(i)->second;
    }
}

bool MemoryMap::init_memory_map(void *file_parser_buffer) {
    m_memory_map.insert(std::pair<int, void *>(0, file_parser_buffer));

    for (int i = 1; i < 11; i++) {
        Memory *ram = new Memory(m_address_space[i+1] - m_address_space[i]);
        ram->init_memory();
        m_memory_map.insert(std::pair<int, Memory*>(i, ram));
    }

    Memory *io = new Memory(1);
    io->init_memory();
    m_memory_map.insert(std::pair<int, Memory *>(11, io));

    return true;
}

uint16_t MemoryMap::write(uint16_t address, uint8_t data) {
    int index = this->get_index(address);

    switch (index) {
        case 0:
            std::cerr << "Cannot write to ROM" << std::endl;
            throw new std::exception;
        case 5: {
            Memory *mem = (Memory *)m_memory_map.find(index-1)->second;
            return mem->write_memory(address - m_address_space[index], data);
        }
        case 7:
        case 9: {
            std::cerr << "Address space unusable: " << index << ". Address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
        default: {
            Memory *mem = (Memory *)m_memory_map.find(index)->second;
            return mem->write_memory(address - m_address_space[index], data);
        }
    }
}

uint8_t MemoryMap::read(uint16_t address) {
    int index = this->get_index(address);

    switch (index) {
        case 0: {
            uint8_t *rom = (uint8_t *)m_memory_map.find(index)->second;
            return rom[address];
        }
        case 5: {
            Memory *mem = (Memory *)m_memory_map.find(index-1)->second;
            return mem->read_memory(address - m_address_space[index]);
        }
        case 7:
        case 9: {
            std::cerr << "Address space unusable: " << index << ". Address: " << static_cast<int>(address) << std::endl;
            throw new std::exception;
        }
        default: {
            Memory *mem = (Memory *)m_memory_map.find(index)->second;
            return mem->read_memory(address - m_address_space[index]);
        }
    }
}

int MemoryMap::get_index(uint16_t address) const {
    for (int i=0; i<12; i++) {
        if (address < m_address_space[i]) {
            return i-1;
        }
    }

    if (address == 0xFFFF) {
        return 11;
    }

    return -1;
}