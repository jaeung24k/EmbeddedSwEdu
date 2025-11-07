/*
 * adc.c
 *
 *  Created on: 2023. 7. 21.
 *      Author: bolta
 */

#include "HYUNDAI_RESKILL.h"


void VADC_G4CH7_sampling(void) {
    VADC_G4_QINR0.U |= 0x07;                    // no. of Request Channel = 7

    VADC_G4_QMR0.U |= 0x1 << TREV_BIT_LSB_IDX;  // Generate Conversion Start Trigger Event
}
unsigned int VADC_G4CH7_read(void){
    unsigned int result;

    while( (VADC_G4_RES0.U & (0x1 << VF_BIT_LSB_IDX)) == 0 );   // wait until read available
    result = VADC_G4_RES0.U & (0xFFF << RESULT_BIT_LSB_IDX);    // read ADC value

    return result;
}


void vadc_clock_enable(void) {
    VADC_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable VADC
}
void vadc_clock_enable_wait(void) {
    // VADC configurations
    while((VADC_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0); // wait until VADC module enabled
}

void vadc_g4_ch7_config(unsigned char PRIO, unsigned char SM, unsigned char CLASS) {

    // priority
    VADC_G4_ARBPR.U &= ~(0x3 << PRIO0_BIT_LSB_IDX);
    VADC_G4_ARBPR.U |=  PRIO << PRIO0_BIT_LSB_IDX;

    // start mode
    VADC_G4_ARBPR.U &= ~(0x1 << CSM0_BIT_LSB_IDX);
    VADC_G4_ARBPR.U |=    SM << CSM0_BIT_LSB_IDX;

    // enable
    VADC_G4_ARBPR.U |=   0x1 << ASEN0_BIT_LSB_IDX;
    VADC_G4_QMR0.U  &= ~(0x3 << ENGT_BIT_LSB_IDX);
    VADC_G4_QMR0.U  |=   0x1 << ENGT_BIT_LSB_IDX;

    // flush
    VADC_G4_QMR0.U  |=   0x1 << FLUSH_BIT_LSB_IDX;

    // normal operation
    VADC_G4_ARBCFG.U |=  0x3 << ANONC_BIT_LSB_IDX;

    // class (12bit, 10bit, 8bit)
    VADC_G4_ICLASS0.U &= ~(0x7 << CMS_BIT_LSB_IDX);
    VADC_G4_ICLASS0.U |= CLASS << CMS_BIT_LSB_IDX;

    // VADC Group 4 Channel 7 configuration
    VADC_G4_CHCTR7.U |=   0x1 << RESPOS_BIT_LSB_IDX;    // result right-aligned
    VADC_G4_CHCTR7.U &= ~(0xF << RESREG_BIT_LSB_IDX);   // store result @ Result Register G4RES0
    VADC_G4_CHCTR7.U &= ~(0x3 << ICLSEL_BIT_LSB_IDX);   // Class 0
}

void g4_ch7_connect_to_vadc(void) {
    VADC_G4_CHASS.U |= 0x1 << ASSCH7_BIT_LSB_IDX;
}
