#ifndef DISPLAY_H
#define DISPLAY_H

#include "Stop.h"
#include <memory>

class Display 
{
public:
    // Display();
    void update(std::shared_ptr<Stop> stop);  // Refresh and display latest stop info

private:

};

#endif // DISPLAY_H
