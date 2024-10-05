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
protected:

    int id;
    std::string type;
    std::vector<int> info;
    std::vector<std::vector <char>>& grid;

public:
    virtual ~Figure() = default;

    Figure(int id, std::string type, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : id(id), type(std::move(type)), info(info), grid(grid) {}

    virtual void draw() {
        std::cout << "Drawing non-existing shape!" << std::endl;
        std::cout << "  /\\_/\\\n";
        std::cout << " ( o.o )\n";
        std::cout << "  > ^ <\n";
    }
};

class Triangle : public Figure {
public:
    ~Triangle() override = default;
    Triangle(int id, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : Figure(id, "triangle", info, grid) {}
    void draw() override {
        int x = info[0], y = info[1], height = info[2];
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
};

class Rhombus : public Figure {
public:
    ~Rhombus() override = default;
    Rhombus(int id, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : Figure(id, "rhombus", info, grid) {}
    void draw() override {
        int x = info[0], y = info[1], height = info[2];
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
};

class Circle : public Figure {
public:
    ~Circle() override = default;
    Circle(int id, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : Figure(id, "circle", info, grid) {}
    void draw() override {
        int x = info[0], y = info[1], radius = info[2];
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
};

class Rectangle : public Figure {
public:
    ~Rectangle() override = default;
    Rectangle(int id, const std::vector<int> &info, std::vector<std::vector <char>>& grid)
        : Figure(id, "rectangle", info, grid) {}
    void draw() override {
        int x = info[0], y = info[1], width = info[2], height = info[3];
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
};
int main() {
    Board board;
    std::vector<std::unique_ptr<Figure>> figures;
    std::unique_ptr<Triangle> tr1 = std::make_unique<Triangle>(1, std::vector<int>{10, 1, 5}, board.grid);
    figures.push_back(std::move(tr1));
    std::unique_ptr<Triangle> tr2 = std::make_unique<Triangle>(2, std::vector<int>{30, 12, 10}, board.grid);
    figures.push_back(std::move(tr2));

    std::unique_ptr<Rhombus> r1 = std::make_unique<Rhombus>(3, std::vector<int>{50, 10, 10}, board.grid);
    figures.push_back(std::move(r1));

    std::unique_ptr<Circle> c1 = std::make_unique<Circle>(4, std::vector<int>{70, 5, 5}, board.grid);
    figures.push_back(std::move(c1));
    std::unique_ptr<Rhombus> r2 = std::make_unique<Rhombus>(5, std::vector<int>{90, 15, 2}, board.grid);
    figures.push_back(std::move(r2));

    std::unique_ptr<Rectangle> rec1 = std::make_unique<Rectangle>(6, std::vector<int>{90, 20, 10, 55}, board.grid);
    figures.push_back(std::move(rec1));



    for (const auto& figure : figures) {
        figure->draw();
    }

    board.print();

    return 0;
}
