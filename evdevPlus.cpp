/*
    This file is part of libevdevPlus.
    Copyright (C) 2018-2021 Reimu NotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "evdevPlus.hpp"

using namespace evdevPlus;


void EventDevice::__open(const std::string &path, int open_flags) {
	int fd = open(path.c_str(), open_flags);

	if (fd < 0)
		throw std::system_error(errno, std::system_category(), "failed to open device");

	path_ = path;
  fd_ = fd;
}

void EventDevice::__close() {
	if (fd_ != -1)
		close(fd_);
}


void EventDevice::__init() {
	if (ioctl(fd_, EVIOCGVERSION, &DriverVersion))
		throw std::system_error(errno, std::system_category(), "EVIOCGVERSION");

	if (ioctl(fd_, EVIOCGID, &(DeviceID.inputId)))
		throw std::system_error(errno, std::system_category(), "EVIOCGID");

	char name[256] = "Unknown";
	ioctl(fd_, EVIOCGNAME(sizeof(name)), name);
	DeviceName = name;


	long evtypes;
	if (ioctl(fd_, EVIOCGBIT(0, sizeof(long)), &evtypes) == -1)
		throw std::system_error(errno, std::system_category(), "EVIOCGBIT");

	// TODO
}

void EventDevice::grab() {
	if (ioctl(fd_, EVIOCGRAB, 1))
		throw std::system_error(errno, std::system_category(), "EVIOCGRAB");
}

void EventDevice::ungrab() {
	if (ioctl(fd_, EVIOCGRAB, 0))
		throw std::system_error(errno, std::system_category(), "EVIOCGRAB");
}

InputEvent EventDevice::read() {
	InputEvent ret;

	ssize_t rc = ::read(fd_, &ret.event, sizeof(input_event));

	if (rc != sizeof(input_event)) {
		if (rc < 0)
			throw std::system_error(errno, std::system_category(), "read");
		else
			throw std::system_error(errno, std::system_category(), "truncated read");
	}

	return ret;
}


