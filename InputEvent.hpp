/*
    This file is part of libevdevPlus.
    Copyright (C) 2018 YukiWorkshop

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef LIBEVDEVPLUS_INPUTEVENT_HPP
#define LIBEVDEVPLUS_INPUTEVENT_HPP

#include "CommonIncludes.hpp"

namespace evdevPlus {
	class InputEvent {
	public:
		input_event event{};

		timeval &Time = event.time;
		uint16_t &Type = event.type;
		uint16_t &Code = event.code;
		int32_t &Value = event.value;

		InputEvent() = default;

		InputEvent(input_event *__event) {
			memcpy(&event, __event, sizeof(input_event));
		}

		InputEvent(uint16_t type, uint16_t code, uint16_t value, timeval *time = NULL) {
			Type = type;
			Code = code;
			Value = value;

			if (time)
				memcpy(&event.time, time, sizeof(timeval));
		}

		friend void swap(InputEvent &first, InputEvent &second) {
			using std::swap;

			swap(first.event, second.event);
		}

		InputEvent(InputEvent &&other) noexcept : InputEvent() {
			swap(*this, other);
		}

		InputEvent& operator= (InputEvent other) {
			swap(*this, other);
			return *this;
		}

		InputEvent(const InputEvent &other) {
			memcpy(&event, &(other.event), sizeof(input_event));
		}

	};

}
#endif //LIBEVDEVPLUS_INPUTEVENT_HPP
