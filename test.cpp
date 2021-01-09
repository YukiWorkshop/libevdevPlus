/*
    This file is part of libevdevPlus.
    Copyright (C) 2018-2021 Reimu NotMoe <reimu@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <evdevPlus.hpp>

using namespace evdevPlus;

int main(int argc, char **argv) {
	if (!argv[1]) {
		fprintf(stderr, "Usage: %s <event device>\n", argv[0]);
		exit(1);
	}

	EventDevice ev(argv[1]);

	std::cout << "Device name: " << ev.device_name() << "\n";
	std::cout << "Bus type: " << ev.device_id().BusType << "\n";
	std::cout << "VID: " << ev.device_id().Vendor << "\n";
	std::cout << "PID: " << ev.device_id().Product << "\n";
	std::cout << "Version: " << ev.device_id().Version << "\n";
	std::cout << "Driver version: " << ev.driver_version() << "\n";

	ev.grab();

	while (true) {
		auto ie = ev.read();

		std::cout << "Event type: " << ie.Type << "\n";
		std::cout << "Event code: " << ie.Code << "\n";
		std::cout << "Event value: " << ie.Value << "\n";

	}
}