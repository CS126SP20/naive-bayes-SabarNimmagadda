// Copyright 2020 Sabar Nimmagadda. All rights reserved.

#include "bayes/image.h"
#include <fstream>


namespace bayes {
    void Image::setImageAsGrid(int grid[kImageSize][kImageSize]) {
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                image_grid[i][j] = grid[i][j];
            }
        }
    }


    //This overloads the input operator to generate a 2-D grid of
    //1's and 0's depending on the shade of the specific image at that specific pixel.
    istream &operator>>(istream &input, Image image) {
        string line;
        int grid[kImageSize][kImageSize];
        for (int lineCount = 0; lineCount < kImageSize; lineCount++) {
            std::getline(input, line);
            if (line.empty()) {
                continue;
            }
            for (size_t columnNumber = 0; columnNumber < kImageSize; columnNumber++) {
                if (line.at(columnNumber) == '+' || line.at(columnNumber) == '#') {
                    grid[lineCount][columnNumber] = 1;
                } else {
                    grid[lineCount][columnNumber] = 0;
                }
            }
        }
        image.setImageAsGrid(grid);
        return input;
    }

}  // namespace bayes

