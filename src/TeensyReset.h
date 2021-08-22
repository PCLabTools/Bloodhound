/*************************************************************************
    File        : TeensyReset.h
    Description : Provides software reset capability on the Teensy 3.x boards
*************************************************************************/

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

/*************************************************************************
    End of File : TeensyReset.h
*************************************************************************/