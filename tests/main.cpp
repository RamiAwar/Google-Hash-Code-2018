#include <ride.h>
#include <car.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#define BONUS_WEIGHT 1
#define DIST_WEIGHT 1
#define WAIT_WEIGHT 1


int distance(int a, int b, int x, int y) {
	return std::abs(a - x) + std::abs(b - y);
}

/**
 * Calculates the fitness of assigning ride R to car C, given the current time of car C
 * @param  R Ride being checked
 * @param  C Car being checked
 * @param  T Final timestamp
 * @param  B Bonus points
 * @return   Fitness as a double
 */
double fitness(Ride R, Car C, int T, int B) {
	if(C.t + distance(C.x, C.y, R.a, R.b) + R.length > R.f
			|| R.f > T) {
		return 0;
	}

	/**
	 * Checking if bonus could apply
	 * i.e. time needed to reach start point is less than start point time
	 */
	int wb = 0;
	if(C.t + distance(C.x, C.y, R.a, R.b) < R.s) {
		wb = BONUS_WEIGHT;
	}

	return DIST_WEIGHT*R.length + wb*B - WAIT_WEIGHT*wb*(R.s - distance(C.x, C.y, R.a, R.b) - C.t);
}

int main() {
	std::string filename;

	std::cout << "asdfasdf" << std::endl;
	std::cin >> filename;
	std::ifstream file(filename);
	int R, C, F, N, B, T;
	file >> R >> C >> F >> N >> B >> T;


	std::vector<Car> cars;
	std::vector<Ride> rides;
	for(int i = 0; i < F; i++) {
		Car C(0, 0, 0);
		cars.push_back(C);
	}

	for(int i = 0; i < N; i++) {
		int a, b, x, y, s, f;
		file >> a >> b >> x >> y >> s >> f;
		Ride R(a, b, x, y, s, f);
		rides.push_back(R);
	}

	std::vector<bool> available(rides.size(), 1);
	std::vector<bool> cars_done(cars.size(), 1);
	std::vector<std::vector<int>> cars2rides(cars.size(), std::vector<int>());
	int finished_cars = 0;

//TODO: Method to calculate overall fitness of assignments.

	while(finished_cars != cars.size()) {
		for(int i = 0; i < cars.size(); i++) {
			if(cars_done[i]) continue;
			int max_fitness = 0;
			int max_index = 0;

			for(int j = 0; j < rides.size(); j++) {

				if(!available[j]) continue;
				int current_fitness = fitness(rides[j], cars[i], T, B);
				if(current_fitness > max_fitness) {
					max_index = j;
					max_fitness = current_fitness;

				}
			}

			if(max_fitness == 0) {
				cars_done[i] = 1;
				finished_cars++;
				break;
			}

			available[max_index] = 0;
			cars2rides[i].push_back(max_index);

			cars[i].t = cars[i].t + distance(cars[i].x, cars[i].y, rides[max_index].a, rides[max_index].b)
				+ rides[max_index].length;
			cars[i].x = rides[max_index].x;
			cars[i].y = rides[max_index].y;
		}
	}

	std::ofstream out_file("outfile.txt");
	for(int i = 0; i < cars2rides.size(); i++) {
		out_file << cars2rides[i].size();
		for(int j = 0; j < cars2rides[i].size(); j++) {
			out_file << " " << cars2rides[i][j];
		}
		out_file << "\n";
	}
}
