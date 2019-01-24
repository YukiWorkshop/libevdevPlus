/*
    This file is part of libevdevPlus.
    Copyright (C) 2018 YukiWorkshop

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef LIBEVDEVPLUS_HPP
#define LIBEVDEVPLUS_HPP

#include "CommonIncludes.hpp"
#include "InputEvent.hpp"

namespace evdevPlus {

	extern const std::unordered_map<std::string, int> Table_FunctionKeys;
	extern const std::unordered_map<std::string, int> Table_ModifierKeys;
	extern const std::unordered_map<char, int> Table_LowerKeys;
	extern const std::unordered_map<char, int> Table_UpperKeys;
	extern const std::unordered_map<std::string, int> Table_KeyCodes;


	class EventDeviceID {
	public:
		input_id inputId{};

		uint16_t &BusType = inputId.bustype;
		uint16_t &Vendor = inputId.vendor;
		uint16_t &Product = inputId.product;
		uint16_t &Version = inputId.version;

		EventDeviceID() = default;
		EventDeviceID(uint16_t bus_type, uint16_t vid, uint16_t pid, uint16_t version) {
			BusType = bus_type;
			Vendor = vid;
			Product = pid;
			Version = version;
		}

		friend void swap(EventDeviceID &first, EventDeviceID &second) {
			using std::swap;

			swap(first.inputId, second.inputId);
		}

		EventDeviceID(EventDeviceID &&other) noexcept : EventDeviceID() {
			swap(*this, other);
		}

		EventDeviceID& operator= (EventDeviceID other) {
			swap(*this, other);
			return *this;
		}

		EventDeviceID(const EventDeviceID &other) {
			memcpy(&inputId, &(other.inputId), sizeof(uinput_setup));
		}

	};


	class EventDevice {
	public:
		int FD = -1;
		std::string Path;

		int DriverVersion = -1;
		EventDeviceID DeviceID;
		std::string DeviceName;
		std::set<int> EventTypes;

		EventDevice() = default;
		EventDevice(const std::string &path, int open_flags = O_RDONLY) {
			Open(path, open_flags);
		}
		EventDevice(int fd) {
			Open(fd);
		}
		~EventDevice() {
			Close();
		}

		void Open(const std::string &path, int open_flags = O_RDONLY);
		void Open(int fd);
		void Close();

		void Init();

		void Grab();
		void Ungrab();

		InputEvent Read();

		static bool IsValidDevice(int fd);
		bool IsValidDevice();


		bool const operator== (const EventDevice &o) const {
			return (Path == o.Path) && (FD == o.FD);
		}

	};
}


#endif //LIBEVDEVPLUS_HPP


