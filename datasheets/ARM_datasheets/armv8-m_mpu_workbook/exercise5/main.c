#include "RTE_Components.h"                 /* This mechanism is the standard way to include */
#include CMSIS_device_header                /* the device header file, in this case ARMCM33.h */
#include <stdio.h>
#include <arm_cmse.h>

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
  /* (Re)mappable Memory
    * When zbt_boot_ctrl = 0, ZBTSRAM 1 is mapped to this region.
    * Otherwise, Remap_ctrl = 0 maps Block RAM and Remap_ctrl = 1 maps ZBTSRAM 1.
    *
    * Configure region 1 from 0x00000000-0x00003FFF: Non-shareable, read/write, non-privileged, executable */
  ARM_MPU_SetRegion(
          0,
          ARM_MPU_RBAR(0x00000000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_EX),
          ARM_MPU_RLAR(0x00003FFFUL, MAIR_ATTR(0))
  );

  /* Configure region 1 - ZBTSRAM 1 */
  /* ZBTSRAM 1 */
  /* Configure region 2 from 0x00004000-0x007FFFFF: Non-shareable, read/write, non-privileged, executable */
  ARM_MPU_SetRegion(
          1,
          ARM_MPU_RBAR(0x20000000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_EX),
          ARM_MPU_RLAR(0x207FFFFFUL, MAIR_ATTR(0))
  );

  /* ZBTSRAM 2 & 3 */
  /* Configure region 3 from 0x20000000-0x207FFFFF: Non-shareable, read/write, non-privileged, executable */
  ARM_MPU_SetRegion(
          2,
          ARM_MPU_RBAR(0x20000000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_EX),
          ARM_MPU_RLAR(0x207FFFFFUL, MAIR_ATTR(0))
  );

  /* CMSDK */
  /* Configure region 4 from 0x40000000-0x4001FFFF: Non-shareable, read-only, non-privileged, non-executable */
  ARM_MPU_SetRegion(
          3,
          ARM_MPU_RBAR(0x40000000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RO, ARM_MPU_AP_NP, ARM_MPU_XN),
          ARM_MPU_RLAR(0x4001FFFFUL, MAIR_ATTR(1))
  );

  /* APB */
  /* Configure region 5 from 0x40020000-0x40024FFF: Non-shareable, read-only, non-privileged, non-executable */
  ARM_MPU_SetRegion(
          4,
          ARM_MPU_RBAR(0x40020000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_XN),
          ARM_MPU_RLAR(0x40024FFFUL, MAIR_ATTR(1))
  );

  /* FPGA System Control & IO, APB */
  /* Configure region 6 from 0x40028000-0x40028FFF: Non-shareable, read-only, non-privileged, non-executable */
  ARM_MPU_SetRegion(
          5,
          ARM_MPU_RBAR(0x40028000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_XN),
          ARM_MPU_RLAR(0x40028FFFUL, MAIR_ATTR(1))
  );

  /* Block RAM (Boot time) */
  /* Configure region 7 from 0x40200000-0x402FFFFF: Non-shareable, read-only, non-privileged, executable */
  ARM_MPU_SetRegion(
          6,
          ARM_MPU_RBAR(0x40200000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RO, ARM_MPU_AP_NP, ARM_MPU_EX),
          ARM_MPU_RLAR(0x402FFFFFUL, MAIR_ATTR(0))
  );

  /* VGA */
  /* Configure region 8 from 0x41000000-0x4110FFFF: Non-shareable, read/write, non-privileged, non-executable */
  ARM_MPU_SetRegion(
          7,
          ARM_MPU_RBAR(0x41000000UL, ARM_MPU_SH_NON, ARM_MPU_AP_RW, ARM_MPU_AP_NP, ARM_MPU_XN),
          ARM_MPU_RLAR(0x4110FFFFUL, MAIR_ATTR(1))
  );
}

int main( void )
{
  mpu_setup();

  cmse_address_info_t test = cmse_TT((void*) 0x00000000);

  return 0;
}
