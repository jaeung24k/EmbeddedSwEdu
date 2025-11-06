#ifndef DRIVER_H
#define DRIVER_H

// Port registers
#define PC1_BIT_LSB_IDX             11
#define PC2_BIT_LSB_IDX             19
#define P1_BIT_LSB_IDX              1
#define P2_BIT_LSB_IDX              2


// SCU registers
#define LCK_BIT_LSB_IDX             1
#define ENDINIT_BIT_LSB_IDX         0
#define EXIS0_BIT_LSB_IDX           4
#define FEN0_BIT_LSB_IDX            8
#define REN0_BIT_LSB_IDX            9
#define EIEN0_BIT_LSB_IDX           11
#define INP0_BIT_LSB_IDX            12
#define IGP0_BIT_LSB_IDX            14


// SRC registers
#define SRPN_BIT_LSB_IDX            0
#define TOS_BIT_LSB_IDX             11
#define SRE_BIT_LSB_IDX             10


// CCU60 registers
#define DISS_BIT_LSB_IDX            1
#define DISR_BIT_LSB_IDX            0
#define CTM_BIT_LSB_IDX             7
#define T12PRE_BIT_LSB_IDX          3
#define T12CLK_BIT_LSB_IDX          0
#define T12STR_BIT_LSB_IDX          6
#define T12RS_BIT_LSB_IDX           1
#define INPT12_BIT_LSB_IDX          10
#define ENT12PM_BIT_LSB_IDX         7

extern unsigned char AccelPressed;
extern unsigned char BreakPressed;


void initERU();
void initButton(void);

#endif // DRIVER_H