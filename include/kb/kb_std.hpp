//
// Created by happy on 8/24/2025.
//

#ifndef KB_NETWORKING_KB_STD_HPP
#define KB_NETWORKING_KB_STD_HPP

#include "kb/kb_core.h"

#include "kb/core/types.hpp"
#include "kb/core/logger.hpp"
#include "kb/core/owning_buffer.hpp"

#include "kb/mem/arena_allocator.hpp"
#include "kb/mem/intrusive_shared_ref.hpp"

namespace kb {

// Default reference handling alias
template <typename T>
using Ref = ::kb::mem::IntrusiveSharedRef<T>;

template <typename T>
using RefCounted = ::kb::mem::RefCounted<T>;

} // end namespace kb

#endif  //KB_NETWORKING_KB_STD_HPP
