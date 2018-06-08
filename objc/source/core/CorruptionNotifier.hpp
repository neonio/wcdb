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

#ifndef CorruptionNotifier_hpp
#define CorruptionNotifier_hpp

#include <WCDB/Lock.hpp>
#include <mutex>
#include <set>

namespace WCDB {

class CorruptionNotifier {
public:
    static CorruptionNotifier *shared();

    void boot();

protected:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::set<std::string> m_paths;

    void addPath(const std::string &path);
    void loop();
};

} //namespace WCDB

#endif /* CorruptionNotifier_hpp */