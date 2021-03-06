#ifndef __DDRTEST_GLOBAL_SRAM_MAP_H_
#define __DDRTEST_GLOBAL_SRAM_MAP_H_ 
#include <soc_lpmcu_baseaddr_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#ifdef __FASTBOOT__
#define DDRTEST_MMBUF_BASE SOC_ACPU_MMBUF_BASE_ADDR
#define DDRTEST_SECRAM_BASE SOC_ACPU_SECRAM_BASE_ADDR
#else
#define DDRTEST_MMBUF_BASE SOC_LPMCU_MMBUF_BASE_ADDR
#define DDRTEST_SECRAM_BASE SOC_LPMCU_SECRAM_BASE_ADDR
#endif
#define DDRTEST_ACPU_RECORD_MAGIC ((unsigned int)("AP"))
#define DDRTEST_LPM3_RECORD_MAGIC ((unsigned int)("M3"))
#define DDRTEST_EX_SPINLOCK_BASE (DDRTEST_SECRAM_BASE)
#define DDRTEST_EX_SPINLOCK_SIZE (0x100)
#define DDRTEST_PRINT_SPINLOCK (DDRTEST_EX_SPINLOCK_BASE)
#define DDRTEST_LOG_SPINLOCK (DDRTEST_PRINT_SPINLOCK + 0x8)
#define DDRTEST_STORAGE_SPINLOCK (DDRTEST_LOG_SPINLOCK + 0x8)
#define DDRTEST_LOG_BUFFER_SPINLOCK (DDRTEST_STORAGE_SPINLOCK + 0x8)
#define DDRTEST_LED_BREATH_SPINLOCK (DDRTEST_LOG_BUFFER_SPINLOCK + 0x8)
#define DDRTEST_EX_SPINLOCK_END (DDRTEST_EX_SPINLOCK_BASE + DDRTEST_EX_SPINLOCK_SIZE)
#define DDRTEST_RECORD_BASE (DDRTEST_EX_SPINLOCK_END)
#define DDRTEST_RECORD_NR (100)
#define DDRTEST_RECORD_SIZE ((32 * DDRTEST_RECORD_NR) + 16)
#define DDRTEST_ACPU_RECORD_BASE (DDRTEST_RECORD_BASE)
#define DDRTEST_LPMCU_RECORD_BASE (DDRTEST_ACPU_RECORD_BASE + DDRTEST_RECORD_SIZE)
#define DDRTEST_RECORD_END (DDRTEST_LPMCU_RECORD_BASE + DDRTEST_RECORD_SIZE)
#define DDRTEST_REG_INFO_BASE (DDRTEST_RECORD_END)
#define DDRTEST_REG_INFO_SIZE (0x1000)
#define DDRTEST_REG_INFO_END (DDRTEST_REG_INFO_BASE + DDRTEST_REG_INFO_SIZE)
#define DDRTEST_REG_TRAIN_BASE (DDRTEST_REG_INFO_END)
#define DDRTEST_REG_TRAIN_SIZE (0x2800)
#define DDRTEST_REG_TRAIN_END (DDRTEST_REG_TRAIN_BASE + DDRTEST_REG_TRAIN_SIZE)
#define DDRTEST_ERROR_AP_FLAG (DDRTEST_REG_TRAIN_END)
#define DDRTEST_ERROR_LPM3_FLAG (DDRTEST_ERROR_AP_FLAG + 4)
#define DDRTEST_LOG_BASE (DDRTEST_MMBUF_BASE)
#define DDRTEST_ACPU_LOG_BASE (DDRTEST_LOG_BASE)
#define DDRTEST_ACPU_LOG_SIZE (0x18000)
#define DDRTEST_LPMCU_LOG_BASE (DDRTEST_ACPU_LOG_BASE + DDRTEST_ACPU_LOG_SIZE)
#define DDRTEST_LPMCU_LOG_SIZE (0x18000)
#define DDRTEST_LOG_END (DDRTEST_LPMCU_LOG_BASE + DDRTEST_LPMCU_LOG_SIZE)
#define STORAGE_FSM_LOG_OFFSET (0x00000000)
#define STORAGE_FSM_CFG_OFFSET (0x00008000)
#define STORAGE_ACPU_LOG_OFFSET (0x00100000)
#define STORAGE_LPM3_LOG_OFFSET (0x00180000)
#define STORAGE_ACPU_RECORD_OFFSET (0x00200000)
#define STORAGE_LPM3_RECORD_OFFSET (0x00280000)
#define STORAGE_TRAIN_INIT_OFFSET (0x00300000)
#define STORAGE_TRAIN_CUR_OFFSET (STORAGE_TRAIN_INIT_OFFSET + DDRTEST_REG_TRAIN_SIZE)
#define STORAGE_TRAIN_REINIT_OFFSET (STORAGE_TRAIN_CUR_OFFSET + DDRTEST_REG_TRAIN_SIZE)
#define STORAGE_REG_DUMP_OFFSET (STORAGE_TRAIN_REINIT_OFFSET + DDRTEST_REG_TRAIN_SIZE)
#define PART_DDR_TEST_LOG (PART_PATCH)
#define PART_DDR_TEST_LOG_OFFSET (0)
#define PART_DDR_TEST_IMAGE (PART_PATCH)
#define PART_DDR_TEST_IMAGE_OFFSET (0x400000)
#define PART_DDR_TEST_LPM3 (PART_PATCH)
#define PART_DDR_TEST_LPM3_OFFSET (0xF00000)
struct ddrtest_error_header {
    char magic_number[4];
    unsigned int error_counter;
    unsigned int wr_index;
    unsigned int overflow :1;
 unsigned int freq_prod :3;
 unsigned int reserved :4;
};
struct ddrtest_error_data {
    unsigned int addr_h;
    unsigned int addr_l;
    unsigned int expect_data;
    unsigned int actual_data;
    unsigned int algo_id;
    unsigned int reserved[3];
};
struct ddrtest_error_info {
    struct ddrtest_error_header header;
    struct ddrtest_error_data data[DDRTEST_RECORD_NR];
};
#endif
