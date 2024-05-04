#pragma once
#include<gl/glut.h>
#include<math.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
using namespace std;
#define M_PI 3.141592653589
#define EYE_Z 4.73
#define DNEAR 0
#define DEFAULT_BUNNY_SIZE 0.1
//#define DFAR 4
#define TAIL 0.2
#define TAIL_THICKNESS 0.25//25% of the original thickness... 0.0075
#define THICKNESS 0.03
#define DEFAULT_NUMBER_OF_BUNNIES 10
#define DEFAULT_BUNNY_COLOR SOLID_RED
#define DEFAULT_SNAKE_COLOR SOLID
#define DEFAULT_SPEED 0.008
#define DEFAULT_THICKNESS 0.03
enum ColorPattern {
    CHECKERED,
    V_STRIPPED,
    H_STRIPPED,
    SOLID,
    SOLID_WHITE,
    SOLID_BLACK,
    SOLID_RED,
    SOLID_GOLD,
    SOLID_BROWN,
    NO_COLOR
};
extern ColorPattern bunnyColor;
extern int bunnyCount;// = DEFAULT_NUMBER_OF_BUNNIES;
extern double bunnySize;// = DEFAULT_BUNNY_SIZE;
extern ColorPattern snakeColor;// = DEFAULT_SNAKE_COLOR;
extern double snakeSpeed;// = DEFAULT_SPEED;
extern double snakeSize;// = DEFAULT_THICKNESS;
#define GROW_WHEN_EAT 25
#define END 0.01
#define INITIAL_LENGTH 0.5
#define MAX_SEGMENTS 1000
#define SPEED 0.008
#define BLINKING_PERIOD 100
#define TONGUE_PERIOD 100
#define FIELD_DEPTH 3
#define INITIAL_Z 2
#define LOW_RES 1
using namespace std;
using std::vector;


enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};
typedef struct {
    double x, y, z;
}Point;

extern Point snakeBody[MAX_SEGMENTS];
extern int bodySegments, lats, longs;
extern GLfloat randomColors[300000];
extern std::vector<GLfloat> vertices;
extern std::vector<GLuint> faces;
extern std::vector<GLfloat> normals;
extern int firstIndex;
extern Point bunnyLocation[50];
Point diff(Point p2, Point p1);
void torus(int lats, int longs, double fromTheta, double toTheta, double r1, double r2, double R, ColorPattern color, double r0, double tail, double tailRange, double headRange, double rx);
void cone(int lats, int longs, double r1, double r2, double L, ColorPattern color);
void head(double rx, double r, int lats, int longs, ColorPattern color, bool blink);
void eyeBall(double rx, double ry, double rz, int lats, int longs, ColorPattern color, ColorPattern frontColor, bool orientation);
double length(double r);
double euclideanDistanceSquare(Point p1, Point p2);
Point randomBunnyLocation(int x, int y, int z, int max, int except);
void load_bunny_data(const char file[], std::vector<GLfloat>& vertices, std::vector<GLuint>& faces, std::vector<GLfloat>& normals);
void bunny(double size, Point loc);
void conicSnake(double r, double tailR, ColorPattern color, Point snakeUp, bool blink,bool Tongue,double Tonguelen, bool defaultCam);
bool snakeCrossesItself();
int eatsBunny();