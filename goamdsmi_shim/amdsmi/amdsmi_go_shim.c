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
#include <amd_smi/amdsmi.h>
#include "amdsmi_go_shim.h"
#include <unistd.h>
#include <stdio.h>

#define nullptr ((void*)0)
#define MAX_SOCKET_ACROSS_SYSTEM	     4
#define CPU_0						     0
#define GPU_SENSOR_0					 0
#define MAX_CPU_PER_SOCKET               1
#define MAX_PHYSICALCORE_ACROSS_SYSTEM 384
#define MAX_LOGICALCORE_ACROSS_SYSTEM  768
#define MAX_GPU_DEVICE_ACROSS_SYSTEM    24

static uint32_t num_apuSockets					   = 0;
static uint32_t num_cpuSockets					   = 0;
static uint32_t num_gpuSockets					   = 0;

static uint32_t num_cpu_inAllSocket          	   = 0;
static uint32_t num_cpu_physicalCore_inAllSocket   = 0;
static uint32_t num_gpu_devices_inAllSocket        = 0;
static amdsmi_socket_handle     amdsmi_socket_handle_all_socket[MAX_SOCKET_ACROSS_SYSTEM]										 = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_across_socket[MAX_SOCKET_ACROSS_SYSTEM*MAX_CPU_PER_SOCKET]       = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_physicalCore_across_socket[MAX_PHYSICALCORE_ACROSS_SYSTEM]        = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_gpu_device_across_socket[MAX_GPU_DEVICE_ACROSS_SYSTEM]				 = {0};

int32_t go_shim_amdsmi_present()
{
	printf("go_shim_amdsmi_present11\n");
	if(0 == access("/opt/rocm/lib/libamd_smi.so", F_OK)) 
	{
		printf("go_shim_amdsmi_present22\n");
		return 1;
	}
	printf("go_shim_amdsmi_present33\n");
	return 0;
}

bool go_shim_amdsmiapu_init()
{
	printf("go_shim_amdsmiapu_init1\n");
	if(0 != num_apuSockets) return true;

	printf("go_shim_amdsmiapu_init2\n");
	if(!go_shim_amdsmi_present()) return false;

	printf("go_shim_amdsmiapu_init3\n");
	if( (AMDSMI_STATUS_SUCCESS != amdsmi_init(AMDSMI_INIT_AMD_APUS)) ||
		(AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_apuSockets, nullptr)) || 
	    (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_apuSockets, &amdsmi_socket_handle_all_socket[0])) ||
		(0 == num_apuSockets))
	{
		printf("go_shim_amdsmiapu_init4\n");
		return false;
	}

	printf("num_apuSockets:%d\n",num_apuSockets);
	for(uint32_t socket_counter = 0; socket_counter < num_apuSockets; socket_counter++)
	{
		uint32_t num_cpu		       = 0;
		uint32_t num_cpu_physicalCores = 0;
		uint32_t num_gpu_devices       = 0;

		printf("go_shim_amdsmiapu_init6\n");
		processor_type_t cpu_processor_type			= AMDSMI_PROCESSOR_TYPE_AMD_CPU;
		processor_type_t cpu_core_processor_type	= AMDSMI_PROCESSOR_TYPE_AMD_CPU_CORE;
		if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_socket_handle_all_socket[socket_counter], cpu_processor_type, nullptr, &num_cpu)) )
		{
			printf("check0:%d\n",num_cpu);
		}
		
		if(	(0 != num_cpu) &&
			(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_socket_handle_all_socket[socket_counter], cpu_processor_type, &amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket], &num_cpu)))
		{
			printf("check1:%d\n",num_cpu);
			//for(uint32_t cpu_counter = 0; cpu_counter < num_cpu; cpu_counter++)
			{
				if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket/*+cpu_counter*/], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)))
				{
					printf("check2:%d\n",num_cpu_physicalCores);
				}
				if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket+1/*+cpu_counter*/], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)))
				{
					printf("check6:%d\n",num_cpu_physicalCores);
				}
				if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_socket_handle_all_socket[socket_counter], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)))
				{
					printf("check7:%d\n",num_cpu_physicalCores);
				}
				
				if	((0 != num_cpu_physicalCores) &&
					(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket/*+cpu_counter*/], cpu_core_processor_type, &amdsmi_processor_handle_all_cpu_physicalCore_across_socket[num_cpu_physicalCore_inAllSocket], &num_cpu_physicalCores)))
				{
					printf("check3:%d\n",num_cpu_physicalCores);
					
					num_cpu_physicalCore_inAllSocket = num_cpu_physicalCore_inAllSocket+num_cpu_physicalCores;
					num_cpuSockets = num_cpuSockets+1;
					printf("num_cpu_physicalCores:%d\n",num_cpu_physicalCores);
					printf("num_cpu_physicalCore_inAllSocket:%d\n",num_cpu_physicalCore_inAllSocket);
					printf("num_cpuSockets:%d\n",num_cpuSockets);
				}
			}
			num_cpu_inAllSocket = num_cpu_inAllSocket+num_cpu;
			printf("num_cpu:%d\n",num_cpu);
			printf("num_cpu_inAllSocket:%d\n",num_cpu_inAllSocket);
		}
		
		printf("go_shim_amdsmiapu_init7\n");
		processor_type_t gpu_device_processor_type	= AMDSMI_PROCESSOR_TYPE_AMD_GPU;
		if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_socket_handle_all_socket[socket_counter], gpu_device_processor_type, nullptr, &num_gpu_devices)) &&
			(0 != num_gpu_devices) &&
			(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_socket_handle_all_socket[socket_counter], gpu_device_processor_type, &amdsmi_processor_handle_all_gpu_device_across_socket[num_gpu_devices_inAllSocket], &num_gpu_devices)))
		{
			 num_gpu_devices_inAllSocket = num_gpu_devices_inAllSocket+num_gpu_devices;
			 num_gpuSockets = num_gpuSockets+1;
			 printf("num_gpu_devices:%d\n",num_gpu_devices);
			 printf("num_gpu_devices_inAllSocket:%d\n",num_gpu_devices_inAllSocket);
			 printf("num_gpuSockets:%d\n",num_gpuSockets);
		}
	}

	uint32_t num_cpu_physicalCores = 0;
	processor_type_t cpu_core_processor_type	= AMDSMI_PROCESSOR_TYPE_AMD_CPU_CORE;
	for(int i =0; i < 4; i++)
	{
		printf("i=%d, %p\n",i,amdsmi_processor_handle_all_cpu_across_socket[i]);
		if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_processor_handle_all_cpu_across_socket[i], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)))
		{
			printf("check8:%d\n",num_cpu_physicalCores);
		}
		if	((0 != num_cpu_physicalCores) &&
			(AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_processor_handle_all_cpu_across_socket[i], cpu_core_processor_type, &amdsmi_processor_handle_all_cpu_physicalCore_across_socket[i], &num_cpu_physicalCores)))
		{
			printf("check9:%d\n",num_cpu_physicalCores);
		}
	}
	printf("****EXIT go_shim_amdsmiapu_init****\n");
	return true;
}
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
int32_t go_shim_amdsmicpu_init()	
{
	//if(access("/opt/rocm/lib/libamd_smi.so", F_OK)) return 0;
	//return (AMDSMI_STATUS_SUCCESS == amdsmi_init(AMDSMI_INIT_AMD_CPUS)) ? 1 : 0;
	printf("go_shim_amdsmicpu_init1\n");
	if(go_shim_amdsmiapu_init())
	{
		printf("go_shim_amdsmicpu_init2\n");
		if((num_cpu_inAllSocket) && (num_cpu_physicalCore_inAllSocket))
		{
			printf("go_shim_amdsmicpu_init3\n");
			return 1;
		}
	}
	printf("go_shim_amdsmicpu_init4\n");
	return 0;
}

int32_t go_shim_amdsmicpu_threads_per_core_get()
{
	printf("go_shim_amdsmicpu_threads_per_core_get1\n");
	uint32_t num_threads_per_core = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_threads_per_core(&num_threads_per_core)))
	{
		printf("go_shim_amdsmicpu_threads_per_core_get2\n");
		return num_threads_per_core;
	}
	printf("go_shim_amdsmicpu_threads_per_core_get3\n");
	return 0;
}

int32_t go_shim_amdsmicpu_number_of_threads_get()
{
	printf("go_shim_amdsmicpu_number_of_threads_get1\n");
	uint32_t total_num_threads    = 0;
	uint32_t num_threads_per_core = go_shim_amdsmicpu_threads_per_core_get();

	total_num_threads = num_cpu_physicalCore_inAllSocket*num_threads_per_core;

	printf("go_shim_amdsmicpu_number_of_threads_get2\n");
	return total_num_threads;
}

int32_t go_shim_amdsmicpu_number_of_sockets_get()
{
	printf("go_shim_amdsmicpu_number_of_sockets_get1\n");
    return num_cpuSockets;
}

uint64_t go_shim_amdsmicpu_core_energy_get(uint32_t thread_index)
{
	uint64_t core_penergy		  = 0;
	uint32_t physicalCore_index   = thread_index%num_cpu_physicalCore_inAllSocket;

	if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_energy(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &core_penergy))
		return core_penergy;

	return 0;
}

uint64_t go_shim_amdsmicpu_s_get(uint32_t socket_index)
{
	uint64_t socket_penergy = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_energy(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_penergy)))
		return socket_penergy;

	return 0;
}

uint32_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_index)
{
	uint32_t prochot = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_prochot_status(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &prochot)))
		return prochot;

 	return 0;
}

uint32_t go_shim_amdsmicpu_socket_power_get(uint32_t socket_index)
{
	uint32_t ppower = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &ppower)))
		return ppower;

	return 0;
}

uint32_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t socket_index)
{
	uint32_t pcap = 0;

	if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power_cap(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &pcap)))
		return pcap;

	return 0;
}

uint32_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t thread_index)
{
	uint32_t boostlimit			  = 0;
	uint32_t physicalCore_index   = thread_index%num_cpu_physicalCore_inAllSocket;

	if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_boostlimit(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &boostlimit))
		return boostlimit;

	return 0;
}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
int32_t go_shim_amdsmigpu_init()
{
	//if(access("/opt/rocm/lib/libamd_smi.so", F_OK)) return 0;
	//return (AMDSMI_STATUS_SUCCESS == amdsmi_init(AMDSMI_INIT_AMD_GPUS)) ? 1 : 0;
	printf("go_shim_amdsmigpu_init1\n");
	if(go_shim_amdsmiapu_init())
	{
		printf("go_shim_amdsmigpu_init2\n");
		if((num_gpu_devices_inAllSocket))
		{
			printf("go_shim_amdsmigpu_init3\n");
			return 1;
		}
	}
	printf("go_shim_amdsmigpu_init4\n");
	return 0;
}

int32_t go_shim_amdsmigpu_shutdown()
{
    //return (AMDSMI_STATUS_SUCCESS == rsmi_shut_down()) ? 1 : 0;
	return 0;
}

int32_t go_shim_amdsmigpu_num_monitor_devices()
{
	printf("go_shim_amdsmigpu_num_monitor_devices1\n");
	return num_gpu_devices_inAllSocket;
}

char* go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind)
{
    /*uint32_t len = 256;
    char *dev_name = (char*)malloc(sizeof(char)*len);
    dev_name[0] = '\0';

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_name_get(dv_ind, dev_name, &len))
    {
            return dev_name;
    }*/

    return NULL;
}

uint16_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind)
{
	uint16_t id = 0;
	
	printf("go_shim_amdsmigpu_dev_id_get1\n");
	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_id(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &id)))
			return id;

	printf("go_shim_amdsmigpu_dev_id_get2\n");
	return 0;
}

uint64_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind)
{
    /*uint64_t id = 0;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_pci_id_get(dv_ind, &id))
            return id;*/

    return 0;
}

char* go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind)
{
    /*uint32_t len = 256;
    char *vendor_name = (char*)malloc(sizeof(char)*len);
    vendor_name[0] = '\0';

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_vendor_name_get(dv_ind, vendor_name, &len))
            return vendor_name;*/

    return NULL;
}

char* go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind)
{
    /*uint32_t len = 256;
    char *vbios_ver = (char*)malloc(sizeof(char)*len);
    vbios_ver[0] = '\0';

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_vbios_version_get(dv_ind, vbios_ver, &len))
    {
            return vbios_ver;
    }*/

    return NULL;
}

uint64_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind)
{
	amdsmi_power_cap_info_t amdsmi_power_cap_info_temp;

	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_cap_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], GPU_SENSOR_0, &amdsmi_power_cap_info_temp)))
			return amdsmi_power_cap_info_temp.power_cap;

	return 0;
}

uint64_t go_shim_amdsmigpu_dev_power_ave_get(uint32_t dv_ind)
{
	amdsmi_power_info_t amdsmi_power_info_temp;

	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &amdsmi_power_info_temp)))
			return amdsmi_power_info_temp.average_socket_power;

	return 0;
}

uint64_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric)
{
	uint64_t temperature = 0;

	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_temp_metric(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], sensor, metric, &temperature)))
			return temperature;

	return 0;
}

uint32_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind)
{
    /*uint32_t od;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_overdrive_level_get(dv_ind, &od))
            return od;*/

    return 0;
}

uint32_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind)
{
    /*uint32_t od;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_mem_overdrive_level_get(dv_ind, &od))
            return od;*/

    return 0;
}

uint32_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind)
{
    /*rsmi_dev_perf_level_t perf;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_perf_level_get(dv_ind, &perf))
            return perf;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind)
{
	amdsmi_frequencies_t freq;
	amdsmi_clk_type_t clk_type = AMDSMI_CLK_TYPE_SYS;

	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], clk_type, &freq)))
			return freq.frequency[freq.current];

	return 0;
}

uint64_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind)
{
	amdsmi_frequencies_t freq;
	amdsmi_clk_type_t clk_type = AMDSMI_CLK_TYPE_MEM;

	if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], clk_type, &freq)))
			return freq.frequency[freq.current];

	return 0;
}

uint64_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind)
{
    /*rsmi_od_volt_freq_data_t odv;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
            return odv.curr_sclk_range.lower_bound;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind)
{
    /*rsmi_od_volt_freq_data_t odv;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
            return odv.curr_mclk_range.lower_bound;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind)
{
    /*rsmi_od_volt_freq_data_t odv;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
            return odv.curr_sclk_range.upper_bound;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind)
{
    /*rsmi_od_volt_freq_data_t odv;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
            return odv.curr_mclk_range.upper_bound;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind)
{
	/*uint64_t usage = 0;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_busy_percent_get(dv_ind, &usage))
               return usage;*/

    return 0;
}


uint64_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind)
{
    /*uint64_t usage = 0;
	uint64_t total = 0;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &usage) && 
	     AMDSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &total))
		return (uint64_t)(usage*100)/total;*/

	return 0;
}

uint64_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind)
{
    /*uint64_t usage = 0;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &usage))
            return (uint64_t)usage;*/

    return 0;
}

uint64_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind)
{
    /*uint64_t total = 0;

    if(AMDSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &total))
            return (uint64_t)total;*/

    return 0;
}

