/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#ifndef __HISI_JPU_H__
#define __HISI_JPU_H__


#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/regulator/driver.h>
#include <linux/compat.h>
#include <linux/fs.h>
#include <linux/module.h>

#include <linux/ion.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/hisi/hisi-iommu.h>

#include "hisi_jpu_def.h"
#include "hisi_jpu_common.h"
#include "hisi_jpu_regs.h"
#include "hisi_jpu_regs.h"
#include "soc_jpu_interface.h"

#define DEV_NAME_JPU	"hisi_jpu"
#define DTS_COMP_JPU_NAME	"hisilicon,hisijpu"
#define REGULATOR_JPU_NAME	"regulator_jpu"

#define IRQ_JPU_DEC_DONE_NAME	"irq_jpu_dec_done"
#define IRQ_JPU_DEC_ERR_NAME	"irq_jpu_dec_err"
#define IRQ_JPU_DEC_OTHER_NAME	"irq_jpu_dec_other"

#define JPU_DEC_DONE_TIMEOUT_THRESHOLD_ASIC	(5 * 1000)
#define JPU_DEC_DONE_TIMEOUT_THRESHOLD_FPGA	(15 * 1000)


#define HISI_JPU_ION_CLIENT_NAME	"hisi_jpu_ion"

#define CONFIG_LOW_POWER
/*#define CONFIG_NO_USE_INTERFACE*/
/*#define CONFIG_JPU_SMMU_DISABLE*/

struct hisi_jpu_data_type {
	uint32_t index;
	uint32_t ref_cnt;
	uint32_t fpga_flag;

	struct platform_device *pdev;
	uint32_t jpu_major;
	struct class *jpu_class;
	struct device *jpu_dev;

	char __iomem *jpu_cvdr_base;
	char __iomem *jpu_top_base;
	char __iomem *jpu_dec_base;
	char __iomem *jpu_smmu_base;
	char __iomem *media1_crg_base;
	char __iomem *peri_crg_base;
	char __iomem *pmctrl_base;
	char __iomem *sctrl_base;

	uint32_t jpu_done_irq;
	uint32_t jpu_err_irq;
	uint32_t jpu_other_irq;

	wait_queue_head_t jpu_dec_done_wq;
	uint32_t jpu_dec_done_flag;

	struct regulator *jpu_regulator;

	const char *isp_axim_clk_name;
	const char *isp_apbm_clk_name;
	const char *jpg_func_clk_name;

	struct clk *isp_axim_clk;
	struct clk *isp_apbm_clk;
	struct clk *jpg_func_clk;

	struct ion_client *ion_client;
	struct ion_handle *lb_ion_handle;
	struct iommu_map_format iommu_format;
	struct iommu_domain* hisijpu_domain;

	uint32_t lb_addr; /* line buffer addr*/
	bool power_on;
	struct semaphore blank_sem;

	jpu_dec_reg_t jpu_dec_reg_default;
	jpu_dec_reg_t jpu_dec_reg;
	bool jpu_res_initialized;

	jpu_data_t jpu_req;
};


/******************************************************************************
** FUNCTIONS PROTOTYPES
*/
extern int g_debug_jpu_dec;
extern int g_debug_jpu_dec_job_timediff;

uint32_t jpu_set_bits32(uint32_t old_val, uint32_t val, uint8_t bw, uint8_t bs);
void jpu_set_reg(char __iomem *addr, uint32_t val, uint8_t bw, uint8_t bs);
void jpu_get_timestamp(struct timeval *tv);
long jpu_timestamp_diff(struct timeval *lasttime, struct timeval *curtime);
int hisi_jpu_lb_alloc(struct hisi_jpu_data_type *hisijd);
void hisi_jpu_lb_free(struct hisi_jpu_data_type *hisijd);

int hisijpu_irq_request(struct hisi_jpu_data_type *hisijd);
int hisijpu_irq_enable(struct hisi_jpu_data_type *hisijd);
int hisijpu_irq_disable(struct hisi_jpu_data_type *hisijd);
int hisijpu_irq_disable_nosync(struct hisi_jpu_data_type *hisijd);

int hisijpu_regulator_enable(struct hisi_jpu_data_type *hisijd);
int hisijpu_regulator_disable(struct hisi_jpu_data_type *hisijd);
int hisijpu_clk_enable(struct hisi_jpu_data_type *hisijd);
int hisijpu_clk_disable(struct hisi_jpu_data_type *hisijd);
int hisijpu_enable_iommu(struct platform_device *pdev);
void hisijpu_disable_iommu(struct platform_device *pdev);
int hisi_jpu_register(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_unregister(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_on(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_off(struct hisi_jpu_data_type *hisijd);

void hisi_jpu_dec_normal_reset(struct hisi_jpu_data_type *hisijd);
void hisi_jpu_dec_error_reset(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_dec_done_config(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_dec_err_config(struct hisi_jpu_data_type *hisijd);
int hisi_jpu_dec_other_config(struct hisi_jpu_data_type *hisijd);

irqreturn_t hisi_jpu_dec_done_isr(int irq, void *ptr);
irqreturn_t hisi_jpu_dec_err_isr(int irq, void *ptr);
irqreturn_t hisi_jpu_dec_other_isr(int irq, void *ptr);
void hisi_jpu_dec_interrupt_unmask(struct hisi_jpu_data_type *hisijd);
void hisi_jpu_dec_interrupt_mask(struct hisi_jpu_data_type *hisijd);
void hisi_jpu_dec_interrupt_clear(struct hisi_jpu_data_type *hisijd);

int hisijpu_check_userdata(struct hisi_jpu_data_type *hisijd, jpu_data_t *jpu_req);
int hisijpu_job_exec(struct hisi_jpu_data_type *hisijd, void __user *argp);


#endif /* __HISI_JPU_H__ */
