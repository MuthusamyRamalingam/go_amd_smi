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
#include <stdbool.h>
#include "goamdsmi.h"

/**
 *  @brief Go language stub to initialize the Debug Level prints
 *         -DENABLE_DEBUG_LEVEL=1 (or) -DENABLE_DEBUG_LEVEL=<Enable_Debug_level_number> must be passed at cmake time
 *
 *  @retval ::bool value of true upon enabling logs
 *  @retval false is returned upon if user does not want to enable logs.
 *
 */
bool enable_debug_level(goamdsmi_Enable_Debug_Level_t debug_level);

////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
/**
 *  @brief Go language stub to initialize the AMDSMI or E-SMI library
 *
 *  @retval ::int value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int goamdsmi_cpu_init();

/**
 *  @brief Go language stub to get the core energy for a given core
 *
 *  @details Given a core index @p num, this function will call the
 *  esmi_core_energy_get() function to update the @p penergy in micro Joules.
 *  This value is then passed as a int val to the Go routine that called it.
 *
 *  @param[in] num is the core index
 *
 *  @retval ::int value of the penergy in micro Joules.
 *  @retval zero is returned upon failure.
 *
 */
int goamdsmi_cpu_core_energy_get(uint32_t num);

/**
 *  @brief Go language stub to get the socket energy for a given socket
 *
 *  @details Given a socket index @p socket_idx, this function will call the
 *  esmi_socket_energy_get() function to get the socket energy counter of an
 *  online cpu in that socket. This value is then passed as a int val to 
 *  the Go routine that called it.
 *
 *  @param[in] socket_idx is the socket index
 *
 *  @retval ::int value of the socket energy counter
 *  @retval zero is returned upon failure.
 *
 */
int goamdsmi_cpu_socket_energy_get(uint32_t socket_idx);

/**
 *  @brief Go language stub to get normalized status of 
 *  the processor's PROCHOT status.
 *  1 - PROCHOT active, 0 - PROCHOT inactive
 *
 *  @details Given a socket index @p socket_idx and this function will get
 *  PROCHOT at @p prochot.
 *
 *  @param[in] socket_idx a socket index
 *
 *  @retval ::int value of the prochot status
 *  @retval -1 is returned upon failure or if status is inactive.
 *
 */
int goamdsmi_cpu_prochot_status_get(uint32_t socket_idx);

/**
 *  @brief Go language stub to get the instantaneous power 
 *  consumption of the provided socket.
 *
 *  @details Given a socket index @p sock_ind this function will 
 *  get the current power consumption (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *
 *  @retval ::int value of the socket power
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_cpu_socket_power_get(uint32_t sock_ind);

/**
 *  @brief Go language stub to get the current power cap value 
 *  for a given socket. 
 *
 *  @details This function will return the valid power cap @p pcap for a given
 *  socket @p sock_ind, this value will be used by the system to limit
 *  the power usage (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *
 *  @retval ::int value of the socket power cap
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_cpu_socket_power_cap_get(uint32_t sock_ind);

/**
 *  @brief Go language stub to get the boostlimit value for a given core
 *
 *  @details This function will return the core's current boost limit
 *  @p boostlimit for a particular @p socket
 *
 *  @param[in] socket a socket index
 *
 *  @retval ::int value of the boostlimit
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_cpu_core_boostlimit_get(uint32_t socket);

/**
 *  @brief Go stub to get the number of threads per core in the system
 *
 *  @retval ::Number of threads per core
 *  @retval Zero is returned upon failure.
 */
int goamdsmi_cpu_threads_per_core_get();

/**
 *  @brief Go stub to get the number of threads available in the system
 *
 *  @retval ::Number of threads
 *  @retval Zero is returned upon failure.
 */
int goamdsmi_cpu_number_of_threads_get();

/**
 *  @brief Go stub to get the total number of processor sockets 
 *  available in the system
 *
 *  @retval ::int value of the socket number
 *  @retval Zero is returned upon failure.
 */
int goamdsmi_cpu_number_of_sockets_get();

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
/**
 *  @brief Go language stub to initialize the ROCm-SMI library
 *
 *  @retval ::int value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int goamdsmi_gpu_init();

/**
 *  @brief Go language stub to shut down the ROCm-SMI library
 *  and do necessary clean up
 *
 *  @retval ::int value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int goamdsmi_gpu_shutdown();

/**
 *  @brief Go language stub to get the number of GPU devices
 *
 *  @details This function will call the rsmi_num_monitor_devices()
 *  function to return the number of GPU devices to be monitored.
 *  This value is then passed as a uint val to the Go routine that
 *  called it.
 *
 *  @param[in] ::
 *
 *  @retval ::int value of num GPUs
 *  @retval zero is returned upon failure.
 *
 */
int goamdsmi_gpu_num_monitor_devices();

/**
 *  @brief Go language stub to get the gpu device name string
 *
 *  @details This function will call the rsmi_dev_name_get()
 *  function to write the gpu device name string (up to len characters)
 *  for device dv_ind and return a char pointer. This value is then
 *  passed as char * to the Go routine that called it. The caller of this
 *  function must free the allocated buffer for the device name.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::char* VBIOS identifier
 *  @retval NA is returned upon failure.
 *
 */
char* goamdsmi_gpu_dev_name_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU device id
 *
 *  @details This function will call the rsmi_dev_id_get()
 *  function to return the GPU device id. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int value of num GPUs
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_id_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU unique pci id
 *
 *  @details This function will call the rsmi_dev_pci_id_get()
 *  function to return the unique PCI device identifier
 *  associated for a device. This value is then passed as
 *  a int val to the Go routine that called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int value of pci id
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_pci_id_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the VBIOS identifier string
 *
 *  @details This function will call the rsmi_dev_vbios_ver_get()
 *  function to write the VBIOS char array (up to len characters)
 *  for device dv_ind and return a char pointer. This value is then
 *  passed as char pointer to the Go routine that called it. The caller
 *  of this funcion must free the allocated buffer for the vbios
 *  identifier
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::char* vbios buffer of length
 *
 *  @retval ::char* VBIOS identifier
 *  @retval NA is returned upon failure
 *
 */
char* goamdsmi_gpu_dev_vbios_version_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the vendor
 *
 *  @details This function will call the rsmi_dev_vendor_name_get()
 *  function to write the name of the vendor char array (up to len
 *  characters) for a device dv_ind and return a char pointer. This
 *  value is then passed as a char pointer to the Go routine that
 *  called it. The caller of this funcion must free the allocated
 *  buffer for the vbios identifier
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::char* vendor name
 *  @retval NA is returned upon failure.
 *
 */
char* goamdsmi_gpu_dev_vendor_name_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU power cap
 *
 *  @details This function will call the rsmi_dev_power_cap_get()
 *  function to return the gpu power cap. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int GPU power cap
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_power_cap_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU power average
 *
 *  @details This function will call the rsmi_dev_power_ave_get()
 *  function to return the gpu power average. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int GPU power average
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_power_ave_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU current temperature
 *
 *  @details This function will call the rsmi_dev_temp_metric_get()
 *  function to return the gpu current temperature. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, uint32_t sensor, uint32_t metric
 *
 *  @retval ::int GPU current temperature
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric);

/**
 *  @brief Go language stub to get the overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_overdrive_level_get()
 *  function to return the overdrive percentage. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int overdrive level
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_overdrive_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the memory overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_mem_overdrive_level_get()
 *  function to return the memory overdrive percentage. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int memory overdrive level
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_mem_overdrive_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the performance level of the device
 *
 *  @details This function will call the rsmi_dev_perf_level_get()
 *  function to return the  rsmi_dev_perf_level_t. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int performance level (rsmi_dev_perf_level_t)
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_perf_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU SCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu SCLK Limit. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int GPU SCLK Limit
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU MCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu MCLK Limit. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int GPU MCLK Limit
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the minimum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported SCLK frequency.
 *  This value is then passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int mimimum supported sclk frequency
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the minimum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported MCLK frequency.
 *  This value is then passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int mimimum supported mclk sfrequency
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the maximum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported SCLK frequency.
 *  This value is then passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int maximum supported sclk frequency
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the maximum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported MCLK frequency.
 *  This value is then passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::int maximum supported mclk sfrequency
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Activity
 *
 *  @details This function will call the rsmi_dev_gpu_activity_get()
 *  function to return the current GPU use. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int GPU Activity use
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_busy_percent_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Memory Use percent
 *
 *  @details This function will call the rsmi_dev_memory_busy_percent_get()
 *  function to return the current device memory use percent. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int GPU memory use percent
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Memory Usage
 *
 *  @details This function will call the rsmi_dev_memory_usage_get()
 *  function to return the amount of memory currently being used. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int GPU memory usage
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_memory_usage_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the Total amount of GPU Memory
 *
 *  @details This function will call the rsmi_dev_memory_total_get()
 *  function to return the total amount of memory. This value is then
 *  passed as a int val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::int Total GPU memory
 *  @retval -1 is returned upon failure.
 *
 */
int goamdsmi_gpu_dev_gpu_memory_total_get(uint32_t dv_ind);
