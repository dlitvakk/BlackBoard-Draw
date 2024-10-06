#include <iostream>
#include <vector>
#include <fstream>

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

    void clear() {
        for (auto& row : grid) {
            for (char& c : row) {
                c = ' ';
            }
        }
    }

     void save(const std::string& filePath) {
        std::fstream file(filePath);
        if (!file) {
            std::cout << "Error opening file!" << std::endl;
            return;
        }
        for (auto& row : grid) {
            for (char c : row) {
                file << c;
            }
            file << "\n";
        }
        file.close();
        std::cout << "The board is succesfully saved." << std::endl;
    }

    void load(const std::string& filePath) {
        // std::vector<std::vector<char>> tempGrid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' '));
        std::fstream file(filePath);
        std::string line;
        std::vector <char> row;
        if (!file) {
            std::cout << "Error opening file!" << std::endl;
            return;
        }
        grid = {};

        while (std::getline(file, line)) {
            row = {};
            for (char c : line) {
                row.push_back(c);
            }
            grid.push_back(row);
        }
        const int tempGridHeight = grid.size();
        const int tempGridWidth = grid[0].size();
        if (tempGridWidth != BOARD_WIDTH && tempGridHeight != BOARD_HEIGHT) {
            std::cout << "Invalid board size!" << std::endl;
            return;
        }
        file.close();
        std::cout << "The board is succesfully loaded." << std::endl;
        // grid = tempGrid;
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
public:

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

    void getInfo() const{
        std::cout  << id << " " << type;
        for (int i = 0; i < info.size(); ++i) {
            if (i == 0) {
                std::cout << " (" << info[i];
            } else if (i == 1) {
                std::cout << ", " << info[i] << ") ";
            } else {
                std::cout << " " << info[i];
            }
        }
        std::cout << std::endl;
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

class CommandParser {
    Board& board;
    static std::vector<std::unique_ptr<Figure>> figures;
    Board previousState;

public:
    explicit CommandParser(Board &board)
        : board(board) {
    }

    static void printShapes() {
        std::cout << "The list of possible shapes:" << std::endl;
        std::cout << "triangle <x> <y> <height>" << std::endl;
        std::cout << "rhombus <x> <y> <height>" << std::endl;
        std::cout << "circle <x> <y> <radius>" << std::endl;
        std::cout << "rectangle <x> <y> <width> <height>" << std::endl;
    }

     void add(const std::string &type, const std::vector<int>& info) const {
        if (type == "triangle") {
            std::unique_ptr<Triangle> tr = std::make_unique<Triangle>(figures.size() + 1, info, board.grid);
            figures.push_back(std::move(tr));
        } else if (type == "rhombus") {
            std::unique_ptr<Rhombus> r = std::make_unique<Rhombus>(figures.size() + 1, info, board.grid);
            figures.push_back(std::move(r));
        } else if (type == "circle") {
            std::unique_ptr<Circle> c = std::make_unique<Circle>(figures.size() + 1, info, board.grid);
            figures.push_back(std::move(c));
        } else if (type == "rectangle") {
            std::unique_ptr<Rectangle> rec = std::make_unique<Rectangle>(figures.size() + 1, info, board.grid);
            figures.push_back(std::move(rec));
        } else {
            std::cout << "Invalid shape type!" << std::endl;
        }
    }

    static bool validation(const std::string &type, const std::vector<int> &info) {
        if (type != "triangle" && type != "rhombus" && type != "circle" && type != "rectangle") {
            std::cout << "Invalid shape type!" << std::endl;
            return false;
        }
        if (type == "rectangle" && info.size() != 4) {
            std::cout << "Invalid number of parameters for rectangle!" << std::endl;
            return false;
        }
        if (type != "rectangle" && info.size() != 3) {
            std::cout << "Invalid number of parameters for " << type << "!" << std::endl;
            return false;
        }
        if (type == "rhombus" && info[2] % 2 != 0) {
            std::cout << "Please, enter valid height for rhombus. Height should be even number." << std::endl;
            return false;
        }
        if (info[0] < 0 || info[0] >= BOARD_WIDTH || info[1] < 0 || info[1] >= BOARD_HEIGHT) {
            std::cout << "The shape is out of scope. Try again!" << std::endl;
            return false;
        }
        for (const auto& figure: figures) {
            if (figure->type == type && figure->info == info) {
                std::cout << "The shape is already added!" << std::endl;
                return false;
            }
        }
        return true;
    }

     void parseCommand(const std::string& command) {
        if (command == "draw") {
            for (const auto& figure : figures) {
                figure->draw();
            }
            board.print();
        } else if (command == "list") {
            for (const auto& figure : figures) {
                figure->getInfo();
            }
            if (figures.empty()) {
                std::cout << "No shapes added yet!" << std::endl;
            }
        } else if (command == "shapes") {
            printShapes();
        } else if (command == "add") {
            // for undo operation, we can keep the previous state of the board
            previousState = board;

            std::string type;
            std::cin >> type;
            std::vector<int> info;
            if (type == "rectangle") {
                for (int i = 0; i < 4; ++i) {
                    int val;
                    std::cin >> val;
                    info.push_back(val);
                }
            } else {
                for (int i = 0; i < 3; ++i) {
                    int val;
                    std::cin >> val;
                    info.push_back(val);

                }
            }

            if (validation(type, info) == true) {
                add(type, info);
                std::cout << "Shape is succesfully added." << std::endl;
            };
        } else if (command == "clear") {
            figures.clear();
            board.clear();
            std::cout << "The board is clear." << std::endl;
        } else if (command == "undo") {
            board = previousState;
            figures.pop_back();
            if (figures.empty()) {
                board.clear();
            }
            std::cout << "Last added shape is removed." << std::endl;
        } else if (command == "save") {
            std::string filePath;
            std::cin >> filePath;
            board.save(filePath);
        } else if (command == "load") {
            std::string filePath;
            std::cin >> filePath;
            board.load(filePath);
            figures.clear();
        } else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
};
std::vector<std::unique_ptr<Figure>> CommandParser::figures;

int main() {
    Board board;
    // std::vector<std::unique_ptr<Figure>> figures;
    CommandParser parser(board);
    std::cout << "Welcome to the blackboard drawing program!" << std::endl;
    std::cout << "Enter one of the commands:\n <draw> for printing the board,\n <list> for showing all the added shapes,\n <shapes> for all possible figures,\n <add> to adding a figure,\n <clear> to clear board,\n <undo> for removing last added shape,\n <exit>" << std::endl;
    while (true) {
        std::string command;
        std::cin >> command;
        if (command == "exit") break;
        parser.parseCommand(command);
    }
}
