/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * *    * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define LOG_NIDEBUG 0

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LOG_TAG "QTI PowerHAL"
#include <hardware/hardware.h>
#include <hardware/power.h>
#include <utils/Log.h>

#include "hint-data.h"
#include "metadata-defs.h"
#include "performance.h"
#include "power-common.h"
#include "utils.h"

#define MIN_VAL(X, Y) ((X > Y) ? (Y) : (X))

static void process_interaction_hint(void* data) {
    int resources[] = { MAX_FREQ_BIG_CORE_0, 0xFFF, MAX_FREQ_LITTLE_CORE_0, 0xFFF, MIN_FREQ_BIG_CORE_0, 1535, MIN_FREQ_LITTLE_CORE_0, 1478 };
    int duration = 200;
    interaction(duration, ARRAY_SIZE(resources), resources);
}

static void process_app_launch_hint(void* data) {
    int resources[] = { SCHED_UP_MIGRATE, 0x28, SCHED_DOWN_MIGRATE, 0x32, MAX_FREQ_BIG_CORE_0, 0xFFF,
                        MAX_FREQ_LITTLE_CORE_0, 0xFFF, MIN_FREQ_BIG_CORE_0, 1535, MIN_FREQ_LITTLE_CORE_0, 1478 };
    int duration = 1200;
    perform_hint(duration, ARRAY_SIZE(resources), resources);
}

int power_hint_override(power_hint_t hint, void* data) {
    switch (hint) {
        case POWER_HINT_VSYNC: {
            break;
        }
        case POWER_HINT_VIDEO_ENCODE: {
            break;
        }
        case POWER_HINT_VIDEO_DECODE: {
            break;
        }
        case POWER_HINT_INTERACTION: {
            process_interaction_hint(data);
            return HINT_HANDLED;
        }
        case POWER_HINT_LAUNCH: {
            process_app_launch_hint(data);
            return HINT_HANDLED;
        }
        default:
            break;
    }
    return HINT_NONE;
}

int set_interactive_override(struct power_module* module, int on) {
    return HINT_HANDLED; /* to set hints for display on and off. Not in use now */
}
