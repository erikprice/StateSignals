//
//  CPBTransitionTable.m
//  StateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import "CPBTransitionTable.h"


@interface CPBTransitionTable ()

// Maps event keys to sub-maps of "from states" to "to states".
@property (nonatomic, strong) NSMutableDictionary *eventMappings;

@end


@implementation CPBTransitionTable

- (id)init
{
    if (self = [super init])
    {
        _eventMappings = [[NSMutableDictionary alloc] init];
    }
    
    return self;
}

- (void)mapEvent:(NSString *)event from:(NSString *)fromState to:(NSString *)toState
{
    NSMutableDictionary *transitions = self.eventMappings[event];
    if (!transitions)
    {
        transitions = [[NSMutableDictionary alloc] init];
        self.eventMappings[event] = transitions;
    }
    
    if (transitions[fromState])
    {
        NSLog(@"Warning: -[CPBTransitionTable mapEvent:%@ from:%@ to:%@] overwriting existing transition to '%@'.", event, fromState, toState, transitions[fromState]);
    }
    
    transitions[fromState] = toState;
}

- (NSString *)toStateForEvent:(NSString *)event from:(NSString *)fromState
{
    NSDictionary *transition = self.eventMappings[event];
    return transition ? transition[fromState] : nil;
}

- (id)copyWithZone:(NSZone *)zone
{
    CPBTransitionTable *copy = [self.class allocWithZone:zone];
    copy->_eventMappings = [self.eventMappings copyWithZone:zone];
    
    return copy;
}

@end
