#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxCcu6_reg.h"
#include "driver.h"

#define H_P02_IOCR0     (*(volatile IOCR_STX*)(0xF003A210u))
#define H_P02_IN        (*(volatile  PIN_STX*)(0xF003A224u))

unsigned char AccelPressed = 0;
unsigned char BreakPressed = 0;

// Timer Interrupt 1
__interrupt(0x0A) __vector_table(0)
void ERU0_ISR(void)
{
    // falling

}

__interrupt(0x0B) __vector_table(1)
void ERU0_ISR(void)
{
    toggle_red_led();
}


void initButton(void)
{
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);       // reset P02_IOCR0 PC1
    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;          // set P02.1 general input (pull-up connected)
}

void initERU(void) {
    // ERU회로 내부의 ERS2회로 입력 4개중에 P02.1을 선택
    SCU_EICR1.U &= ~(0x7 << EXIS0_BIT_LSB_IDX);
    SCU_EICR1.U |=  (0x1 << EXIS0_BIT_LSB_IDX);


    // falling edge 선택
    SCU_EICR1.U |=   0x1 << FEN0_BIT_LSB_IDX;


    // rising edge 선택
    SCU_EICR1.U |=   0x1 << REN0_BIT_LSB_IDX;


    // external interrupt 활성화
    SCU_EICR1.U |=   0x1 << EIEN0_BIT_LSB_IDX;


    // OGU0를 사용
    SCU_EICR1.U &= ~(0x7 << INP0_BIT_LSB_IDX);


    // OGU0 activation by external trigger
    SCU_IGCR0.U &= ~(0x3 << IGP0_BIT_LSB_IDX);
    SCU_IGCR0.U |=   0x1 << IGP0_BIT_LSB_IDX;


    // 인터럽트 우선순위 및 ID설정.
    SRC_SCU_SCU_ERU0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |=   0x0A << SRPN_BIT_LSB_IDX;


    // 인터럽트 서비스 실행 cpu를 cpu0로 설정정
    SRC_SCU_SCU_ERU0.U &= ~(0x3  << TOS_BIT_LSB_IDX);


    // 최종적으로 cpu가 ISR함수를 실행하도록 허용
    SRC_SCU_SCU_ERU0.U |= 1      << SRE_BIT_LSB_IDX;
}

unsigned char read_port   (unsigned char group, unsigned char pin) {
    if(group == 2 && pin == 1) {
        unsigned char val = P02_IN.U & (0x1 << P1_BIT_LSB_IDX);
        if(val == 2)
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