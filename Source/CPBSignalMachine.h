//
//  CPBSignalMachine.h
//  CPBStateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CPBTransitionTable;


@interface CPBSignalMachine : NSObject

/// Creates a new signal machine with the specified transition table.
///
/// @param table The transition table to be used by this signal machine. A defensive copy is made.
/// @return The newly-created signal machine.
- (id)initWithTransitionTable:(CPBTransitionTable *)table;

/// Notifies this signal machine of a new input event, to prompt a transition.
///
/// @param event The input event occurring in this instance.
- (void)inputEvent:(NSString *)event;

/// Notifies this signal machine of a new input event with the specified event context, to prompt a transition.
///
/// @param event The input event occurring in this instance.
/// @param eventContext A context object to be included as payload to transition handlers.
- (void)inputEvent:(NSString *)event context:(id)eventContext;

/// Returns a new signal which sends every event received by this signal machine.
///
/// @return a new signal which sends every event received by this signal machine.
- (RACSignal *)allEvents;

/// Returns a new signal which sends every transition made by this signal machine.
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @return a new signal which sends every transition made by this signal machine.
- (RACSignal *)allTransitions;

/// Returns a new signal which sends every transition made by this signal machine from the specified state.
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @return a new signal which sends every transition made by this signal machine from the specified state.
- (RACSignal *)transitionsFrom:(NSString *)fromState;

/// Returns a new signal which sends every transition made by this signal machine from the specified `fromState` to the specified `toState`.
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @return a new signal which sends every transition made by this signal machine from the specified `fromState` to the specified `toState`.
- (RACSignal *)transitionsFrom:(NSString *)fromState to:(NSString *)toState;

/// Returns a new signal which sends every transition made by this signal machine to the specified state.
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @return a new signal which sends every transition made by this signal machine to the specified state.
- (RACSignal *)transitionsTo:(NSString *)toState;

@end
