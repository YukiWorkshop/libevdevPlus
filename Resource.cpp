/*
    This file is part of libevdevPlus.
    Copyright (C) 2018 YukiWorkshop

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "evdevPlus.hpp"

const std::unordered_map<std::string, int> evdevPlus::KeyStringTable = {
	{"ALT", KEY_LEFTALT}, {"ALT_L", KEY_LEFTALT}, {"ALT_R", KEY_RIGHTALT},
	{"SHIFT", KEY_LEFTSHIFT}, {"SHIFT_L", KEY_LEFTSHIFT}, {"SHIFT_R", KEY_RIGHTSHIFT},
	{"CTRL", KEY_LEFTCTRL}, {"CTRL_L", KEY_LEFTCTRL}, {"CTRL_R", KEY_RIGHTCTRL},
	{"META", KEY_LEFTMETA}, {"META_L", KEY_LEFTMETA}, {"META_R", KEY_RIGHTMETA},
	{"TAB", KEY_TAB}, {"CAPSLOCK", KEY_CAPSLOCK}, {"NUMLOCK", KEY_NUMLOCK}, {"SCROLLLOCK", KEY_SCROLLLOCK}, {"ESC", KEY_ESC}, {"ENTER", KEY_ENTER}, {"BACKSPACE", KEY_BACKSPACE}, {"DELETE", KEY_DELETE},
	{"INSERT", KEY_INSERT}, {"HOME", KEY_HOME}, {"END", KEY_END}, {"PAGEUP", KEY_PAGEUP}, {"PAGEDOWN", KEY_PAGEDOWN}, {"SYSRQ", KEY_SYSRQ}, {"PAUSE", KEY_PAUSE},
	{"F1", KEY_F1}, {"F2", KEY_F2}, {"F3", KEY_F3}, {"F4", KEY_F4}, {"F5", KEY_F5}, {"F6", KEY_F6}, {"F7", KEY_F7}, {"F8", KEY_F8}, {"F9", KEY_F9}, {"F10", KEY_F10}, {"F11", KEY_F11}, {"F12", KEY_F12}
};