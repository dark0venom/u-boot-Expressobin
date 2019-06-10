/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 */

/*
 * T2080 RDB/PCIe board configuration file
 */

#ifndef __T2080RDB_H
#define __T2080RDB_H

#define CONFIG_ICS307_REFCLK_HZ 25000000  /* ICS307 ref clk freq */
#define CONFIG_FSL_SATA_V2

/* High Level Configuration Options */
#define CONFIG_SYS_BOOK3E_HV	/* Category E.HV supported */
#define CONFIG_ENABLE_36BIT_PHYS

#ifdef CONFIG_PHYS_64BIT
#define CONFIG_ADDR_MAP 1
#define CONFIG_SYS_NUM_ADDR_MAP 64 /* number of TLB1 entries */
#endif

#define CONFIG_SYS_FSL_CPC	/* Corenet Platform Cache */
#define CONFIG_SYS_NUM_CPC	CONFIG_SYS_NUM_DDR_CTLRS
#define CONFIG_ENV_OVERWRITE

#ifdef CONFIG_RAMBOOT_PBL
#define CONFIG_SYS_FSL_PBL_PBI board/freescale/t208xrdb/t2080_pbi.cfg

#define CONFIG_SPL_FLUSH_IMAGE
#define CONFIG_SPL_PAD_TO		0x40000
#define CONFIG_SPL_MAX_SIZE		0x28000
#define RESET_VECTOR_OFFSET		0x27FFC
#define BOOT_PAGE_OFFSET		0x27000
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SPL_SKIP_RELOCATE
#define CONFIG_SPL_COMMON_INIT_DDR
#define CONFIG_SYS_CCSR_DO_NOT_RELOCATE
#endif

#ifdef CONFIG_NAND
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(768 << 10)
#define CONFIG_SYS_NAND_U_BOOT_DST	0x00200000
#define CONFIG_SYS_NAND_U_BOOT_START	0x00200000
#define CONFIG_SYS_NAND_U_BOOT_OFFS	(256 << 10)
#define CONFIG_SYS_LDSCRIPT  "arch/powerpc/cpu/mpc85xx/u-boot-nand.lds"
#define CONFIG_SYS_FSL_PBL_RCW board/freescale/t208xrdb/t2080_nand_rcw.cfg
#define CONFIG_SPL_NAND_BOOT
#endif

#ifdef CONFIG_SPIFLASH
#define        CONFIG_RESET_VECTOR_ADDRESS             0x200FFC
#define CONFIG_SPL_SPI_FLASH_MINIMAL
#define CONFIG_SYS_SPI_FLASH_U_BOOT_SIZE       (768 << 10)
#define CONFIG_SYS_SPI_FLASH_U_BOOT_DST                (0x00200000)
#define CONFIG_SYS_SPI_FLASH_U_BOOT_START      (0x00200000)
#define CONFIG_SYS_SPI_FLASH_U_BOOT_OFFS       (256 << 10)
#define CONFIG_SYS_LDSCRIPT    "arch/powerpc/cpu/mpc85xx/u-boot.lds"
#ifndef CONFIG_SPL_BUILD
#define CONFIG_SYS_MPC85XX_NO_RESETVEC
#endif
#define CONFIG_SYS_FSL_PBL_RCW board/freescale/t208xrdb/t2080_spi_rcw.cfg
#define CONFIG_SPL_SPI_BOOT
#endif

#ifdef CONFIG_SDCARD
#define        CONFIG_RESET_VECTOR_ADDRESS             0x200FFC
#define CONFIG_SYS_MMC_U_BOOT_SIZE     (768 << 10)
#define CONFIG_SYS_MMC_U_BOOT_DST      (0x00200000)
#define CONFIG_SYS_MMC_U_BOOT_START    (0x00200000)
#define CONFIG_SYS_MMC_U_BOOT_OFFS     (260 << 10)
#define CONFIG_SYS_LDSCRIPT    "arch/powerpc/cpu/mpc85xx/u-boot.lds"
#ifndef CONFIG_SPL_BUILD
#define CONFIG_SYS_MPC85XX_NO_RESETVEC
#endif
#define CONFIG_SYS_FSL_PBL_RCW board/freescale/t208xrdb/t2080_sd_rcw.cfg
#define CONFIG_SPL_MMC_BOOT
#endif

#endif /* CONFIG_RAMBOOT_PBL */

#define CONFIG_SRIO_PCIE_BOOT_MASTER
#ifdef CONFIG_SRIO_PCIE_BOOT_SLAVE
/* Set 1M boot space */
#define CONFIG_SYS_SRIO_PCIE_BOOT_SLAVE_ADDR (CONFIG_SYS_TEXT_BASE & 0xfff00000)
#define CONFIG_SYS_SRIO_PCIE_BOOT_SLAVE_ADDR_PHYS \
		(0x300000000ull | CONFIG_SYS_SRIO_PCIE_BOOT_SLAVE_ADDR)
#define CONFIG_RESET_VECTOR_ADDRESS 0xfffffffc
#endif

#ifndef CONFIG_RESET_VECTOR_ADDRESS
#define CONFIG_RESET_VECTOR_ADDRESS	0xeffffffc
#endif

/*
 * These can be toggled for performance analysis, otherwise use default.
 */
#define CONFIG_SYS_CACHE_STASHING
#define CONFIG_BTB		/* toggle branch predition */
#define CONFIG_DDR_ECC
#ifdef CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE		0xdeadbeef
#endif

#define CONFIG_SYS_MEMTEST_START	0x00200000 /* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00400000

#if defined(CONFIG_SPIFLASH)
#define CONFIG_ENV_SIZE		0x2000	   /* 8KB */
#define CONFIG_ENV_OFFSET	0x100000   /* 1MB */
#define CONFIG_ENV_SECT_SIZE	0x10000
#elif defined(CONFIG_SDCARD)
#define CONFIG_SYS_MMC_ENV_DEV	0
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_OFFSET	(512 * 0x800)
#elif defined(CONFIG_NAND)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_OFFSET	(2 * CONFIG_SYS_NAND_BLOCK_SIZE)
#elif defined(CONFIG_SRIO_PCIE_BOOT_SLAVE)
#define CONFIG_ENV_ADDR		0xffe20000
#define CONFIG_ENV_SIZE		0x2000
#elif defined(CONFIG_ENV_IS_NOWHERE)
#define CONFIG_ENV_SIZE		0x2000
#else
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x20000 /* 128K (one sector) */
#endif

#ifndef __ASSEMBLY__
unsigned long get_board_sys_clk(void);
unsigned long get_board_ddr_clk(void);
#endif

#define CONFIG_SYS_CLK_FREQ	66660000
#define CONFIG_DDR_CLK_FREQ	133330000

/*
 * Config the L3 Cache as L3 SRAM
 */
#define CONFIG_SYS_INIT_L3_ADDR		0xFFFC0000
#define CONFIG_SYS_L3_SIZE		(512 << 10)
#define CONFIG_SPL_GD_ADDR		(CONFIG_SYS_INIT_L3_ADDR + 32 * 1024)
#ifdef CONFIG_RAMBOOT_PBL
#define CONFIG_ENV_ADDR			(CONFIG_SPL_GD_ADDR + 4 * 1024)
#endif
#define CONFIG_SPL_RELOC_MALLOC_ADDR	(CONFIG_SPL_GD_ADDR + 12 * 1024)
#define CONFIG_SPL_RELOC_MALLOC_SIZE	(50 << 10)
#define CONFIG_SPL_RELOC_STACK		(CONFIG_SPL_GD_ADDR + 64 * 1024)

#define CONFIG_SYS_DCSRBAR	0xf0000000
#define CONFIG_SYS_DCSRBAR_PHYS	0xf00000000ull

/* EEPROM */
#define CONFIG_ID_EEPROM
#define CONFIG_SYS_I2C_EEPROM_NXID
#define CONFIG_SYS_EEPROM_BUS_NUM	0
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2

/*
 * DDR Setup
 */
#define CONFIG_VERY_BIG_RAM
#define CONFIG_SYS_DDR_SDRAM_BASE	0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	(4 * CONFIG_DIMM_SLOTS_PER_CTLR)
#define CONFIG_DDR_SPD
#define CONFIG_SYS_SPD_BUS_NUM	0
#define CONFIG_SYS_SDRAM_SIZE	2048	/* for fixed parameter use */
#define SPD_EEPROM_ADDRESS1	0x51
#define SPD_EEPROM_ADDRESS2	0x52
#define SPD_EEPROM_ADDRESS	SPD_EEPROM_ADDRESS1
#define CTRL_INTLV_PREFERED	cacheline

/*
 * IFC Definitions
 */
#define CONFIG_SYS_FLASH_BASE		0xe8000000
#define CONFIG_SYS_FLASH_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_FLASH_BASE)
#define CONFIG_SYS_NOR0_CSPR_EXT	(0xf)
#define CONFIG_SYS_NOR0_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR_AMASK	IFC_AMASK(128*1024*1024)

/* NOR Flash Timing Params */
#define CONFIG_SYS_NOR_CSOR	CSOR_NAND_TRHZ_80

#define CONFIG_SYS_NOR_FTIM0	(FTIM0_NOR_TACSE(0x4) | \
				FTIM0_NOR_TEADC(0x5) | \
				FTIM0_NOR_TEAHC(0x5))
#define CONFIG_SYS_NOR_FTIM1	(FTIM1_NOR_TACO(0x35) | \
				FTIM1_NOR_TRAD_NOR(0x1A) |\
				FTIM1_NOR_TSEQRAD_NOR(0x13))
#define CONFIG_SYS_NOR_FTIM2	(FTIM2_NOR_TCS(0x4) | \
				FTIM2_NOR_TCH(0x4) | \
				FTIM2_NOR_TWPH(0x0E) | \
				FTIM2_NOR_TWP(0x1c))
#define CONFIG_SYS_NOR_FTIM3	0x0

#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45 /* count down from 45/5: 9..1 */

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* number of banks */
#define CONFIG_SYS_MAX_FLASH_SECT	1024	/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000	/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (ms) */
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS }

/* CPLD on IFC */
#define CONFIG_SYS_CPLD_BASE	0xffdf0000
#define CONFIG_SYS_CPLD_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_CPLD_BASE)
#define CONFIG_SYS_CSPR2_EXT	(0xf)
#define CONFIG_SYS_CSPR2	(CSPR_PHYS_ADDR(CONFIG_SYS_CPLD_BASE) \
				| CSPR_PORT_SIZE_8 \
				| CSPR_MSEL_GPCM \
				| CSPR_V)
#define CONFIG_SYS_AMASK2	IFC_AMASK(64*1024)
#define CONFIG_SYS_CSOR2	0x0

/* CPLD Timing parameters for IFC CS2 */
#define CONFIG_SYS_CS2_FTIM0		(FTIM0_GPCM_TACSE(0x0e) | \
					FTIM0_GPCM_TEADC(0x0e) | \
					FTIM0_GPCM_TEAHC(0x0e))
#define CONFIG_SYS_CS2_FTIM1		(FTIM1_GPCM_TACO(0x0e) | \
					FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_CS2_FTIM2		(FTIM2_GPCM_TCS(0x0e) | \
					FTIM2_GPCM_TCH(0x8) | \
					FTIM2_GPCM_TWP(0x1f))
#define CONFIG_SYS_CS2_FTIM3		0x0

/* NAND Flash on IFC */
#define CONFIG_NAND_FSL_IFC
#define CONFIG_SYS_NAND_BASE		0xff800000
#define CONFIG_SYS_NAND_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_NAND_BASE)

#define CONFIG_SYS_NAND_CSPR_EXT	(0xf)
#define CONFIG_SYS_NAND_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS) \
				| CSPR_PORT_SIZE_8 /* Port Size = 8 bit */ \
				| CSPR_MSEL_NAND	 /* MSEL = NAND */ \
				| CSPR_V)
#define CONFIG_SYS_NAND_AMASK	IFC_AMASK(64*1024)

#define CONFIG_SYS_NAND_CSOR	(CSOR_NAND_ECC_ENC_EN	/* ECC on encode */ \
				| CSOR_NAND_ECC_DEC_EN	/* ECC on decode */ \
				| CSOR_NAND_ECC_MODE_4	/* 4-bit ECC */	    \
				| CSOR_NAND_RAL_3	/* RAL = 2Byes */   \
				| CSOR_NAND_PGS_2K	/* Page Size = 2K */\
				| CSOR_NAND_SPRZ_64	/* Spare size = 64 */\
				| CSOR_NAND_PB(64))	/*Pages Per Block = 64*/

#define CONFIG_SYS_NAND_ONFI_DETECTION

/* ONFI NAND Flash mode0 Timing Params */
#define CONFIG_SYS_NAND_FTIM0		(FTIM0_NAND_TCCST(0x07) | \
					FTIM0_NAND_TWP(0x18)    | \
					FTIM0_NAND_TWCHT(0x07)  | \
					FTIM0_NAND_TWH(0x0a))
#define CONFIG_SYS_NAND_FTIM1		(FTIM1_NAND_TADLE(0x32) | \
					FTIM1_NAND_TWBE(0x39)   | \
					FTIM1_NAND_TRR(0x0e)    | \
					FTIM1_NAND_TRP(0x18))
#define CONFIG_SYS_NAND_FTIM2		(FTIM2_NAND_TRAD(0x0f)  | \
					FTIM2_NAND_TREH(0x0a)   | \
					FTIM2_NAND_TWHRE(0x1e))
#define CONFIG_SYS_NAND_FTIM3		0x0

#define CONFIG_SYS_NAND_DDR_LAW		11
#define CONFIG_SYS_NAND_BASE_LIST	{ CONFIG_SYS_NAND_BASE }
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BLOCK_SIZE	(512 * 1024)

#if defined(CONFIG_NAND)
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NAND_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NOR0_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NOR0_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NOR_FTIM3
#else
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NOR0_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NOR0_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NAND_FTIM3
#endif

#if defined(CONFIG_RAMBOOT_PBL)
#define CONFIG_SYS_RAMBOOT
#endif

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_MONITOR_BASE  CONFIG_SPL_TEXT_BASE
#else
#define CONFIG_SYS_MONITOR_BASE  CONFIG_SYS_TEXT_BASE /* start of monitor */
#endif

#define CONFIG_HWCONFIG

/* define to use L1 as initial stack */
#define CONFIG_L1_INIT_RAM
#define CONFIG_SYS_INIT_RAM_LOCK
#define CONFIG_SYS_INIT_RAM_ADDR	0xfdd00000 /* Initial L1 address */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH	0xf
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW	0xfe03c000
/* The assembler doesn't like typecast */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS \
			((CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH * 1ull << 32) | \
			CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW)
#define CONFIG_SYS_INIT_RAM_SIZE	0x00004000
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
						GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET
#define CONFIG_SYS_MONITOR_LEN		(768 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)

/*
 * Serial Port
 */
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		(get_bus_freq(0)/2)
#define CONFIG_SYS_BAUDRATE_TABLE	\
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}
#define CONFIG_SYS_NS16550_COM1 (CONFIG_SYS_CCSRBAR+0x11C500)
#define CONFIG_SYS_NS16550_COM2 (CONFIG_SYS_CCSRBAR+0x11C600)
#define CONFIG_SYS_NS16550_COM3 (CONFIG_SYS_CCSRBAR+0x11D500)
#define CONFIG_SYS_NS16550_COM4 (CONFIG_SYS_CCSRBAR+0x11D600)

/*
 * I2C
 */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_FSL
#define CONFIG_SYS_FSL_I2C_SLAVE   0x7F
#define CONFIG_SYS_FSL_I2C2_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C3_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C4_SLAVE  0x7F
#define CONFIG_SYS_FSL_I2C_OFFSET  0x118000
#define CONFIG_SYS_FSL_I2C2_OFFSET 0x118100
#define CONFIG_SYS_FSL_I2C3_OFFSET 0x119000
#define CONFIG_SYS_FSL_I2C4_OFFSET 0x119100
#define CONFIG_SYS_FSL_I2C_SPEED   100000
#define CONFIG_SYS_FSL_I2C2_SPEED  100000
#define CONFIG_SYS_FSL_I2C3_SPEED  100000
#define CONFIG_SYS_FSL_I2C4_SPEED  100000
#define I2C_MUX_PCA_ADDR_PRI	0x77 /* I2C bus multiplexer,primary */
#define I2C_MUX_PCA_ADDR_SEC1	0x75 /* I2C bus multiplexer,secondary 1 */
#define I2C_MUX_PCA_ADDR_SEC2	0x76 /* I2C bus multiplexer,secondary 2 */
#define I2C_MUX_CH_DEFAULT	0x8

#define I2C_MUX_CH_VOL_MONITOR	0xa

#define CONFIG_VID_FLS_ENV		"t208xrdb_vdd_mv"
#ifndef CONFIG_SPL_BUILD
#define CONFIG_VID
#endif
#define CONFIG_VOL_MONITOR_IR36021_SET
#define CONFIG_VOL_MONITOR_IR36021_READ
/* The lowest and highest voltage allowed for T208xRDB */
#define VDD_MV_MIN			819
#define VDD_MV_MAX			1212

/*
 * RapidIO
 */
#define CONFIG_SYS_SRIO1_MEM_VIRT	0xa0000000
#define CONFIG_SYS_SRIO1_MEM_PHYS	0xc20000000ull
#define CONFIG_SYS_SRIO1_MEM_SIZE	0x10000000 /* 256M */
#define CONFIG_SYS_SRIO2_MEM_VIRT	0xb0000000
#define CONFIG_SYS_SRIO2_MEM_PHYS	0xc30000000ull
#define CONFIG_SYS_SRIO2_MEM_SIZE	0x10000000 /* 256M */
/*
 * for slave u-boot IMAGE instored in master memory space,
 * PHYS must be aligned based on the SIZE
 */
#define CONFIG_SRIO_PCIE_BOOT_IMAGE_MEM_PHYS 0xfef200000ull
#define CONFIG_SRIO_PCIE_BOOT_IMAGE_MEM_BUS1 0xfff00000ull
#define CONFIG_SRIO_PCIE_BOOT_IMAGE_SIZE     0x100000 /* 1M */
#define CONFIG_SRIO_PCIE_BOOT_IMAGE_MEM_BUS2 0x3fff00000ull
/*
 * for slave UCODE and ENV instored in master memory space,
 * PHYS must be aligned based on the SIZE
 */
#define CONFIG_SRIO_PCIE_BOOT_UCODE_ENV_MEM_PHYS 0xfef100000ull
#define CONFIG_SRIO_PCIE_BOOT_UCODE_ENV_MEM_BUS 0x3ffe00000ull
#define CONFIG_SRIO_PCIE_BOOT_UCODE_ENV_SIZE    0x40000	/* 256K */

/* slave core release by master*/
#define CONFIG_SRIO_PCIE_BOOT_BRR_OFFSET 0xe00e4
#define CONFIG_SRIO_PCIE_BOOT_RELEASE_MASK 0x00000001 /* release core 0 */

/*
 * SRIO_PCIE_BOOT - SLAVE
 */
#ifdef CONFIG_SRIO_PCIE_BOOT_SLAVE
#define CONFIG_SYS_SRIO_PCIE_BOOT_UCODE_ENV_ADDR 0xFFE00000
#define CONFIG_SYS_SRIO_PCIE_BOOT_UCODE_ENV_ADDR_PHYS \
		(0x300000000ull | CONFIG_SYS_SRIO_PCIE_BOOT_UCODE_ENV_ADDR)
#endif

/*
 * eSPI - Enhanced SPI
 */

/*
 * General PCI
 * Memory space is mapped 1-1, but I/O space must start from 0.
 */
#define CONFIG_PCIE1		/* PCIE controller 1 */
#define CONFIG_PCIE2		/* PCIE controller 2 */
#define CONFIG_PCIE3		/* PCIE controller 3 */
#define CONFIG_PCIE4		/* PCIE controller 4 */
#define CONFIG_FSL_PCI_INIT	/* Use common FSL init code */
#define CONFIG_SYS_PCI_64BIT	/* enable 64-bit PCI resources */
/* controller 1, direct to uli, tgtid 3, Base address 20000 */
#define CONFIG_SYS_PCIE1_MEM_VIRT	0x80000000
#define CONFIG_SYS_PCIE1_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE1_MEM_PHYS	0xc00000000ull
#define CONFIG_SYS_PCIE1_MEM_SIZE	0x20000000      /* 512M */
#define CONFIG_SYS_PCIE1_IO_VIRT	0xf8000000
#define CONFIG_SYS_PCIE1_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE1_IO_PHYS	0xff8000000ull
#define CONFIG_SYS_PCIE1_IO_SIZE	0x00010000	/* 64k */

/* controller 2, Slot 2, tgtid 2, Base address 201000 */
#define CONFIG_SYS_PCIE2_MEM_VIRT	0xa0000000
#define CONFIG_SYS_PCIE2_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE2_MEM_PHYS	0xc20000000ull
#define CONFIG_SYS_PCIE2_MEM_SIZE	0x10000000 /* 256M */
#define CONFIG_SYS_PCIE2_IO_VIRT	0xf8010000
#define CONFIG_SYS_PCIE2_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE2_IO_PHYS	0xff8010000ull
#define CONFIG_SYS_PCIE2_IO_SIZE	0x00010000	/* 64k */

/* controller 3, Slot 1, tgtid 1, Base address 202000 */
#define CONFIG_SYS_PCIE3_MEM_VIRT	0xb0000000
#define CONFIG_SYS_PCIE3_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE3_MEM_PHYS	0xc30000000ull
#define CONFIG_SYS_PCIE3_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE3_IO_VIRT	0xf8020000
#define CONFIG_SYS_PCIE3_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE3_IO_PHYS	0xff8020000ull
#define CONFIG_SYS_PCIE3_IO_SIZE	0x00010000	/* 64k */

/* controller 4, Base address 203000 */
#define CONFIG_SYS_PCIE4_MEM_VIRT       0xc0000000
#define CONFIG_SYS_PCIE4_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE4_MEM_PHYS	0xc40000000ull
#define CONFIG_SYS_PCIE4_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE4_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE4_IO_PHYS	0xff8030000ull
#define CONFIG_SYS_PCIE4_IO_SIZE	0x00010000	/* 64k */

#ifdef CONFIG_PCI
#define CONFIG_PCI_INDIRECT_BRIDGE
#define CONFIG_FSL_PCIE_RESET           /* need PCIe reset errata LSZ ADD */
#define CONFIG_PCI_SCAN_SHOW	/* show pci devices on startup */
#endif

/* Qman/Bman */
#ifndef CONFIG_NOBQFMAN
#define CONFIG_SYS_BMAN_NUM_PORTALS	18
#define CONFIG_SYS_BMAN_MEM_BASE	0xf4000000
#define CONFIG_SYS_BMAN_MEM_PHYS	0xff4000000ull
#define CONFIG_SYS_BMAN_MEM_SIZE	0x02000000
#define CONFIG_SYS_BMAN_SP_CENA_SIZE    0x4000
#define CONFIG_SYS_BMAN_SP_CINH_SIZE    0x1000
#define CONFIG_SYS_BMAN_CENA_BASE       CONFIG_SYS_BMAN_MEM_BASE
#define CONFIG_SYS_BMAN_CENA_SIZE       (CONFIG_SYS_BMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_BMAN_CINH_BASE       (CONFIG_SYS_BMAN_MEM_BASE + \
					CONFIG_SYS_BMAN_CENA_SIZE)
#define CONFIG_SYS_BMAN_CINH_SIZE       (CONFIG_SYS_BMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_BMAN_SWP_ISDR_REG	0xE08
#define CONFIG_SYS_QMAN_NUM_PORTALS	18
#define CONFIG_SYS_QMAN_MEM_BASE	0xf6000000
#define CONFIG_SYS_QMAN_MEM_PHYS	0xff6000000ull
#define CONFIG_SYS_QMAN_MEM_SIZE	0x02000000
#define CONFIG_SYS_QMAN_SP_CENA_SIZE    0x4000
#define CONFIG_SYS_QMAN_SP_CINH_SIZE    0x1000
#define CONFIG_SYS_QMAN_CENA_BASE       CONFIG_SYS_QMAN_MEM_BASE
#define CONFIG_SYS_QMAN_CENA_SIZE       (CONFIG_SYS_QMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_QMAN_CINH_BASE       (CONFIG_SYS_QMAN_MEM_BASE + \
					CONFIG_SYS_QMAN_CENA_SIZE)
#define CONFIG_SYS_QMAN_CINH_SIZE       (CONFIG_SYS_QMAN_MEM_SIZE >> 1)
#define CONFIG_SYS_QMAN_SWP_ISDR_REG	0xE08

#define CONFIG_SYS_DPAA_FMAN
#define CONFIG_SYS_DPAA_PME
#define CONFIG_SYS_PMAN
#define CONFIG_SYS_DPAA_DCE
#define CONFIG_SYS_DPAA_RMAN		/* RMan */
#define CONFIG_SYS_INTERLAKEN

/* Default address of microcode for the Linux Fman driver */
#if defined(CONFIG_SPIFLASH)
/*
 * env is stored at 0x100000, sector size is 0x10000, ucode is stored after
 * env, so we got 0x110000.
 */
#define CONFIG_SYS_CORTINA_FW_IN_SPIFLASH
#define CONFIG_SYS_FMAN_FW_ADDR		0x110000
#define CONFIG_CORTINA_FW_ADDR		0x120000

#elif defined(CONFIG_SDCARD)
/*
 * PBL SD boot image should stored at 0x1000(8 blocks), the size of the image is
 * about 1MB (2048 blocks), Env is stored after the image, and the env size is
 * 0x2000 (16 blocks), 8 + 2048 + 16 = 2072, enlarge it to 2080.
 */
#define CONFIG_SYS_CORTINA_FW_IN_MMC
#define CONFIG_SYS_FMAN_FW_ADDR		(512 * 0x820)
#define CONFIG_CORTINA_FW_ADDR		(512 * 0x8a0)

#elif defined(CONFIG_NAND)
#define CONFIG_SYS_CORTINA_FW_IN_NAND
#define CONFIG_SYS_FMAN_FW_ADDR		(3 * CONFIG_SYS_NAND_BLOCK_SIZE)
#define CONFIG_CORTINA_FW_ADDR		(4 * CONFIG_SYS_NAND_BLOCK_SIZE)
#elif defined(CONFIG_SRIO_PCIE_BOOT_SLAVE)
/*
 * Slave has no ucode locally, it can fetch this from remote. When implementing
 * in two corenet boards, slave's ucode could be stored in master's memory
 * space, the address can be mapped from slave TLB->slave LAW->
 * slave SRIO or PCIE outbound window->master inbound window->
 * master LAW->the ucode address in master's memory space.
 */
#define CONFIG_SYS_CORTINA_FW_IN_REMOTE
#define CONFIG_SYS_FMAN_FW_ADDR		0xFFE00000
#define CONFIG_CORTINA_FW_ADDR		0xFFE10000
#else
#define CONFIG_SYS_CORTINA_FW_IN_NOR
#define CONFIG_SYS_FMAN_FW_ADDR		0xEFF00000
#define CONFIG_CORTINA_FW_ADDR		0xEFE00000
#endif
#define CONFIG_SYS_QE_FMAN_FW_LENGTH	0x10000
#define CONFIG_SYS_FDT_PAD		(0x3000 + CONFIG_SYS_QE_FMAN_FW_LENGTH)
#endif /* CONFIG_NOBQFMAN */

#ifdef CONFIG_SYS_DPAA_FMAN
#define CONFIG_PHY_CORTINA
#define CONFIG_PHY_REALTEK
#define CONFIG_CORTINA_FW_LENGTH	0x40000
#define RGMII_PHY1_ADDR		0x01  /* RealTek RTL8211E */
#define RGMII_PHY2_ADDR		0x02
#define CORTINA_PHY_ADDR1	0x0c  /* Cortina CS4315 */
#define CORTINA_PHY_ADDR2	0x0d
#define FM1_10GEC3_PHY_ADDR	0x00  /* Aquantia AQ1202 10G Base-T */
#define FM1_10GEC4_PHY_ADDR	0x01
#endif

#ifdef CONFIG_FMAN_ENET
#define CONFIG_ETHPRIME		"FM1@DTSEC3"
#endif

/*
 * SATA
 */
#ifdef CONFIG_FSL_SATA_V2
#define CONFIG_SYS_SATA_MAX_DEVICE	2
#define CONFIG_SATA1
#define CONFIG_SYS_SATA1		CONFIG_SYS_MPC85xx_SATA1_ADDR
#define CONFIG_SYS_SATA1_FLAGS		FLAGS_DMA
#define CONFIG_SATA2
#define CONFIG_SYS_SATA2		CONFIG_SYS_MPC85xx_SATA2_ADDR
#define CONFIG_SYS_SATA2_FLAGS		FLAGS_DMA
#define CONFIG_LBA48
#endif

/*
 * USB
 */
#ifdef CONFIG_USB_EHCI_HCD
#define CONFIG_USB_EHCI_FSL
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_HAS_FSL_DR_USB
#endif

/*
 * SDHC
 */
#ifdef CONFIG_MMC
#define CONFIG_SYS_FSL_ESDHC_ADDR	CONFIG_SYS_MPC85xx_ESDHC_ADDR
#define CONFIG_SYS_FSL_ESDHC_BROKEN_TIMEOUT
#define CONFIG_SYS_FSL_MMC_HAS_CAPBLT_VS33
#endif

/*
 * Dynamic MTD Partition support with mtdparts
 */

/*
 * Environment
 */

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LOAD_ADDR	0x2000000 /* default load address */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 64 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ	(64 << 20)	/* Initial map for Linux*/
#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* Increase max gunzip size */

#ifdef CONFIG_CMD_KGDB
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2	/* which serial port to use */
#endif

/*
 * Environment Configuration
 */
#define CONFIG_ROOTPATH	 "/opt/nfsroot"
#define CONFIG_BOOTFILE	 "uImage"
#define CONFIG_UBOOTPATH "u-boot.bin"	/* U-Boot image on TFTP server */

/* default location for tftp and bootm */
#define CONFIG_LOADADDR		1000000
#define __USB_PHY_TYPE		utmi

#define	CONFIG_EXTRA_ENV_SETTINGS				\
	"hwconfig=fsl_ddr:"					\
	"ctlr_intlv=" __stringify(CTRL_INTLV_PREFERED) ","	\
	"bank_intlv=auto;"					\
	"usb1:dr_mode=host,phy_type=" __stringify(__USB_PHY_TYPE) "\0"\
	"netdev=eth0\0"						\
	"uboot=" __stringify(CONFIG_UBOOTPATH) "\0"		\
	"ubootaddr=" __stringify(CONFIG_SYS_TEXT_BASE) "\0"	\
	"tftpflash=tftpboot $loadaddr $uboot && "		\
	"protect off $ubootaddr +$filesize && "			\
	"erase $ubootaddr +$filesize && "			\
	"cp.b $loadaddr $ubootaddr $filesize && "		\
	"protect on $ubootaddr +$filesize && "			\
	"cmp.b $loadaddr $ubootaddr $filesize\0"		\
	"consoledev=ttyS0\0"					\
	"ramdiskaddr=2000000\0"					\
	"ramdiskfile=t2080rdb/ramdisk.uboot\0"			\
	"fdtaddr=1e00000\0"					\
	"fdtfile=t2080rdb/t2080rdb.dtb\0"			\
	"bdev=sda3\0"

/*
 * For emulation this causes u-boot to jump to the start of the
 * proof point app code automatically
 */
#define CONFIG_PROOF_POINTS				\
	"setenv bootargs root=/dev/$bdev rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"cpu 1 release 0x29000000 - - -;"		\
	"cpu 2 release 0x29000000 - - -;"		\
	"cpu 3 release 0x29000000 - - -;"		\
	"cpu 4 release 0x29000000 - - -;"		\
	"cpu 5 release 0x29000000 - - -;"		\
	"cpu 6 release 0x29000000 - - -;"		\
	"cpu 7 release 0x29000000 - - -;"		\
	"go 0x29000000"

#define CONFIG_HVBOOT				\
	"setenv bootargs config-addr=0x60000000; "	\
	"bootm 0x01000000 - 0x00f00000"

#define CONFIG_ALU				\
	"setenv bootargs root=/dev/$bdev rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"cpu 1 release 0x01000000 - - -;"		\
	"cpu 2 release 0x01000000 - - -;"		\
	"cpu 3 release 0x01000000 - - -;"		\
	"cpu 4 release 0x01000000 - - -;"		\
	"cpu 5 release 0x01000000 - - -;"		\
	"cpu 6 release 0x01000000 - - -;"		\
	"cpu 7 release 0x01000000 - - -;"		\
	"go 0x01000000"

#define CONFIG_LINUX				\
	"setenv bootargs root=/dev/ram rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"setenv ramdiskaddr 0x02000000;"		\
	"setenv fdtaddr 0x00c00000;"			\
	"setenv loadaddr 0x1000000;"			\
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_HDBOOT					\
	"setenv bootargs root=/dev/$bdev rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $loadaddr $bootfile;"			\
	"tftp $fdtaddr $fdtfile;"			\
	"bootm $loadaddr - $fdtaddr"

#define CONFIG_NFSBOOTCOMMAND			\
	"setenv bootargs root=/dev/nfs rw "	\
	"nfsroot=$serverip:$rootpath "		\
	"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $loadaddr $bootfile;"		\
	"tftp $fdtaddr $fdtfile;"		\
	"bootm $loadaddr - $fdtaddr"

#define CONFIG_RAMBOOTCOMMAND				\
	"setenv bootargs root=/dev/ram rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $ramdiskaddr $ramdiskfile;"		\
	"tftp $loadaddr $bootfile;"			\
	"tftp $fdtaddr $fdtfile;"			\
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_BOOTCOMMAND		CONFIG_LINUX

#include <asm/fsl_secure_boot.h>

#endif	/* __T2080RDB_H */
