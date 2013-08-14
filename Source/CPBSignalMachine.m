//
//  CPBSignalMachine.m
//  CPBStateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import "CPBSignalMachine.h"

#import "CPBTransitionTable.h"


@interface CPBSignalMachine ()

@property (nonatomic, strong) CPBTransitionTable *transitionTable;

@end


@implementation CPBSignalMachine

- (id)init
{
    NSLog(@"%@ is not a valid initializer; use -[CPBSignalMachine initWithTransitionTable:] instead", NSStringFromSelector(_cmd));
    return [super init];
}

- (id)initWithTransitionTable:(CPBTransitionTable *)table
{
    if (self = [super init])
    {
        _transitionTable = [table copy];
    }
    
    return self;
}

- (void)inputEvent:(NSString *)event
{
    
}

- (void)inputEvent:(NSString *)event context:(id)eventContext
{
    
}

- (RACSignal *)allEvents
{
    return nil;
}

- (RACSignal *)allTransitions
{
    return nil;
}

- (RACSignal *)transitionsFrom:(NSString *)fromState
{
    return nil;
}

- (RACSignal *)transitionsFrom:(NSString *)fromState to:(NSString *)toState
{
    return nil;
}

- (RACSignal *)transitionsTo:(NSString *)toState
{
    return nil;
}

@end
