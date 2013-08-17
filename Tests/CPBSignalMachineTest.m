//
//  CPBSignalMachineTest.m
//  StateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "CPBSignalMachine.h"
#import "CPBTransitionTable.h"


@interface CPBSignalMachineTest : XCTestCase

@end


@implementation CPBSignalMachineTest

CPBSignalMachine *_machine;
CPBTransitionTable *_table;

- (void)setUp
{
    [super setUp];
    
    _table = [[CPBTransitionTable alloc] init];
    [_table mapEvent:@"start" from:@"initial" to:@"A"];
    [_table mapEvent:@"event0" from:@"A" to:@"B"];
    [_table mapEvent:@"event1" from:@"B" to:@"C"];
    [_table mapEvent:@"event2" from:@"C" to:@"D"];
    [_table mapEvent:@"event3" from:@"D" to:@"A"];
    [_table mapEvent:@"event3" from:@"B" to:@"D"];
    
    _machine = [[CPBSignalMachine alloc] initWithTransitionTable:_table initialState:@"initial"];
}

- (void)tearDown
{
    _table = nil;
    _machine = nil;
    
    [super tearDown];
}

- (void)testAllTransitions_TransitionsBeforeSignalObtained_SendsTransitionsOnlySinceSignalObtained
{
    [_machine inputEvent:@"start"];
    [_machine inputEvent:@"event0"];
    
    __block NSUInteger executed = 0;
    __block BOOL errored = NO;
    RACSignal *signal = [_machine allTransitions];
    [signal subscribeNext:^(RACTuple *transition) {
        
        executed++;
        
    } error:^(NSError *error) {
        
        errored = YES;
        
    }];
    
    [_machine inputEvent:@"event1"];
    
    XCTAssertEqual((NSUInteger)1, executed, @"");
    XCTAssertFalse(errored, @"");
}

- (void)testTransitionsFrom_FromStateIsCurrentState_SendsTransition
{
    [_machine inputEvent:@"start"];
    [_machine inputEvent:@"event0"];
    
    __block BOOL executed = NO;
    __block BOOL errored = NO;
    RACSignal *signal = [_machine transitionsFrom:@"B"];
    [signal subscribeNext:^(RACTuple *transition) {
        
        executed = YES;
        XCTAssertEqualObjects(@"B", transition.first, @"");
        XCTAssertEqualObjects(@"C", transition.second, @"");
        
    } error:^(NSError *error) {
        
        errored = YES;
        
    }];
    
    [_machine inputEvent:@"event1"];
    
    XCTAssertTrue(executed, @"");
    XCTAssertFalse(errored, @"");
}

- (void)testTransitionsFrom_FromStateIsNotCurrentState_SendsTransition
{
    __block BOOL executed = NO;
    __block BOOL errored = NO;
    RACSignal *signal = [_machine transitionsFrom:@"B"];
    [signal subscribeNext:^(RACTuple *transition) {
        
        executed = YES;
        
    } error:^(NSError *error) {
        
        errored = YES;
        
    }];
    
    [_machine inputEvent:@"start"];
    [_machine inputEvent:@"event0"];
    
    XCTAssertFalse(executed, @"");
    XCTAssertFalse(errored, @"");
}

- (void)testTransitionsFrom_NoTransitionMappedForEvent_SendsNilToState
{
    [_machine inputEvent:@"start"];
    [_machine inputEvent:@"event0"];
    
    __block BOOL executed = NO;
    __block BOOL errored = NO;
    RACSignal *signal = [_machine transitionsFrom:@"B"];
    [signal subscribeNext:^(RACTuple *transition) {
        
        executed = YES;
        XCTAssertEqualObjects(NSNull.null, transition.second, @"");
        
    } error:^(NSError *error) {
        
        errored = YES;
        
    }];
    
    [_machine inputEvent:@"unregistered"];
    
    XCTAssertTrue(executed, @"");
    XCTAssertFalse(errored, @"");
}

- (void)testTransitions_NoTransitionMappedForEvent_SendsNSNull
{
    __block BOOL executed = NO;
    __block BOOL errored = NO;
    RACSignal *signal = [_machine allTransitions];
    [signal subscribeNext:^(RACTuple *transition) {
        
        executed = YES;
        XCTAssertEqualObjects(NSNull.null, transition.second, @"");
        
    } error:^(NSError *error) {
        
        errored = YES;
        
    }];
    
    [_machine inputEvent:@"unregistered"];
    
    XCTAssertTrue(executed, @"");
    XCTAssertFalse(errored, @"");
}

@end
