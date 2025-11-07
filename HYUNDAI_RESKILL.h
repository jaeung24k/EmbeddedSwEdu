/*
 * HYUNDAI_RESKILL.h
 *
 *  Created on: 2023. 7. 21.
 *      Author: bolta
 */

#ifndef HYUNDAI_RESKILL_H_
#define HYUNDAI_RESKILL_H_


#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxCcu6_reg.h"
#include "IfxVadc_reg.h"
#include "IfxGtm_reg.h"

// Port registers
#define PC1_BIT_LSB_IDX             11
#define PC2_BIT_LSB_IDX             19
#define PC3_BIT_LSB_IDX             27
#define PC4_BIT_LSB_IDX             3
#define PC5_BIT_LSB_IDX             11
#define PC6_BIT_LSB_IDX             19
#define PC7_BIT_LSB_IDX             27
#define P0_BIT_LSB_IDX              0
#define P1_BIT_LSB_IDX              1
#define P2_BIT_LSB_IDX              2
#define P3_BIT_LSB_IDX              3
#define P4_BIT_LSB_IDX              4
#define P5_BIT_LSB_IDX              5
#define P6_BIT_LSB_IDX              6
#define P7_BIT_LSB_IDX              7

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
#define T12SSC_BIT_LSB_IDX          0

// VADC registers
#define DISS_BIT_LSB_IDX            1
#define DISR_BIT_LSB_IDX            0
#define ANONC_BIT_LSB_IDX           0
#define ASEN0_BIT_LSB_IDX           24
#define CSM0_BIT_LSB_IDX            3
#define PRIO0_BIT_LSB_IDX           0
#define CMS_BIT_LSB_IDX             8
#define FLUSH_BIT_LSB_IDX           10
#define TREV_BIT_LSB_IDX            9
#define ENGT_BIT_LSB_IDX            0
#define RESPOS_BIT_LSB_IDX          21
#define RESREG_BIT_LSB_IDX          16
#define ICLSEL_BIT_LSB_IDX          0
#define VF_BIT_LSB_IDX              31
#define RESULT_BIT_LSB_IDX          0
#define ASSCH7_BIT_LSB_IDX          7

// GTM registers
#define DISS_BIT_LSB_IDX            1
#define DISR_BIT_LSB_IDX            0
#define SEL7_BIT_LSB_IDX            14
#define EN_FXCLK_BIT_LSB_IDX        22
#define FXCLK_SEL_BIT_LSB_IDX       0

// GTM - TOM0 registers
#define UPEN_CTRL1_BIT_LSB_IDX      18
#define HOST_TRIG_BIT_LSB_IDX       0
#define ENDIS_CTRL1_BIT_LSB_IDX     2
#define OUTEN_CTRL1_BIT_LSB_IDX     2
#define CLK_SRC_SR_BIT_LSB_IDX      12
#define OSM_BIT_LSB_IDX             26
#define TRIGOUT_BIT_LSB_IDX         24
#define SL_BIT_LSB_IDX              11
#define RSCNT0_CN1_BIT_LSB_IDX      18
#define FUPD_CTRL1_BIT_LSB_IDX      2

// user API
void          initLED         (void);
void          initButton      (void);
void          initERU_SW2     (void);
void          initERU_ECHO    (void);
void          initCCU60       (void);
void          initRGBLED      (void);
void          VADC_G4CH7_sampling (void);
unsigned int  VADC_G4CH7_read     (void);
void          initVADC_G4CH7  (void);
void          initCCU61       (void);
void          initUSonic      (void);

// PWM dimming for P10.1 (red led)
void          initPWMLED(void); // P10.1 --> PWM output
void          initGTM(void);    // configure GTM (PWM unit)

// gpio
void          swdelay         (unsigned int count);
unsigned char read_port       (unsigned char group, unsigned char pin);
void          p10_1_out_mode  (void);
void          p10_1_pwm_mode  (void);
void          p10_2_out_mode  (void);
void          p02_0_in_mode   (void);
void          p02_1_in_mode   (void);
void          toggle_red_led  (void);
void          toggle_blue_led (void);
void          on_red_led      (void);
void          on_blue_led     (void);
void          off_red_led     (void);
void          off_blue_led    (void);
unsigned char read_switch2    (void);
void          p02_7_out_mode  (void);
void          p10_5_out_mode  (void);
void          p10_3_out_mode  (void);
void          on_rgb_red      (void);
void          on_rgb_green    (void);
void          on_rgb_blue     (void);
void          on_rgb_white    (void);
void          p02_6_out_mode  (void);
void          p00_4_in_mode   (void);
void          p02_6_out_clear (void);
void          p02_6_out_set   (void);

// eru
void          eru0_esr2_input_sel(unsigned char CH);
void          eru0_etl_edge_sel  (unsigned char F_EN, unsigned char R_EN);
void          eru0_ogu0_enable   (void);
void          eru0_int_config    (unsigned char ID, unsigned char cpu_no);
void          eru0_isr_enable    (void);

// scu
void          unlock_scu      (void);
void          lock_scu        (void);

// ccu60
void          ccu60_int_config(unsigned char ID, unsigned char cpu_no);
void          ccu60_clock_enable(void);
void          ccu60_clock_enable_wait(void);
void          ccu60_clock_config(unsigned char div1, unsigned char div2, unsigned char ctm);
void          ccu60_period_config(unsigned short N);
void          ccu60_connect_to_cpu(unsigned char SR);
void          ccu60_t12_start(void);
void          ccu60_single_shot_mode(void);
void          ccu60_counter_clear(void);
void          ccu61_clock_enable(void);
void          ccu61_clock_enable_wait(void);
void          ccu61_clock_config(unsigned char div1, unsigned char div2, unsigned char ctm);
void          ccu61_period_config(unsigned short N);
void          ccu61_counter_clear(void);
void          ccu61_t12_start(void);
void          ccu61_t12_stop(void);
void          ccu61_counter_reset(void);

// vadc
void          vadc_clock_enable(void);
void          vadc_clock_enable_wait(void);
void          vadc_g4_ch7_config(unsigned char PRIO, unsigned char SM, unsigned char CLASS);
void          g4_ch7_connect_to_vadc(void);

// gtm
void          gtm_clock_enable(void);
void          gtm_clock_enable_wait(void);
void          gtm_tom0_trigger(void);
void          gtm_clock(unsigned char FXCLK);
void          gtm_tom0_ch1_config(unsigned char SL, unsigned char CLK, unsigned OSM);
void          tom0_ch1_connect_to_p10_1(void);
void          gtm_tom0_ch1_period_config(unsigned short N);
void          gtm_tom0_ch1_duty_config(unsigned short N);



#endif /* HYUNDAI_RESKILL_H_ */
