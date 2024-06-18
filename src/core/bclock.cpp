//
// Created by Matylda on 18.06.2024.
//

#include "bclock.h"

#include "platform/platform.h"

void bclock::start() {
    start_time = platform_get_absolute_time();
    elapsed = 0;
}

void bclock::stop() {
    start_time = 0;
}

void bclock::update() {
    if(start_time == 0) return;

    elapsed = platform_get_absolute_time() - start_time;
}

f64 bclock::get_elapsed() const {
    return elapsed;
}

f64 bclock::get_start_time() const {
    return start_time;
}
