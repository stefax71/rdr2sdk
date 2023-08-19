#include "../../public/Utility/Utils.h"
#include "../../public/native/types.h"
#include "../../public/native/natives.h"
#include "../../public/Logger/RdrLogger.h"

#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace std
{
    class mutex;
}

void export_hashes_to_file(const char* file_name, const char* enum_name, std::mutex& mut, std::vector<std::string> input)
{
    {
        std::lock_guard<std::mutex> lock(mut);
        RdrLogger* hash_output = RdrLogger::get_logger(file_name, LogLevel::INFO);
        std::stringstream hash_output_str;
        hash_output_str << "enum class " << enum_name << endl;
        hash_output_str << "{" <<  endl;
        for (std::string single_element: input)
        {
            const Hash single_element_hash = MISC::GET_HASH_KEY(single_element.c_str());
            if (single_element_hash > 0)
            {
                hash_output_str << "\t" << single_element << " = " << single_element_hash << "," << endl;
            }
        }

        hash_output_str << "};" << endl;
        hash_output->raw_write_to_log(hash_output_str.str().c_str());
    }
}

void raw_write_to_file(const char* file_name, const char* msg)
{
    std::ofstream file;
    file.open(file_name, std::ios_base::app);
    if (file.is_open())
    {
        file << msg;
        file.close();
    }
}