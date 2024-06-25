// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2022, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sellcopies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *  - The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Advanced Micro Devices,
 * Inc. shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization from
 * the Advanced Micro Devices, Inc.
 *
 */

#include <stdint.h>
#include "rocm_smi_go_shim.h"
#ifdef WITH_ROCM_SMI
#include <rocm_smi/rocm_smi.h>
#endif
#include <stdlib.h>

#ifdef WITH_ROCM_SMI
goamdsmi_status_t go_shim_rsmi_init()
{
	return (RSMI_STATUS_SUCCESS == rsmi_init(0)) ? GOAMDSMI_STATUS_SUCCESS : GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_shutdown()
{
    return (RSMI_STATUS_SUCCESS == rsmi_shut_down()) ? GOAMDSMI_STATUS_SUCCESS : GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_num_monitor_devices(uint32_t* gpu_num_monitor_devices)
{
	*gpu_num_monitor_devices				= 0;
	uint32_t gpu_num_monitor_devices_temp	= 0;

	if(RSMI_STATUS_SUCCESS == rsmi_num_monitor_devices(&gpu_num_monitor_devices_temp))
	{
		*gpu_num_monitor_devices = gpu_num_monitor_devices_temp
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)
{
    uint32_t len = 256;
    char *dev_name = (char*)malloc(sizeof(char)*len);
    dev_name[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_name_get(dv_ind, dev_name, &len))
    {
        *gpu_dev_name = dev_name;
		return GOAMDSMI_STATUS_SUCCESS;
    }
	
	free(dev_name);dev_name = NULL;
	
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)
{
	*gpu_dev_id					= 0;
	uint16_t gpu_dev_id_temp 	= 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_id_get(dv_ind, &gpu_dev_id_temp))
	{
		*gpu_dev_id = gpu_dev_id_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)
{
	*gpu_pci_id					= 0;
	uint64_t gpu_pci_id_temp 	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_pci_id_get(dv_ind, &gpu_pci_id_temp))
	{
		*gpu_pci_id = gpu_pci_id_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;;
}

goamdsmi_status_t go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)
{
    uint32_t len = 256;
    char *vendor_name = (char*)malloc(sizeof(char)*len);
    vendor_name[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_vendor_name_get(dv_ind, vendor_name, &len))
    {
        *gpu_vendor_name = vendor_name;
		return GOAMDSMI_STATUS_SUCCESS;
    }

	free(vendor_name);vendor_name = NULL;
	
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)
{
    uint32_t len = 256;
    char *vbios_ver = (char*)malloc(sizeof(char)*len);
    vbios_ver[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_vbios_version_get(dv_ind, vbios_ver, &len))
    {
        *vbios_version = vbios_ver;
		return GOAMDSMI_STATUS_SUCCESS;
    }
	free(vbios_ver);vbios_ver = NULL;
	
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)
{
	*gpu_power_cap					= 0;
	uint64_t gpu_power_cap_temp 	= 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_power_cap_get(dv_ind, 0, &gpu_power_cap_temp))
	{
		*gpu_power_cap = gpu_power_cap_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_power_ave_get(uint32_t dv_ind, uint64_t* gpu_power_avg)
{
	*gpu_power_avg					= 0;
	uint64_t gpu_power_avg_temp	 	= 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_power_ave_get(dv_ind, 0, &gpu_power_avg_temp))
	{
		*gpu_power_avg = gpu_power_avg_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)
{
	*gpu_temperature					= 0;
	uint64_t gpu_temperature_temp	 	= 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_temp_metric_get(dv_ind, sensor, metric, &gpu_temperature_temp))
	{
		*gpu_temperature = gpu_temperature_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)
{
	*gpu_overdrive_level					= 0;
	uint64_t gpu_overdrive_level_temp	 	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_overdrive_level_get(dv_ind, &gpu_overdrive_level_temp))
	{
		*gpu_overdrive_level = gpu_overdrive_level_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)
{
	*gpu_mem_overdrive_level				= 0;
	uint64_t gpu_mem_overdrive_level_temp	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_mem_overdrive_level_get(dv_ind, &gpu_mem_overdrive_level_temp))
    {
		*gpu_mem_overdrive_level = gpu_mem_overdrive_level_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)
{
	*gpu_perf					= 0;
    rsmi_dev_perf_level_t perf	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_perf_level_get(dv_ind, &perf))
	{
		*gpu_perf = perf;				//Conversion from rsmi_dev_perf_level_t to uint32_t
		return GOAMDSMI_STATUS_SUCCESS;
	}

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)
{
	*gpu_sclk_freq				= 0;
	rsmi_frequencies_t freq		= {0};

	if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_SYS, &freq))
	{
		*gpu_sclk_freq = freq.frequency[freq.current];
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)
{
	*gpu_memclk_freq			= 0;
	rsmi_frequencies_t freq		= {0};

	if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_MEM, &freq))
	{
		*gpu_memclk_freq = freq.frequency[freq.current];
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)
{
	*gpu_min_sclk			= 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
	{
        *gpu_min_sclk = odv.curr_sclk_range.lower_bound;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)
{
	*gpu_min_memclk			= 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
	{
        *gpu_min_memclk = odv.curr_mclk_range.lower_bound;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)
{
	*gpu_max_sclk			= 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
	{
        *gpu_max_sclk = odv.curr_sclk_range.upper_bound;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)
{
	*gpu_max_memclk			= 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
	{
        *gpu_max_memclk = odv.curr_mclk_range.upper_bound;
		return GOAMDSMI_STATUS_SUCCESS;
	}

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_busy_percent)
{
	*gpu_busy_percent				= 0;
	uint64_t gpu_busy_percent_temp	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_busy_percent_get(dv_ind, &gpu_busy_percent_temp))
	{
        *gpu_busy_percent = gpu_busy_percent_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}


goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)
{
	*gpu_memory_busy_percent 		= 0
     uint64_t gpu_memory_total 		= 0;
	 uint64_t gpu_memory_total_temp = 0;

    if( (RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_total))&& 
		(RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp)))
	{
		*gpu_memory_busy_percent = (uint64_t)(gpu_memory_total*100)/gpu_memory_total_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)
{
	*gpu_memory_usage				= 0;
    uint64_t gpu_memory_usage_temp	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_usage_temp))
	{
        *gpu_memory_usage = (uint64_t)gpu_memory_usage_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}

uint64_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)
{
	*gpu_memory_total				= 0;
    uint64_t gpu_memory_total_temp	= 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp))
	{
        *gpu_memory_total = (uint64_t)gpu_memory_total_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
		
    return GOAMDSMI_STATUS_FAILURE;
}
#else
goamdsmi_status_t go_shim_rsmi_init()														{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_shutdown()													{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_num_monitor_devices(uint32_t* gpu_num_monitor_devices)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_power_ave_get(uint32_t dv_ind, uint64_t* gpu_power_avg)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)							{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)				{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_busy_percent)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)					{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)			{return GOAMDSMI_STATUS_FAILURE;}
#endif	

