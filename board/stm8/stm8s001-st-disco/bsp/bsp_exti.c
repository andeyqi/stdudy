#include "stm8s.h"
/**
  * @addtogroup GPIO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

#define BUTTON_GPIO_PORT  (GPIOC)
#define BUTTON_GPIO_PINS  (GPIO_PIN_3)

void button_init(void)
{
  /* Initialize I/Os in Output Mode */
    GPIO_Init(BUTTON_GPIO_PORT, (GPIO_Pin_TypeDef)BUTTON_GPIO_PINS, GPIO_MODE_IN_FL_IT);
  /* Initialize the Interrupt sensitivity */
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_FALL);
    //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  
    enableInterrupts();
}


