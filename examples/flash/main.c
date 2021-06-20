/* Copyright (c) 2020-2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include "hal/flash_api.h"

#ifndef ALIGN_DOWN
#define ALIGN_DOWN(x, a) ((x)& ~((a) - 1))
#endif

int main()
{      
    flash_t test_flash;
    int32_t ret;
    
    ret = flash_init(&test_flash);
    //TEST_ASSERT_EQUAL_INT32(0, ret);

    uint32_t test_size = flash_get_page_size(&test_flash);

    uint8_t *data = (uint8_t*) malloc(test_size);
    uint8_t *data_flashed = (uint8_t*) malloc(test_size);

    memset(data, 0xCE, test_size);

    // the one before the last page in the system
    uint32_t address = flash_get_start_address(&test_flash) + flash_get_size(&test_flash) - (2 * test_size);

    // sector size might not be same as page size
    uint32_t erase_sector_boundary = ALIGN_DOWN(address, flash_get_sector_size(&test_flash, address));
    //utest_printf("ROM ends at 0x%lx, test starts at 0x%lx\n", FLASHIAP_APP_ROM_END_ADDR, erase_sector_boundary);
    //TEST_SKIP_UNLESS_MESSAGE(erase_sector_boundary >= FLASHIAP_APP_ROM_END_ADDR, "Test skipped. Test region overlaps code.");

    ret = flash_erase_sector(&test_flash, erase_sector_boundary);
    //TEST_ASSERT_EQUAL_INT32(0, ret);

    ret = flash_program_page(&test_flash, address, data, test_size);
    //TEST_ASSERT_EQUAL_INT32(0, ret);

    ret = flash_read(&test_flash, address, data_flashed, test_size);
    //TEST_ASSERT_EQUAL_INT32(0, ret);
    //TEST_ASSERT_EQUAL_UINT8_ARRAY(data, data_flashed, test_size);

    // sector size might not be same as page size
    erase_sector_boundary = ALIGN_DOWN(address, flash_get_sector_size(&test_flash, address));
    ret = flash_erase_sector(&test_flash, erase_sector_boundary);
    //TEST_ASSERT_EQUAL_INT32(0, ret);

    // write another data to be certain we are re-flashing
    memset(data, 0xAC, test_size);
    
    ret = flash_program_page(&test_flash, address, data, test_size);
    //TEST_ASSERT_EQUAL_INT32(0, ret);

    ret = flash_read(&test_flash, address, data_flashed, test_size);
    //TEST_ASSERT_EQUAL_INT32(0, ret);
    //TEST_ASSERT_EQUAL_UINT8_ARRAY(data, data_flashed, test_size);

    ret = flash_free(&test_flash);
    //TEST_ASSERT_EQUAL_INT32(0, ret);
    free(data);
    free(data_flashed);

    while(1);
}