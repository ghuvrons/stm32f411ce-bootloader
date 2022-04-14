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

    #define APP_ADDR 0x08020000
    static void BOOT_Shutdown(void);

    /* ..... */

    int main(void) {
      /* ..... */

      /* Infinite loop */
      /* USER CODE BEGIN WHILE */
      while (1){
        /* To do Somethings before go to app */
        bepBlink(1, 100, 100);
        
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        /* Go To App */
        uint32_t appStack = *(__IO uint32_t *)(APP_ADDR);
        void (*jump)(void) = (void (*)(void))(*(__IO uint32_t *)(APP_ADDR + 4));

        BOOT_Shutdown();
        __set_MSP(appStack);
        jump();
      }
      /* USER CODE END 3 */

      /* ..... */
    }

    /* ..... */

    static void BOOT_Shutdown(void)
    {
      /* exec HAL_XXX_MaspDeinit() */

      /* DeInit */
      HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);
      HAL_RCC_DeInit();
      HAL_DeInit();
      __disable_irq();

      SysTick->CTRL = 0;
      SysTick->LOAD = 0;
      SysTick->VAL = 0;
      SYSCFG->MEMRMP = 0x01;
      
      __enable_irq();
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
    - define USER_VECT_TAB_ADDRESS. (Uncomment line 95 for my sourcecode) :

      ```c
      #define USER_VECT_TAB_ADDRESS
      ```

    - Define VECT_TAB_OFFSET, (line 109 in my sourcecode), as Application address offset. in this examample, 0x00020000U

      ```c
      #define VECT_TAB_OFFSET         0x00020000U    /*!< Vector Table base offset field.
                                                          This value must be a multiple of 0x200. */
      ```
