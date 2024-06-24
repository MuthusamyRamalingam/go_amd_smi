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
#include <e_smi.h>
#include "esmi_go_shim.h"

int32_t go_shim_esmi_init()
{
#ifdef ESMI_BUILD
	return (ESMI_SUCCESS == esmi_init()) ? 1 : 0;
#endif
	return 0;
}

int32_t go_shim_esmi_threads_per_core_get()
{
#ifdef ESMI_BUILD
	uint32_t num_threads_per_core;

	if(ESMI_SUCCESS == esmi_threads_per_core_get(&num_threads_per_core))
		return num_threads_per_core;
#endif
	return 0;
}

int32_t go_shim_esmi_number_of_threads_get()
{
#ifdef ESMI_BUILD
	uint32_t total_num_threads;

	if(ESMI_SUCCESS ==  esmi_number_of_cpus_get(&total_num_threads))
		return total_num_threads;
#endif
	return 0;
}

int32_t go_shim_esmi_number_of_sockets_get()
{
#ifdef ESMI_BUILD
	uint32_t num_sockets;

	if (ESMI_SUCCESS == esmi_number_of_sockets_get(&num_sockets))
		return num_sockets;
#endif
    return 0;
}

uint64_t go_shim_esmi_core_energy_get(uint32_t thread_index)
{
#ifdef ESMI_BUILD
	uint64_t core_penergy = 0;

	if(ESMI_SUCCESS == esmi_core_energy_get(thread_index, &core_penergy))
		return core_penergy;
#endif
	return 0;
}

uint64_t go_shim_esmi_socket_energy_get(uint32_t socket_index)
{
#ifdef ESMI_BUILD
	uint64_t socket_penergy = 0;

	if(ESMI_SUCCESS == esmi_socket_energy_get(socket_index, &socket_penergy))
		return socket_penergy;
#endif
	return 0;
}

uint32_t go_shim_esmi_prochot_status_get(uint32_t socket_index)
{
#ifdef ESMI_BUILD
	uint32_t prochot = 0;

	if(ESMI_SUCCESS == esmi_prochot_status_get(socket_index, &prochot))
		return prochot;
#endif
 	return 0;
}

uint32_t go_shim_esmi_socket_power_get(uint32_t socket_index)
{
#ifdef ESMI_BUILD
	uint32_t ppower;

	if(ESMI_SUCCESS == esmi_socket_power_get(socket_index, &ppower))
		return ppower;
#endif
	return 0;
}

uint32_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index)
{
#ifdef ESMI_BUILD
	uint32_t pcap;

	if(ESMI_SUCCESS == esmi_socket_power_cap_get(socket_index, &pcap))
		return pcap;
#endif
	return 0;
}

uint32_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index)
{
#ifdef ESMI_BUILD
	uint32_t boostlimit = 0;

	if(ESMI_SUCCESS == esmi_core_boostlimit_get(thread_index, &boostlimit))
		return boostlimit;
#endif
	return 0;
}

