/*
 * gpio.c
 *
 *  Created on: 2023. 7. 21.
 *      Author: bolta
 */

#include "HYUNDAI_RESKILL.h"

void swdelay(unsigned int count) {
    for(unsigned int i = 0; i < count; i++); // sw delay
}

void  p10_1_out_mode(void) {
    // set P10.1 push-pull general output
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P10_IOCR0.U |=   0x10 << PC1_BIT_LSB_IDX;
  //P10_IOCR0.B.PC1 = 0x10;
}

void  p10_1_pwm_mode(void) {
    // set P10.1 pwm output mode
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P10_IOCR0.U |=   0x11 << PC1_BIT_LSB_IDX;
}

void  p10_2_out_mode(void) {
    // set P10.2 push-pull general output
    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);
    P10_IOCR0.U |=   0x10 << PC2_BIT_LSB_IDX;
  //P10_IOCR0.B.PC2 = 0x10;
}

void p02_1_in_mode(void ) {
    // p02.1 input mode
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;
}

unsigned char read_port   (unsigned char group, unsigned char pin) {
    if(group == 2 && pin == 1) {
        unsigned char val = P02_IN.U & (0x1 << P1_BIT_LSB_IDX);
        if(val == 2)
            return 1;
        else
            return 0;
    } else if(group == 2 && pin == 0) {
        unsigned char val = P02_IN.U & (0x1 << P0_BIT_LSB_IDX);
        if(val == 1)
            return 1;
        else
            return 0;
    } else if(group == 0 && pin == 4) {
        unsigned char val = P00_IN.U & (0x1 << P4_BIT_LSB_IDX);
        if(val == 16)
            return 1;
        else
            return 0;
    } else {
        return 0;
    }
}

unsigned char read_switch2() {
    return read_port(2, 1);
}
unsigned char read_switch1() {
    return read_port(2, 0);
}

void toggle_red_led(void) {
    P10_OUT.U ^= (0x1 << P1_BIT_LSB_IDX);       // toggle P10.1 (LED D13 RED)
}
void toggle_blue_led(void) {
    P10_OUT.U ^= (0x1 << P2_BIT_LSB_IDX);       // toggle P10.2 (LED D13 BLUE)
}

void on_red_led(void) {
    P10_OUT.U |= (0x1 << P1_BIT_LSB_IDX);       // set P10.1 (LED D13 RED)
}
void on_blue_led(void) {
    P10_OUT.U |= (0x1 << P2_BIT_LSB_IDX);       // set P10.2 (LED D13 BLUE)
}

void off_red_led(void) {
    P10_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX);       // clear P10.1 (LED D13 RED)
}
void off_blue_led(void) {
    P10_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX);       // clear P10.2 (LED D13 BLUE)
}

// P02.7 --> red led on RGB led
void p02_7_out_mode() {
    // set Port as general purpose output (push-pull)
    P02_IOCR4.U &= ~(0x1F << PC7_BIT_LSB_IDX);
    P02_IOCR4.U |=   0x10 << PC7_BIT_LSB_IDX;
}

// P10.5 --> green led on RGB led
void p10_5_out_mode() {
    P10_IOCR4.U &= ~(0x1F << PC5_BIT_LSB_IDX);
    P10_IOCR4.U |=   0x10 << PC5_BIT_LSB_IDX;
}

// P10.3 --> blue led on RGB led
void p10_3_out_mode() {
    P10_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);
    P10_IOCR0.U |=   0x10 << PC3_BIT_LSB_IDX;
}

// RED on RGB led
void on_rgb_red (void) {
    P02_OUT.U |=   0x1 << P7_BIT_LSB_IDX;
    P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
    P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);
}

// GREEN on RGB led
void on_rgb_green (void) {
    P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    P10_OUT.U |=   0x1 << P5_BIT_LSB_IDX;
    P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);
}

// BLUE on RGB led
void on_rgb_blue (void) {
    P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
    P10_OUT.U |=   0x1 << P3_BIT_LSB_IDX;
}

// WHITE on RGB led
void on_rgb_white (void) {
    P02_OUT.U |=   0x1 << P7_BIT_LSB_IDX;
    P10_OUT.U |=   0x1 << P5_BIT_LSB_IDX;
    P10_OUT.U |=   0x1 << P3_BIT_LSB_IDX;
}

void p02_6_out_mode(void) {
    // TRIG output
    P02_IOCR4.U &= ~(0x1F << PC6_BIT_LSB_IDX);
    P02_IOCR4.U |=   0x10 << PC6_BIT_LSB_IDX;
}


void p00_4_in_mode(void) {
    // ECHO input
    P00_IOCR4.U &= ~(0x1F << PC4_BIT_LSB_IDX);
    P00_IOCR4.U |=   0x01 << PC4_BIT_LSB_IDX;
}

void p02_6_out_clear(void) {
    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX);
}

void p02_6_out_set(void) {
    P02_OUT.U |= 0x1 << P6_BIT_LSB_IDX;
}

