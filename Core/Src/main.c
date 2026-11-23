#include "init.h"

#define LED1_SET    GPIO_BSRR_BS3       // Uses GPIO_A
#define LED2_SET    GPIO_BSRR_BS0       // Uses GPIO_C
#define LED3_SET    GPIO_BSRR_BS3       // Uses GPIO_C
#define LED4_SET    GPIO_BSRR_BS3       // Uses GPIO_F
#define LED5_SET    GPIO_BSRR_BS5       // Uses GPIO_F
#define LED6_SET    GPIO_BSRR_BS10      // Uses GPIO_F

#define LED1_RESET  GPIO_BSRR_BR3       // Uses GPIO_A
#define LED2_RESET  GPIO_BSRR_BR0       // Uses GPIO_C
#define LED3_RESET  GPIO_BSRR_BR3       // Uses GPIO_C
#define LED4_RESET  GPIO_BSRR_BR3       // Uses GPIO_F
#define LED5_RESET  GPIO_BSRR_BR5       // Uses GPIO_F
#define LED6_RESET  GPIO_BSRR_BR10      // Uses GPIO_F

#define BUT1        GPIO_IDR_IDR_5      // Включает светодиоды поочередно
#define BUT2        GPIO_IDR_IDR_6      // Выключает светодиоды в обратном порядке
#define BUT3        GPIO_IDR_IDR_7      // Меняет местами функционал кнопок 1 и 2

int main(void){
    GPIO_init();

    uint8_t light_amount=0;         // Количество включенных диодов
    uint8_t is_reverse=0;           // Инвертированы ли функции кнопок 1 и 2

    while(1){
        uint8_t light_up_mode=0;    // режим: включаем (1)/выключаем (2) диоды или ничего не делаем (0)

        if(BIT_READ(GPIOA->IDR,BUT3)){
            if(is_reverse) is_reverse=0;
            else is_reverse=1;
        }
        else if(BIT_READ(GPIOA->IDR,BUT1)){
            if(is_reverse) light_up_mode=2;
            else light_up_mode=1;
        }
        else if(BIT_READ(GPIOA->IDR,BUT2)){
            if(is_reverse) light_up_mode=1;
            else light_up_mode=2;
        }

        if (light_up_mode>>1 & light_amount>0) light_amount--;
        else if (light_up_mode & light_amount<6) light_amount++;

        if (light_amount==1) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_RESET|LED3_RESET);
            BIT_SET(GPIOF->BSRR,LED4_RESET|LED5_RESET|LED6_RESET);
        }
        else if (light_amount==2) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_SET|LED3_RESET);
            BIT_SET(GPIOF->BSRR,LED4_RESET|LED5_RESET|LED6_RESET);
        }
        else if (light_amount==3) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_SET|LED3_SET);
            BIT_SET(GPIOF->BSRR,LED4_RESET|LED5_RESET|LED6_RESET);
        }
        else if (light_amount==4) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_SET|LED3_SET);
            BIT_SET(GPIOF->BSRR,LED4_SET|LED5_RESET|LED6_RESET);
        }
        else if (light_amount==5) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_SET|LED3_SET);
            BIT_SET(GPIOF->BSRR,LED4_SET|LED5_SET|LED6_RESET);
        }
        else if (light_amount==6) {
            BIT_SET(GPIOA->BSRR,LED1_SET);
            BIT_SET(GPIOC->BSRR,LED2_SET|LED3_SET);
            BIT_SET(GPIOF->BSRR,LED4_SET|LED5_SET|LED6_SET);
        }
        else {
            BIT_SET(GPIOA->BSRR,LED1_RESET);
            BIT_SET(GPIOC->BSRR,LED2_RESET|LED3_RESET);
            BIT_SET(GPIOF->BSRR,LED4_RESET|LED5_RESET|LED6_RESET);
        }
    }
}