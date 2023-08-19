#include "../../public/Objects/RDRPed.h"

namespace game
{

    void RdrPed::request_model(Hash model)
    {
        if (STREAMING::IS_MODEL_IN_CDIMAGE(model))
        {
            STREAMING::REQUEST_MODEL(model, false);
            while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
        }
    }

    void RdrPed::release_model(Hash model)
    {
        if (STREAMING::IS_MODEL_IN_CDIMAGE(model))
        {
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
        }
    }
    
    // Thanks @CruelMasterMC
    RdrPed* RdrPed::create_ped_new(const char* model, Vector3 position, float heading, Hash group_hash,
                                int combat_ability, ECombatMovement combat_movement, BOOL keep_doing_task,
                                BOOL block_temporary_events, const char* weapon_name, bool drop_weapon_on_death)
    {
        Hash model_hash = MISC::GET_HASH_KEY(model);
        request_model(model_hash);

        Ped ped = PED::CREATE_PED(model_hash, position.x, position.y, position.z, heading, 0, 0, 0, 0);
        ENTITY::SET_ENTITY_VISIBLE(ped, 1);
        PED::_SET_RANDOM_OUTFIT_VARIATION(ped, 1);
        ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, 1, 1);
        if (group_hash > 0)
        {
            PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, group_hash);    
        }
        
        Blip blip = MAP::BLIP_ADD_FOR_ENTITY(MISC::GET_HASH_KEY("BLIP_STYLE_ENEMY"), ped);//BLIP_STYLE_ENEMY
        PED::SET_PED_COMBAT_ABILITY(ped, combat_ability);
        PED::SET_PED_COMBAT_MOVEMENT(ped, combat_movement);
        PED::SET_PED_KEEP_TASK(ped, keep_doing_task);
        PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, block_temporary_events);
        if (weapon_name != nullptr)
        {
            Hash weapon_hash = MISC::GET_HASH_KEY(weapon_name);
            WEAPON::GIVE_WEAPON_TO_PED(ped, weapon_hash, 10000, false, true, 2, false, 0.5f, 1.0f, 0x4A6726C9, true, 1.0f, 1);    
        }
        
        WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(ped, drop_weapon_on_death);
        // GroupsVector.push_back(ped);
        if (group_hash > 0)
        {
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(6, group_hash, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID()));
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(6, PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID()), group_hash);
        }

        release_model(model_hash);
        return new RdrPed(ped);
    }
    
    RdrPed* RdrPed::create_ped(const char* modelName, Vector3 pos, float heading, bool visible, EBlipStyles blip)
    {
        // RdrLogger* logger = RdrLogger::get_logger("GangRescue.log", LogLevel::INFO);
        const Hash model = MISC::GET_HASH_KEY(modelName);
        STREAMING::REQUEST_MODEL(model, false);
        while (!STREAMING::HAS_MODEL_LOADED(model))
        {
            WAIT(0);
        }
        // logger->info("Model ready");

        const Ped ped = PED::CREATE_PED(model, pos.x, pos.y, pos.z, heading, false, false, false, false);
        PED::_SET_RANDOM_OUTFIT_VARIATION(ped, true);

        if (visible)
        {
            ENTITY::SET_ENTITY_VISIBLE(ped, visible);
        }

        if (blip != BLIP_STYLE_NONE)
        {
            const auto blip_as_unsigned_int = static_cast<unsigned int>(blip);
            MAP::BLIP_ADD_FOR_ENTITY(blip_as_unsigned_int, ped);
        }
        ENTITY::PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true);
        return new RdrPed(ped);
    }

  

    bool RdrPed::is_carrying_something() const
    {
        const BOOL result = PED::IS_PED_CARRYING_SOMETHING(*this);
        return result > 0;
    }

    Hash RdrPed::get_ped_outlaws_gang() const
    {
        const Hash current_relationship = get_relationship();
        if (gang::Gang::is_gang(current_relationship))
        {
            return current_relationship;
        }
        return -1;
    }

    MapArea* RdrPed::get_area_from_position() const
    {
        Hash hash = MapAreasManager::get_map_zone_at_pos(get_position());
        if (hash > 0)
        {
            auto map_areas_manager = &MapAreasManager::get_instance();
            const auto town_name = static_cast<ETownName>(hash);
            MapArea* map_area = map_areas_manager->get_map_area(town_name);
            return map_area;
        }
        return nullptr;
    }

    std::shared_ptr<RdrEntity> RdrPed::get_carried_entity() const
    {
        Entity entity = PED::_GET_FIRST_ENTITY_PED_IS_CARRYING(*this);
        return std::make_shared<game::RdrEntity>(entity);
    }

    void RdrPed::task_go_to_entity(RdrEntity* target, float distance, int duration, float speed) const
    {
        if (mount_ != nullptr)
        {
            TASK::TASK_GO_TO_ENTITY(*mount_, *target, duration, distance, speed, 0, 0);
        }
        else
        {
            TASK::TASK_GO_TO_ENTITY(*this, *target, duration, distance, speed, 0, 0);
        }
    }

    void RdrPed::safely_delete_ped()
    {
        if (mount_ != nullptr)
        {
            Ped horse_handle = mount_->get_original_handle();
            ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&horse_handle);
            delete mount_;
        }
        ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&this->handle_);
    }

    void RdrPed::task_combat_ped(RdrPed* target) const
    {
        PED::SET_PED_COMBAT_RANGE(*this, 14);
        PED::SET_PED_COMBAT_MOVEMENT(*this, 2);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 28, true);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 50, true);
        WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(*this, true);
        PED::SET_PED_FLEE_ATTRIBUTES(*this, 32768, false);
        PED::SET_PED_FLEE_ATTRIBUTES(*this, 16384, true);
        PED::SET_PED_FLEE_ATTRIBUTES(*this, 512, true);
        PED::SET_PED_FLEE_ATTRIBUTES(*this, 1024, true);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 5, true);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 14, false);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 17, false);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 58, true);
        PED::SET_PED_COMBAT_ATTRIBUTES(*this, 46, true);
        PED::SET_PED_CONFIG_FLAG(*this, 225, false);
        TASK::TASK_COMBAT_PED(*this, *target, 0, 0);
        PED::SET_PED_KEEP_TASK(*this, 1);
    }
    
    void RdrPed::set_relationship(const char* gang) const
    {
        const Hash gang_hash = MISC::GET_HASH_KEY(gang);
        PED::SET_PED_RELATIONSHIP_GROUP_HASH(*this, gang_hash);
    }
    
    void RdrPed::set_ped_on_mount(const Ped mount, int seat_index)
    {
        this->mount_ = new RdrPed(mount);
        PED::SET_PED_ONTO_MOUNT(*this, mount, seat_index, true);
    }

    RdrPed* RdrPed::get_current_mount()
    {
        int current_registered_mount = 0;
        const Ped mount_in_game = PED::GET_MOUNT(handle_);
        
        if (mount_ != nullptr)
        {
            current_registered_mount = *mount_;
            if (mount_in_game != current_registered_mount )
            {
                delete mount_;
                mount_ = new RdrPed(mount_in_game);
            }
        } else
        {
            mount_ = new RdrPed(mount_in_game);
        }
        return mount_;
    }

    // TODO: Right now, just tries to remove the blip
    void RdrPed::set_blip_for_ped(EBlipStyles blip)
    {
        if (BLIP_STYLE_NONE == blip)
        {
            MAP::REMOVE_BLIP(&this->blip_);
        }
    }

    void RdrPed::flee_from_location(const Vector3& vector3, float distance)
    {
        this->is_fleeing = true;
        TASK::TASK_SMART_FLEE_COORD(*this, vector3.x, vector3.y, vector3.z, distance, -1, true, true);
    }

    void RdrPed::flee_from_ped(RdrPed* ped_to_flee_from, EFleeStyle flee_style) const
    {
        TASK::TASK_FLEE_PED(handle_, *ped_to_flee_from, static_cast<int>(flee_style), 0, -1.0f, -1, 0);
    }
}
