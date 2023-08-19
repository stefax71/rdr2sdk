#include "../../public/Pool/ObjectPool.h"

#include <sstream>

#include "../../public/Logger/RdrLogger.h"
//
// template <typename EntityType>
// EntityType* EntityPool<EntityType>::acquire_entity(Entity entity)
// {
//     std::lock_guard<std::mutex> lock(pool_mutex_);
//     RDR2Logger* dev_log = RDR2Logger::GetLogger("developer.txt", TRIVIAL);
//
//
//     auto it = idToPedMap.find(entity);
//     if (it == idToPedMap.end())
//     {
//         it = idToPedMap.emplace(entity, std::make_shared<rdr_entity>(entity)).first;
//     }
//
//     rdr_entity* en = it->second.get();
//     stringstream str;
//     str << "Restituisco " << en << " per la entity " << entity;
//     dev_log->log_trivial(str.str().c_str());
//     return en;
// }
