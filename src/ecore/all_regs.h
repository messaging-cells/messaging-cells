
// all_regs.h

#ifndef BJ_ALL_REGS_H
#define BJ_ALL_REGS_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

// eCore General Purpose Registers
typedef enum {
	BJ_CORE_GP_REG_BASE     = 0xf0000,
	BJ_REG_R0               = BJ_CORE_GP_REG_BASE + 0x0000,
	BJ_REG_R1               = BJ_CORE_GP_REG_BASE + 0x0004,
	BJ_REG_R2               = BJ_CORE_GP_REG_BASE + 0x0008,
	BJ_REG_R3               = BJ_CORE_GP_REG_BASE + 0x000c,
	BJ_REG_R4               = BJ_CORE_GP_REG_BASE + 0x0010,
	BJ_REG_R5               = BJ_CORE_GP_REG_BASE + 0x0014,
	BJ_REG_R6               = BJ_CORE_GP_REG_BASE + 0x0018,
	BJ_REG_R7               = BJ_CORE_GP_REG_BASE + 0x001c,
	BJ_REG_R8               = BJ_CORE_GP_REG_BASE + 0x0020,
	BJ_REG_R9               = BJ_CORE_GP_REG_BASE + 0x0024,
	BJ_REG_R10              = BJ_CORE_GP_REG_BASE + 0x0028,
	BJ_REG_R11              = BJ_CORE_GP_REG_BASE + 0x002c,
	BJ_REG_R12              = BJ_CORE_GP_REG_BASE + 0x0030,
	BJ_REG_R13              = BJ_CORE_GP_REG_BASE + 0x0034,
	BJ_REG_R14              = BJ_CORE_GP_REG_BASE + 0x0038,
	BJ_REG_R15              = BJ_CORE_GP_REG_BASE + 0x003c,
	BJ_REG_R16              = BJ_CORE_GP_REG_BASE + 0x0040,
	BJ_REG_R17              = BJ_CORE_GP_REG_BASE + 0x0044,
	BJ_REG_R18              = BJ_CORE_GP_REG_BASE + 0x0048,
	BJ_REG_R19              = BJ_CORE_GP_REG_BASE + 0x004c,
	BJ_REG_R20              = BJ_CORE_GP_REG_BASE + 0x0050,
	BJ_REG_R21              = BJ_CORE_GP_REG_BASE + 0x0054,
	BJ_REG_R22              = BJ_CORE_GP_REG_BASE + 0x0058,
	BJ_REG_R23              = BJ_CORE_GP_REG_BASE + 0x005c,
	BJ_REG_R24              = BJ_CORE_GP_REG_BASE + 0x0060,
	BJ_REG_R25              = BJ_CORE_GP_REG_BASE + 0x0064,
	BJ_REG_R26              = BJ_CORE_GP_REG_BASE + 0x0068,
	BJ_REG_R27              = BJ_CORE_GP_REG_BASE + 0x006c,
	BJ_REG_R28              = BJ_CORE_GP_REG_BASE + 0x0070,
	BJ_REG_R29              = BJ_CORE_GP_REG_BASE + 0x0074,
	BJ_REG_R30              = BJ_CORE_GP_REG_BASE + 0x0078,
	BJ_REG_R31              = BJ_CORE_GP_REG_BASE + 0x007c,
	BJ_REG_R32              = BJ_CORE_GP_REG_BASE + 0x0080,
	BJ_REG_R33              = BJ_CORE_GP_REG_BASE + 0x0084,
	BJ_REG_R34              = BJ_CORE_GP_REG_BASE + 0x0088,
	BJ_REG_R35              = BJ_CORE_GP_REG_BASE + 0x008c,
	BJ_REG_R36              = BJ_CORE_GP_REG_BASE + 0x0090,
	BJ_REG_R37              = BJ_CORE_GP_REG_BASE + 0x0094,
	BJ_REG_R38              = BJ_CORE_GP_REG_BASE + 0x0098,
	BJ_REG_R39              = BJ_CORE_GP_REG_BASE + 0x009c,
	BJ_REG_R40              = BJ_CORE_GP_REG_BASE + 0x00a0,
	BJ_REG_R41              = BJ_CORE_GP_REG_BASE + 0x00a4,
	BJ_REG_R42              = BJ_CORE_GP_REG_BASE + 0x00a8,
	BJ_REG_R43              = BJ_CORE_GP_REG_BASE + 0x00ac,
	BJ_REG_R44              = BJ_CORE_GP_REG_BASE + 0x00b0,
	BJ_REG_R45              = BJ_CORE_GP_REG_BASE + 0x00b4,
	BJ_REG_R46              = BJ_CORE_GP_REG_BASE + 0x00b8,
	BJ_REG_R47              = BJ_CORE_GP_REG_BASE + 0x00bc,
	BJ_REG_R48              = BJ_CORE_GP_REG_BASE + 0x00c0,
	BJ_REG_R49              = BJ_CORE_GP_REG_BASE + 0x00c4,
	BJ_REG_R50              = BJ_CORE_GP_REG_BASE + 0x00c8,
	BJ_REG_R51              = BJ_CORE_GP_REG_BASE + 0x00cc,
	BJ_REG_R52              = BJ_CORE_GP_REG_BASE + 0x00d0,
	BJ_REG_R53              = BJ_CORE_GP_REG_BASE + 0x00d4,
	BJ_REG_R54              = BJ_CORE_GP_REG_BASE + 0x00d8,
	BJ_REG_R55              = BJ_CORE_GP_REG_BASE + 0x00dc,
	BJ_REG_R56              = BJ_CORE_GP_REG_BASE + 0x00e0,
	BJ_REG_R57              = BJ_CORE_GP_REG_BASE + 0x00e4,
	BJ_REG_R58              = BJ_CORE_GP_REG_BASE + 0x00e8,
	BJ_REG_R59              = BJ_CORE_GP_REG_BASE + 0x00ec,
	BJ_REG_R60              = BJ_CORE_GP_REG_BASE + 0x00f0,
	BJ_REG_R61              = BJ_CORE_GP_REG_BASE + 0x00f4,
	BJ_REG_R62              = BJ_CORE_GP_REG_BASE + 0x00f8,
	BJ_REG_R63              = BJ_CORE_GP_REG_BASE + 0x00fc,
} bj_gp_reg_id_t;

// eCore Special Registers
typedef enum {
	BJ_CORE_SP_REG_BASE     = 0xf0000,
	// Control registers
	BJ_REG_CONFIG           = BJ_CORE_SP_REG_BASE + 0x0400,
	BJ_REG_STATUS           = BJ_CORE_SP_REG_BASE + 0x0404,
	BJ_REG_PC               = BJ_CORE_SP_REG_BASE + 0x0408,
	BJ_REG_DEBUGSTATUS      = BJ_CORE_SP_REG_BASE + 0x040c,
	BJ_REG_LC               = BJ_CORE_SP_REG_BASE + 0x0414,
	BJ_REG_LS               = BJ_CORE_SP_REG_BASE + 0x0418,
	BJ_REG_LE               = BJ_CORE_SP_REG_BASE + 0x041c,
	BJ_REG_IRET             = BJ_CORE_SP_REG_BASE + 0x0420,
	BJ_REG_IMASK            = BJ_CORE_SP_REG_BASE + 0x0424,
	BJ_REG_ILAT             = BJ_CORE_SP_REG_BASE + 0x0428,
	BJ_REG_ILATST           = BJ_CORE_SP_REG_BASE + 0x042C,
	BJ_REG_ILATCL           = BJ_CORE_SP_REG_BASE + 0x0430,
	BJ_REG_IPEND            = BJ_CORE_SP_REG_BASE + 0x0434,
	BJ_REG_CTIMER0          = BJ_CORE_SP_REG_BASE + 0x0438,
	BJ_REG_CTIMER1          = BJ_CORE_SP_REG_BASE + 0x043C,
	BJ_REG_FSTATUS          = BJ_CORE_SP_REG_BASE + 0x0440,
	BJ_REG_DEBUGCMD         = BJ_CORE_SP_REG_BASE + 0x0448,

	// DMA Registers
	BJ_REG_DMA0CONFIG       = BJ_CORE_SP_REG_BASE + 0x0500,
	BJ_REG_DMA0STRIDE       = BJ_CORE_SP_REG_BASE + 0x0504,
	BJ_REG_DMA0COUNT        = BJ_CORE_SP_REG_BASE + 0x0508,
	BJ_REG_DMA0SRCADDR      = BJ_CORE_SP_REG_BASE + 0x050C,
	BJ_REG_DMA0DSTADDR      = BJ_CORE_SP_REG_BASE + 0x0510,
	BJ_REG_DMA0AUTODMA0     = BJ_CORE_SP_REG_BASE + 0x0514,
	BJ_REG_DMA0AUTODMA1     = BJ_CORE_SP_REG_BASE + 0x0518,
	BJ_REG_DMA0STATUS       = BJ_CORE_SP_REG_BASE + 0x051C,
	BJ_REG_DMA1CONFIG       = BJ_CORE_SP_REG_BASE + 0x0520,
	BJ_REG_DMA1STRIDE       = BJ_CORE_SP_REG_BASE + 0x0524,
	BJ_REG_DMA1COUNT        = BJ_CORE_SP_REG_BASE + 0x0528,
	BJ_REG_DMA1SRCADDR      = BJ_CORE_SP_REG_BASE + 0x052C,
	BJ_REG_DMA1DSTADDR      = BJ_CORE_SP_REG_BASE + 0x0530,
	BJ_REG_DMA1AUTODMA0     = BJ_CORE_SP_REG_BASE + 0x0534,
	BJ_REG_DMA1AUTODMA1     = BJ_CORE_SP_REG_BASE + 0x0538,
	BJ_REG_DMA1STATUS       = BJ_CORE_SP_REG_BASE + 0x053C,

	// Memory Protection Registers
	BJ_REG_MEMSTATUS        = BJ_CORE_SP_REG_BASE + 0x0604,
	BJ_REG_MEMPROTECT       = BJ_CORE_SP_REG_BASE + 0x0608,

	// Node Registers
	BJ_REG_MESHCFG          = BJ_CORE_SP_REG_BASE + 0x0700,
	BJ_REG_COREID           = BJ_CORE_SP_REG_BASE + 0x0704,
	BJ_REG_CORE_RESET       = BJ_CORE_SP_REG_BASE + 0x070c,
} bj_core_reg_id_t;

// Chip registers
typedef enum {
	BJ_CHIP_REG_BASE        = 0xf0000,
	BJ_REG_IO_LINK_MODE_CFG = BJ_CHIP_REG_BASE + 0x0300,
	BJ_REG_IO_LINK_TX_CFG   = BJ_CHIP_REG_BASE + 0x0304,
	BJ_REG_IO_LINK_RX_CFG   = BJ_CHIP_REG_BASE + 0x0308,
	BJ_REG_IO_GPIO_CFG      = BJ_CHIP_REG_BASE + 0x030c,
	BJ_REG_IO_FLAG_CFG      = BJ_CHIP_REG_BASE + 0x0318,
	BJ_REG_IO_SYNC_CFG      = BJ_CHIP_REG_BASE + 0x031c,
	BJ_REG_IO_HALT_CFG      = BJ_CHIP_REG_BASE + 0x0320,
	BJ_REG_IO_RESET         = BJ_CHIP_REG_BASE + 0x0324,
	BJ_REG_IO_LINK_DEBUG    = BJ_CHIP_REG_BASE + 0x0328,
} bj_chip_reg_id_t;


#ifdef __cplusplus
}
#endif

#endif // BJ_ALL_REGS_H


