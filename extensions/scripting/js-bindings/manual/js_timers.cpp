#include "js-bindings/manual/js_timers.h"

#include "axmol/base/Utils.h"
#include "js_timers.h"

namespace ax
{
static inline uint64_t nowMs()
{
    return ax::utils::getTimeInMilliseconds();
}

JsTimers::JsTimers() : _nextId(0), _timers(), _dataMap() {}

JsTimers::~JsTimers()
{
    clear();
}

void JsTimers::clear()
{
    _timers.clear();
    _dataMap.clear();
    _callbacks.clear();
}

JsTimers::TimerId JsTimers::queueTimerInternal(bool repeat, uint64_t timeoutMs, TimerData data)
{
    TimerId id        = _nextId++;
    uint64_t deadline = nowMs() + timeoutMs;

    uint64_t timerType = kTimerTypeOnce;
    if (repeat)
    {
        timerType = std::max(uint64_t(1), timeoutMs);
    }

    _timers.insert({deadline, id, timerType});
    _dataMap.emplace(id, std::move(data));

    return id;
}

std::optional<JsTimers::TimerData> JsTimers::cancelTimer(TimerId id)
{
    auto it = _dataMap.find(id);
    if (it == _dataMap.end())
    {
        return std::nullopt;
    }

    TimerData data = std::move(it->second);
    _dataMap.erase(it);

    if (_dataMap.empty())
    {
        _timers.clear();
    }

    return data;
}

std::span<JsTimers::TimerCallback> JsTimers::pollTimers(v8::Isolate* isolate)
{
    uint64_t now = nowMs();
    _callbacks.clear();

    TimerKey splitOff = {now, 0, kTimerTypeOnce};
    auto splitOffIt   = _timers.lower_bound(splitOff);
    if (splitOffIt == _timers.end())
    {
        return _callbacks;
    }

    // Extract expired timers (those with deadline <= now)
    std::vector<TimerKey> expiredTimers;
    expiredTimers.reserve(std::distance(splitOffIt, _timers.end()));
    for (auto it = splitOffIt; it != _timers.end(); ++it)
    {
        expiredTimers.push_back(*it);
    }

    // Remove expired timers from the main set
    _timers.erase(_timers.begin(), splitOffIt);

    // Process expired timers
    for (const auto& timerKey : expiredTimers)
    {
        auto dataIt = _dataMap.find(timerKey.id);
        if (dataIt != _dataMap.end())
        {
            // Timer data still exists, so execute it
            uint32_t depth    = std::get<0>(dataIt->second);
            auto jsCallback   = std::get<1>(dataIt->second).Get(isolate);
            auto callbackData = std::make_tuple(depth, timerKey.id, jsCallback);
            _callbacks.emplace_back(std::move(callbackData));

            if (timerKey.repeat != kTimerTypeOnce)
            {
                // Repeat timer - reschedule it
                uint64_t nextDeadline = now + timerKey.repeat;
                TimerKey newKey       = {nextDeadline, timerKey.id, timerKey.repeat};
                _timers.insert(newKey);
            }
            else
            {
                // One-time timer - execute and remove
                _dataMap.erase(dataIt);
            }
        }
    }

    // Clean up timers if data map is empty
    if (_dataMap.empty())
    {
        _timers.clear();
        return _callbacks;
    }

    // Run front-compaction: remove timer keys that no longer have corresponding data
    while (!_timers.empty())
    {
        auto firstTimer = _timers.begin();
        if (_dataMap.find(firstTimer->id) != _dataMap.end())
        {
            // Found valid timer, stop compaction
            break;
        }
        else
        {
            // Remove orphaned timer key
            _timers.erase(firstTimer);
        }
    }

    // Run full compaction if there are too many orphaned timer keys
    const size_t COMPACTION_MINIMUM = 100;  // Threshold for full compaction
    size_t tombstoneCount           = _timers.size() > _dataMap.size() ? _timers.size() - _dataMap.size() : 0;

    if (tombstoneCount > COMPACTION_MINIMUM)
    {
        // Remove all timer keys that don't have corresponding data
        auto it = _timers.begin();
        while (it != _timers.end())
        {
            if (_dataMap.find(it->id) == _dataMap.end())
            {
                it = _timers.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    return _callbacks;
}

}  // namespace ax
