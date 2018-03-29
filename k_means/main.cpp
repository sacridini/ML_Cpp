#include <iostream>
#include <vector>
#include <valarray>
#include <utility>
#include <cmath>
#include <algorithm> 

using namespace std;

class KMeans {
public:
	KMeans() {};
	~KMeans() {};
	KMeans(int _k, vector<pair<double, double>>& _data) : k(_k), means(_k), data(_k) {
		this->data[0] = _data;
	}

	void cluster_data(valarray<pair<double, double>>& init_means, int num_iters) {
		means = init_means;
		this->assing_labels();

		int i = 0;
		while (i < num_iters && !this->compute_means()) {
			cout << "Running iteration: " << i << "\r\n";
			this->assing_labels();
			i++;
		}

	}

	void print_cluster() const {
		for (int i = 0; i < k; i++) {
			for (const auto& it : data[i]) {
				cout << " [" << get<0>(it) << " , " << get<1>(it) << "] ";
			}
			cout << "\r\n";
		}
	}

private:

	bool compute_means() {
		// return true if means are  the same as previous iteration
		bool res = true;
		for (int i = 0; i < k; i++) {
			pair<double, double> mean(0,0);
			int num_features_of_k = data[k].size();
			for (auto const& it : data[k]) {
				get<0>(mean) += get<0>(it);
				get<1>(mean) += get<1>(it);
			}
			get<0>(mean) /= num_features_of_k;
			get<1>(mean) /= num_features_of_k;
			res = (means[k] == mean && res == true) ? true : false;
			means[k] = mean;
			cout << "Cluster centroid << " << k << " :\tx " << get<0>(mean) << " ,y " << get<1>(mean) << "\t";
		}
		cout << "\r\n";
		return res;
	}

	void assing_labels() {
		valarray<vector<pair<double, double>>> new_data(k);
		for (auto const& clust : data) {
			for (auto const& feature : clust) {
				int closest_mean = this->compute_closest_centroid(feature);
				new_data[closest_mean].push_back(feature);
			}
		}
		data = new_data;
	}

	int compute_closest_centroid(const pair<double, double>& point) {
		valarray<double> distances(k);
		for (int i = 0; i < k; i++) {
			double del_x = get<0>(point) - get<0>(means[i]);
			double del_y = get<1>(point) - get<1>(means[i]);
			double dist = sqrt(pow(del_x, 2) + pow(del_y, 2));
			// double dist = sqrt((del_x * del_x) + (del_y * del_y));
			distances[k] = dist;
		}
		auto closest_mean = distance(begin(distances),min_element(begin(distances),end(distances)));
		return closest_mean;
	}

	int k; // numero de classes
	int features; // numero total de pontos a serem processados 
	valarray<pair<double, double>> means; // container para armazenar as medias
	valarray<vector<pair<double, double>>> data; // array of vectors containing the data
};

int main(int argc, char **argv) {
	vector<pair<double, double>> teste =
	{{1.1, 1}, {1.4, 2}, {3.8, 7}, {5.0, 8}, {4.3, 6},
	{8, 5.0}, {6, 8.5}, {3, 2.0}, {9, 6}, {9.1, 4}};

	KMeans km(2, teste);
	valarray<pair<double, double>> init_means = { {1,1}, {3,4} };
	km.cluster_data(init_means, 10);
	km.print_cluster();

	cin.get();
}