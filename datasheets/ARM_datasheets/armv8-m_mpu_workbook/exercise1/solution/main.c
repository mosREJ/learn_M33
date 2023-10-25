#include "RTE_Components.h"                 /* This mechanism is the standard way to include */
#include CMSIS_device_header                /* the device header file, in this case ARMCM33.h */
#include <stdio.h>

void mpu_setup( void ) {
  /* Exercise 1 - Add your code here to determine how many MPU memory regions are available */
  printf("My system's MPU is configured with %d MPU regions.", ARM_MPU_TYPE());
}

int main( void )
{
  mpu_setup();
  return 0;
}