# STM32F411CE Bootloader

This example will partition by 2 part. First 128K Flash mem will be contain bootloader, and next memory will be contain application.

## Bootloader - Initialitation

1. Setup Flash Memory in Linker script file:
    Change memories definition in both files "STM32F411CEUX_FLASH.ld" and "STM32F411CEUX_RAM.ld" to :

    ```c
    /* Memories definition */
    MEMORY
    {
      RAM   (xrw) : ORIGIN = 0x20000000,  LENGTH = 128K
      FLASH (rx)  : ORIGIN =  0x8000000,  LENGTH = 128K
    }

    ```

1. Write Jump

    ```c
    /* ..... */

    static void BOOT_Shutdown(void);

    /* ..... */

    int main(){
      while(1) {
        uint32_t appStack = *(__IO uint32_t *)(APP_ADDR);
        void (*jump)(void) = (void (*)(void))(*(__IO uint32_t *)(APP_ADDR + 4));

        BOOT_Shutdown();
        __set_MSP(appStack);
        jump();
      }
    }

    /* ..... */

    static void BOOT_Shutdown(void)
    {
      HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);
      HAL_RCC_DeInit();
      HAL_DeInit();
      __disable_irq();

      SysTick->CTRL = 0;
      SysTick->LOAD = 0;
      SysTick->VAL = 0;


      SYSCFG->MEMRMP = 0x01;
      __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
    }
    
    /* ..... */
    ```

## Application - Initialitation

1. Setup Flash Memory in Linker script file:
    Change memories definition in both files "STM32F411CEUX_FLASH.ld" and "STM32F411CEUX_RAM.ld" to :

    ```c
    /* Memories definition */
    MEMORY
    {
      RAM   (xrw) : ORIGIN = 0x20000000,  LENGTH = 128K
      FLASH (rx)  : ORIGIN =  0x8020000,  LENGTH = 512K - 128K
    }

    ```

1. Set VECT_TAB_OFFSET
    In file "/Core/Src/system_stm32f4xx.c":
    - Uncomment line 95 : "#define USER_VECT_TAB_ADDRESS"
    - Define VECT_TAB_OFFSET, in line 109, as Application address offset. in this examample, 0x00020000U
