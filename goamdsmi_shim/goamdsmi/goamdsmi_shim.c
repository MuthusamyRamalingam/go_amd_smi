// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2024, Advanced Micro Devices, Inc.
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
#include "goamdsmi_shim.h"
#include <unistd.h>

int32_t goamdsmi_amdsmi_present()
{
	if(0 == access("/opt/rocm/lib/libamd_smi.so", F_OK)) 
	{
		return 1;
	}
	return 0;
}
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
int32_t goamdsmi_cpu_init()	
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_init();
	}
	return go_shim_esmi_init();
}

int32_t goamdsmi_cpu_threads_per_core_get()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_threads_per_core_get();
	}
	return go_shim_esmi_threads_per_core_get();
}

int32_t goamdsmi_cpu_number_of_threads_get()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_number_of_threads_get();
	}
	return go_shim_esmi_number_of_threads_get();
}

int32_t goamdsmi_cpu_number_of_sockets_get()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_number_of_sockets_get();
	}
	return go_shim_esmi_number_of_sockets_get();
}

uint64_t goamdsmi_cpu_core_energy_get(uint32_t thread_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_core_energy_get(thread_index);
	}
	return go_shim_esmi_core_energy_get(thread_index);
}

uint64_t goamdsmi_cpu_socket_energy_get(uint32_t socket_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_socket_energy_get(socket_index);
	}
	return go_shim_esmi_socket_energy_get(socket_index);
}

uint32_t goamdsmi_cpu_prochot_status_get(uint32_t socket_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_prochot_status_get(socket_index);
	}
	return go_shim_esmi_prochot_status_get(socket_index);
}

uint32_t goamdsmi_cpu_socket_power_get(uint32_t socket_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_socket_power_get(socket_index);
	}
	return go_shim_esmi_socket_power_get(socket_index);
}

uint32_t goamdsmi_cpu_socket_power_cap_get(uint32_t socket_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_socket_power_cap_get(socket_index);
	}
	return go_shim_esmi_socket_power_cap_get(socket_index);
}

uint32_t goamdsmi_cpu_core_boostlimit_get(uint32_t thread_index)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmicpu_core_boostlimit_get(thread_index);
	}
	return go_shim_esmi_core_boostlimit_get(thread_index);
}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
int32_t goamdsmi_gpu_init()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_init();
	}
	return go_shim_rsmi_init();
}

int32_t goamdsmi_gpu_shutdown()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_shutdown();
	}
	return go_shim_rsmi_shutdown();
}

int32_t goamdsmi_gpu_num_monitor_devices()
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_num_monitor_devices();
	}
	return go_shim_rsmi_num_monitor_devices();
}

char* goamdsmi_gpu_dev_name_get(uint32_t dv_ind)
{
    if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_name_get(dv_ind);
	}
	return go_shim_rsmi_dev_name_get(dv_ind);
}

uint16_t goamdsmi_gpu_dev_id_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_id_get(dv_ind);
	}
	return go_shim_rsmi_dev_id_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_pci_id_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_pci_id_get(dv_ind);
	}
	return go_shim_rsmi_dev_pci_id_get(dv_ind);
}

char* goamdsmi_gpu_dev_vendor_name_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_vendor_name_get(dv_ind);
	}
	return go_shim_rsmi_dev_vendor_name_get(dv_ind);
}

char* goamdsmi_gpu_dev_vbios_version_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_vbios_version_get(dv_ind);
	}
	return go_shim_rsmi_dev_vbios_version_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_power_cap_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_power_cap_get(dv_ind);
	}
	return go_shim_rsmi_dev_power_cap_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_power_ave_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_power_ave_get(dv_ind);
	}
	return go_shim_amdsmigpu_dev_power_ave_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_temp_metric_get(dv_ind, sensor, metric);
	}
	return go_shim_rsmi_dev_temp_metric_get(dv_ind, sensor, metric);
}

uint32_t goamdsmi_gpu_dev_overdrive_level_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_overdrive_level_get(dv_ind);
	}
	return go_shim_rsmi_dev_overdrive_level_get(dv_ind);
}

uint32_t goamdsmi_gpu_dev_mem_overdrive_level_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_overdrive_level_get(dv_ind);
	}
	return go_shim_rsmi_dev_overdrive_level_get(dv_ind);
}

uint32_t goamdsmi_gpu_dev_perf_level_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_perf_level_get(dv_ind);
	}
	return go_shim_rsmi_dev_perf_level_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_clk_freq_get_sclk(dv_ind);
}

uint64_t goamdsmi_gpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_clk_freq_get_mclk(dv_ind);
}

uint64_t goamdsmi_gpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(dv_ind);
	}
	return go_shim_rsmi_od_volt_freq_range_min_get_sclk(dv_ind);
}

uint64_t goamdsmi_gpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(dv_ind);
	}
	return go_shim_rsmi_od_volt_freq_range_min_get_mclk(dv_ind);
}

uint64_t goamdsmi_gpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(dv_ind);
	}
	return go_shim_rsmi_od_volt_freq_range_max_get_sclk(dv_ind);
}

uint64_t goamdsmi_gpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(dv_ind);
	}
	return go_shim_rsmi_od_volt_freq_range_max_get_mclk(dv_ind);
}

uint64_t goamdsmi_gpu_dev_gpu_busy_percent_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_busy_percent_get(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_busy_percent_get(dv_ind);
}


uint64_t goamdsmi_gpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_memory_busy_percent_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_gpu_memory_usage_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_memory_usage_get(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_memory_usage_get(dv_ind);
}

uint64_t goamdsmi_gpu_dev_gpu_memory_total_get(uint32_t dv_ind)
{
	if(goamdsmi_amdsmi_present())
	{
		return go_shim_amdsmigpu_dev_gpu_memory_total_get(dv_ind);
	}
	return go_shim_rsmi_dev_gpu_memory_total_get(dv_ind);
}

