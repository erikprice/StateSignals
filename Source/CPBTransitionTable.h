//
//  CPBTransitionTable.h
//  StateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface CPBTransitionTable : NSObject <NSCopying, NSObject>

/// Maps an event to a transition from one state to another.
///
/// @param event The event to trigger this transition.
/// @param fromState The "current" state of the state machine in order for `event` to trigger this transition.
/// @param toState The state to which to transition (from `fromState`) when the event is received.
- (void)mapEvent:(NSString *)event from:(NSString *)fromState to:(NSString *)toState;

/// Returns the state to which a transition has been mapped, given the specified event and current state.
///
/// @param event The event which triggered the transition.
/// @param fromState The "current" state of the state machine, for which a corresponding state to transition to is sought.
/// @return The state for which a transition has been registered when `event` is triggered while in `fromState`, or nil if no transition could be found.
- (NSString *)toStateForEvent:(NSString *)event from:(NSString *)fromState;

@end
