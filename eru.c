/*
 * eru.c
 *
 *  Created on: 2023. 7. 24.
 *      Author: bolta
 */


#include "HYUNDAI_RESKILL.h"

// input channel selection for ERU
void eru0_esr2_input_sel(unsigned char CH) {
    SCU_EICR1.U &= ~(0x7 << EXIS0_BIT_LSB_IDX);
    SCU_EICR1.U |=  (CH  << EXIS0_BIT_LSB_IDX);
}

// Edge selection
void eru0_etl_edge_sel(unsigned char F_EN, unsigned char R_EN) {
    // falling edge 선택
    SCU_EICR1.U &= ~( 0x1 << FEN0_BIT_LSB_IDX);
    SCU_EICR1.U |=   F_EN << FEN0_BIT_LSB_IDX;

    // rising edge 선택
    SCU_EICR1.U &= ~( 0x1 << REN0_BIT_LSB_IDX);
    SCU_EICR1.U |=   R_EN << REN0_BIT_LSB_IDX;

    // external interrupt 활성화
    SCU_EICR1.U |=   0x1 << EIEN0_BIT_LSB_IDX;

}

// OGU0 unit selection to transfer event to cpu
void eru0_ogu0_enable(void) {
    SCU_EICR1.U &= ~(0x7 << INP0_BIT_LSB_IDX);

    // OGU0 activation by external trigger
    SCU_IGCR0.U &= ~(0x3 << IGP0_BIT_LSB_IDX);
    SCU_IGCR0.U |=   0x1 << IGP0_BIT_LSB_IDX;
}

// interrupt ID, cpu no selection
void eru0_int_config(unsigned char ID, unsigned char cpu_no) {
    // interrupt ID & priority
    SRC_SCU_SCU_ERU0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |=  (  ID << SRPN_BIT_LSB_IDX);

    // 인터럽트 서비스 실행 cpu 번호 설정
    SRC_SCU_SCU_ERU0.U &= ~(0x3     << TOS_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |=  (cpu_no  << TOS_BIT_LSB_IDX);
}

void eru0_isr_enable(void) {
    SRC_SCU_SCU_ERU0.U |= 1      << SRE_BIT_LSB_IDX;
}

