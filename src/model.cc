// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/model.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <bayes/image.h>
using std::ifstream;
namespace bayes {

    void Model::GetLabelsFromFile(const string& filepath) {
        if (filepath.empty()) {
            return;
        }
        std::ifstream read_file(filepath);
        if(!read_file) {
            cout << "Invalid file";
            return;
        }
        int num_class;
        while (read_file >> num_class) {
            labels.push_back(num_class);
        }
    }

    void Model::GetImagesFromFile(const string& filepath) {
        if (filepath.empty()) {
            return;
        }
        std::ifstream read_file(filepath);
        if(!read_file) {
            cout << "Invalid file";
            return;
        }
        string line;
        while (std::getline(read_file,line)){
            Image image;
            //This is the overloaded operator that generates the grid.
            read_file >> image;
            image_objects.push_back(image);
        }
    }

    void Model::initialize(const string& label_file, const string& image_file, double smoothing) {
        smoothing_factor = smoothing;
        GetImagesFromFile(image_file);
        GetLabelsFromFile(label_file);
    }

    int Model::MostCommonShadeInFeature(int row, int col, Image image) {
        int whiteCount = 0;
        int shadedCount = 1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (image.image_grid[i][j] == 0) {
                    whiteCount++;
                } else {
                    shadedCount++;
                }
            }
        }
        if (whiteCount > shadedCount) {
            return 0;
        }
        return 1;
    }

    double Model::ComputeProbOfFeature(int row, int col, int num_class, int shade) {
        int count_of_nums_of_class = 0;
        int count_of_shade_at_position = 0;
        for (long i = 0; i < labels.size(); i++) {
            if (labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }

            Image image = image_objects.at(i);
            if (MostCommonShadeInFeature(row, col, image) == shade) {
                count_of_shade_at_position++;
            }
        }
        return (smoothing_factor + count_of_shade_at_position)
               / (2*smoothing_factor + count_of_nums_of_class);
    }


    double Model::ComputeProbabilityOfClassInLabels(int num_class) {
        int count_of_nums_of_class = 0;
        for (long i = 0; i < labels.size(); i++) {
            if (labels.at(i) == num_class) {
                count_of_nums_of_class++;
            }
        }
        return (double) count_of_nums_of_class / labels.size();
    }

    void Model::setProbabilityOfPriorsVector() {

        for (int i = 0; i < kNumClasses; i++) {
            double probability_of_class = ComputeProbabilityOfClassInLabels(i);
            probabilities_of_priors.push_back(probability_of_class);
        }

    }

    void Model::setFeatureProbabilityArray() {
        for (int i = 0; i < kImageSize; i++) {
            for (int j = 0; j < kImageSize; j++) {
                for (int k = 0; k < kNumClasses; k++) {
                    for (int l = 0; l < kNumShades; l++) {
                        probs_[i][j][k][l] = ComputeProbOfFeature(i, j ,k ,l);
                    }
                }
            }
        }
    }

    void Model::train(const string& image_file, const string& label_file, double smoothing) {
        smoothing_factor = smoothing;
        GetImagesFromFile(image_file);
        GetLabelsFromFile(label_file);
        setFeatureProbabilityArray();
        setProbabilityOfPriorsVector();
    }




}  // namespace bayes

