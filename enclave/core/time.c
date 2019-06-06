// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <openenclave/bits/types.h>
#include <openenclave/corelibc/time.h>
#include <openenclave/internal/calls.h>
#include <openenclave/internal/time.h>

int oe_sleep_msec(uint64_t milliseconds)
{
    int ret = -1;

    if (oe_ocall(
            OE_OCALL_SLEEP,
            milliseconds,
            sizeof(milliseconds),
            false,
            NULL,
            0) != OE_OK)
        goto done;

    ret = 0;

done:

    return ret;
}

uint64_t oe_get_time(void)
{
    uint64_t ret = (uint64_t)-1;
    uint64_t arg = 0;

    if (oe_ocall(
            OE_OCALL_GET_TIME, arg, sizeof(arg), false, &ret, sizeof(ret)) !=
        OE_OK)
    {
        ret = (uint32_t)-1;
        goto done;
    }

done:

    return ret;
}

/* OE core libc wrapper for time() function */
time_t oe_time(time_t* tloc)
{
    uint64_t msec = oe_get_time() / 1000;
    time_t time = (time_t)(msec > OE_LONG_MAX ? OE_LONG_MAX : msec);

    if (tloc)
        *tloc = time;

    return time;
}
