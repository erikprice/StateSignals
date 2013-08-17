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


#pragma mark Transition signals that send error on fault

/// Returns a signal which sends a tuple for every transition made by this signal machine.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// If a transition is not registered for an event in a given "from state", the tuple's "to state" will be NSNull.
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param A Boolean indicating whether the returned signal should send an error if a transition lookup fault occurs.
/// @return a signal which sends every transition made by this signal machine.
- (RACSignal *)allTransitionsWithErrorOnTransitionFault:(BOOL)sendErrorOnFault;

/// Returns a signal which sends a tuple for every transition made by this signal machine from the specified state.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @param A Boolean indicating whether the returned signal should send an error if a transition lookup fault occurs.
/// @return a signal which sends every transition made by this signal machine from the specified state.
- (RACSignal *)transitionsFrom:(NSString *)fromState errorOnTransitionFault:(BOOL)sendErrorOnFault;

/// Returns a signal which sends a tuple for every transition made by this signal machine from the specified `fromState` to the specified `toState`.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param fromState The "from state" from which transitions must be made to be sent on the returned signal.
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @param A Boolean indicating whether the returned signal should send an error if a transition lookup fault occurs.
/// @return a signal which sends every transition made by this signal machine from the specified `fromState` to the specified `toState`.
- (RACSignal *)transitionsFrom:(NSString *)fromState to:(NSString *)toState errorOnTransitionFault:(BOOL)sendErrorOnFault;

/// Returns a signal which sends a tuple for every transition made by this signal machine to the specified state.
/// The tuple consists of the "from state", the "to state", the input event, and the event context (or NSNull if none was provided).
/// Sends an error if any event is sent which has no corresponding transition mapping.
///
/// @param toState The "to state" to which transitions must be made to be sent on the returned signal.
/// @param A Boolean indicating whether the returned signal should send an error if a transition lookup fault occurs.
/// @return a signal which sends every transition made by this signal machine to the specified state.
- (RACSignal *)transitionsTo:(NSString *)toState errorOnTransitionFault:(BOOL)sendErrorOnFault;

/// Returns a signal which sends an error if this signal machine could not find a corresponding registered transition for a given event and/or "from state".
///
/// @param A Boolean indicating whether the returned signal should send an error if a transition lookup fault occurs.
/// @return a signal which sends an error if this signal machine faults a transition lookup.
- (RACSignal *)transitionFaultsWithError:(BOOL)sendErrorOnFault;

@end
