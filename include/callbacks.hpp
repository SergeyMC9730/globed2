#pragma once

#include "_internal.hpp"

class PlayerObject;

namespace globed::callbacks {
    using PlayerJoinFn = std::function<void (int, PlayerObject*, PlayerObject*)>;
    using PlayerLeaveFn = std::function<void (int, PlayerObject*, PlayerObject*)>;
    using PlayerDestroyFn = std::function<void (PlayerObject*)>;

    // Sets a callback that will be called when another player joins the current level.
    // Callback is removed when the user leaves the level.
    Result<void> onPlayerJoin(PlayerJoinFn func);

    // Sets a callback that will be called when another player leaves the current level.
    // Callback is removed when the user leaves the level.
    Result<void> onPlayerLeave(PlayerLeaveFn func);

    // Sets a callback that will be called when another player dies on the current level.
    // Callback is removed when the user leaves the level.
    Result<void> onPlayerDestroy(PlayerDestroyFn func);
} // namespace globed::callbacks

// Implementation

namespace globed::callbacks {
    inline Result<void> onPlayerJoin(PlayerJoinFn func) {
        return _internal::request<void>(_internal::Type::CbPlayerJoin, func);
    }

    inline Result<void> onPlayerLeave(PlayerLeaveFn func) {
        return _internal::request<void>(_internal::Type::CbPlayerLeave, func);
    }

    inline Result<void> onPlayerDestroy(PlayerDestroyFn func) {
        return _internal::request<void>(_internal::Type::CbPlayerDestroy, func);
    }
} // namespace globed::callbacks
