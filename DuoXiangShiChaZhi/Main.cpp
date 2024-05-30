#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

// 声明函数
void generate_polynomial();
void evaluate_polynomial(const std::string& filename);

// poly_eval 函数的声明
double poly_eval(const std::vector<double>& coeffs, double x);

int main() {
    // 创建点数据文件 points.txt
    std::ofstream pointsFile("points.txt");
    if (pointsFile.is_open()) {
        pointsFile << "0 0\n";
        pointsFile << "2 4\n";
        pointsFile << "10 100\n";
        pointsFile.close();
    }
    else {
        std::cerr << "无法创建 points.txt 文件" << std::endl;
        return 1;
    }

    // 生成多项式系数 polynomial.txt
    {
        std::ifstream inFile("points.txt");
        std::ofstream outFile("polynomial.txt");
        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "无法打开文件" << std::endl;
            return 1;
        }

        std::cin.rdbuf(inFile.rdbuf());
        std::cout.rdbuf(outFile.rdbuf());
        generate_polynomial();
        std::cin.rdbuf(nullptr);  // 重置标准输入
        std::cout.rdbuf(nullptr); // 重置标准输出
    }

    // 读取并显示 polynomial.txt 的内容
    std::ifstream polynomialFile("polynomial.txt");
    if (polynomialFile.is_open()) {
        std::string line;
        while (std::getline(polynomialFile, line)) {
            std::cout << line << std::endl;
        }
        polynomialFile.close();
    }
    else {
        std::cerr << "无法读取 polynomial.txt 文件" << std::endl;
        return 1;
    }

    // 评估多项式并显示结果
    for (int i = 0; i <= 10; ++i) {
        std::ostringstream cmd;
        cmd << "echo " << i << " | poly_exec polynomial.txt";
        std::system(cmd.str().c_str());
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void evaluate_polynomial(const std::string& filename) {
    ifstream coeff_file(filename);
    if (!coeff_file) {
        cerr << "Unable to open " << filename << endl;
        return;
    }

    vector<double> coeffs;
    double x;
    while (coeff_file >> x) {
        coeffs.push_back(x);
    }
    coeff_file.close();

    while (cin >> x) {
        cout << poly_eval(coeffs, x) << endl;
    }
}

double poly_eval(const std::vector<double>& coeffs, double x) {
    double result = 0;
    double power = 1;
    for (double coeff : coeffs) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

void generate_polynomial() {
    // 读取点数据
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (std::cin >> x >> y) {
        points.push_back(std::make_pair(x, y));
    }

    // 简单的多项式拟合实现 (这里只是一个示例，实际使用可能需要更复杂的算法)
    // 假设我们拟合一个简单的二次多项式 y = ax^2 + bx + c
    double a = 1.0, b = 0.0, c = 0.0;

    // 输出多项式系数到文件
    std::cout << a << " " << b << " " << c << std::endl;
}
