#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"

 void find_neighbors(int height, int width, int pos, int neighbors[], Image<Pixel> image){
  //neighbors[0] = previous row, neighbors[1] = next row, neighbors[2] = previous col, neighbors[3] = next col
  //off sets for prev and next
  int row_offsets[4] = {-1, 1, 0, 0};
  int col_offsets[4] = {0, 0, -1, 1};

  //convert single int position to our row col data
  int row = pos/width;
  int col = pos%width;
  for(int i = 0; i < 4; i++){
    int new_row = row + row_offsets[i];
    int new_col = col + col_offsets[i];

    if(new_row < 0 || new_row >= height || new_col < 0 || new_col >= width || image(new_row, new_col) == BLACK){ //boundary check
      neighbors[i] = -1; //invalid bounds
    }
    else {
      neighbors[i] = new_row*width+new_col; //convert row col data to single int
    }
  }
}

int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // Read input image from file
  Image<Pixel> image;
  //error handling
  try{
    image = readFromFile(input_file);
  }catch(std::runtime_error& my_error){
    std::cerr<<"Error: failed to readFromFile()"<<my_error.what()<<std::endl;
    return EXIT_FAILURE;
  }
  // TODO
  int start_position = 0;
  int height = image.height();
  int width = image.width();
  int red_found = 0;
  for(int row = 0; row < height; row++){
     for(int col = 0; col < width; col++){
      bool is_red = image(row,col) == RED; //check red
      if(is_red){
        start_position = row*width+col; //creates a unique single digit int that can be used to get the original values later
        red_found++; //number of red pixels
      }
      if(image(row, col) != RED && image(row, col) != WHITE && image(row, col) != BLACK){ //check invalid colors
        std::cerr<<"Error: Invalid Color found inside Maze"<<std::endl;
        return EXIT_FAILURE;
      }
    }
  }
  if(red_found == 0 || red_found > 1){ //should be equal to 1
    std::cerr<<"Error: Incorrect number of red pixels found"<<std::endl;
    return EXIT_FAILURE;
  }

  Queue<int, List<int>> my_queue;

  my_queue.enqueue(start_position); //begin queue

  int my_neighbors[4] = {0, 0, 0, 0};
  bool visited[height*width];
  while(!my_queue.isEmpty()){
    //get front, and remove front
    int current_position = my_queue.peekFront();
    my_queue.dequeue(); 
    find_neighbors(height, width, current_position, my_neighbors, image); //neighbors are now all stored in the array
    //iterate through the neighbors
    for(int neighbor : my_neighbors){
      if(neighbor == -1){
        continue; //skip -1 as it means invalid neighbor
      } else{
        if(!visited[neighbor]){
          my_queue.enqueue(neighbor); //add not visited position to queue
        }
        visited[neighbor] = true; //neighbor unless invalid, will be a unique int
      }
    }
    //convert to row column data
    int row = current_position/width;
    int col = current_position%width;
    if(row == 0 || row == height-1 || col == width-1 || col == 0){
      std::cout<<"Solution Found"<<std::endl;
      image(row, col) = GREEN;
      // Write solution image to file
      try{
        writeToFile(image, output_file);
      }catch(std::runtime_error& my_error){
        std::cerr<<"Error: failed to writeToFile()"<<my_error.what()<<std::endl;
        return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
    }
  }
  // Write solution image to file
  try{
    writeToFile(image, output_file);
  }catch(std::runtime_error& my_error){
    std::cerr<<"Error: failed to writeToFile()"<<my_error.what()<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"No Solution Found"<<std::endl;
  return EXIT_SUCCESS;
}
