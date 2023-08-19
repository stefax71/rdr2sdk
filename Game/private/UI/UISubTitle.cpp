#include "../../public/UI/UISubTitle.h"



void ui::HudDisplay::show_subtitle(const char* text_to_show)
{
    UILOG::_UILOG_SET_CACHED_OBJECTIVE(MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text_to_show)); 
    UILOG::_UILOG_PRINT_CACHED_OBJECTIVE(); 
    UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();         
}

void ui::HudDisplay::show_subtitle(std::string& text_to_show)
{
    show_subtitle(text_to_show.c_str());
}


// void ui::ShowHelp(const std::string& text_to_show, int duration)
// {
//     UIHelpTextParam1 p1;
//     
//     p1.duration = duration * 1000;
//     p1.unknown1 = 0;
//     p1.unknown2 = 0;
//     p1.unknown3 = 0;
//
//     UIHelpTextParam2 p2;
//     p2.unknown1 = 0;
//     p2.help_text = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text_to_show);
//
//     UIFEED::_UI_FEED_POST_HELP_TEXT((Any*)&p1, (Any*)&p2, 1);
// }

void ui::display_help_text(const char* text, int duration)
{
    FeedData data{};
    FeedInfo info{};
    info.title = MISC::VAR_STRING(10, "LITERAL_STRING", text);
    data.duration = duration;
    UIFEED::_UI_FEED_POST_HELP_TEXT((Any*)&data, (Any*)&info, true);
}


