#include "../../public/World/Gang.h"

namespace gang
{
    std::vector<Hash> Gang::gangs = {ODRISCOLL, DEL_LOBO, LEMOYNE_RIDER, MURFREE_BROOD};

    std::unordered_map<Hash, std::vector<std::string>> Gang::models = {
        {Gang::ODRISCOLL, {"G_M_M_UniDuster_01", "G_M_M_UniDuster_02", "G_M_M_UniDuster_03", "G_M_M_UniDuster_04", "G_M_M_UniDuster_05"}},
        {Gang::DEL_LOBO, {"g_m_m_unibanditos_01"},},
        {Gang::LEMOYNE_RIDER, {"g_m_o_uniexconfeds_01", "g_m_y_uniexconfeds_01", "g_m_y_uniexconfeds_02"}},
        {Gang::MURFREE_BROOD, {"g_m_m_uniinbred_01"}},
        {Gang::SKINNER_BROTHERS, {"G_M_M_UniMountainMen_01"}}
    };

    std::string Gang::get_gang_name(Hash hash)
    {
        switch (hash)
        {
        case ODRISCOLL:
            return "O'Driscoll";
        case DEL_LOBO:
            return "Del Lobo";
        case LEMOYNE_RIDER:
            return "Lemoyne Raiders";
        case MURFREE_BROOD:
            return "Murfree Brood";
        case SKINNER_BROTHERS:
            return "Skinner Brothers";
        default:
            return "Unknown";
        }
    }

    std::string Gang::get_model_for_gang(Hash hash)
    {
        if (models.find(hash) != models.end() && !models[hash].empty())
        {
            int modelIndex = random_number_in_range(0, models[hash].size() - 1);
            return models[hash][modelIndex];
        }
        // Handle the case when the hash is not found or the vector is empty
        return "G_M_M_UniDuster_03";
    }
    
}
