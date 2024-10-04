#include <iostream>
#include <vector>

const int BOARD_WIDTH = 100;
const int BOARD_HEIGHT = 40;

struct Board {
    std::vector<std::vector<char>> grid;
    Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}
    void print() {
        for (auto& row : grid) {
            for (char c : row) {
                std::cout << c;
            }
            std::cout << "\n";
        }
    }

};

/*
Figure

unique id
type
parameters (info)
draw method
board (grid)
 */

class Figure {
    int id;
    std::string type;
    std::vector<int> info;
    std::vector<std::vector <char>>& grid;

public:
    Figure(int id, std::string type, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : id(id), type(std::move(type)), info(info), grid(grid) {}

    void drawTriangle(int x, int y, int height) {
        if (height <= 0) return;
        for (int i = 0; i < height; ++i) {
            int leftMost = x - i;
            int rightMost = x + i;
            int posY = y + i;

            if (posY < BOARD_HEIGHT) {
                if (leftMost >= 0 && leftMost < BOARD_WIDTH) {
                    grid[posY][leftMost] = '*';
                }
                if (rightMost >= 0 && rightMost < BOARD_WIDTH && leftMost != rightMost) {
                    grid[posY][rightMost] = '*';
                }
            }
        }

        for (int j = 0; j < 2 * height - 1; ++j) {
            int baseX = x - height + 1 + j;
            int baseY = y + height - 1;
            if (baseX >= 0 && baseX < BOARD_WIDTH && baseY < BOARD_HEIGHT)
                grid[baseY][baseX] = '*';
        }
    }

    void drawRhombus(int x, int y, int height) {
        if (height <= 0) return;
        if (height % 2 != 0) {
            std::cout << "Please, enter valid height for rhombus. Height should be even number." << std::endl;
            return;
        }
        for (int i = 0; i <= height / 2; ++i) {
            int leftMost = x - i;
            int rightMost = x + i;
            int posY = y + i;

            if (posY < BOARD_HEIGHT) {
                if (leftMost >= 0 && leftMost < BOARD_WIDTH)
                    grid[posY][leftMost] = '*';
                if (rightMost >= 0 && rightMost < BOARD_WIDTH && leftMost != rightMost) {
                    grid[posY][rightMost] = '*';
                }
            }
        }

        for (int i = height / 2 - 1; i >= 0; --i) {
            int leftMost = x - i;
            int rightMost = x + i;
            int posY = y + height - i;

            if (posY < BOARD_HEIGHT) {
                if (leftMost >= 0 && leftMost < BOARD_WIDTH)
                    grid[posY][leftMost] = '*';
                if (rightMost >= 0 && rightMost < BOARD_WIDTH && leftMost != rightMost)
                    grid[posY][rightMost] = '*';
            }
        }
    }

    void drawCircle(int x, int y, int radius) {
        if (radius <= 0) return;
        for (int i = -radius; i <= radius; ++i) {
            int posY = y + i + radius;

            int offset = int(sqrt(radius * radius - i * i));
            int posX1 = x + offset;
            int posX2 = x - offset;

            if (posY >= 0 && posY < BOARD_HEIGHT) {
                if (posX1 >= 0 && posX1 < BOARD_WIDTH) {
                    grid[posY][posX1] = '*';
                }
                if (posX2 >= 0 && posX2 < BOARD_WIDTH) {
                    grid[posY][posX2] = '*';
                }
            }
        }
    }

    void drawRectangle(int x, int y, int width, int height) {
        if (width <= 0 || height <= 0) return;

        for (int i = 0; i < width; ++i) {
            int posX = x + i;
            if (posX >= 0 && posX < BOARD_WIDTH) {
                if (y >= 0 && y < BOARD_HEIGHT) {
                    grid[y][posX] = '*';
                }
                if (y + height - 1 >= 0 && y + height - 1 < BOARD_HEIGHT) {
                    grid[y + height - 1][posX] = '*';
                }
            }
        }

        for (int i = 0; i < height; ++i) {
            int posY = y + i;
            if (posY >= 0 && posY < BOARD_HEIGHT) {
                if (x >= 0 && x < BOARD_WIDTH) {
                    grid[posY][x] = '*';
                }
                if (x + width - 1 >= 0 && x + width - 1 < BOARD_WIDTH) {
                    grid[posY][x + width - 1] = '*';
                }
            }
        }
    }

    void draw() {
        if (type == "triangle") drawTriangle(info[0], info[1], info[2]);
        else if (type == "rhombus") drawRhombus(info[0], info[1], info[2]);
        else if (type == "circle") drawCircle(info[0], info[1], info[2]);
        else if (type == "rectangle") drawRectangle(info[0], info[1], info[2], info[3]);
        else std::cout << "Unknown figure type with ID " << id << std::endl;
    }
};


int main() {
    Board board;
    std::unique_ptr<Figure> figure1 = std::make_unique<Figure>(1, "triangle", std::vector<int>{15, 15, 10}, board.grid);
    figure1->draw();
    std::unique_ptr<Figure> figure2 = std::make_unique<Figure>(2, "rhombus", std::vector<int>{25, 25, 10}, board.grid);
    figure2->draw();
    std::unique_ptr<Figure> figure3 = std::make_unique<Figure>(3, "circle", std::vector<int>{25, 5, 5}, board.grid);
    figure3->draw();
    std::unique_ptr<Figure> figure4 = std::make_unique<Figure>(4, "rectangle", std::vector<int>{10, 10, 10, 20}, board.grid);
    figure4->draw();
    std::unique_ptr<Figure> figure5 = std::make_unique<Figure>(5, "diamond", std::vector<int>{10, 10, 10}, board.grid);
    figure5->draw();
    board.print();

    return 0;
}
