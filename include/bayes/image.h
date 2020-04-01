// Copyright (c) 2020 [Sabar Nimmagadda]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::istream;
using std::ifstream;
using std::ostream;

namespace bayes {

    constexpr size_t kImageSize = 28;

/**
 * Class that is associated with creating objects,
 * and functions relevant to images.
 */
    class Image {


    public:
        int image_grid[kImageSize][kImageSize];

        /**
         * This overloads the input operator to read an Image object.
         * @param input the input stream that reads the image.
         * @param image the Image object that contains the image.
         * @return the input stream where the image is being read.
         */
        friend istream &operator>>(istream &input, Image image);

        /**
         * setter for image_grid;
         * @param grid the grid the 2-D array must be set to.
         */
        void setImageAsGrid(int grid[kImageSize][kImageSize]);


    };
}// namespace bayes

#endif  // BAYES_IMAGE_H_
