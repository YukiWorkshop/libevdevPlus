/*
    This file is part of libevdevPlus.
    Copyright (C) 2018-2021 Reimu NotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#pragma once

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
	private:
		int fd_ = -1;
		std::string path_;

		int DriverVersion = -1;
		EventDeviceID DeviceID;
		std::string DeviceName;
		std::set<int> EventTypes;

		void __open(const std::string &path, int open_flags = O_RDONLY);
		void __init();
		void __close();
	public:

		EventDevice() = default;

		EventDevice(const std::string &path, int open_flags = O_RDONLY) {
			__open(path, open_flags);
			__init();
		}

		~EventDevice() {
			__close();
		}

		int driver_version() const noexcept {
			return DriverVersion;
		}

		const EventDeviceID& device_id() const noexcept {
			return DeviceID;
		}

		const std::string& device_name() const noexcept {
			return DeviceName;
		}

		void grab();
		void ungrab();

		InputEvent read();

		bool const operator== (const EventDevice &o) const {
			return (path_ == o.path_) && (fd_ == o.fd_);
		}

	};
}

