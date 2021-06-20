# Copyright (c) 2020-2021 Arm Limited
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# Sets the post build operation for Mbed targets.
#
macro(mbed_set_post_build_operation)

    add_custom_target(mbed-post-build-bin-${mbed_target_name})

    add_custom_command(
        TARGET
            mbed-post-build-bin-${mbed_target_name}
        POST_BUILD
        COMMAND
            ${post_build_command}
        VERBATIM
    )
endmacro()
