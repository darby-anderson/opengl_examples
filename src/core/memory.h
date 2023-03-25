//
// Created by darby on 3/24/2023.
//

#pragma once

#include "platform.h"

namespace rockhopper {

    struct Allocator {
        virtual ~Allocator() {}
        virtual void*       allocate(size_t size, size_t alignment) = 0;
        virtual void*       allocate(size_t size, size_t alignment, cstring file, i32 line) = 0;

        virtual void        deallocate(void* pointer) = 0;
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

}