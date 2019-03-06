
#ifndef CPU_DATATYPES_H
#define CPU_DATATYPES_H


#define bool8 unsigned char
#define Uint8 unsigned char


#define Uint32 unsigned int

#define int32 long int
#define int8 char
#define int16 int
#define Uint16 int
#define float32 float

#define NULL_PTR (void*)0


#define TRUE 1
#define FALSE 0

#define DEBUG


#define get_word(FirstValue, SecondValue) (FirstValue << 8u | SecondValue)

#endif //CPU_DATATYPES_H
