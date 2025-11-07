/*
 * timer.c
 *
 *  Created on: 2023. 7. 21.
 *      Author: bolta
 */


#include "HYUNDAI_RESKILL.h"


void ccu60_int_config(unsigned char ID, unsigned char cpu_no) {
    // setting interrupt service ID
    SRC_CCU6_CCU60_SR0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR0.U |=   ID << SRPN_BIT_LSB_IDX;

    // allocating CPU0 for T12 PM interrupt
    SRC_CCU6_CCU60_SR0.U &= ~(0x3 << TOS_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR0.U |= cpu_no << TOS_BIT_LSB_IDX;

    // ISR call enable
    SRC_CCU6_CCU60_SR0.U |= 0x1 << SRE_BIT_LSB_IDX;
}


void ccu60_clock_enable() {
    CCU60_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable CCY
}

void ccu60_clock_enable_wait() {
    while((CCU60_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0);
}


// div1: 0 --> 1/1
//       1 --> 1/2
//       2 --> 1/4
//       ...
// div2: 1 --> 1/256
//       0 --> bypass
//
// ctm : 0 --> edge aligned mode
//       1 --> center aligned mode (counter decrement after period match)
void ccu60_clock_config(unsigned char div1, unsigned char div2, unsigned char ctm) {

    CCU60_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX);
    CCU60_TCTR0.U |=  div1 << T12CLK_BIT_LSB_IDX;

    CCU60_TCTR0.U &=  ~(0x1 << T12PRE_BIT_LSB_IDX);
    CCU60_TCTR0.U |=   div2 << T12PRE_BIT_LSB_IDX;

    CCU60_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX);
    CCU60_TCTR0.U |=   ctm << CTM_BIT_LSB_IDX;

}

void ccu60_period_config(unsigned short N) {
    // timer clock: F Hz, --> period match interrupt happens after 1/F * N
    CCU60_T12PR.U = N - 1;

    // transfer period match value from shadow register
    CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;
}

void ccu60_single_shot_mode() {
    // Single Shot Control
    CCU60_TCTR2.B.T12SSC = 0x1;
}

void ccu60_counter_clear() {
    // clear counter value on T12
    CCU60_T12.U = 0;
}

void ccu60_connect_to_cpu(unsigned char SR) {
    // timer counter value clear
    CCU60_T12.U = 0;

    // using SR0, to report interrupt to cpu
    CCU60_INP.U &= ~(0x3 << INPT12_BIT_LSB_IDX);
    CCU60_INP.U |=    SR << INPT12_BIT_LSB_IDX;

    // transfer timer interrupt to CPU ISR()
    CCU60_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX;
}

void ccu60_t12_start(void) {
    CCU60_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;
}




void ccu61_clock_enable() {
    CCU61_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable CCY
}

void ccu61_clock_enable_wait() {
    while((CCU61_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0);
}


// div1: 0 --> 1/1
//       1 --> 1/2
//       2 --> 1/4
//       ...
// div2: 1 --> 1/256
//       0 --> bypass
//
// ctm : 0 --> edge aligned mode
//       1 --> center aligned mode (counter decrement after period match)
void ccu61_clock_config(unsigned char div1, unsigned char div2, unsigned char ctm) {

    CCU61_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX);
    CCU61_TCTR0.U |=  div1 << T12CLK_BIT_LSB_IDX;

    CCU61_TCTR0.U &=  ~(0x1 << T12PRE_BIT_LSB_IDX);
    CCU61_TCTR0.U |=   div2 << T12PRE_BIT_LSB_IDX;

    // Edge Aligned Mode (Restart timer after Period Match)
    CCU61_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX);
    CCU61_TCTR0.U |=   ctm << CTM_BIT_LSB_IDX;

}

void ccu61_period_config(unsigned short N) {
    // timer clock: F Hz, --> period match interrupt happens after 1/F * N
    CCU61_T12PR.U = N - 1;

    // transfer period match value from shadow register
    CCU61_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;
}

void ccu61_counter_clear() {
    // clear counter value on T12
    CCU61_T12.U = 0;
}

void ccu61_counter_reset() {
    CCU61_TCTR4.B.T12RES = 0x1;       // reset CCU61 T12 counter
}

void ccu61_t12_start(void) {
    CCU61_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;
}

void ccu61_t12_stop(void) {
    CCU61_TCTR4.B.T12RR = 0x1;
}
