#include "init.h"

int main(void){
    GPIO_init();

    uint8_t light_amount=0;     // Количество включенных диодов
    uint8_t is_reverse=0;       // Инвертированы ли функции кнопок 1 и 2

    while(1){
        uint8_t light_up_mode=0;    // режим: включаем (1)/выключаем (2) диоды или ничего не делаем (0)

        if(*(uint32_t*)(0x40020010UL) & 0x80UL){            //Проверка сигнала на GPIO_A IDR 7 - Меняет местами функционал кнопок 1 и 2
            if(is_reverse) is_reverse=0;
            else is_reverse=1;
        }
        else if(*(uint32_t*)(0x40020010UL) & 0x20UL){       //Проверка сигнала на GPIO_A IDR 5 - Включает светодиоды поочередно
            if(is_reverse) light_up_mode=2;
            else light_up_mode=1;
        }
        else if(*(uint32_t*)(0x40020010UL) & 0x40UL){       //Проверка сигнала на GPIO_A IDR 6 - Выключает светодиоды в обратном порядке
            if(is_reverse) light_up_mode=1;
            else light_up_mode=2;
        }

        if (light_up_mode>>1 & light_amount>0) light_amount--;
        else if (light_up_mode & light_amount<6) light_amount++;

        //Указываем, какие светодиоды включать
        if (light_amount==1) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x00090000UL;   // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04280000UL;   // GPIO_F BSRR пин 3, 5, 10
        }
        else if (light_amount==2) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x00080001UL;   // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04280000UL;   // GPIO_F BSRR пин 3, 5, 10
        }
        else if (light_amount==3) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x0009UL;       // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04280000UL;   // GPIO_F BSRR пин 3, 5, 10
        }
        else if (light_amount==4) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x0009UL;       // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04200008UL;   // GPIO_F BSRR пин 3, 5, 10
        }
        else if (light_amount==5) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x0009UL;       // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04000028UL;   // GPIO_F BSRR пин 3, 5, 10
        }
        else if (light_amount==6) {
            *(uint32_t*)(0x40020018UL)|=0x0008UL;       // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x0009UL;       // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x0428UL;       // GPIO_F BSRR пин 3, 5, 10
        }
        else {
            *(uint32_t*)(0x40020018UL)|=0x00080000UL;   // GPIO_A BSRR пин 3
            *(uint32_t*)(0x40020818UL)|=0x00090000UL;   // GPIO_C BSRR пин 0 и 3
            *(uint32_t*)(0x40021418UL)|=0x04280000UL;   // GPIO_F BSRR пин 3, 5, 10
        }
    }
}