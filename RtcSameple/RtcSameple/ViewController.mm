//
//  ViewController.m
//  RtcSameple
//
//  Created by raymon_wang on 14-7-24.
//  Copyright (c) 2014年 yunwei. All rights reserved.
//

#import "ViewController.h"
#include "MediaSample.h"

static MediaSample* media = NULL;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    media = new MediaSample;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
