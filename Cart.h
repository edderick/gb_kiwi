#ifndef CART_H
#define CART_H

#include <string> 
#include <vector>

namespace gbemu {

class Cartridge {
    private:
        // PRIVATE DATA
        std::vector<unsigned char> d_rom;

    public:
        // PUBLIC ACCESSORS
        unsigned int size() const;
        unsigned char& operator[](unsigned int i);
        const unsigned char& operator[](unsigned int i) const;

        bool check_graphic() const;
        std::string get_title() const;
        bool is_color() const;

        unsigned char get_type() const;
        unsigned char get_rom_size_code() const;
        unsigned char get_ram_size_code() const;

    public:
        // PUBLIC MANIPULATORS
        void load_rom(const std::string &filename);
};

// ===========================================================================
//                      Inline function definitions
// ===========================================================================

inline
unsigned int Cartridge::size() const {
    return d_rom.size();
}

} // Close Namespace gbemu

#endif
