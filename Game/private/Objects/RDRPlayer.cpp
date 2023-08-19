#include "../../public/Objects/RDRPlayer.h"

#include <sstream>

#include "../../public/Objects/RDRPed.h"
#include "../../public/Logger/RdrLogger.h"
#include "../../public/Pool/ObjectPool.h"
#include "../../public/Objects/RDREntity.h"

namespace game
{
    RdrEntity* RdrPlayer::get_entity_is_free_aiming_at() const
    {
        Entity target;
        BOOL result = PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(*this, &target);
        if (result != 0)
        {
            return new RdrEntity(target);
        }
        return nullptr;
    }

    // TODO: Testare questa cosa qui
    RdrEntity* RdrPlayer::get_target_entity()
    {
        Entity target;
        ObjectPool<RdrEntity>& entity_pool = ObjectPool<RdrEntity>::getInstance();
        BOOL result = PLAYER::GET_PLAYER_TARGET_ENTITY(*this, &target);
        if (result != 0)
        {
            current_target = entity_pool.acquire_entity(target);
        }
        return current_target;
    }

    Vector3 RdrPlayer::get_position() const
    {
        if (character != nullptr)
        {
            return character->get_position();
        }
        return Vector3{0, 0, 0};
    }
}
