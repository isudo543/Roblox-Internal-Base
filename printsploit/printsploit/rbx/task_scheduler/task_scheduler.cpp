#pragma once
#include "task_scheduler.h"

#define mHandle (reinterpret_cast<uintptr_t>(GetModuleHandleA("RobloxPlayerBeta.exe")))

std::string readstring(uintptr_t address) {
	int length = *reinterpret_cast<int*>(address + 0x18);
	uintptr_t strAddress = (length >= 16)
		? *reinterpret_cast<uintptr_t*>(address)
		: address;

	char buffer[201]{};
	for (int i = 0; i < sizeof(buffer) - 1; ++i) {
		buffer[i] = *reinterpret_cast<char*>(strAddress + i);
		if (buffer[i] == '\0') break;
	}

	return std::string(buffer);
}

uintptr_t Uwp::taskScheduler::getTaskScheduler() {
	auto ptr = mHandle + offsets::TaskSchedulerPointer;
	uintptr_t tasksched = *reinterpret_cast<uintptr_t*>(ptr);
	return tasksched;
}

std::vector<uintptr_t> Uwp::taskScheduler::getJobs() {
	std::vector<uintptr_t> jobs;

	auto tasksched = g_Scheduler->getTaskScheduler();
	if (!tasksched) return;

	uintptr_t jobstart_ptr = tasksched + offsets::JobStart;
	uintptr_t jobend_ptr = tasksched + offsets::JobEnd;

	uintptr_t jobstart = *reinterpret_cast<uintptr_t*>(jobstart_ptr);
	uintptr_t jobend = *reinterpret_cast<uintptr_t*>(jobend_ptr);

	if (!jobstart || !jobend || jobstart >= jobend) return;

	for (uintptr_t job = jobstart; job < jobend; job += 0x10) {
		uintptr_t jobptr = job;
		if (!jobptr) continue;

		uintptr_t jobaddr = *reinterpret_cast<uintptr_t*>(jobptr);
		if (!jobaddr) continue;

		jobs.emplace_back(uintptr_t(reinterpret_cast<void*>(jobaddr)));
	}

	return jobs;
}

std::string Uwp::taskScheduler::getJobName() {
	Uwp::taskScheduler Scheduler;
	uintptr_t jobname_ptr =  reinterpret_cast<uintptr_t>(Scheduler.getAddress()) + offsets::Job_Name;
	return readstring(jobname_ptr);
}