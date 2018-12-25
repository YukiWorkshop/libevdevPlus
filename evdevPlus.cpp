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

using namespace evdevPlus;


void EventDevice::Open(const std::string &path, int open_flags) {
	int fd = open(path.c_str(), open_flags);

	if (fd < 0)
		throw std::runtime_error("failed to open device: " + std::string(strerror(errno)));

	Open(fd);
}

void EventDevice::Open(int fd) {
	if (!IsValidDevice(fd))
		throw std::runtime_error("not a valid event device");

	FD = fd;

	Init();
}

void EventDevice::Close() {
	if (FD != -1)
		close(FD);
}

bool EventDevice::IsValidDevice(int fd) {
	if (fcntl(fd, F_GETFD) == -1)
		return false;

	int _;

	return ioctl(fd, EVIOCGVERSION, &_) == 0;
}

bool EventDevice::IsValidDevice() {
	return IsValidDevice(FD);
}

void EventDevice::Init() {
	if (ioctl(FD, EVIOCGVERSION, &DriverVersion))
		throw std::runtime_error(std::string("EVIOCGVERSION") + " failed");

	if (ioctl(FD, EVIOCGID, &(DeviceID.inputId)))
		throw std::runtime_error(std::string("EVIOCGID") + " failed");

	char name[256] = "Unknown";
	ioctl(FD, EVIOCGNAME(sizeof(name)), name);
	DeviceName = name;


	long evtypes;
	if (ioctl(FD, EVIOCGBIT(0, sizeof(long)), &evtypes) == -1)
		throw std::runtime_error(std::string("EVIOCGBIT") + " failed");

	// TODO
}

void EventDevice::Grab() {
	if (ioctl(FD, EVIOCGRAB, 1))
		throw std::runtime_error(std::string("EVIOCGRAB") + "failed");
}

void EventDevice::Ungrab() {
	if (ioctl(FD, EVIOCGRAB, 0))
		throw std::runtime_error(std::string("EVIOCGRAB") + "failed");
}

InputEvent EventDevice::Read() {
	InputEvent ret;

	ssize_t rc = read(FD, &ret.event, sizeof(input_event));

	if (rc != sizeof(input_event)) {
		if (rc < 0)
			throw std::runtime_error(strerror(errno));
		else
			throw std::runtime_error("truncated read");
	}

	return ret;
}


