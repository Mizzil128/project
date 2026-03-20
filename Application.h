#pragma once

namespace CRUD {
	class Application {
		public:
			Application() = default;          //here =default means compiler generates constructor automatically 
			~Application() = default;
			void run();
			void displayMenu();
	};
}