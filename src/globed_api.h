#pragma once

#include "managers/game_server.hpp"
#include "managers/room.hpp"
#include "defs/all.hpp"

namespace globed {
    namespace api {
        static bool connectedToServer() {
            return GameServerManager::get().getActiveServer().has_value();
        }
        static bool connectedToRoom() {
            return connectedToServer() && RoomManager::get().isInRoom();
        }
    }
}
