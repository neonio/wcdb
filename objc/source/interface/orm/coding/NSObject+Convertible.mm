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

#import <WCDB/NSData+noCopyData.h>
#import <WCDB/WCDB.h>

namespace WCDB {

LiteralValue LiteralValueConvertible<NSObject *>::as(NSObject *const &t)
{
    assert([t conformsToProtocol:@protocol(WCTColumnCoding)]);
    id value = [(id<WCTColumnCoding>) t archivedWCTValue];
    value = [(id<WCTColumnCoding>) value archivedWCTValue];
    if ([value isKindOfClass:NSData.class]) {
        NSData *data = (NSData *) value;
        return LiteralValue(data.noCopyData);
    } else if ([value isKindOfClass:NSString.class]) {
        NSString *string = (NSString *) value;
        return LiteralValue(string.UTF8String);
    } else if ([value isKindOfClass:NSNumber.class]) {
        NSNumber *number = (NSNumber *) value;
        if (CFNumberIsFloatType((CFNumberRef) number)) {
            return LiteralValue(number.doubleValue);
        } else {
            if (CFNumberGetByteSize((CFNumberRef) number) <= 4) {
                return LiteralValue(number.intValue);
            } else {
                return LiteralValue(number.longLongValue);
            }
        }
    } else {
        return LiteralValue(nullptr);
    }
}

Expression ExpressionConvertible<NSObject *>::as(NSObject *const &t)
{
    return Expression(LiteralValueConvertible<NSObject *>::as(t));
}

} //namespace WCDB