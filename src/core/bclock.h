#ifndef BCLOCK_H
#define BCLOCK_H

#include "defines.h"

class bclock {
public:
    void start();
    void stop();
    f64 update();

    [[nodiscard]] f64 get_elapsed() const;
    [[nodiscard]] f64 get_start_time() const;
private:
    f64 start_time{};
    f64 elapsed{};
};

#endif //BCLOCK_H
