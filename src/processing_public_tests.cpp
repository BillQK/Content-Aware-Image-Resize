#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix_test_helpers.h"
#include "Image_test_helpers.h"

using namespace std;

void test_all(string prefix, int sizes[], int num_sizes);
void test_rotate(const Image& img, string prefix);
void test_energy(const Matrix& energy_mat, string prefix);
void test_cost(const Matrix& cost_mat, string prefix);
void test_find_seam(const vector<int>& seam, int n, string prefix);
void test_remove_seam(const Image& img, const vector<int>& seam, string prefix);
void test_seam_carve(const Image& img, string prefix,
                            int new_width, int new_height);
static Matrix load_matrix(string filename);
static void write_matrix(const Matrix& mat, string filename);
static Image load_image(string filename);
static void write_image(const Image& img, string filename);
static vector<int> load_seam(string filename);
static void write_seam(const vector<int>& seam, int len, string filename);

const string OUT_PPM_EXT = ".out.ppm";
const string OUT_TXT_EXT = ".out.txt";

int main(int argc, char *argv[]){
  if (argc > 2 ||
      (argc == 2&&
       strcmp(argv[1], "dog") &&
       strcmp(argv[1], "crabster") &&
       strcmp(argv[1], "horses"))) {
    cout << "Usage: " << argv[0] << " [dog|crabster|horses]" << endl;
    return 1;
  }

  string which_test = argc == 2 ? argv[1] : "all";

  if (which_test == "all" || which_test == "dog") {
    int dog_sizes[] = {4, 5};
    test_all("dog", dog_sizes, 1);
  }
  if (which_test == "all" || which_test == "crabster") {
    int crabster_sizes[] = {50, 45, 70, 35};
    test_all("crabster", crabster_sizes, 2);
  }
  if (which_test == "all" || which_test == "horses") {
    int horses_sizes[] = {300, 382, 400, 250};
    test_all("horses", horses_sizes, 2);
  }
}

void test_all(string prefix, int sizes[], int num_sizes){
  auto img = load_image(prefix + ".ppm");

  // Test rotate
  test_rotate(img, prefix);

  // Test energy
  auto energy = compute_energy_matrix(img);
  test_energy(energy, prefix);

  // Test cost
  auto cost = compute_vertical_cost_matrix(img);
  test_cost(cost, prefix);

  // Test find seam
  auto seam = find_minimal_vertical_seam(cost);
  test_find_seam(seam, cost.get_height(), prefix);

  // Test remove seam
  test_remove_seam(img, seam, prefix);

  // Test full seam carving algorithm on various sizes
  for(int i = 0; i < num_sizes; ++i){
    test_seam_carve(img, prefix, sizes[2*i], sizes[2*i + 1]);
  }

  cout << prefix << " tests PASS" << endl << endl;
}

void test_rotate(const Image& img, string prefix) {
  // Test left rotation
  cout << "Testing " << prefix << " rotate left..." << flush;
  auto rotated_img = rotate_left(img);
  write_image(rotated_img, prefix + "_left" + OUT_PPM_EXT);

  auto rotated_img_correct = load_image(prefix + "_left.correct.ppm");
  assert(Image_equal(rotated_img, rotated_img_correct));
  cout << "PASS" << endl;

  // Test right rotation
  cout << "Testing " << prefix << " rotate right...";
  rotated_img = rotate_right(img);
  write_image(rotated_img, prefix + "_right" + OUT_PPM_EXT);

  rotated_img_correct = load_image(prefix + "_right.correct.ppm");
  assert(Image_equal(rotated_img, rotated_img_correct));
  cout << "PASS" << endl;
}

void test_energy(const Matrix& energy_mat, string prefix){
  cout << "Testing " << prefix << " energy..." << flush;

  write_matrix(energy_mat, prefix + "_energy" + OUT_TXT_EXT);

  auto energy_mat_correct = load_matrix(prefix + "_energy_correct.txt");

  assert(Matrix_equal(energy_mat, energy_mat_correct));
  cout << "PASS" << endl;
}


void test_cost(const Matrix& cost_mat, string prefix){
  cout << "Testing " << prefix << " cost..." << flush;

  write_matrix(cost_mat, prefix + "_cost" + OUT_TXT_EXT);

  auto cost_mat_correct = load_matrix(prefix + "_cost_correct.txt");

  assert(Matrix_equal(cost_mat, cost_mat_correct));
  cout << "PASS" << endl;
}

void test_find_seam(const vector<int>& seam, int n, string prefix) {
  cout << "Testing " << prefix << " find seam..." << flush;
  write_seam(seam, n, prefix + "_seam" + OUT_TXT_EXT);

  auto seam_correct = load_seam(prefix + "_seam_correct.txt");

  assert(seam == seam_correct);
  cout << "PASS" << endl;
}

void test_remove_seam(const Image& img, const vector<int>& seam, string prefix) {
  cout << "Testing " << prefix << " remove seam..." << flush;

  auto removed_img = remove_vertical_seam(img, seam);
  write_image(removed_img, prefix + "_removed" + OUT_PPM_EXT);

  auto removed_img_correct = load_image(prefix + "_removed.correct.ppm");

  assert(Image_equal(removed_img, removed_img_correct));
  cout << "PASS" << endl;
}

void test_seam_carve(const Image& img, string prefix,
                            int new_width, int new_height){
  cout << "Testing " << prefix << " seam carve ";
  cout << new_width << "x" << new_height << "..." << flush;
  auto carved_img = seam_carve(img, new_width, new_height);
  write_image(carved_img,
    prefix + "_" + to_string(new_width) +
    "x" + to_string(new_height) + OUT_PPM_EXT);

  auto carved_img_correct = load_image(
    prefix + "_" + to_string(new_width)
    + "x" + to_string(new_height) + ".correct.ppm");

  assert(Image_equal(carved_img, carved_img_correct));
  cout << "PASS" << endl;
}

static Matrix load_matrix(string filename){
  ifstream fin(filename);

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  int width, height;
  fin >> width >> height;
  auto mat = Matrix(width, height);

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      fin >> mat.at(r, c);
    }
  }
  return mat;
}

static void write_matrix(const Matrix& mat, string filename){
  ofstream fout(filename);
  mat.print(fout);
}

static Image load_image(string filename){
  ifstream fin(filename);

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  return Image::read_ppm(fin);
}

static void write_image(const Image& img, string filename){
  ofstream fout(filename);
  img.print(fout);
}

static vector<int> load_seam(string filename) {
  ifstream fin(filename);
  vector<int> seam;

  if (!fin.is_open()){
    cout << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  for(int i = 0, column; fin >> column; ++i){
    seam.push_back(column);
  }

  return seam;
}

static void write_seam(const vector<int>& seam, int len, string filename) {
  ofstream fout(filename);
  for(int i = 0; i < len; ++i){
    fout << seam[i] << endl;
  }
}
