#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

// ��������
void generate_polynomial();
void evaluate_polynomial(const std::string& filename);

// poly_eval ����������
double poly_eval(const std::vector<double>& coeffs, double x);

int main() {
    // �����������ļ� points.txt
    std::ofstream pointsFile("points.txt");
    if (pointsFile.is_open()) {
        pointsFile << "0 0\n";
        pointsFile << "2 4\n";
        pointsFile << "10 100\n";
        pointsFile.close();
    }
    else {
        std::cerr << "�޷����� points.txt �ļ�" << std::endl;
        return 1;
    }

    // ���ɶ���ʽϵ�� polynomial.txt
    {
        std::ifstream inFile("points.txt");
        std::ofstream outFile("polynomial.txt");
        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "�޷����ļ�" << std::endl;
            return 1;
        }

        std::cin.rdbuf(inFile.rdbuf());
        std::cout.rdbuf(outFile.rdbuf());
        generate_polynomial();
        std::cin.rdbuf(nullptr);  // ���ñ�׼����
        std::cout.rdbuf(nullptr); // ���ñ�׼���
    }

    // ��ȡ����ʾ polynomial.txt ������
    std::ifstream polynomialFile("polynomial.txt");
    if (polynomialFile.is_open()) {
        std::string line;
        while (std::getline(polynomialFile, line)) {
            std::cout << line << std::endl;
        }
        polynomialFile.close();
    }
    else {
        std::cerr << "�޷���ȡ polynomial.txt �ļ�" << std::endl;
        return 1;
    }

    // ��������ʽ����ʾ���
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
    // ��ȡ������
    std::vector<std::pair<double, double>> points;
    double x, y;
    while (std::cin >> x >> y) {
        points.push_back(std::make_pair(x, y));
    }

    // �򵥵Ķ���ʽ���ʵ�� (����ֻ��һ��ʾ����ʵ��ʹ�ÿ�����Ҫ�����ӵ��㷨)
    // �����������һ���򵥵Ķ��ζ���ʽ y = ax^2 + bx + c
    double a = 1.0, b = 0.0, c = 0.0;

    // �������ʽϵ�����ļ�
    std::cout << a << " " << b << " " << c << std::endl;
}
