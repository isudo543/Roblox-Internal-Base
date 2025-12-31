#pragma once
#include <Windows.h>
#include <iostream>
#include "../update/update.h"


namespace Uwp {
	struct taskScheduler {
	private:
		void* scheduler;

	public:
		uintptr_t getTaskScheduler();
		std::vector<uintptr_t> getJobs();
		std::string getJobName(); // switch to instance later bro idc
		void* getAddress() const { return scheduler; }
	};
	inline std::unique_ptr<taskScheduler> g_Scheduler = std::make_unique<taskScheduler>();
}