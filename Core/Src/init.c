#include "init.h"

void GPIO_init(){
    BIT_SET(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN|RCC_AHB1ENR_GPIOFEN);              // Активируем тактирование портов A, C, F по RCC AHB1ENR

    BIT_SET(GPIOA->MODER,GPIO_MODER_MODE3_0);                                                       //Режим General Purpose Output для 3го пина
    BIT_SET(GPIOC->OTYPER,0x00UL);                                                                  //Режим вывода Push-Pull
    BIT_SET(GPIOA->OSPEEDR,GPIO_OSPEEDR_OSPEED3_0);                                                 //Режим скорости работы 3го пина: middle
    BIT_SET(GPIOA->PUPDR,0x00UL);                                                                   //Оставляем пины без подтяжки и стяжки к общему питанию

    BIT_SET(GPIOC->MODER,GPIO_MODER_MODE0_0|GPIO_MODER_MODE3_0);                                    //Режим General Purpose Output для 0, 3 пинов
    BIT_SET(GPIOF->OTYPER,0x00UL);                                                                  //Режим вывода Push-Pull
    BIT_SET(GPIOC->OSPEEDR,GPIO_OSPEEDR_OSPEED0_0|GPIO_OSPEEDR_OSPEED3_0);                          //Режим скорости работы 0, 3 пинов: middle
    BIT_SET(GPIOC->PUPDR,0x00UL);                                                                   //Оставляем пины без подтяжки и стяжки к общему питанию

    BIT_SET(GPIOF->MODER,GPIO_MODER_MODE3_0|GPIO_MODER_MODE5_0|GPIO_MODER_MODE10_0);                //Режим General Purpose Output для 3, 5, 10 пинов
    BIT_SET(GPIOF->OTYPER,0x00UL);                                                                  //Режим вывода Push-Pull
    BIT_SET(GPIOF->OSPEEDR,GPIO_OSPEEDR_OSPEED3_0|GPIO_OSPEEDR_OSPEED5_0|GPIO_OSPEEDR_OSPEED10_0);  //Режим скорости работы 3, 5, 10 пинов: middle
    BIT_SET(GPIOF->PUPDR,0x00UL);                                                                   //Оставляем пины без подтяжки и стяжки к общему питанию
}