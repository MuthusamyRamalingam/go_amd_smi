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
#include "../amdsmi/amdsmi_go_shim.h"
#include "../esmi/esmi_go_shim.h"
#include "../rsmi/rocm_smi_go_shim.h"
#include "goamdsmi.h"
#include <unistd.h>
#include <stdbool.h>
static bool amdsmi_init	= false;
static bool esmi_init	= false; 		
static bool rsmi_init	= false; 		
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
uint32_t goamdsmi_cpu_init()	
{	
	goamdsmi_status_t amdsmi_	= go_shim_amdsmicpu_init();
	goamdsmi_status_t esmi_		= go_shim_esmi_init();
	
	if(GOAMDSMI_STATUS_SUCCESS == amdsmi_)	{amdsmi_init = true;}
	if(GOAMDSMI_STATUS_SUCCESS == esmi_)	{esmi_init = true;}
	if(amdsmi_init || rsmi_init)			return 1;
	
	return 0;
}

uint32_t goamdsmi_cpu_threads_per_core_get()
{
	uint32_t threads_per_core_temp  = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_threads_per_core_get(&threads_per_core_temp))){return threads_per_core_temp;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_threads_per_core_get(&threads_per_core_temp)))		{return threads_per_core_temp;}

	return 0;
}

uint32_t goamdsmi_cpu_number_of_threads_get()
{
	uint32_t num_threads_per_core = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_number_of_threads_get(&num_threads_per_core))){return num_threads_per_core;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_number_of_threads_get(&num_threads_per_core)))		{return num_threads_per_core;}
	
	return 0;
}

uint32_t goamdsmi_cpu_number_of_sockets_get()
{
	uint32_t number_of_sockets = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_number_of_sockets_get(&number_of_sockets))){return number_of_sockets;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_number_of_sockets_get(&number_of_sockets)))	 {return number_of_sockets;}
	
	return 0;
}

uint64_t goamdsmi_cpu_core_energy_get(uint32_t thread_index)
{
	uint64_t core_energy = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_core_energy_get(thread_index, &core_energy)))	{return core_energy;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_core_energy_get(thread_index, &core_energy)))	 	{return core_energy;}
	
	return 0;
}

uint64_t goamdsmi_cpu_socket_energy_get(uint32_t socket_index)
{
	uint64_t socket_energy = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_socket_energy_get(socket_index, &socket_energy))){return socket_energy;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_socket_energy_get(socket_index, &socket_energy)))	  {return socket_energy;}
	
	return 0;
}

uint32_t goamdsmi_cpu_prochot_status_get(uint32_t socket_index)
{
	uint32_t prochot = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_prochot_status_get(socket_index, &prochot))){return prochot;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_prochot_status_get(socket_index, &prochot)))	 {return prochot;}
	
	return 0;
}

uint32_t goamdsmi_cpu_socket_power_get(uint32_t socket_index)
{
	uint32_t socket_power = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_socket_power_get(socket_index, &socket_power))){return socket_power;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_socket_power_get(socket_index, &socket_power)))		{return socket_power;}
	
	return 0;
}

uint32_t goamdsmi_cpu_socket_power_cap_get(uint32_t socket_index)
{
	uint32_t socket_power_cap = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_socket_power_cap_get(socket_index, &socket_power_cap))){return socket_power_cap;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_socket_power_cap_get(socket_index, &socket_power_cap)))		{return socket_power_cap;}
	
	return 0;
}

uint32_t goamdsmi_cpu_core_boostlimit_get(uint32_t thread_index)
{
	uint32_t core_boostlimit = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_core_boostlimit_get(thread_index, &core_boostlimit))){return core_boostlimit;}
	else if	((esmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_esmi_core_boostlimit_get(thread_index, &core_boostlimit)))	  {return core_boostlimit;}
	
	return 0;
}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
uint32_t goamdsmi_gpu_init()
{
	goamdsmi_status_t amdsmi_	= go_shim_amdsmicpu_init();
	goamdsmi_status_t rsmi_		= go_shim_rsmi_init();
	
	if(GOAMDSMI_STATUS_SUCCESS == amdsmi_)	{amdsmi_init = true;}
	if(GOAMDSMI_STATUS_SUCCESS == rsmi_)	{rsmi_init = true;}
	if(amdsmi_init || rsmi_init)			return 1;
	
	return 0;
}

uint32_t goamdsmi_gpu_shutdown()
{	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_shutdown()))	{return 1;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_shutdown()))		{return 1;}
	
	return 0;
}

uint32_t goamdsmi_gpu_num_monitor_devices()
{
	uint32_t gpu_num_monitor_devices = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_num_monitor_devices(&gpu_num_monitor_devices))){return gpu_num_monitor_devices;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_num_monitor_devices(&gpu_num_monitor_devices)))	 {return gpu_num_monitor_devices;}
	
	return 0;
}

char* goamdsmi_gpu_dev_name_get(uint32_t dv_ind)
{
	char *dev_name = NULL;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_name_get(dv_ind, &dev_name)))	{return dev_name;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_name_get(dv_ind, &dev_name)))		{return dev_name;}
	
	return NULL;
}

uint16_t goamdsmi_gpu_dev_id_get(uint32_t dv_ind)
{
	uint16_t gpu_dev_id = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_id_get(dv_ind, &gpu_dev_id)))	{return gpu_dev_id;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_id_get(dv_ind, &gpu_dev_id)))		{return gpu_dev_id;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_pci_id_get(uint32_t dv_ind)
{
	uint64_t gpu_pci_id = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_pci_id_get(dv_ind, &gpu_pci_id)))	{return gpu_pci_id;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_pci_id_get(dv_ind, &gpu_pci_id)))		{return gpu_pci_id;}
	
	return 0;
}

char* goamdsmi_gpu_dev_vendor_name_get(uint32_t dv_ind)
{
	char *gpu_vendor_name = NULL;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_vendor_name_get(dv_ind, &gpu_vendor_name))){return gpu_vendor_name;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_vendor_name_get(dv_ind, &gpu_vendor_name)))	 {return gpu_vendor_name;}
	
	return NULL;
}

char* goamdsmi_gpu_dev_vbios_version_get(uint32_t dv_ind)
{
	char *vbios_version = NULL;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_vbios_version_get(dv_ind, &vbios_version))){return vbios_version;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_vbios_version_get(dv_ind, &vbios_version)))	 {return vbios_version;}
	
	return NULL;
}

uint64_t goamdsmi_gpu_dev_power_cap_get(uint32_t dv_ind)
{
	uint64_t gpu_power_cap = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_power_cap_get(dv_ind, &gpu_power_cap)))	{return gpu_power_cap;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_power_cap_get(dv_ind, &gpu_power_cap)))		{return gpu_power_cap;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_power_ave_get(uint32_t dv_ind)
{
	uint64_t gpu_power_avg = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_power_ave_get(dv_ind, &gpu_power_avg))){return gpu_power_avg;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_power_ave_get(dv_ind, &gpu_power_avg))){return gpu_power_avg;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric)
{
	uint64_t gpu_temperature = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_temp_metric_get(dv_ind, sensor, metric, &gpu_temperature))){return gpu_temperature;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_temp_metric_get(dv_ind, sensor, metric, &gpu_temperature)))	 {return gpu_temperature;}
	
	return 0;
}

uint32_t goamdsmi_gpu_dev_overdrive_level_get(uint32_t dv_ind)
{
	uint32_t gpu_overdrive_level = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_overdrive_level_get(dv_ind, &gpu_overdrive_level))){return gpu_overdrive_level;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_overdrive_level_get(dv_ind, &gpu_overdrive_level)))	 {return gpu_overdrive_level;}
	
	return 0;
}

uint32_t goamdsmi_gpu_dev_mem_overdrive_level_get(uint32_t dv_ind)
{
	uint32_t gpu_mem_overdrive_level = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_overdrive_level_get(dv_ind, &gpu_mem_overdrive_level))){return gpu_mem_overdrive_level;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_overdrive_level_get(dv_ind, &gpu_mem_overdrive_level)))	 {return gpu_mem_overdrive_level;}
	
	return 0;
}

uint32_t goamdsmi_gpu_dev_perf_level_get(uint32_t dv_ind)
{
	uint32_t gpu_perf = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_perf_level_get(dv_ind, &gpu_perf))){return gpu_perf;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_perf_level_get(dv_ind, &gpu_perf)))	 {return gpu_perf;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind)
{
	uint64_t gpu_sclk_freq = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(dv_ind, &gpu_sclk_freq))){return gpu_sclk_freq;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_clk_freq_get_sclk(dv_ind, &gpu_sclk_freq)))	 {return gpu_sclk_freq;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind)
{
	uint64_t gpu_memclk_freq = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(dv_ind, &gpu_memclk_freq)))	{return gpu_memclk_freq;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_clk_freq_get_mclk(dv_ind, &gpu_memclk_freq)))		{return gpu_memclk_freq;}
	
	return 0;
}

uint64_t goamdsmi_gpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind)
{
	uint64_t gpu_min_sclk = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(dv_ind, &gpu_min_sclk)))	{return gpu_min_sclk;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_od_volt_freq_range_min_get_sclk(dv_ind, &gpu_min_sclk)))		{return gpu_min_sclk;}
	
	return 0;
}

uint64_t goamdsmi_gpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind)
{
	uint64_t gpu_min_memclk = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(dv_ind, &gpu_min_memclk))){return gpu_min_memclk;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_od_volt_freq_range_min_get_mclk(dv_ind, &gpu_min_memclk)))		{return gpu_min_memclk;}
	
	return 0;
}

uint64_t goamdsmi_gpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind)
{
	uint64_t gpu_max_sclk = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(dv_ind, &gpu_max_sclk)))	{return gpu_max_sclk;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_od_volt_freq_range_max_get_sclk(dv_ind, &gpu_max_sclk)))		{return gpu_max_sclk;}
	
	return 0;
}

uint64_t goamdsmi_gpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind)
{
	uint64_t gpu_max_memclk = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(dv_ind, &gpu_max_memclk))){return gpu_max_memclk;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_od_volt_freq_range_max_get_mclk(dv_ind, &gpu_max_memclk)))		{return gpu_max_memclk;}
	
	return 0;
}

uint32_t goamdsmi_gpu_dev_gpu_busy_percent_get(uint32_t dv_ind)
{
	uint32_t gpu_busy_percent = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_busy_percent_get(dv_ind, &gpu_busy_percent)))	{return gpu_busy_percent;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_busy_percent_get(dv_ind, &gpu_busy_percent)))		{return gpu_busy_percent;}
	
	return 0;
}


uint64_t goamdsmi_gpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind)
{
	uint64_t gpu_memory_busy_percent = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(dv_ind, &gpu_memory_busy_percent))){return gpu_memory_busy_percent;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_memory_busy_percent_get(dv_ind, &gpu_memory_busy_percent)))	 {return gpu_memory_busy_percent;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_gpu_memory_usage_get(uint32_t dv_ind)
{
	uint64_t gpu_memory_usage = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_memory_usage_get(dv_ind, &gpu_memory_usage)))	{return gpu_memory_usage;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_memory_usage_get(dv_ind, &gpu_memory_usage)))		{return gpu_memory_usage;}
	
	return 0;
}

uint64_t goamdsmi_gpu_dev_gpu_memory_total_get(uint32_t dv_ind)
{
	uint64_t gpu_memory_total = 0;
	
	if		((amdsmi_init)&&(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmigpu_dev_gpu_memory_total_get(dv_ind, &gpu_memory_total)))	{return gpu_memory_total;}
	else if	((rsmi_init)  &&(GOAMDSMI_STATUS_SUCCESS == go_shim_rsmi_dev_gpu_memory_total_get(dv_ind, &gpu_memory_total)))		{return gpu_memory_total;}
	
	return 0;
}

