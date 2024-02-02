#if !defined( STRINGS_H )
#define STRINGS_H

#define STR_CONSOLE_LOADING               "Loading..."
#define STR_CONSOLE_HAVEFUN               "Done, have fun in there!\n"
#define STR_CONSOLE_CLEANINGUP            "Cleaning up..."
#define STR_CONSOLE_BURRITO               "Done, enjoy your burrito!\n\n"

#define STR_MAIN_LOADINGGAME              "Loading game"
#define STR_MAIN_RUNNINGGAME              "Game loaded, running"
#define STR_MAIN_GAMECLOSED               "Game closed, freeing memory"
#define STR_MAIN_MEMALLOCATED             "Total bytes allocated"
#define STR_MAIN_MEMFREED                 "Total bytes freed"
#define STR_MAIN_MEMMAX                   "Highest byte allocation"
#define STR_MAIN_SFMLOBJCREATED           "Total SFML objects created"
#define STR_MAIN_SFMLOBJDESTROYED         "Total SFML objects destroyed"
#define STR_MAIN_SFMLOBJMAX               "Highest SFML objects count"

#define STR_WINDOW_TITLE                  "CSFML Game Base"

#define STR_FRAMERATEFORMATTER            "  Frame Rate: %d"
#define STR_TOTALFRAMESFORMATTER          "Total Frames: %d"
#define STR_LAGFRAMESFORMATTER            "  Lag Frames: %d"
#define STR_ELAPSEDTIMEFORMATTER          "Elapsed Time: %s"

#define STR_ON                            "on"
#define STR_OFF                           "off"

#define STR_INDEFINITE_LOWERA             "a"
#define STR_INDEFINITE_UPPERA             "A"
#define STR_INDEFINITE_LOWERAN            "an"
#define STR_INDEFINITE_UPPERAN            "An"

#define STR_DEBUG_DIAGNOSTICSFORMATTER    "Toggled diagnostics %s"

#define STR_CHEAT_NOCLIPFORMATTER         "Toggled no-clip mode %s"
#define STR_CHEAT_NOENCOUNTERFORMATTER    "Toggled no-encounters mode %s"
#define STR_CHEAT_FIGHT                   "Forced an enemy encounter"
#define STR_CHEAT_CLEARED                 "Cleared all cheats"

#define STR_ERROR                         "ERROR"
#define STR_ERROR_MALLOC                  "Could not allocate dynamic memory"
#define STR_ERROR_OPENLOGFILE             "Could not open logfile to write message"
#define STR_ERROR_WRITELOGFILE            "Could not write message to logfile"
#define STR_ERROR_CLOSELOGFILE            "Could not close logfile"
#define STR_ERROR_INVALIDBATTLECOMMAND    "Invalid menu command passed into battle"
#define STR_ERROR_BATTLESPRITEINDEX       "Battle sprite state index is out of bounds"

#define STR_MENU_CARAT                    ">"
#define STR_MENU_QUITGAME                 "Quit Game"
#define STR_MENU_CLOSEMENU                "Close Menu"
#define STR_MENU_ATTACK                   "Attack"
#define STR_MENU_GUARD                    "Guard"
#define STR_MENU_FLEE                     "Flee"

#define STR_BATTLE_INTROFORMATTER         "You've encountered %s %s!"
#define STR_BATTLE_HITPOINTSFORMATTER     "  HP: %d"
#define STR_BATTLE_MAGPOINTSFORMATTER     "  MP: %d"
#define STR_BATTLE_SELECTACTION           "Select an action"

#endif // STRINGS_H
