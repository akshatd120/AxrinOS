/*
    NOTE: No libraries can be used at this point in the app
*/
#include "types.h"

void clearScr(){
    uint16_t* VIDEO_MEMORY = (uint16_t*)0xb8000;
    for(int i = 0;i < 80 * 25; ++i)
    {
        VIDEO_MEMORY[i] = 0;
    }
}

void m_printf(char* cstr, uint8_t color = 0x07)
{
    uint16_t* VIDEO_MEMORY = (uint16_t*)0xb8000;
    static uint8_t x = 0;
    static uint8_t y = 0;
    for (int i = 0; cstr[i] != '\0' ; ++i){
        
        VIDEO_MEMORY[y * 80 + x] = ((uint16_t)color << 8) | cstr[i];
        if(cstr[i] == '\n' || x >= 80) {
            y += 1;
            x = 0;
        }
    }
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
    clearScr();
    m_printf((char*)"OS INFO: Axrin OS v1.2\n");
    
    while(1);
}
