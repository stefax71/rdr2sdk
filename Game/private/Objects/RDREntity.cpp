#include "../../public/Objects/RDREntity.h"

namespace game
{
    Vector3 RdrEntity::get_position() const
    {
        return ENTITY::GET_ENTITY_COORDS(handle_, true, false);
    }

    // TODO: not working really well as it returns a vector to the right of the entity
    Vector3 RdrEntity::get_position_in_front_of_entity(float distance)
    {
        Vector3 position = get_position();
        Vector3 forward_vector = ENTITY::_GET_ENTITY_FORWARD_VECTOR_YX(handle_);
        auto var = multiply(&forward_vector, distance);
        auto vector3 = add(&position, &var);
        Vector3 target = vector3;
        return target;
    }

    RdrEntity* RdrEntity::create_entity_from_handle(Entity entity_handle)
    {
        return new RdrEntity(entity_handle);
    }
}
