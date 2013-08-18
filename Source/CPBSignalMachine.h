//
//  CPBSignalMachine.h
//  CPBStateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <Foundation/Foundation.h>


extern NSString * const CPBStateSignalsErrorDomain;
extern NSInteger const CPBStateSignalsErrorCodeNoTransitionRegistered;


@class CPBTransitionTable;


@interface CPBSignalMachine : NSObject

/// Creates a new signal machine with the specified transition table and initial state.
///
/// @param table The transition table to be used by this signal machine. A defensive copy is made.
/// @param initialState The initial state for this signal machine.
/// @return The newly-created signal machine.
- (id)initWithTransitionTable:(CPBTransitionTable *)table initialState:(NSString *)initialState;


#pragma mark Event inputs

/// Notifies this signal machine of a new input event, to prompt a transition.
///
/// @param event The input event occurring in this instance.
- (void)inputEvent:(NSString *)event;

/// Notifies this signal machine of a new input event with the specified event context, to prompt a transition.
///
/// @param event The input event occurring in this instance.
/// @param eventContext A context object to be included as payload to transition handlers.
- (void)inputEvent:(NSString *)event context:(id)eventContext;


#pragma mark Transition signals

/// Returns a signal which sends a tuple for every transition made by this signal machine.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// If a transition is not registered for an event in a given "from state", the tuple's "to state" will be NSNull.
/// Will not send an error if an event is sent which has no corresponding transition mapping.
///
/// @return a signal which sends every transition made by this signal machine.
- (RACSignal *)allTransitions;

/// Returns a signal which sends a tuple for every transition made by this signal machine from the specified state.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Will not send an error if an event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @return a signal which sends every transition made by this signal machine from the specified state.
- (RACSignal *)transitionsFrom:(NSString *)fromState;

/// Returns a signal which sends a tuple for every transition made by this signal machine from the specified `fromState` to the specified `toState`.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Will not send an error if an event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @return a signal which sends every transition made by this signal machine from the specified `fromState` to the specified `toState`.
- (RACSignal *)transitionsFrom:(NSString *)fromState to:(NSString *)toState;

/// Returns a signal which sends a tuple for every transition made by this signal machine to the specified state.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Will not send an error if an event is sent which has no corresponding transition mapping.
///
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @return a signal which sends every transition made by this signal machine to the specified state.
- (RACSignal *)transitionsTo:(NSString *)toState;

/// Returns a signal which sends a tuple for every transition made by this signal machine that could not find a corresponding registered transition.
/// The tuple consists of the "from state", NSNull, the input event, and the event context (or NSNull if none was provided).
///
/// @return a signal which sends every faulted transition made by this signal machine.
- (RACSignal *)transitionFaults;


#pragma mark Operations

/// Returns a signal which behaves identically to `source`, except that it sends an error if a registered transition could not be found (i.e., if the transition "to state" is NSNull).
///
/// @source The signal whose behavior to modify.
/// @return a signal which sends an error if `source` sends a transition whose "to state" (the second parameter in the tuple) is NSNull.
+ (RACSignal *)errorOnTransitionFault:(RACSignal *)source;

@end
