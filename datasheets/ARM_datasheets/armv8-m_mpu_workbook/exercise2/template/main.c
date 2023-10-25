#include "RTE_Components.h"                 /* This mechanism is the standard way to include */
#include CMSIS_device_header                /* the device header file, in this case ARMCM33.h */
#include <stdio.h>

void mpu_setup( void ) {
  /* Exercise 2 - Add your code here to Initialize two Memory Attributes  */
  // Set Memory Attr 0

  // Set Memory Attr 1
}

int main( void )
{
  mpu_setup();
  return 0;
}
