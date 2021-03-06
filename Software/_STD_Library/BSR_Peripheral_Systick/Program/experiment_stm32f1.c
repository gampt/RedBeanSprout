/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "experiment_stm32f1.h"
/*====================================================================================================*/
/*====================================================================================================*/
volatile uint32_t Systick_Delay = 0;

void SystickDelay_1ms( volatile uint32_t DelayTimes )
{
  Systick_Delay = DelayTimes;
  while(Systick_Delay != 0);
}

int main( void )
{
  GPIO_Config();

  if(SysTick_Config(SystemCoreClock / 72000)) {
    while(1);
  }

  while(1) {
    LED_R = !LED_R;
    Delay_100ms(1);
    if(KEY_BO == 1 | KEY_WU == 1) {
      LED_G = !LED_G;
      Delay_100ms(1);
    }
    LED_B = !LED_B;
    SystickDelay_1ms(100);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  /* LED_B PC13 */  /* LED_G PC14 */  /* LED_R PC15 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY_WU PA0 */  /* KEY_BO PB2 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
}
/*====================================================================================================*/
/*====================================================================================================*/
