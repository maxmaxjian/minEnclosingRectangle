#include <iostream>
#include <vector>
#include <string>

class solution {
  public:
    int minArea(const std::vector<std::string> & image, int x, int y) {
        int minrow = 0, maxrow = image.size()-1, mincol = 0, maxcol = image[0].length()-1;

        auto allzerosRow = [](const std::vector<std::string> & image, int row) {
            for (int j = 0; j < image[row].length(); j++)
                if (image[row][j] != '0')
                    return false;
            return true;
        };

        auto allzerosCol = [](const std::vector<std::string> & image, int col) {
                for (int i = 0; i < image.size(); i++)
                    if (image[i][col] != '0')
                        return false;
                return true;
            };
        
        int minx = binsearch_increasing(image, minrow, x, allzerosRow);
        int maxx = binsearch_decreasing(image, x, maxrow, allzerosRow);
        int miny = binsearch_increasing(image, mincol, y, allzerosCol);
        int maxy = binsearch_decreasing(image, y, maxcol, allzerosCol);

            std::cout << "minx = " << minx << ", maxx = " << maxx << std::endl;
            std::cout << "miny = " << miny << ", maxy = " << maxy << std::endl;

        return (maxx-minx+1)*(maxy-miny+1);
    }

  private:
    template<typename Functor>
    int binsearch_increasing(const std::vector<std::string> & image, int min, int max, Functor f) {
            if (!f(image, min))
                return min;
                
        if (min == max)
            return min;
        else {
            int result;
            while (max-min > 1) {
                result = (min+max)/2;
                auto fmin = f(image, min);
                auto fmax = f(image, max);
                auto fmid = f(image, result);
                if (fmin == fmid)
                    min = result;
                else if (fmax == fmid)
                    max = result;
            }
            
            if (!f(image, min))
                return min;
            return max;
        }
    }

    template<typename Functor>
    int binsearch_decreasing(const std::vector<std::string> & image, int min, int max, Functor f) {
            if (!f(image, max))
                return max;
            
        if (min == max)
            return min;
        else {
            int result;
            while (max-min > 1) {
                result = (min+max)/2;
                auto fmin = f(image, min);
                auto fmax = f(image, max);
                auto fmid = f(image, result);
                if (fmin == fmid)
                    min = result;
                else if (fmax == fmid)
                    max = result;
            }
            
            if (!f(image, max))
                return max;
            return min;
        }
    }
    
    // bool allzerosRow(const std::vector<std::string> & image, int row) {
    //     for (int j = 0; j < image[row].length(); j++)
    //         if (image[row][j] != '0')
    //             return false;
    //     return true;
    // }

    // bool allzerosCol(const std::vector<std::string> & image, int col) {
    //     for (int i = 0; i < image.size(); i++)
    //         if (image[i][col] != '0')
    //             return false;
    //     return true;
    // }
};

int main() {
    std::vector<std::string> image {
            "0010",
            "0110",
            // "0010",
            // "1110",
            // "0010"
            "0100"
    };

    int x = 0, y = 2;

    solution soln;
    int minA = soln.minArea(image, x, y);

    std::cout << "The area of the minimum enclosing rectangle is:" << std::endl;
    std::cout << minA << std::endl;

    return 0;
}
