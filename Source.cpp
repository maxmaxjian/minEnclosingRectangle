#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class solution {
public:
	void minEnclosingRectangle(const vector<string> & grid, size_t x, size_t y) {
		size_t xmin = 0, xmax = grid.size()-1, ymin = 0, ymax = grid[0].size()-1;
		
		auto allzerosRow = [](const vector<string> & grid, size_t row) {
			for (size_t j = 0; j < grid[row].size(); j++)
				if (grid[row][j] != '0')
					return false;
			return true;
		};
		
		auto allzerosCol = [](const vector<string> & grid, size_t col) {
			for (size_t i = 0; i < grid.size(); i++)
				if (grid[i][col] != '0')
					return false;
			return true;
		};
		
		size_t minx = binsearch(grid, xmin, x, allzerosRow, ascending<true>());
		size_t maxx = binsearch(grid, x, xmax, allzerosRow, ascending<false>());
		size_t miny = binsearch(grid, ymin, y, allzerosCol, ascending<true>());
		size_t maxy = binsearch(grid, y, ymax, allzerosCol, ascending<false>());
		
		std::cout << "minx = " << minx << ", maxx = " << maxx << std::endl;
		std::cout << "miny = " << miny << ", maxy = " << maxy << std::endl;
		
		std::cout << "Minimum area of the enclosing rectangle is:" << std::endl;
		std::cout << (maxx-minx+1)*(maxy-miny+1) << std::endl;
	}
	
private:
	template<bool>
	class ascending{
	};

	template<typename Functor, typename TrueType>
	size_t binsearch(const vector<string> & grid, size_t min, size_t max, Functor f, TrueType);

	template<typename Functor>
	size_t binsearch(const vector<string> & grid, size_t min, size_t max, Functor f, ascending<true>) {
		if (min == max)
			return min;
		else {
			size_t mid;
			while (max - min > 1) {
				mid = (max+min)/2;
				auto fmin = f(grid, min), fmax = f(grid, max), fmid = f(grid, mid);
				if (fmin == fmid)
					min = mid;
				else if (fmax == fmid)
					max = mid;
				std::cout << "acending: min(" << min << "), max(" << max << ")" << std::endl; 
			}

			if (!f(grid, min))
				return min;
			return max;
		}
	}

	template<typename Functor>
	size_t binsearch(const vector<string> & grid, size_t min, size_t max, Functor f, ascending<false>) {
		if (min == max)
			return min;
		else {
			size_t mid;
			while (max - min > 1) {
				mid = (max+min)/2;
				auto fmin = f(grid, min), fmax = f(grid, max), fmid = f(grid, mid);
				if (fmin == fmid)
					min = mid;
				else if (fmax == fmid)
					max = mid;
				std::cout << "descending: min(" << min << "), max(" << max << ")" << std::endl; 
			}

			if (!f(grid, max))
				return max;
			return min;
		}
	}
};

int main() {
	vector<string> grid {
		"0010",
		"0110",
		"0100"
	};
	
	size_t x = 0, y = 2;
	
	solution soln;
	soln.minEnclosingRectangle(grid, x, y);
	
	return 0;
}
