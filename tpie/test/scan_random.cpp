// Copyright (c) 1994 Darren Erik Vengroff
//
// File: scan_random.cpp
// Author: Darren Erik Vengroff <darrenv@eecs.umich.edu>
// Created: 10/6/94
//
// A scan management object to write a stream of random integers.
//

// Get information on the configuration to test.
#include "app_config.h"

#include <versions.h>
VERSION(scan_random_cpp,"$Id: scan_random.cpp,v 1.9 2003-09-11 17:51:20 jan Exp $");

#include "scan_random.h"

scan_random::scan_random(unsigned int count, int seed) {
    this->max = count;
    this->remaining = count;

    LOG_APP_DEBUG("scan_random seed = ");
    LOG_APP_DEBUG(seed);
    LOG_APP_DEBUG('\n');

    TPIE_OS_SRANDOM(seed);
}

scan_random::~scan_random(void)
{
}


AMI_err scan_random::initialize(void)
{
    this->remaining = this->max;

    return AMI_ERROR_NO_ERROR;
};

AMI_err scan_random::operate(int *out1, AMI_SCAN_FLAG *sf)
{
    if ((*sf = ((this->remaining)-- != 0))) {
        *out1 = TPIE_OS_RANDOM();
        return AMI_SCAN_CONTINUE;
    } else {
        return AMI_SCAN_DONE;
    }
};
