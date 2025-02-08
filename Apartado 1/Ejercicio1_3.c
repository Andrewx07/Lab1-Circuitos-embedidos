#include <stdint.h>

typedef enum//fixed from class
{
    Touch = 0x01;
    Gravity = 0x02;
    inactivity = 0x03;
    double_tap = 0x04;

}interruptions;


typedef struct ITEM{
    interruptions interrupt;
    
}item;