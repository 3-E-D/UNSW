#include <stdio.h>
#include <stdlib.h> 
#include "guess.h"
#include "image.h"
#include "heuristics.h"

int main(int argc, char *argv[]) {

    //read the digit, get it's bounding box and get its balance
    int height, width, start_row, start_column, box_width, box_height, holes;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    //reads the pbm into the array pixels
    int pixels[height][width];

    //get all the attributes of the digit inside this function
    if (read_pbm(argv[1], height, width, pixels)) {
        
        //gets the bounding box around the pixel
        get_bounding_box(height, width, pixels, &start_row, &start_column,
                &box_height, &box_width);
        //puts the bounded pixel in box_pixels 
        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height,
                box_width, box_pixels);

        //find the similarity between the bounded digit and templates
        int similarity_scores[DIGITS] = {0};
        int reverse_scores[DIGITS] = {0};
        get_scores(box_height, box_width, box_pixels, similarity_scores, reverse_scores);
    
        //implements logic to get the best digit possible
        int guess = check_guess(similarity_scores, reverse_scores,
                box_height, box_width, box_pixels);

        //prints the guess
        printf("%d\n", guess);
    }
    return 0;
}
