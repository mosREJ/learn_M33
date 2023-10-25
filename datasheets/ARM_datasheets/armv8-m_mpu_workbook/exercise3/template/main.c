#include "RTE_Components.h"                 /* This mechanism is the standard way to include */
#include CMSIS_device_header                /* the device header file, in this case ARMCM33.h */
#include <stdio.h>

void mpu_setup( void ) {
  // Set Memory Attr 0
  ARM_MPU_SetMemAttr(0UL, ARM_MPU_ATTR( /* Normal memory */
    MPU_ATTR_NORMAL_OUTER_WT_TR_RA_WA,  /* Outer Write-Back transient with read and write allocate */
    MPU_ATTR_NORMAL_INNER_WT_TR_RA_WA   /* Inner Write-Through transient with read and write allocate */
  ));

  // Set Memory Attr 1
  ARM_MPU_SetMemAttr(1UL, ARM_MPU_ATTR(
    ARM_MPU_ATTR_DEVICE,          /* Device memory */
    ARM_MPU_ATTR_DEVICE_nGnRnE    /* non-Gathering, non-Reordering, no Early Write Acknowledgement */
  ));

  /* Set up Attr 2-7 for further Normal and Device memory configurations */

  /* Exercise 3 - Add your code here to initialize memory regions */

    /* Configure region 0 - Mappable memory */

    /* Configure region 1 - ZBTSRAM 1 */

    /* Configure region 2 - ZBTSRAM 2 & 3 (2x32-bit) */
}

int main()
{

  return 0;
}
