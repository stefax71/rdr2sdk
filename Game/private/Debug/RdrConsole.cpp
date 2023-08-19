#include "../../public/Debug/RdrConsole.h"

#include <sstream>

#include "../../public/Logger/RdrLogger.h"
#include "../../public/native/natives.h"

void RdrConsole::write_to_console(std::string text)
{
    if (!console_lines_.empty())
    {
        std::string last_line = console_lines_.back();
        if (text == last_line)
        {
            return;
        }
        if (console_lines_.size() >= 15)
        {
            console_lines_.pop_front();
        }
    }

    this->console_lines_.push_back(text);

    update();
}

void RdrConsole::write_static_line(std::string static_line)
{
    static_text_creation_ts_ = std::chrono::steady_clock::now();
    static_line_ = static_line;
}

void RdrConsole::update()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - static_text_creation_ts_).count();

    if (elapsed >= 2)
    {
        static_line_ = std::string("");
    }

    if (!this->console_lines_.empty())
    {
        float text_position = 0.01f;

        stringstream current_console_content_as_stream;
        for (std::string current_line : this->console_lines_)
        {
            current_console_content_as_stream << current_line << endl;
        }
        UIDEBUG::_BG_SET_TEXT_SCALE(0.25f, 0.25f);
        UIDEBUG::_BG_SET_TEXT_COLOR(255, 255, 255, 255);            
        UIDEBUG::_BG_DISPLAY_TEXT((char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", current_console_content_as_stream.str().c_str()), 0.01,
                                  text_position);
        
    }

    if (static_line_ != "")
    {
        UIDEBUG::_BG_SET_TEXT_SCALE(0.25f, 0.25f);
        UIDEBUG::_BG_SET_TEXT_COLOR(255, 234, 0, 255);
        UIDEBUG::_BG_DISPLAY_TEXT((char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", static_line_.c_str()), 0.01,
                                  0.31);
    }
}
