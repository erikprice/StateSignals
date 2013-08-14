//
//  CPBSignalMachine.h
//  CPBStateSignals
//
//  Created by Erik Price on 2013-08-14.
//  Copyright (c) 2013 Erik Price. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CPBTransitionTable.h"


@interface CPBSignalMachine : NSObject

- (id)initWithTransitionTable:(CPBTransitionTable *)table;


@end
