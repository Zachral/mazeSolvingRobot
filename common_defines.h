#ifndef _COMMON_DEFINES_H__
#define _COMMON_DEFINES_H__

//This file contains defines relating to bit operations and pin-, ddr-, and port handling. 

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define CON_CAT(a,b)                a ## b
#define DDR_(name)        CON_CAT(DDR,name)
#define PORT_(name)       CON_CAT(PORT,name)
#define PIN_(name)        CON_CAT(PIN,name)
#define BIT_(name)        CON_CAT(BIT,name)

#define LEFT    1
#define RIGHT   2

#endif
