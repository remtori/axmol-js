#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <tuple>

#include <v8.h>

namespace ax
{
/**
 * Specialized timer for js setTimeout, setInterval, ...
 *
 * Axmol / Cocos scheduler is not suitable for timer with a custom interval like js timers.
 */
class JsTimers
{
public:
    using TimerId       = uint64_t;
    using TimerCallback = std::tuple<uint32_t, TimerId, v8::Local<v8::Function>>;

    enum
    {
        kTimerTypeOnce = 0,
    };

    struct TimerKey
    {
        uint64_t deadline;
        TimerId id;
        uint64_t repeat;

        inline bool operator==(const TimerKey& other) const noexcept
        {
            return deadline == other.deadline && id == other.id && repeat == other.repeat;
        }

        inline bool operator>(const TimerKey& other) const noexcept
        {
            if (deadline != other.deadline)
                return deadline > other.deadline;
            if (id != other.id)
                return id > other.id;
            return repeat > other.repeat;
        }
    };

    using TimerData = std::tuple<uint32_t, v8::Global<v8::Function>>;

public:
    JsTimers();

    ~JsTimers();

    JsTimers(const JsTimers&) = delete;

    JsTimers& operator=(const JsTimers&) = delete;

    JsTimers(JsTimers&& other) = default;

    JsTimers& operator=(JsTimers&& other) = default;

    void clear();

    TimerId queueTimer(uint64_t timeoutMs, TimerData data)
    {
        return queueTimerInternal(false, timeoutMs, std::move(data));
    }

    TimerId queueTimerRepeat(uint64_t timeoutMs, TimerData data)
    {
        return queueTimerInternal(true, timeoutMs, std::move(data));
    }

    std::optional<TimerData> cancelTimer(TimerId id);

    std::span<TimerCallback> pollTimers(v8::Isolate* isolate);

private:
    TimerId queueTimerInternal(bool repeat, uint64_t timeoutMs, TimerData data);

    TimerId _nextId;
    std::set<TimerKey, std::greater<TimerKey>> _timers;
    std::map<TimerId, TimerData> _dataMap;

    std::vector<TimerCallback> _callbacks;
};
}  // namespace ax
