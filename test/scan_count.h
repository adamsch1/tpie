// Copyright (c) 1994 Darren Erik Vengroff
//
// File: scan_count.h
// Author: Darren Erik Vengroff <darrenv@eecs.umich.edu>
// Created: 10/6/94
//
// $Id: scan_count.h,v 1.2 1995-06-30 21:09:29 darrenv Exp $
//
#ifndef _SCAN_COUNT_H
#define _SCAN_COUNT_H

class scan_count : AMI_scan_object {
private:
    int maximum;
public:
    int ii;
    unsigned long int called;

    scan_count(int max = 1000);
    AMI_err initialize(void);
    AMI_err operate(int *out1, AMI_SCAN_FLAG *sf);
};

#endif // _SCAN_COUNT_H 
