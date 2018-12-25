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

int main(int argc, char **argv) {
	if (!argv[1]) {
		fprintf(stderr, "Usage: %s <event device>\n", argv[0]);
		exit(1);
	}

	EventDevice ev(argv[1]);

	std::cout << "Device name: " << ev.DeviceName << "\n";
	std::cout << "Bus type: " << ev.DeviceID.BusType << "\n";
	std::cout << "VID: " << ev.DeviceID.Vendor << "\n";
	std::cout << "PID: " << ev.DeviceID.Product << "\n";
	std::cout << "Version: " << ev.DeviceID.Version << "\n";
	std::cout << "Driver version: " << ev.DriverVersion << "\n";

	ev.Grab();

	while (true) {
		auto ie = ev.Read();

		std::cout << "Event type: " << ie.Type << "\n";
		std::cout << "Event code: " << ie.Code << "\n";
		std::cout << "Event value: " << ie.Value << "\n";

	}
}