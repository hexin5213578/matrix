/*
 * Tencent is pleased to support the open source community by making wechat-matrix available.
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the BSD 3-Clause License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef memory_logging_event_buffer_h
#define memory_logging_event_buffer_h

#include "logger_internal.h"
#include "memory_logging_event.h"

struct memory_logging_event_buffer {
    int32_t write_index;
    int32_t last_write_index;
    int32_t read_index;
    int32_t buffer_size;
    uint8_t *buffer;
    
    malloc_lock_s lock;
    
    volatile thread_id t_id;
    memory_logging_event_buffer *next_event_buffer;
};

void memory_logging_event_buffer_compress(memory_logging_event_buffer *event_buffer);

FORCE_INLINE void memory_logging_event_buffer_lock(memory_logging_event_buffer *event_buffer);
FORCE_INLINE void memory_logging_event_buffer_unlock(memory_logging_event_buffer *event_buffer);

FORCE_INLINE bool memory_logging_event_buffer_is_full(memory_logging_event_buffer *event_buffer, bool is_alloc = false);
FORCE_INLINE memory_logging_event *memory_logging_event_buffer_new_event(memory_logging_event_buffer *event_buffer);
FORCE_INLINE memory_logging_event *memory_logging_event_buffer_last_event(memory_logging_event_buffer *event_buffer);

FORCE_INLINE memory_logging_event *memory_logging_event_buffer_begin(memory_logging_event_buffer *event_buffer);
FORCE_INLINE memory_logging_event *memory_logging_event_buffer_next(memory_logging_event_buffer *event_buffer);

FORCE_INLINE void memory_logging_event_buffer_update_write_index_with_size(memory_logging_event_buffer *event_buffer, size_t write_size);
FORCE_INLINE void memory_logging_event_buffer_update_to_last_write_index(memory_logging_event_buffer *event_buffer);

#endif /* memory_logging_event_buffer_h */
