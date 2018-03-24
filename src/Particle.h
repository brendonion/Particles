#pragma once

namespace window {
	// structs are same as classes but member variables are public by default instead of private
	struct Particle {
		double m_x;
		double m_y;
		
		private:
			double m_speed;
			double m_direction;
			
		private:
			void init();
		
		public:
			Particle();
			virtual ~Particle();
			void update(int interval);		
	};
	
}
