//
// Created by darby on 3/26/2023.
//

#pragma once

namespace rockhopper {

    struct Service {
        virtual void        init(void* configuration);
        virtual void        shutdown();
    };

}
