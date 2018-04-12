/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <WCDB/WCTCommon.h>
#import <WCDB/WCTProperty.h>

@protocol WCTTableCoding
@required
+ (const WCTBinding *)objectRelationalMappingForWCDB;
+ (const WCTPropertyList &)AllProperties;
+ (const WCDB::Expression::All &)AllResults;
@optional
@property(nonatomic, assign) long long lastInsertedRowID;
@property(nonatomic, assign) BOOL isAutoIncrement;
@end

@protocol WCTColumnCoding
@required
+ (instancetype)unarchiveWithWCTValue:(id /* NSData*, NSString*, NSNumber*, nil */)value; //value could be nil
- (id /* NSData*, NSString*, NSNumber*, nil */)archivedWCTValue;                          //value could be nil
+ (WCDB::ColumnType)columnTypeForWCDB;
@end