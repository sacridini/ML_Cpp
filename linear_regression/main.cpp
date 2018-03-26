#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>
#include <cmath>
#include <limits>

using namespace std;

class LinearRegression {
public:
	LinearRegression() {}
	~LinearRegression() {}
	LinearRegression(vector<double>& m_x_vals, vector<double>& m_y_vals) {
		this->m_x_vals = m_x_vals;
		this->m_y_vals = m_y_vals;
		this->m_num_elems = m_y_vals.size();
		m_old_err = std::numeric_limits<double>::max();
	}

	void train(int num_iters, double a_init, double b_init) {
		int iter = 0;
		m_a = a_init;
		m_b = b_init;

		// Gradient Descent
		while (!isConverged() && iter < num_iters) {
			// update the gradient
			double step = 2 / static_cast<double>(iter + 2);
			double a_grad = 0;
			double b_grad = 0;

			// compute the gradient of error wrt to a
			for (int i = 0; i < m_num_elems; i++) {
				a_grad += m_x_vals[i] * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
			}
			a_grad = (2 * a_grad) / m_num_elems;

			// computer the gradient of error wrt to b
			for (int i = 0; i < m_num_elems; i++) {
				b_grad += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
			}
			b_grad = (2 * b_grad) / m_num_elems;

			// take a step
			m_a = m_a - (step * a_grad);
			m_b = m_b - (step * b_grad);

			cout << "a:\t" << m_a << ", b:\t" << m_b << "\r\n";
			cout << "a_grad:\t" << a_grad << ", b_grad:\t" << b_grad << "\r\n";
			iter++;
		}
	}

	double regress(double x) {
		double res = m_a * x + m_b;
		return res;
	}

private:

	bool isConverged() {
		double error = 0;
		double thresh = 0.001;

		for (int i = 0; i < m_num_elems; i++) {
			error += pow(((m_a * m_x_vals[i] + m_b) - m_y_vals[i]), 2);
		}
		error /= m_num_elems;
		cout << "Error" << error << "\r\n";
		bool res = (abs(error) > m_old_err - thresh && abs(error) < m_old_err + thresh) ? true : false;
		m_old_err = abs(error);
		return res;
	}

	vector<double> m_x_vals;
	vector<double> m_y_vals;
	double m_num_elems;
	double m_old_err;
	double m_a;
	double m_b;
};

int main(int argc, char **argv) {

	vector<double> y({ 2.8,2.9,7.6,9,8.6 });
	vector<double> x({ 1,2,3,4,5 });

	LinearRegression lr(x, y);
	lr.train(1000, 3, -10);
	cout << lr.regress(3) << endl;

	cin.get();
}