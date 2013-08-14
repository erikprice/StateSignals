//
//  CPBTransitionTableTest.m
//  StateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "CPBTransitionTable.h"


@interface CPBTransitionTableTest : XCTestCase

@end

@implementation CPBTransitionTableTest

CPBTransitionTable *_table;

- (void)setUp
{
    [super setUp];

    _table = [[CPBTransitionTable alloc] init];
    [_table mapEvent:@"event0" from:@"A" to:@"B"];
    [_table mapEvent:@"event1" from:@"B" to:@"C"];
    [_table mapEvent:@"event2" from:@"C" to:@"D"];
    [_table mapEvent:@"event3" from:@"D" to:@"A"];
    [_table mapEvent:@"event3" from:@"B" to:@"D"];
}

- (void)tearDown
{
    _table = nil;
    
    [super tearDown];
}

- (void)testStateForEventFrom_NoTransitionMapped_ReturnsNil
{
    XCTAssertNil([_table toStateForEvent:@"event99" from:@"Z"], @"");
    XCTAssertNil([_table toStateForEvent:@"event0" from:@"Z"], @"");
    XCTAssertNil([_table toStateForEvent:@"event99" from:@"A"], @"");
}

- (void)testStateForEventFrom_TransitionMapped_ReturnsNewState
{
    XCTAssertEqualObjects(@"B", [_table toStateForEvent:@"event0" from:@"A"], @"");
    XCTAssertEqualObjects(@"C", [_table toStateForEvent:@"event1" from:@"B"], @"");
    XCTAssertEqualObjects(@"D", [_table toStateForEvent:@"event2" from:@"C"], @"");
}

- (void)testCopy_ChangesMadeToOriginalAfterCopy_CopyUnaffected
{
    CPBTransitionTable *copy = [_table copy];
    
    [_table mapEvent:@"event20" from:@"D" to:@"E"];
    [copy mapEvent:@"event20" from:@"D" to:@"F"];
    
    XCTAssertEqualObjects(@"B", [_table toStateForEvent:@"event0" from:@"A"], @"");
    XCTAssertEqualObjects(@"B", [copy toStateForEvent:@"event0" from:@"A"], @"");
    
    XCTAssertEqualObjects(@"E", [_table toStateForEvent:@"event20" from:@"D"], @"");
    XCTAssertEqualObjects(@"F", [copy toStateForEvent:@"event20" from:@"D"], @"");
}

- (void)testStateForEventFrom_EventMappedToMultipleTransitions_ReturnsCorrectNewStateForCombination
{
    XCTAssertEqualObjects(@"A", [_table toStateForEvent:@"event3" from:@"D"], @"");
    XCTAssertEqualObjects(@"D", [_table toStateForEvent:@"event3" from:@"B"], @"");
}

- (void)testMapEventFromTo_ExistingTransitionMappedForEvent_OverwritesPreviousTransition
{
    [_table mapEvent:@"event2" from:@"C" to:@"A"];
    
    XCTAssertEqualObjects(@"A", [_table toStateForEvent:@"event2" from:@"C"], @"");
}

@end
