#ifndef BOOTSTRAP_H 
#define BOOTSTRAP_H

#include <vector>

namespace gbemu {

class Bootstrap {
    private:
        // PRIVATE DATA
        std::vector<unsigned char> d_rom;

    private:
        // PRIVATE DATA
        Bootstrap(const Bootstrap &);           // = delete
        Bootstrap operator=(const Bootstrap &); // = delete

    public: 
        // CREATORS
        Bootstrap();

    public:
        // PUBLIC ACCESSORS
        unsigned int size();
        unsigned char& operator[](unsigned int i);
};

} // Close Namespace gbemu

#endif
