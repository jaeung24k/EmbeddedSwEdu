/*
 * gtm.c
 *
 *  Created on: 2023. 7. 21.
 *      Author: bolta
 */

#include "HYUNDAI_RESKILL.h"

void gtm_clock_enable(void) {

    GTM_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);    // enable GTM

}
void gtm_clock_enable_wait(void) {

    while((GTM_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0); // wait until GTM module enabled

}

// FXCLK 0~15
// 0 is fastest
void gtm_clock(unsigned char FXCLK) {
    // GTM clock configuration
    GTM_CMU_FXCLK_CTRL.U &= ~(0xF   << FXCLK_SEL_BIT_LSB_IDX);
    GTM_CMU_FXCLK_CTRL.U |=   FXCLK << FXCLK_SEL_BIT_LSB_IDX;

    GTM_CMU_CLK_EN.U |= 0x2 << EN_FXCLK_BIT_LSB_IDX;
}

// Timer Output Module 0's CH1
//  SL:  1 --> high pulse
//       0 --> low pulse width
//
// CLK:  0 --> 100MHz
//       1 --> 100MHz/16=6250Khz
//       2 --> 100MHz/256.
//         ...
// OSM   0 --> one shot mode
//       1 --> continuous mode
//
void gtm_tom0_ch1_config(unsigned char SL, unsigned char CLK, unsigned OSM) {
    // GTM TOM0 PWM configuration
    // TOM channel 1 update enable
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL1_BIT_LSB_IDX;

    // enable channel 1 on update trigger
    GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL1_BIT_LSB_IDX;

    // enable channel 1 output on update trigger
    GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL1_BIT_LSB_IDX;

    //  signal level for duty cycle
    GTM_TOM0_CH1_CTRL.U &= ~(0x1 << SL_BIT_LSB_IDX);
    GTM_TOM0_CH1_CTRL.U |=    SL << SL_BIT_LSB_IDX;

    // clock source --> CMU_FXCLK(1) = 3125 kHz
    GTM_TOM0_CH1_CTRL.U &= ~(0x7 << CLK_SRC_SR_BIT_LSB_IDX);
    GTM_TOM0_CH1_CTRL.U |=   CLK << CLK_SRC_SR_BIT_LSB_IDX;

    // continuous mode enable
    GTM_TOM0_CH1_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);
    GTM_TOM0_CH1_CTRL.U |=   OSM << OSM_BIT_LSB_IDX;

    // TRIG[x] = TRIG[x-1]
    GTM_TOM0_CH1_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX);
}


void tom0_ch1_connect_to_p10_1() {
    GTM_TOUTSEL6.U &= ~(0x3 << SEL7_BIT_LSB_IDX);
}

void gtm_tom0_ch1_period_config(unsigned short N) {
    GTM_TOM0_CH1_SR0.U = N;
}

void gtm_tom0_ch1_duty_config(unsigned short N) {
    GTM_TOM0_CH1_SR1.U = N;
}

// gtm start
void gtm_tom0_trigger() {
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;
}

