#include "init.h"

#define LED1_SET    GPIO_B+BS_B11
#define LED2_SET    GPIO_B+BS_B10
#define LED3_SET    GPIO_E+BS_B15
#define LED4_SET    GPIO_E+BS_B14
#define LED5_SET    GPIO_E+BS_B12
#define LED6_SET    GPIO_E+BS_B10

#define BUT1        GPIO_B+IDR_B12
#define BUT2        GPIO_B+IDR_B13
#define BUT3        GPIO_B+IDR_B15

int main(void){
    GPIO_init();

    uint8_t light_amount=0;
    uint8_t is_reverse=0;

    while(1){
        if(BIT_READ(BUT1,1)){
            light_amount=(light_amount+1)%7;
        }
        else if(BIT_READ(BUT2,1) & light_amount>0){
            light_amount=light_amount-1;
        }
        else if(BIT_READ(BUT3,1)){
            if(is_reverse>0) is_reverse=0;
            else is_reverse=1;
        }

        if (light_amount==1) BIT_SET(GPIO_B+BSRR,LED1_SET+BR_MUL*(LED2_SET+LED3_SET+LED4_SET+LED5_SET+LED6_SET));
        else if (light_amount==2) BIT_SET(GPIO_B+BSRR,LED1_SET+LED2_SET+BR_MUL*(LED3_SET+LED4_SET+LED5_SET+LED6_SET));
        else if (light_amount==3) BIT_SET(GPIO_B+BSRR,LED1_SET+LED2_SET+LED3_SET+BR_MUL*(LED4_SET+LED5_SET+LED6_SET));
        else if (light_amount==4) BIT_SET(GPIO_B+BSRR,LED1_SET+LED2_SET+LED3_SET+LED4_SET+BR_MUL*(LED5_SET+LED6_SET));
        else if (light_amount==5) BIT_SET(GPIO_B+BSRR,LED1_SET+LED2_SET+LED3_SET+LED4_SET+LED5_SET+BR_MUL*LED6_SET);
        else if (light_amount==6) BIT_SET(GPIO_B+BSRR,LED1_SET+LED2_SET+LED3_SET+LED4_SET+LED5_SET+LED6_SET);
        else BIT_SET(GPIO_B+BSRR,BR_MUL*(LED1_SET+LED2_SET+LED3_SET+LED4_SET+LED5_SET+LED6_SET));
    }
}