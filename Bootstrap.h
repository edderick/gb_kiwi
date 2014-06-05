#ifndef BOOTSTRAP_H 
#define BOOTSTRAP_H

#include <vector>

using namespace std;
class Bootstrap {
        vector<unsigned char> rom; 
    public: 
        Bootstrap();
        unsigned int size();
        unsigned char& operator[](unsigned int i);
};

#endif
