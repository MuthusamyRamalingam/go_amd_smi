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
#include "amdsmi_go_shim.h"
#ifdef AMDSMI_BUILD
#include <amd_smi/amdsmi.h>
#endif
#include <unistd.h>
#include <stdio.h>

#define nullptr ((void*)0)

#ifdef AMDSMI_BUILD
#define MAX_SOCKET_ACROSS_SYSTEM	     4
#define CPU_0						     0
#define GPU_SENSOR_0					 0
#define MAX_CPU_PER_SOCKET               4
#define MAX_PHYSICALCORE_ACROSS_SYSTEM 384
#define MAX_LOGICALCORE_ACROSS_SYSTEM  768
#define MAX_GPU_DEVICE_ACROSS_SYSTEM    24

static uint32_t num_apuSockets					   = 0;
static uint32_t num_cpuSockets					   = 0;
static uint32_t num_gpuSockets					   = 0;

static uint32_t num_cpu_inAllSocket          	   = 0;
static uint32_t num_cpu_physicalCore_inAllSocket   = 0;
static uint32_t num_gpu_devices_inAllSocket        = 0;

static amdsmi_socket_handle     amdsmi_apusocket_handle_all_socket[MAX_SOCKET_ACROSS_SYSTEM+MAX_GPU_DEVICE_ACROSS_SYSTEM]		= {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_across_socket[MAX_SOCKET_ACROSS_SYSTEM*MAX_CPU_PER_SOCKET]      = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_physicalCore_across_socket[MAX_PHYSICALCORE_ACROSS_SYSTEM]      = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_gpu_device_across_socket[MAX_GPU_DEVICE_ACROSS_SYSTEM]				= {0};

goamdsmi_status_t go_shim_amdsmi_present()
{
	if(0 == access("/opt/rocm/lib/libamd_smi.so", F_OK)) 
	{
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmiapu_init()
{
	if(0 != num_apuSockets) return GOAMDSMI_STATUS_SUCCESS;

	if(GOAMDSMI_STATUS_FAILURE == go_shim_amdsmi_present()) 	return GOAMDSMI_STATUS_FAILURE;

	if( (AMDSMI_STATUS_SUCCESS != amdsmi_init(AMDSMI_INIT_AMD_APUS)) ||
		(AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_apuSockets, nullptr)) || 
	    (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_apuSockets, &amdsmi_apusocket_handle_all_socket[0])) ||
		(0 == num_apuSockets))
	{
		return GOAMDSMI_STATUS_FAILURE;
	}

	for(uint32_t socket_counter = 0; socket_counter < num_apuSockets; socket_counter++)
	{
		uint32_t num_cpu		       = 0;
		uint32_t num_cpu_physicalCores = 0;
		uint32_t num_gpu_devices       = 0;

		processor_type_t cpu_processor_type			= AMDSMI_PROCESSOR_TYPE_AMD_CPU;
		processor_type_t cpu_core_processor_type	= AMDSMI_PROCESSOR_TYPE_AMD_CPU_CORE;
		if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_processor_type, nullptr, &num_cpu)) &&
			(0 != num_cpu) &&
			(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_processor_type, &amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket], &num_cpu)))
		{
			if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)) &&
				(0 != num_cpu_physicalCores) &&
				(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_core_processor_type, &amdsmi_processor_handle_all_cpu_physicalCore_across_socket[num_cpu_physicalCore_inAllSocket], &num_cpu_physicalCores)))
			{
				num_cpu_physicalCore_inAllSocket = num_cpu_physicalCore_inAllSocket+num_cpu_physicalCores;
			}
			num_cpu_inAllSocket = num_cpu_inAllSocket+num_cpu;
			num_cpuSockets = num_cpuSockets+1;
		}
		
		processor_type_t gpu_device_processor_type	= AMDSMI_PROCESSOR_TYPE_AMD_GPU;
		if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], gpu_device_processor_type, nullptr, &num_gpu_devices)) &&
			(0 != num_gpu_devices) &&
			(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], gpu_device_processor_type, &amdsmi_processor_handle_all_gpu_device_across_socket[num_gpu_devices_inAllSocket], &num_gpu_devices)))
		{
			 num_gpu_devices_inAllSocket = num_gpu_devices_inAllSocket+num_gpu_devices;
			 num_gpuSockets = num_gpuSockets+1;
		}
	}
	return GOAMDSMI_STATUS_SUCCESS;
}
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmicpu_init()	
{
	printf("enter go_shim_amdsmicpu_init\n");
	if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmiapu_init())
	{
		if((num_cpu_inAllSocket) && (num_cpu_physicalCore_inAllSocket))
		{
			printf("enter go_shim_amdsmicpu_init success\n");
			return GOAMDSMI_STATUS_SUCCESS;
		}
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_threads_per_core_get(uint32_t* threads_per_core)
{
	printf("enter go_shim_amdsmicpu_threads_per_core_get");
	*threads_per_core 				= 0;
	uint32_t threads_per_core_temp  = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_threads_per_core(&threads_per_core_temp)))
	{
		*threads_per_core = threads_per_core_temp;
		printf("go_shim_amdsmicpu_threads_per_core_get:%d\n",*threads_per_core);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_number_of_threads_get(uint32_t* number_of_threads)
{
	*number_of_threads 			  = 0;
	uint32_t num_threads_per_core = 0;
	if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_threads_per_core_get(&num_threads_per_core))
	{
		*number_of_threads = num_cpu_physicalCore_inAllSocket*num_threads_per_core;
		printf("enter go_shim_amdsmicpu_number_of_threads_get:%d\n",*number_of_threads);
		return GOAMDSMI_STATUS_SUCCESS;
	}

	printf("go_shim_amdsmicpu_number_of_threads_get:%d\n",*number_of_threads);
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_number_of_sockets_get(uint32_t* number_of_sockets)
{
	*number_of_sockets = num_cpuSockets;
	printf("go_shim_amdsmicpu_number_of_sockets_get:%d\n",*number_of_sockets);
    return GOAMDSMI_STATUS_SUCCESS;
}

goamdsmi_status_t go_shim_amdsmicpu_core_energy_get(uint32_t thread_index, uint64_t* core_energy)
{
	*core_energy				= 0;
	uint64_t core_energy_temp	= 0;
	uint32_t physicalCore_index	= thread_index%num_cpu_physicalCore_inAllSocket;

	printf("enter go_shim_amdsmicpu_core_energy_get[%d]:pc:%d:energy:%d\n",thread_index,physicalCore_index,*core_energy);
	if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_energy(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &core_energy_temp))
	{
		*core_energy = core_energy_temp;
		printf("go_shim_amdsmicpu_core_energy_get[%d]:pc:%d:energy:%d\n",thread_index,physicalCore_index,*core_energy);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)
{
	*socket_energy				= 0;
	uint64_t socket_energy_temp	= 0;
	printf("enter go_shim_amdsmicpu_s_get[%d]:socket_penergy:%d\n",socket_index,*socket_energy);
	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_energy(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_energy_temp)))
	{
		*socket_energy = socket_energy_temp;
		printf("go_shim_amdsmicpu_s_get[%d]:socket_penergy:%d\n",socket_index,*socket_energy);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_index, uint32_t* prochot)
{
	*prochot				= 0;
	uint32_t prochot_temp	= 0;
	printf("enter go_shim_amdsmicpu_prochot_status_get[%d]:prochot:%d\n",socket_index,*prochot);
	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_prochot_status(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &prochot_temp)))
	{
		*prochot = prochot_temp;
		printf("go_shim_amdsmicpu_prochot_status_get[%d]:prochot:%d\n",socket_index,*prochot);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_power_get(uint32_t socket_index, uint32_t* socket_power)
{
	*socket_power				= 0;
	uint32_t socket_power_temp	= 0;
	printf("enter go_shim_amdsmicpu_socket_power_get[%d]:socket_power:%d\n",socket_index,*socket_power);
	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_power_temp)))
	{
		*socket_power = socket_power_temp;
		printf("go_shim_amdsmicpu_socket_power_get[%d]:socket_power:%d\n",socket_index,*socket_power);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)
{
	*socket_power_cap 				= 0;
	uint32_t socket_power_cap_temp 	= 0;
	printf("enter go_shim_amdsmicpu_socket_power_cap_get[%d]:socket_power_cap:%d\n",socket_index,*socket_power_cap);
	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power_cap(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_power_cap_temp)))
	{
		*socket_power_cap = socket_power_cap_temp;
		printf("go_shim_amdsmicpu_socket_power_cap_get[%d]:socket_power_cap:%d\n",socket_index,*socket_power_cap);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)
{
	*core_boostlimit				= 0;
	uint32_t core_boostlimit_temp	= 0;
	uint32_t physicalCore_index   = thread_index%num_cpu_physicalCore_inAllSocket;

	printf("enter go_shim_amdsmicpu_core_boostlimit_get[%d]:pc:%d:core_boostlimit:%d\n",thread_index,physicalCore_index,*core_boostlimit);
	if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_boostlimit(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &core_boostlimit_temp))
	{
		*core_boostlimit = core_boostlimit_temp;
		printf("go_shim_amdsmicpu_core_boostlimit_get[%d]:pc:%d:core_boostlimit:%d\n",thread_index,physicalCore_index,*core_boostlimit);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmigpu_init()
{
	printf("enter go_shim_amdsmigpu_init\n");
	if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmiapu_init())
	{
		if((num_gpu_devices_inAllSocket))
		{
			printf("go_shim_amdsmigpu_init success\n");
			return GOAMDSMI_STATUS_SUCCESS;
		}
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_shutdown()
{
	printf("enter go_shim_amdsmigpu_shutdown\n");
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_num_monitor_devices(uint32_t* gpu_num_monitor_devices)
{
	printf("enter go_shim_amdsmigpu_num_monitor_devices:%d\n",*gpu_num_monitor_devices);
	*gpu_num_monitor_devices = num_gpu_devices_inAllSocket;
	printf("go_shim_amdsmigpu_num_monitor_devices:%d\n",*gpu_num_monitor_devices);
    return GOAMDSMI_STATUS_SUCCESS;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)
{
	printf("enter go_shim_amdsmigpu_dev_name_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)
{
	*gpu_dev_id					= 0;
	uint16_t gpu_dev_id_temp 	= 0;
	
	printf("enter go_shim_amdsmigpu_dev_id_get[%d]:gpu_dev_id:%d\n",dv_ind,*gpu_dev_id);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_id(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &gpu_dev_id_temp)))
	{
		*gpu_dev_id = gpu_dev_id_temp;
		printf("go_shim_amdsmigpu_dev_id_get[%d]:gpu_dev_id:%d\n",dv_ind,*gpu_dev_id);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)
{
	printf("enter go_shim_amdsmigpu_dev_pci_id_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)
{
	printf("enter go_shim_amdsmigpu_dev_vendor_name_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)
{
	printf("enter go_shim_amdsmigpu_dev_vbios_version_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)
{
	*gpu_power_cap										= 0;
	amdsmi_power_cap_info_t amdsmi_power_cap_info_temp	= {0};

	printf("enter go_shim_amdsmigpu_dev_power_cap_get[%d]:power_cap:%d\n",dv_ind,*gpu_power_cap);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_cap_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], GPU_SENSOR_0, &amdsmi_power_cap_info_temp)))
	{
		*gpu_power_cap = amdsmi_power_cap_info_temp.power_cap;
		printf("go_shim_amdsmigpu_dev_power_cap_get[%d]:power_cap:%d\n",dv_ind,*gpu_power_cap);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_power_ave_get(uint32_t dv_ind, uint64_t* gpu_power_avg)
{
	*gpu_power_avg								= 0;
	amdsmi_power_info_t amdsmi_power_info_temp	= {0};

#if 1
	printf("enter go_shim_amdsmigpu_dev_power_ave_get[%d]:gpu_power_avg:%d\n",dv_ind,*gpu_power_avg);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &amdsmi_power_info_temp)))
	{
		*gpu_power_avg = amdsmi_power_info_temp.average_socket_power;
		printf("amdsmi_get_power_info[%d]:gpu_power_avg:%d\n",dv_ind,*gpu_power_avg);
		return GOAMDSMI_STATUS_SUCCESS;
	}
#else
	printf("enter amdsmi_get_gpu_metrics_info[%d]:gpu_power_avg:%d\n",dv_ind,*gpu_power_avg);
	amdsmi_gpu_metrics_t metrics = {0};
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_metrics_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &metrics)))
	{
		*gpu_power_avg = metrics.average_socket_power;
		printf("amdsmi_get_gpu_metrics_info[%d]:gpu_power_avg:%d\n",dv_ind,*gpu_power_avg);
		return GOAMDSMI_STATUS_SUCCESS;
	}
#endif
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)
{
	*gpu_temperature 				= 0;
	uint64_t gpu_temperature_temp	= 0;

	printf("enter go_shim_amdsmigpu_dev_temp_metric_get[dv_ind:%d:sensor:%d:metric:%d]:gpu_temperature:%d\n",dv_ind,sensor,metric,*gpu_temperature);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_temp_metric(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], sensor, metric, &gpu_temperature_temp)))
	{
		*gpu_temperature = gpu_temperature_temp;
		printf("go_shim_amdsmigpu_dev_temp_metric_get[dv_ind:%d:sensor:%d:metric:%d]:gpu_temperature:%d\n",dv_ind,sensor,metric,*gpu_temperature);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)
{
	printf("enter go_shim_amdsmigpu_dev_overdrive_level_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)
{
	printf("enter go_shim_amdsmigpu_dev_mem_overdrive_level_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)
{
	printf("enter go_shim_amdsmigpu_dev_perf_level_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)
{
	*gpu_sclk_freq				= 0;
	amdsmi_frequencies_t freq	= {0};

	printf("enter go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk[%d]:sclkfrequency:%d\n",dv_ind,*gpu_sclk_freq);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_CLK_TYPE_SYS, &freq)))
	{
		*gpu_sclk_freq = freq.frequency[freq.current];
		printf("go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk[%d]:sclkfrequency:%d\n",dv_ind,*gpu_sclk_freq);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)
{
	*gpu_memclk_freq			= 0;
	amdsmi_frequencies_t freq	= {0};

	printf("enter go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk[%d]:mclkfrequency:%d\n",dv_ind,*gpu_memclk_freq);
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_CLK_TYPE_MEM, &freq)))
	{
		*gpu_memclk_freq = freq.frequency[freq.current];
		printf("go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk[%d]:mclkfrequency:%d\n",dv_ind,*gpu_memclk_freq);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)
{
	printf("enter go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)
{
	printf("enter go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)
{
	printf("enter go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)
{
	printf("enter go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)
{
	printf("enter go_shim_amdsmigpu_dev_gpu_busy_percent_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)
{
	printf("enter go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get\n");
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)
{
	printf("enter go_shim_amdsmigpu_dev_gpu_memory_usage_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)
{
	printf("enter go_shim_amdsmigpu_dev_gpu_memory_total_get\n");
    return GOAMDSMI_STATUS_FAILURE;
}
#else
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmicpu_init()																	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_threads_per_core_get(uint32_t* threads_per_core)						{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_number_of_threads_get(uint32_t* number_of_threads)						{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_number_of_sockets_get(uint32_t* number_of_sockets)						{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_core_energy_get(uint32_t thread_index, uint64_t* core_energy)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_index, uint32_t* prochot)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_power_get(uint32_t socket_index, uint32_t* socket_power)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)	{return GOAMDSMI_STATUS_FAILURE;}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmigpu_init()														{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_shutdown()													{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_num_monitor_devices(uint32_t* gpu_num_monitor_devices)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name){return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version){return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_power_ave_get(uint32_t dv_ind, uint64_t* gpu_power_avg)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)							{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)				{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)					{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)			{return GOAMDSMI_STATUS_FAILURE;}
#endif


