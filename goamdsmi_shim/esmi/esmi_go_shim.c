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
#include "esmi_go_shim.h"
#ifdef ESMI_BUILD
#include <e_smi.h>
#endif
#include <stdio.h>

#ifdef ESMI_BUILD
goamdsmi_status_t go_shim_esmi_init()
{
	printf("CCCC go_shim_esmi_init\n");
	return (ESMI_SUCCESS == esmi_init()) ? GOAMDSMI_STATUS_SUCCESS : GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_threads_per_core_get(uint32_t* threads_per_core)
{
	*threads_per_core				= 0;
	uint32_t threads_per_core_temp	= 0;

	printf("CCCC go_shim_esmi_threads_per_core_get");
	if(ESMI_SUCCESS == esmi_threads_per_core_get(&threads_per_core_temp))
	{
		*threads_per_core = threads_per_core_temp;
		printf("DDDD go_shim_esmi_threads_per_core_get:%d\n",*threads_per_core);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_number_of_threads_get(uint32_t* number_of_threads)
{
	*number_of_threads 				= 0;
	uint32_t number_of_threads_temp	= 0;

	printf("CCCC go_shim_esmi_number_of_threads_get:%d\n",*number_of_threads);
	if(ESMI_SUCCESS ==  esmi_number_of_cpus_get(&number_of_threads_temp))
	{
		*number_of_threads = number_of_threads_temp;
		printf("DDDD go_shim_esmi_number_of_threads_get:%d\n",*number_of_threads);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_number_of_sockets_get(uint32_t* number_of_sockets)
{
	*number_of_sockets				= 0;
	uint32_t number_of_sockets_temp = 0;

	printf("CCCC go_shim_esmi_number_of_sockets_get:%d\n",*number_of_sockets);
	if (ESMI_SUCCESS == esmi_number_of_sockets_get(&number_of_sockets_temp))
	{
		*number_of_sockets = number_of_sockets_temp;
		printf("DDDD go_shim_esmi_number_of_sockets_get:%d\n",*number_of_sockets);
		return GOAMDSMI_STATUS_SUCCESS;
	}

	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_core_energy_get(uint32_t thread_index, uint64_t* core_energy)
{
	*core_energy				= 0;
	uint64_t core_energy_temp	= 0;

	printf("CCCC go_shim_esmi_core_energy_get[%d]:pc:%d:energy:%d\n",thread_index,thread_index,*core_energy);
	if(ESMI_SUCCESS == esmi_core_energy_get(thread_index, &core_energy_temp))
	{
		*core_energy = core_energy_temp;
		printf("DDDD go_shim_esmi_core_energy_get[%d]:pc:%d:energy:%d\n",thread_index,thread_index,*core_energy);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)
{
	*socket_energy				= 0;
	uint64_t socket_energy_temp	= 0;

	if(ESMI_SUCCESS == esmi_socket_energy_get(socket_index, &socket_energy_temp))
	{
		*socket_energy = socket_energy_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_prochot_status_get(uint32_t socket_index, uint32_t* prochot)
{
	*prochot				= 0;
	uint32_t prochot_temp	= 0;

	if(ESMI_SUCCESS == esmi_prochot_status_get(socket_index, &prochot_temp))
	{
		*prochot = prochot_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_power_get(uint32_t socket_index, uint32_t* socket_power)
{
	*socket_power				= 0;
	uint32_t socket_power_temp	= 0;

	if(ESMI_SUCCESS == esmi_socket_power_get(socket_index, &socket_power_temp))
	{
		*socket_power = socket_power_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)
{
	*socket_power_cap 				= 0;
	uint32_t socket_power_cap_temp 	= 0;

	if(ESMI_SUCCESS == esmi_socket_power_cap_get(socket_index, &socket_power_cap_temp))
	{
		*socket_power_cap = socket_power_cap_temp;
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)
{
	*core_boostlimit				= 0;
	uint32_t core_boostlimit_temp	= 0;

	printf("CCCC go_shim_esmi_core_boostlimit_get[%d]:pc:%d:core_boostlimit:%d\n",thread_index,thread_index,*core_boostlimit);
	if(ESMI_SUCCESS == esmi_core_boostlimit_get(thread_index, &core_boostlimit_temp))
	{
		*core_boostlimit = core_boostlimit_temp;
		printf("DDDD go_shim_esmi_core_boostlimit_get[%d]:pc:%d:core_boostlimit:%d\n",thread_index,thread_index,*core_boostlimit);
		return GOAMDSMI_STATUS_SUCCESS;
	}
	
	return GOAMDSMI_STATUS_FAILURE;
}
#else
goamdsmi_status_t go_shim_esmi_init()																	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_threads_per_core_get(uint32_t* threads_per_core)							{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_number_of_threads_get(uint32_t* number_of_threads)						{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_number_of_sockets_get(uint32_t* number_of_sockets)						{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_core_energy_get(uint32_t thread_index, uint64_t* core_energy)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_prochot_status_get(uint32_t socket_index, uint32_t* prochot)				{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_power_get(uint32_t socket_index, uint32_t* socket_power)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)	{return GOAMDSMI_STATUS_FAILURE;}
#endif	

