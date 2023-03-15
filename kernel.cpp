/*
    NOTE: No libraries can be used at this point in the app
*/
#include "types.h"

void m_printf(char* cstr)
{
    uint16_t * VIDEO_MEMORY = (uint16_t*)0xb8000;
    for (int i = 0; cstr[i] != '\0' ; ++i)
        VIDEO_MEMORY[i] = (VIDEO_MEMORY[i] & 0xFF00) | cstr[i];
        //Refer Video https://www.youtube.com/watch?v=1rnA6wpF0o4&list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M&index=1;
}

typedef void(*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor* i = &start_ctors;i != &end_ctors; ++i)
    {
        (*i)();
    }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t magicNum)
{
    m_printf((char*)"Hello World v1.0.1");
    
    while(1);
}