//
// Created by darby on 3/24/2023.
//

#pragma once

#include "platform.h"
#include "service.h"

namespace rockhopper {

    struct MemoryStatistics {
        size_t              allocated_bytes;
        size_t              total_bytes;

        u32                 allocation_count;

        void                add(size_t a) {
            if(a) {
                allocated_bytes += a;
                allocation_count++;
            }
        }
    };

    struct Allocator {
        virtual ~Allocator() {}
        virtual void*       allocate(size_t size, size_t alignment) = 0;
        virtual void*       allocate(size_t size, size_t alignment, cstring file, i32 line) = 0;

        virtual void        deallocate(void* pointer) = 0;
    };

    // A Heap Allocator is useful allocations lasting more than a frame
    struct HeapAllocator : public Allocator {
        ~HeapAllocator() override;

        void                init(size_t size);
        void                shutdown();

        void                debug_ui();

        void*               allocate(size_t size, size_t alignment) override;
        void*               allocate(size_t size, size_t alignment, cstring file, i32 line) override;

        void                deallocate(void* pointer) override;

        void*               tlsf_handle;
        void*               memory;
        size_t              allocated_size = 0;
        size_t              max_size = 0;
    };

    struct StackAllocator : public Allocator {
        void                init(size_t size);
        void                shutdown();

        void*               allocate(size_t size, size_t alignment) override;
        void*               allocate(size_t size, size_t alignment, cstring file, i32 line) override;

        void                deallocate(void* pointer) override;

        size_t              get_marker();
        void                free_marker(size_t marker);

        void                clear();

        u8*                 memory = nullptr;
        size_t              total_size = 0;
        size_t              allocated_size = 0;
    };

    // A Linear Allocator could be useful for resources with a frame-level lifetime
    struct LinearAllocator : public Allocator {
        ~LinearAllocator();

        void                init(size_t size);
        void                shutdown();

        void*               allocate(const size_t size, size_t alignment) override;
        void*               allocate(const size_t size, size_t alignment, cstring file, i32 line) override;

        void                deallocate(void* pointer) override;

        void                clear();

        u8*                 memory = nullptr;
        size_t              total_size = 0;
        size_t              allocated_size = 0;
    };

    struct MemoryServiceConfiguration {
        // Defaults to max 32MB of dynamic memory.
        size_t              maximum_dynamic_size = 32 * 1024 * 1024;
    };

    struct MemoryService : public Service {

        ROCKHOPPER_DECLARE_SERVICE( MemoryService );

        void init(void* configuration) override;
        void shutdown() override;

        void imgui_draw();

        // System Allocator
        HeapAllocator system_allocator;

        void test();
    };

    #define rock_alloc(size, allocator)                     ((allocator)->allocate(size, 1, __FILE__, __LINE__))
    #define rock_alloc_aligned(size, allocator, alignment)  ((allocator)->allocate(size, alignment, __FILE__, __LINE__))

    #define rock_free(pointer, allocator)                   (allocator)->deallocate(pointer)

    #define rock_kilo(size)                                 (size * 1024)
    #define rock_mega(size)                                 (size * 1024 * 1024)
    #define rock_giga(size)                                 (size * 1024 * 1024 * 1024)

}